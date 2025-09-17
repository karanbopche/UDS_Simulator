

#include "UdsServices/Service3E.h"
#include "UdsServices/Service10.h"
#include "UdsServices/Service3E_Config.h"
#include "UdsServices/Utils/Uds_Nrcs.h"

static Service3E_Config_T const *config;

void Service3E_Init(Service3E_Config_T const *const newConfig) { config = newConfig; }

void Service3E_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length != 2U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if ((Get_SubFunction(reqBuf->buffer.data[1]) != 0U)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    }
    Service10_Session_Timer_Reset();
    if (!Is_Resp_Suppressed(reqBuf->buffer.data[1])) {
        Uds_Buffer_Clear(&respBuf->buffer);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[1]);
    }
}
