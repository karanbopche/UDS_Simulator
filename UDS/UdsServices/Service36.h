#ifndef SERVICE36_H
#define SERVICE36_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsGateway_Configuration.h"

void Service36_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE36_H
