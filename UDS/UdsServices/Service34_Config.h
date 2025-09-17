#ifndef SERVICE_34_CONFIG_H
#define SERVICE_34_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef struct Service34_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
} Service34_Config_T;

#endif
