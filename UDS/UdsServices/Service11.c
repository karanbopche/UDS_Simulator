

#include "UdsServices/Service11.h"

void Service11_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service11_Config_T const *const config = Uds_Gateway_Configurations.services.service11;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if ((reqBuf->buffer.length != 2)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }

    const uint8_t requestedSubFunc = Get_SubFunction(reqBuf->buffer.data[1]);

    for (uint16_t i = 0; i < config->supportedSubFunctionsListSize; i++) {
        if (requestedSubFunc == config->supportedSubFunctionsList[i].subFunctionId &&
            config->supportedSubFunctionsList[i].subFunctionHandler) {
            return config->supportedSubFunctionsList[i].subFunctionHandler(reqBuf, respBuf);
        }
    }
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Clear(&respBuf->buffer);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, SERVICE_ID_11 | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, requestedSubFunc);
    }
}

void Service11_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service11_Config_T const *const config = Uds_Gateway_Configurations.services.service11;
    const uint8_t requestedSubFunc = Get_SubFunction(reqBuf->buffer.data[1]);
    for (uint16_t i = 0; i < config->supportedSubFunctionsListSize; i++) {
        if (requestedSubFunc == config->supportedSubFunctionsList[i].subFunctionId &&
            config->supportedSubFunctionsList[i].subFunctionHandler) {
            return config->supportedSubFunctionsList[i].subFunctionHandler(reqBuf, respBuf);
        }
    }
}
