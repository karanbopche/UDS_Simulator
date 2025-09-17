#ifndef SERVICE_31_CONFIG_H
#define SERVICE_31_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef enum Service31_RoutineControl_Tag {
    SERVICE_31_START_ROUTINE = 0x01,
    SERVICE_31_STOP_ROUTINE = 0x02,
    SERVICE_31_REQUEST_ROUTINE_RESULT = 0x03,
} Service31_RoutineControl_T;

typedef struct Service31_RID_Config_Tag {
    uint16_t RID;
    Request_Handler_T routineHandler;
    Request_Handler_T postResponseHandler;
} Service31_RID_Config_T;

typedef struct Service31_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
    uint16_t supportedRIDsListSize;
    Service31_RID_Config_T const *const supportedRIDsList;
} Service31_Config_T;

#endif
