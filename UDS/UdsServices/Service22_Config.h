#ifndef SERVICE_22_CONFIG_H
#define SERVICE_22_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service22_DID_Config_Tag {
    uint16_t didId;
    Request_Preconditions_T preconditions;
    void (*didCallback)(UDS_Buffer_T *resultBuffer);
} Service22_DID_Config_T;

typedef struct Service22_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t supportedDIDListSize;
    Service22_DID_Config_T const *const supportedDIDList;
} Service22_Config_T;

#endif
