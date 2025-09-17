

#include <string.h>

#include "UdsServices/Service27.h"
#include "UdsServices/Service27_Config.h"
#include "UdsServices/Utils/Uds_Nrcs.h"

static uint16_t currentSecurityLevel = 0U;
static Service27_Config_T const *config;

void Service27_Init(Service27_Config_T const *const newConfig) { config = newConfig; }

void Service27_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {

    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 2U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }

    const uint8_t subFunction = Get_SubFunction(reqBuf->buffer.data[1]);

    for (uint8_t i = 0; i < config->securityLevelListSize; i++) {
        if (subFunction == config->securitylevelsList[i].subFunctionId && config->securitylevelsList[i].subFunctionCallback) {
            return config->securitylevelsList[i].subFunctionCallback(reqBuf, respBuf, &currentSecurityLevel);
        }
    }
    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    return;
}

uint16_t Service27_Get_Current_Security_Level(void) { return currentSecurityLevel; }

void Security27_Lock_ECU(void) { currentSecurityLevel = 0U; }

bool Security27_Is_ECU_Locked(void) { return currentSecurityLevel == 0; }
