

#include "UdsServices/Service31.h"

void Service31_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service31_Config_T const *const config = Uds_Gateway_Configurations.services.service31;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 4U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (config->preconditions && !config->preconditions(reqBuf, respBuf)) {
        return;
    }
    const uint16_t routineId = Fetch_uint16(&reqBuf->buffer.data[2]);
    for (uint16_t i = 0; i < config->supportedRIDsListSize; i++) {
        if (config->supportedRIDsList[i].RID == routineId) {
            config->supportedRIDsList[i].routineHandler(reqBuf, respBuf);
            return;
        }
    }
    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REQUEST_OUT_OF_RANGE);
    return;
}

void Service31_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service31_Config_T const *const config = Uds_Gateway_Configurations.services.service31;
    const uint16_t routineId = Fetch_uint16(&reqBuf->buffer.data[2]);
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return;
    }
    for (uint16_t i = 0; i < config->supportedRIDsListSize; i++) {
        if (config->supportedRIDsList[i].RID == routineId) {
            config->supportedRIDsList[i].postResponseHandler(reqBuf, respBuf);
        }
    }
}
