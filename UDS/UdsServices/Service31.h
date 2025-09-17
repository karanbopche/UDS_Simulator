#ifndef SERVICE31_H
#define SERVICE31_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service31_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service31_Init(Service31_Config_T const *const config);
void Service31_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
void Service31_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE31_H
