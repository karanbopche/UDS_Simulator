#include "UdsServices/Service10.h"
#include "UdsServices/Service10_Config.h"
#include "UdsServices/Service27.h"
#include "UdsServices/Utils/Uds_Nrcs.h"

#define REQUEST_LENGTH 2
#define RESPONSE_LENGTH 6

Service10_Config_T const *config;

static void Service10_Session_Timeout(void);
static void Service10_Default_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession);
static void Service10_Programming_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                          uint8_t *currentSession);
static void Service10_Extended_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession);

static uint8_t currentSession = SERVICE_10_DEFAULT_SESSION;
static int32_t sessionTimeoutTimer = 0;

void Service10_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if ((reqBuf->buffer.length != REQUEST_LENGTH)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (config->preconditions && !config->preconditions(reqBuf, respBuf)) {
        return;
    }

    const uint8_t requestedSession = Get_SubFunction(reqBuf->buffer.data[1]);
    for (uint16_t i = 0U; i < config->customSessionsListSize; i++) {
        if (config->customSessionsList[i].sessionId == requestedSession && config->customSessionsList[i].callback) {
            return config->customSessionsList[i].callback(reqBuf, respBuf, &currentSession);
        }
    }

    switch (requestedSession) {
    case SERVICE_10_DEFAULT_SESSION:
        return Service10_Default_Session(reqBuf, respBuf, &currentSession);
    case SERVICE_10_PROGRAMMING_SESSION:
        return Service10_Programming_Session(reqBuf, respBuf, &currentSession);
    case SERVICE_10_EXTENDED_SESSION:
        return Service10_Extended_Session(reqBuf, respBuf, &currentSession);
    default:
        break;
    }

    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    return;
}

uint8_t Service10_Get_Current_Session() { return currentSession; }

void Service10_Session_Timer_Reset() {
    if (currentSession == SERVICE_10_EXTENDED_SESSION) {
        sessionTimeoutTimer = config->s3TimerExtendedSession;
    } else if (currentSession == SERVICE_10_PROGRAMMING_SESSION) {
        sessionTimeoutTimer = config->s3TimerProgrammingSession;
    } else {
        for (uint16_t i = 0U; i < config->customSessionsListSize; i++) {
            if (config->customSessionsList[i].sessionId == currentSession) {
                sessionTimeoutTimer = config->customSessionsList[i].sessionTimeoutTimer;
                break;
            }
        }
    }
}

static void Service10_Default_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession) {
    *currentSession = SERVICE_10_DEFAULT_SESSION;
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Clear(&respBuf->buffer);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2Timer);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2MaxTimer);
    }
}

static void Service10_Programming_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                          uint8_t *currentSession) {
    *currentSession = SERVICE_10_PROGRAMMING_SESSION;
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Clear(&respBuf->buffer);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2Timer);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2MaxTimer);
    }
}

static void Service10_Extended_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession) {
    *currentSession = SERVICE_10_EXTENDED_SESSION;
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Clear(&respBuf->buffer);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2Timer);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2MaxTimer);
    }
}

static void Service10_Session_Timeout(void) {
    currentSession = SERVICE_10_DEFAULT_SESSION;
    sessionTimeoutTimer = 0;
}

void Service10_Periodic_Handler(const uint32_t elapsedMs) {
    if (sessionTimeoutTimer > 0) {
        sessionTimeoutTimer -= elapsedMs;
        if (sessionTimeoutTimer <= 0) {
            sessionTimeoutTimer = 0;
            Service10_Session_Timeout();
        }
    }
}

void Service10_Init(Service10_Config_T const *const newConfig) { config = newConfig; }
