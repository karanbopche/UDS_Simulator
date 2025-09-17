#include <string.h>

#include "UdsGateway.h"
#include "UdsServices/Service10.h"
#include "UdsServices/Service11.h"
#include "UdsServices/Service22.h"
#include "UdsServices/Service27.h"
#include "UdsServices/Service28.h"
#include "UdsServices/Service2E.h"
#include "UdsServices/Service31.h"
#include "UdsServices/Service34.h"
#include "UdsServices/Service36.h"
#include "UdsServices/Service37.h"
#include "UdsServices/Service3E.h"
#include "UdsServices/Service85.h"
#include "UdsServices/Utils/Uds_Nrcs.h"
#include "UdsServices/Utils/Uds_Services.h"

static UDS_Request_T Uds_Request_Buffer;
static UDS_Response_T Uds_Response_Buffer;
static Uds_Config_T const *config;

void Uds_Request_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const uint8_t serviceId = reqBuf->buffer.data[0];
    switch (serviceId) {
    case SERVICE_ID_10:
        Service10_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_11:
        Service11_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_22:
        Service22_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_27:
        Service27_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_28:
        Service28_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_2E:
        Service2E_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_31:
        Service31_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_34:
        Service34_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_36:
        Service36_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_37:
        Service37_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_3E:
        Service3E_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_85:
        Service85_Handler(reqBuf, respBuf);
        break;

    default:
        Uds_Fill_Nrc(&respBuf->buffer, serviceId, NRC_SERVICE_NOT_SUPPORTED);
    }
    return;
}

void Uds_Request_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const uint8_t serviceId = reqBuf->buffer.data[0];
    switch (serviceId) {
    case SERVICE_ID_11:
        Service11_Post_Handler(reqBuf, respBuf);
        break;
    case SERVICE_ID_31:
        Service31_Post_Handler(reqBuf, respBuf);
        break;
    default:
        break;
    }
}

void Uds_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Request_Handler(reqBuf, respBuf);
    if (&respBuf->buffer.length > 0U) {
        config->send(respBuf->buffer.data, respBuf->buffer.length);
    }
    Uds_Request_Post_Handler(reqBuf, respBuf);
}

bool Uds_Engine() {
    Uds_Request_Buffer.buffer.length = config->receive(Uds_Request_Buffer.buffer.data);
    if (Uds_Request_Buffer.buffer.length > 0U) {
        Uds_Handler(&Uds_Request_Buffer, &Uds_Response_Buffer);
        return true;
    }
    return false;
}

void Uds_Periodic_Task(const uint32_t elapsedMs) { Service10_Periodic_Handler(elapsedMs); }

void Uds_Send_Response(UDS_Response_T const *const response) { config->send(response->buffer.data, response->buffer.length); }

void Uds_Inject_Request(uint8_t const *const request, uint16_t length, bool isFunctionalRequest) {
    Uds_Buffer_Clear(&Uds_Request_Buffer.buffer);
    Uds_Request_Buffer.isFunctionalRequest = isFunctionalRequest;
    for (uint16_t i = 0; i < length; i++) {
        Uds_Buffer_Push_Uint8(&Uds_Request_Buffer.buffer, request[i]);
    }
    Uds_Handler(&Uds_Request_Buffer, &Uds_Response_Buffer);
}

void Uds_Init(Uds_Config_T const *const newConfig) {
    config = newConfig;
    Service10_Init(newConfig->services.service10);
    Service11_Init(newConfig->services.service11);
    Service22_Init(newConfig->services.service22);
    Service27_Init(newConfig->services.service27);
    Service28_Init(newConfig->services.service28);
    Service2E_Init(newConfig->services.service2E);
    Service31_Init(newConfig->services.service31);
    Service34_Init(newConfig->services.service34);
    Service36_Init(newConfig->services.service36);
    Service37_Init(newConfig->services.service37);
    Service3E_Init(newConfig->services.service3E);
    Service85_Init(newConfig->services.service85);
}
