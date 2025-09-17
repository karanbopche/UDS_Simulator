#ifndef SERVICE10_H
#define SERVICE10_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service10_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service10_Init(Service10_Config_T const *const config);
void Service10_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
void Service10_Session_Timer_Reset();
void Service10_Periodic_Handler(const uint32_t elapsedMs);
uint8_t Service10_Get_Current_Session();

#ifdef __cplusplus
}
#endif

#endif // SERVICE10_H
