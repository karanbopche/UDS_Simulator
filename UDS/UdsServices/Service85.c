

#include "UdsServices/Service85.h"
#include "UdsServices/Service10.h"

#define DTC_SETTING_ENABLE 0x01U
#define DTC_SETTING_DISABLE 0x02U

void Service85_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Service85_Config_T const *const config = Uds_Gateway_Configurations.services.service85;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length != 2U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    const uint8_t subFunction = Get_SubFunction(reqBuf->buffer.data[1]);

    for (uint16_t i = 0; i < Uds_Gateway_Configurations.services.service85->customSubFunctionsListSize; i++) {
        if (Uds_Gateway_Configurations.services.service85->customSubFunctionsList[i].subFunctionId == subFunction &&
            Uds_Gateway_Configurations.services.service85->customSubFunctionsList[i].subFunctionHandler) {
            return Uds_Gateway_Configurations.services.service85->customSubFunctionsList[i].subFunctionHandler(reqBuf, respBuf);
        }
    }
    Uds_Buffer_Clear(&respBuf->buffer);
    if (subFunction == DTC_SETTING_ENABLE && Uds_Gateway_Configurations.services.service85->enableDtcCallback) {
        Uds_Gateway_Configurations.services.service85->enableDtcCallback();
        Uds_Buffer_Push_Uint8(&respBuf->buffer, SERVICE_ID_85 | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, DTC_SETTING_ENABLE);
        return;
    }
    if (subFunction == DTC_SETTING_DISABLE && Uds_Gateway_Configurations.services.service85->disableDtcCallback) {
        Uds_Gateway_Configurations.services.service85->disableDtcCallback();
        Uds_Buffer_Push_Uint8(&respBuf->buffer, SERVICE_ID_85 | POSITIVE_RESPONSE_MASK);
        Uds_Buffer_Push_Uint8(&respBuf->buffer, DTC_SETTING_DISABLE);
        return;
    }
    Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SUBFUNCTION_NOT_SUPPORTED);
    return;
}
