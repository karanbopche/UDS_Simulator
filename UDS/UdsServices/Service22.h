#ifndef SERVICE22_H
#define SERVICE22_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service22_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service22_Init(Service22_Config_T const *const config);
void Service22_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE22_H
