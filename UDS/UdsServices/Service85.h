#ifndef SERVICE85_H
#define SERVICE85_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsServices/Service85_Config.h"
#include "UdsServices/Utils/Uds_Buffers.h"

void Service85_Init(Service85_Config_T const *const config);
void Service85_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE85_H
