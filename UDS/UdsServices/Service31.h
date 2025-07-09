#ifndef SERVICE31_H
#define SERVICE31_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsGateway_Configuration.h"

void Service31_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
void Service31_Post_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE31_H
