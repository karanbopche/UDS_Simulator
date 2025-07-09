

#include "UdsServices/Service37.h"
#include "UdsGateway_Configuration.h"

extern Uds_Transfer_Data_Request_T transferRequest;

void Service37_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service37_Config_T const *const config = Uds_Gateway_Configurations.services.service37;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length == 1U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (!Is_Transfer_Started(&transferRequest)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REQUEST_SEQUENCE_ERROR);
    } else if (transferRequest.bytesTransfered != transferRequest.transferSize) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_CONDITIONS_NOT_CORRECT);
    }
    if (Uds_Gateway_Configurations.services.service37->tranferCompleteCallback) {
        Uds_Gateway_Configurations.services.service37->tranferCompleteCallback();
    }
    Stop_Uds_Transfer(&transferRequest);
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
}
