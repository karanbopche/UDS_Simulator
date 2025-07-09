#include "UdsServices/Service27.h"

static void SubFunction_03_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel);
static void SubFunction_04_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel);
static void SubFunction_11_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel);
static void SubFunction_12_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel);

const Service27_SubFunctions_T subFuntions[] = {
    {
        .subFunctionId = 0x03,
        .subFunctionCallback = SubFunction_03_Handler,
    },
    {
        .subFunctionId = 0x04,
        .subFunctionCallback = SubFunction_04_Handler,
    },
    {
        .subFunctionId = 0x11,
        .subFunctionCallback = SubFunction_11_Handler,
    },
    {
        .subFunctionId = 0x12,
        .subFunctionCallback = SubFunction_12_Handler,
    },
};

const Service27_Config_T service27Config = {
    .isFunctionalAddressSupported = false,
    .securityLevelListSize = 0,
    .securitylevelsList = NULL,
};

static void SubFunction_03_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel) {}
static void SubFunction_04_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel) {}
static void SubFunction_11_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel) {}
static void SubFunction_12_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                   uint16_t *currentSecuriyLevel) {}
