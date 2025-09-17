#ifndef SERVICE34_H
#define SERVICE34_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service34_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service34_Init(Service34_Config_T const *const config);
void Service34_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE34_H
