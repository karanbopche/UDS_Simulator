#include "UdsServices/Service11.h"

static void Service11_SubFunction_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
static void Service11_SubFunction_Post_Handler(void);

const Service11_SubFunction_Config_T service11SubFunctionsConfig[] = {
    {
        .subFunctionId = 0x01,
        .subFunctionHandler = Service11_SubFunction_Handler,
        .postHandler = Service11_SubFunction_Post_Handler,
    },
    {
        .subFunctionId = 0x02,
        .subFunctionHandler = Service11_SubFunction_Handler,
        .postHandler = Service11_SubFunction_Post_Handler,
    },
    {
        .subFunctionId = 0x03,
        .subFunctionHandler = Service11_SubFunction_Handler,
        .postHandler = Service11_SubFunction_Post_Handler,
    },
};

const Service11_Config_T service11Config = {
    .isFunctionalAddressSupported = false,
    .supportedSubFunctionsListSize = sizeof(service11SubFunctionsConfig) / sizeof(service11SubFunctionsConfig[0]),
    .supportedSubFunctionsList = service11SubFunctionsConfig,
};

static void Service11_SubFunction_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
}

static void Service11_SubFunction_Post_Handler(void) {}
