

#include "UdsServices/Service34.h"

Uds_Transfer_Data_Request_T transferRequest;

void Service34_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service34_Config_T const *const config = Uds_Gateway_Configurations.services.service34;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 4U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (reqBuf->buffer.data[1] != 0U || reqBuf->buffer.data[2] != 0x44U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REQUEST_OUT_OF_RANGE);
    }
    if (Is_Transfer_Started(&transferRequest)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_CONDITIONS_NOT_CORRECT);
    }
    const uintptr_t address = Fetch_uint32(&reqBuf->buffer.data[3]);
    const uintptr_t size = Fetch_uint32(&reqBuf->buffer.data[7]);
    if (Uds_Gateway_Configurations.services.service34->preconditions &&
        !Uds_Gateway_Configurations.services.service34->preconditions(reqBuf, respBuf)) {
        return;
    }
    Initiate_Uds_Download(&transferRequest, address, size);
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[2]);
    Uds_Buffer_Push_Uint16(&respBuf->buffer, sizeof(reqBuf->buffer.data));
}
