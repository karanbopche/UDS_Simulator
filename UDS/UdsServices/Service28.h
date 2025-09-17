#ifndef SERVICE28_H
#define SERVICE28_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service28_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service28_Init(Service28_Config_T const *const config);
void Service28_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE28_H
