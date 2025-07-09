#include "UdsServices/Service31.h"

static void Service31_FF01_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
static void Service31_0202_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
static void Service31_F085_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
static void Service31_F085_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

static const Service31_RID_Config_T service31RIDConfig[] = {
    {
        .RID = 0xFF01,
        .routineHandler = Service31_FF01_Handler,
        .postResponseHandler = NULL,
    },
    {
        .RID = 0xF085,
        .routineHandler = Service31_F085_Handler,
        .postResponseHandler = Service31_F085_Post_Handler,
    },
    {
        .RID = 0x0202,
        .routineHandler = Service31_0202_Handler,
        .postResponseHandler = NULL,
    },
};

const Service31_Config_T service31Config = {
    .isFunctionalAddressSupported = false,
    .preconditions = NULL,
    .supportedRIDsListSize = sizeof(service31RIDConfig) / sizeof(service31RIDConfig[0]),
    .supportedRIDsList = service31RIDConfig,
};

static void Service31_FF01_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    if ((reqBuf->buffer.length != 4U)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (Get_SubFunction(reqBuf->buffer.data[1]) != SERVICE_31_START_ROUTINE) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    }

    Uds_Buffer_Clear(&respBuf->buffer);
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[2]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[3]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, 0U);
    }
}

static void Service31_0202_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const bool suppressPosRspMsg = (reqBuf->buffer.data[1] & 0x80) ? true : false;

    if (reqBuf->buffer.length != 8U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (Get_SubFunction(reqBuf->buffer.data[1]) != SERVICE_31_START_ROUTINE) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    }

    Uds_Buffer_Clear(&respBuf->buffer);
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[2]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[3]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, 0U);
    }
}

static void Service31_F085_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    if (reqBuf->buffer.length != 4U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (Get_SubFunction(reqBuf->buffer.data[1]) != SERVICE_31_START_ROUTINE) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    }

    Uds_Buffer_Clear(&respBuf->buffer);
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[2]);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[3]);
    }
}

static void Service31_F085_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {}
