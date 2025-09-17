#ifndef SERVICE_11_CONFIG_H
#define SERVICE_11_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service11_SubFunction_Config_Tag {
    uint8_t subFunctionId;
    Request_Handler_T subFunctionHandler;
    Request_Post_Handler_T postHandler;
} Service11_SubFunction_Config_T;

typedef struct Service11_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t supportedSubFunctionsListSize;
    Service11_SubFunction_Config_T const *const supportedSubFunctionsList;
} Service11_Config_T;

#endif
