

#include "UdsServices/Service22.h"

void Service22_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service22_Config_T const *const config = Uds_Gateway_Configurations.services.service22;

    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 3U || (reqBuf->buffer.length % 2) == 0) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }

    const uint8_t didCount = (reqBuf->buffer.length - 1) / 2;
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
    for (uint8_t didIndex = 0; didIndex < didCount; didIndex++) {
        const uint16_t requestedDID = Fetch_uint16(&reqBuf->buffer.data[didIndex * 2 + 1]);
        for (uint16_t i = 0; i < config->supportedDIDListSize; i++) {
            if (config->supportedDIDList[i].didId == requestedDID) {
                if (config->supportedDIDList[i].preconditions && !config->supportedDIDList[i].preconditions(reqBuf, respBuf)) {
                    return;
                }
                Uds_Buffer_Push_Uint16(&respBuf->buffer, requestedDID);
                config->supportedDIDList[i].didCallback(&respBuf->buffer);
            }
        }
    }

    if (respBuf->buffer.length == 1) {
        Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REQUEST_OUT_OF_RANGE);
    }
    return;
}
