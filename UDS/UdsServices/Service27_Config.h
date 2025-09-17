#ifndef SERVICE_27_CONFIG_H
#define SERVICE_27_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef void (*Security_Callback_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                    uint16_t *currentSecuriyLevel);

typedef struct Service27_SubFunctions_Tag {
    uint8_t subFunctionId;
    Security_Callback_T subFunctionCallback;
} Service27_SubFunctions_T;

typedef struct Service27_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t securityLevelListSize;
    Service27_SubFunctions_T const *const securitylevelsList;
} Service27_Config_T;

#endif
