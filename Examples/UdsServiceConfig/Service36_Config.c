#include "UdsServices/Service36.h"
#include <string.h>

static uint32_t readMemory(const void *address, void *const data, const uint32_t size);
static uint32_t writeMemory(void *const address, void const *const data, const uint32_t size);
static bool preconditionCheck(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

const Service36_Config_T service36Config = {
    .isFunctionalAddressSupported = false,
    .preconditions = preconditionCheck,
    .memWrite = writeMemory,
    .memRead = readMemory,
};

static uint32_t readMemory(const void *address, void *const data, const uint32_t size) {
    memcpy(data, (void *)address, size);
    return size;
}

static uint32_t writeMemory(void *const address, void const *const data, const uint32_t size) {
    memcpy(address, data, size);
    return size;
}

static bool preconditionCheck(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) { return true; }
