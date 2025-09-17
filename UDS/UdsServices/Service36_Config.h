#ifndef SERVICE_36_CONFIG_H
#define SERVICE_36_CONFIG_H

#include "UdsServices/Utils/Uds_Services.h"

typedef uint32_t (*Memory_Write_Callback_T)(void *const address, void const *const data, const uint32_t size);
typedef uint32_t (*Memory_Read_Callback_T)(const void *address, void *const data, const uint32_t size);

typedef struct Service36_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
    Memory_Write_Callback_T memWrite;
    Memory_Read_Callback_T memRead;
} Service36_Config_T;

#endif
