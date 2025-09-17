#ifndef SERVICE_85_CONFIG_H
#define SERVICE_85_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service85_SubFunction_Config_Tag {
    uint8_t subFunctionId;
    Request_Handler_T subFunctionHandler;
} Service85_SubFunction_Config_T;

typedef struct Service85_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Post_Handler_T enableDtcCallback;
    Request_Post_Handler_T disableDtcCallback;
    uint16_t customSubFunctionsListSize;
    Service85_SubFunction_Config_T const *const customSubFunctionsList;
} Service85_Config_T;

#endif
