

#include "UdsServices/Service22.h"

static void Did_F188_Handler(UDS_Buffer_T *const resultBuffer);
static void Did_F199_Handler(UDS_Buffer_T *const resultBuffer);

const Service22_DID_Config_T supportedDIds[] = {{.didId = 0xF188, .preconditions = NULL, .didCallback = Did_F188_Handler},
                                                {.didId = 0xF199, .preconditions = NULL, .didCallback = Did_F199_Handler}};
const Service22_Config_T service22Config = {
    .isFunctionalAddressSupported = true,
    .supportedDIDListSize = sizeof(supportedDIds) / sizeof(supportedDIds[0]),
    .supportedDIDList = supportedDIds,
};

static void Did_F188_Handler(UDS_Buffer_T *const resultBuffer) {
    Uds_Buffer_Push_Uint8(resultBuffer, 0x88);
    Uds_Buffer_Push_Uint8(resultBuffer, 0x88);
    Uds_Buffer_Push_Uint8(resultBuffer, 0x88);
    Uds_Buffer_Push_Uint8(resultBuffer, 0x88);
}

static void Did_F199_Handler(UDS_Buffer_T *const resultBuffer) {
    Uds_Buffer_Push_Uint8(resultBuffer, 0x99);
    Uds_Buffer_Push_Uint8(resultBuffer, 0x99);
    Uds_Buffer_Push_Uint8(resultBuffer, 0x99);
    Uds_Buffer_Push_Uint8(resultBuffer, 0x99);
}
