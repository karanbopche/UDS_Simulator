#ifndef SERVICE11_H
#define SERVICE11_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service11_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service11_Init(Service11_Config_T const *const config);
void Service11_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
void Service11_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE11_H
