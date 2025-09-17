#ifndef SERVICE_37_CONFIG_H
#define SERVICE_37_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service37_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Post_Handler_T tranferCompleteCallback;
} Service37_Config_T;

#endif
