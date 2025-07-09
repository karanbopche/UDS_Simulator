

#include "UdsServices/Service28.h"
#include "UdsServices/Service10.h"

void Service28_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service28_Config_T const *const config = Uds_Gateway_Configurations.services.service28;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 4U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (Uds_Gateway_Configurations.services.service28->preconditions &&
        !Uds_Gateway_Configurations.services.service28->preconditions(reqBuf, respBuf)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_CONDITIONS_NOT_CORRECT);
    }
    const uint8_t subFunction = Get_SubFunction(reqBuf->buffer.data[1]);
    for (uint8_t i = 0; i < Uds_Gateway_Configurations.services.service28->supportedSubFunctionListSize; i++) {
        if (subFunction == Uds_Gateway_Configurations.services.service28->supportedSubFunctionList[i].subFunctionId &&
            Uds_Gateway_Configurations.services.service28->supportedSubFunctionList[i].subfunctionHandler) {
            return Uds_Gateway_Configurations.services.service28->supportedSubFunctionList[i].subfunctionHandler(reqBuf, respBuf);
        }
    }
    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
}
