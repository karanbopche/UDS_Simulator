#ifndef SERVICE3E_H
#define SERVICE3E_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service3E_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service3E_Init(Service3E_Config_T const *const config);
void Service3E_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE3E_H
