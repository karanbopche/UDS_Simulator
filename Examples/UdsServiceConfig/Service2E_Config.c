#include "UdsServices/Service2E.h"

static void Service2E_F199_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

static const Service2E_DID_Config_T supportedDIDs[] = {{
    .DID = 0xF199,
    .callback = Service2E_F199_Handler,
}};

const Service2E_Config_T service2EConfig = {
    .isFunctionalAddressSupported = false,
    .supportedDIDListSize = sizeof(supportedDIDs) / sizeof(supportedDIDs[0]),
    .supportedDIDList = supportedDIDs,
};

static void Service2E_F199_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    if (reqBuf->buffer.length != 7U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    const uint16_t did = Fetch_uint16(&reqBuf->buffer.data[1]);
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
    Uds_Buffer_Push_Uint16(&respBuf->buffer, did);
}
