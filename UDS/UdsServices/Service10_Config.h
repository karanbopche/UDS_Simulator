#ifndef SERVICE_10_CONFIG_H
#define SERVICE_10_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef enum Service10_Session_Tag {
    SERVICE_10_DEFAULT_SESSION = 0x01,
    SERVICE_10_PROGRAMMING_SESSION = 0x02,
    SERVICE_10_EXTENDED_SESSION = 0x03,
} Service10_Session_T;

typedef void (*Service10_Session_Callback_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                             uint8_t *currentSession);

typedef struct Service10_Session_Config_Tag {
    uint8_t sessionId;
    uint16_t sessionTimeoutTimer;
    Service10_Session_Callback_T callback;
} Service10_Session_Config_T;

typedef struct Service10_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t p2Timer;
    uint16_t p2MaxTimer;
    uint16_t s3TimerProgrammingSession;
    uint16_t s3TimerExtendedSession;
    Request_Preconditions_T preconditions;
    uint16_t customSessionsListSize;
    Service10_Session_Config_T const *const customSessionsList;
} Service10_Config_T;

#endif
