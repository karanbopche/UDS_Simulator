#ifndef SERVICE_2E_CONFIG_H
#define SERVICE_2E_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service2E_DID_Config_Tag {
    uint16_t DID;
    Request_Handler_T callback;
} Service2E_DID_Config_T;

typedef struct Service2E_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t supportedDIDListSize;
    Service2E_DID_Config_T const *const supportedDIDList;
} Service2E_Config_T;

#endif
