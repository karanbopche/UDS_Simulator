#ifndef SERVICE10_H
#define SERVICE10_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsGateway_Configuration.h"

typedef enum Service10_Session_Tag {
    SERVICE_10_DEFAULT_SESSION = 0x01,
    SERVICE_10_PROGRAMMING_SESSION = 0x02,
    SERVICE_10_EXTENDED_SESSION = 0x03,
} Service10_Session_T;

void Service10_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
void Service10_Session_Timer_Reset();
void Service10_Periodic_Handler(const uint32_t elapsedMs);
uint8_t Service10_Get_Current_Session();

#ifdef __cplusplus
}
#endif

#endif // SERVICE10_H
