#ifndef SERVICE27_H
#define SERVICE27_H

#ifdef __cplusplus
extern "C" {
#endif

#include "UdsGateway_Configuration.h"

void Service27_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
uint16_t Service27_Get_Current_Security_Level(void);
void Security27_Lock_ECU(void);

#ifdef __cplusplus
}
#endif

#endif // SERVICE27_H
