#ifndef SERVICE36_H
#define SERVICE36_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service36_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service36_Init(Service36_Config_T const *const config);
void Service36_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE36_H
