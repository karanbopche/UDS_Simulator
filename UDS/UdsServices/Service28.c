

#include "UdsServices/Service28.h"
#include "UdsServices/Service10.h"
#include "UdsServices/Service28_Config.h"
#include "UdsServices/Utils/Uds_Nrcs.h"

static Service28_Config_T const *config;

void Service28_Init(Service28_Config_T const *const newConfig) { config = newConfig; }

void Service28_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 4U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (config->preconditions && !config->preconditions(reqBuf, respBuf)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_CONDITIONS_NOT_CORRECT);
    }
    const uint8_t subFunction = Get_SubFunction(reqBuf->buffer.data[1]);
    for (uint8_t i = 0; i < config->supportedSubFunctionListSize; i++) {
        if (subFunction == config->supportedSubFunctionList[i].subFunctionId &&
            config->supportedSubFunctionList[i].subfunctionHandler) {
            return config->supportedSubFunctionList[i].subfunctionHandler(reqBuf, respBuf);
        }
    }
    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
}
