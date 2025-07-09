#include "UdsServices/Service10.h"
#include "UdsServices/Service27.h"

#define REQUEST_LENGTH 2
#define RESPONSE_LENGTH 6

static void Service10_Session_Timeout(void);
static uint8_t Service10_FillResponse(UDS_Buffer_T *respBuf);
static void Service10_Default_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession);
static void Service10_Programming_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                          uint8_t *currentSession);
static void Service10_Extended_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession);

static uint8_t currentSession = SERVICE_10_DEFAULT_SESSION;
static int32_t sessionTimeoutTimer = 0;

static const Service10_Session_Config_T standardSessions[] = {
    {.sessionId = 0x01U, .callback = Service10_Default_Session},
    {.sessionId = 0x02U, .callback = Service10_Programming_Session},
    {.sessionId = 0x03U, .callback = Service10_Extended_Session},
};
static const uint8_t standardSessionsSize = sizeof(standardSessions) / sizeof(standardSessions[0]);

static void Service10_Default_Session(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf, uint8_t *currentSession) {
    Service10_Config_T const *const config = Uds_Gateway_Configurations.services.service10;
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
    Service10_Config_T const *const config = Uds_Gateway_Configurations.services.service10;
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
    Service10_Config_T const *const config = Uds_Gateway_Configurations.services.service10;
    *currentSession = SERVICE_10_EXTENDED_SESSION;
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Clear(&respBuf->buffer);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2Timer);
        Uds_Buffer_Push_Uint16(&respBuf->buffer, config->p2MaxTimer);
    }
}

void Service10_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service10_Config_T const *const config = Uds_Gateway_Configurations.services.service10;
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

    for (uint16_t i = 0U; i < standardSessionsSize; i++) {
        if (standardSessions[i].sessionId == requestedSession) {
            return standardSessions[i].callback(reqBuf, respBuf, &currentSession);
        }
    }

    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    return;
}

uint8_t Service10_Get_Current_Session() { return currentSession; }

void Service10_Session_Timer_Reset() {
    Service10_Config_T const *const config = Uds_Gateway_Configurations.services.service10;
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
