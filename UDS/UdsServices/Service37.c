

#include "UdsServices/Service37.h"
#include "UdsServices/Service37_Config.h"
#include "UdsServices/Utils/Uds_Download_Context.h"
#include "UdsServices/Utils/Uds_Nrcs.h"

extern Uds_Transfer_Data_Request_T transferRequest;
static Service37_Config_T const *config;

void Service37_Init(Service37_Config_T const *const newConfig) { config = newConfig; }

void Service37_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
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
    if (config->tranferCompleteCallback) {
        config->tranferCompleteCallback();
    }
    Stop_Uds_Transfer(&transferRequest);
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
}
