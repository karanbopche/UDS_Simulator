#ifndef UDSGATEWAY_CONFIGURATION_H
#define UDSGATEWAY_CONFIGURATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service10_Config.h"
#include "UdsServices/Service11_Config.h"
#include "UdsServices/Service22_Config.h"
#include "UdsServices/Service27_Config.h"
#include "UdsServices/Service28_Config.h"
#include "UdsServices/Service2E_Config.h"
#include "UdsServices/Service31_Config.h"
#include "UdsServices/Service34_Config.h"
#include "UdsServices/Service36_Config.h"
#include "UdsServices/Service37_Config.h"
#include "UdsServices/Service3E_Config.h"
#include "UdsServices/Service85_Config.h"

typedef uint16_t (*Uds_Receive_Request_Callback_T)(uint8_t *const data);
typedef void (*Uds_Send_Response_Callback_T)(uint8_t const *const data, const uint16_t length);

typedef struct Uds_Services_Config_Tag {
    Service10_Config_T const *const service10;
    Service11_Config_T const *const service11;
    Service22_Config_T const *const service22;
    Service27_Config_T const *const service27;
    Service28_Config_T const *const service28;
    Service2E_Config_T const *const service2E;
    Service3E_Config_T const *const service3E;
    Service31_Config_T const *const service31;
    Service34_Config_T const *const service34;
    Service36_Config_T const *const service36;
    Service37_Config_T const *const service37;
    Service85_Config_T const *const service85;
} Uds_Services_Config_T;

typedef struct Uds_Config_Tag {
    Uds_Send_Response_Callback_T send;
    Uds_Receive_Request_Callback_T receive;
    Uds_Services_Config_T services;
} Uds_Config_T;

#ifdef __cplusplus
}
#endif

#endif // UDSGATEWAY_CONFIGURATION_H
