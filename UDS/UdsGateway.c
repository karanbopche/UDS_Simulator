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

typedef struct StandardServiceConfig_Tag {
    uint8_t serviceId;
    Request_Handler_T serviceHandler;
    Request_Handler_T postResponseHandler;
} StandardServiceConfig_T;

static UDS_Request_T Uds_Request_Buffer;
static UDS_Response_T Uds_Response_Buffer;
static const StandardServiceConfig_T standardServicesList[] = {
    {
        .serviceId = SERVICE_ID_10,
        .serviceHandler = Service10_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_11,
        .serviceHandler = Service11_Handler,
        .postResponseHandler = Service11_Post_Handler,
    },
    {
        .serviceId = SERVICE_ID_22,
        .serviceHandler = Service22_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_27,
        .serviceHandler = Service27_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_28,
        .serviceHandler = Service28_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_2E,
        .serviceHandler = Service2E_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_3E,
        .serviceHandler = Service3E_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_31,
        .serviceHandler = Service31_Handler,
        .postResponseHandler = Service31_Post_Handler,
    },
    {
        .serviceId = SERVICE_ID_34,
        .serviceHandler = Service34_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_36,
        .serviceHandler = Service36_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_37,
        .serviceHandler = Service37_Handler,
        .postResponseHandler = NULL,
    },
    {
        .serviceId = SERVICE_ID_85,
        .serviceHandler = Service85_Handler,
        .postResponseHandler = NULL,
    },
};

static const uint8_t standardServicesListSize = sizeof(standardServicesList) / sizeof(standardServicesList[0]);

void Uds_Request_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const uint8_t serviceId = reqBuf->buffer.data[0];
    for (uint8_t i = 0; i < standardServicesListSize; i++) {
        if (standardServicesList[i].serviceId == serviceId && standardServicesList[i].serviceHandler) {
            return standardServicesList[i].serviceHandler(reqBuf, respBuf);
        }
    }
    Uds_Fill_Nrc(&respBuf->buffer, serviceId, NRC_SERVICE_NOT_SUPPORTED);
    return;
}

void Uds_Request_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const uint8_t serviceId = reqBuf->buffer.data[0];
    for (uint8_t i = 0; i < standardServicesListSize; i++) {
        if (standardServicesList[i].serviceId == serviceId && standardServicesList[i].postResponseHandler) {
            return standardServicesList[i].postResponseHandler(reqBuf, respBuf);
        }
    }
}

void Uds_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Request_Handler(reqBuf, respBuf);
    if (&respBuf->buffer.length > 0U) {
        Uds_Gateway_Configurations.send(respBuf->buffer.data, respBuf->buffer.length);
    }
    Uds_Request_Post_Handler(reqBuf, respBuf);
}

bool Uds_Engine() {
    Uds_Request_Buffer.buffer.length = Uds_Gateway_Configurations.receive(Uds_Request_Buffer.buffer.data);
    if (Uds_Request_Buffer.buffer.length > 0U) {
        Uds_Handler(&Uds_Request_Buffer, &Uds_Response_Buffer);
        return true;
    }
    return false;
}

void Uds_Periodic_Task(const uint32_t elapsedMs) { Service10_Periodic_Handler(elapsedMs); }

void Uds_Send_Response(UDS_Response_T const *const response) {
    Uds_Gateway_Configurations.send(response->buffer.data, response->buffer.length);
}

void Uds_Inject_Request(uint8_t const *const request, uint16_t length, bool isFunctionalRequest) {
    Uds_Buffer_Clear(&Uds_Request_Buffer.buffer);
    Uds_Request_Buffer.isFunctionalRequest = isFunctionalRequest;
    for (uint16_t i = 0; i < length; i++) {
        Uds_Buffer_Push_Uint8(&Uds_Request_Buffer.buffer, request[i]);
    }
    Uds_Handler(&Uds_Request_Buffer, &Uds_Response_Buffer);
}
