#ifndef SERVICE37_H
#define SERVICE37_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service37_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service37_Init(Service37_Config_T const *const config);
void Service37_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE37_H
