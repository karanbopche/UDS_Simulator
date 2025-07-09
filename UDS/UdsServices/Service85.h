#ifndef SERVICE85_H
#define SERVICE85_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsGateway_Configuration.h"

void Service85_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

#ifdef __cplusplus
}
#endif

#endif // SERVICE85_H
