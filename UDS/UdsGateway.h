#ifndef UDSGATEWAY_H
#define UDSGATEWAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsGateway_Configuration.h"

void Uds_Request_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
void Uds_Send_Response(UDS_Response_T const *const buffer);
void Uds_Periodic_Task(const uint32_t elapsedMs);
bool Uds_Engine(void);
void Uds_Inject_Request(uint8_t const *const request, uint16_t length, bool isFunctionalRequest);

#ifdef __cplusplus
}
#endif

#endif // UDSGATEWAY_H
