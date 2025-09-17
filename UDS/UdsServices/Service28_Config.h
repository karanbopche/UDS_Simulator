#ifndef SERVICE_28_CONFIG_H
#define SERVICE_28_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service28_SubFunction_Config_Tag {
    uint8_t subFunctionId;
    Request_Handler_T subfunctionHandler;
} Service28_SubFunction_Config_T;

typedef struct Service28_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
    uint16_t supportedSubFunctionListSize;
    Service28_SubFunction_Config_T const *const supportedSubFunctionList;
} Service28_Config_T;

#endif
