#include "UdsServices/Service2E.h"

void Service2E_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service2E_Config_T const *const config = Uds_Gateway_Configurations.services.service2E;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 3) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }

    const uint16_t requestDID = Fetch_uint16(&reqBuf->buffer.data[1]);
    for (uint16_t i = 0; i < config->supportedDIDListSize; i++) {
        if (requestDID == config->supportedDIDList[i].DID) {
            return config->supportedDIDList[i].callback(reqBuf, respBuf);
        }
    }
    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    return;
}
