#ifndef UDS_SERVICES_H
#define UDS_SERVICES_H

#include "UdsServices/Utils/Uds_Buffers.h"

#define POSITIVE_RESPONSE_MASK 0x40U

typedef enum Uds_Services_Tag {
    SERVICE_ID_10 = 0x10,
    SERVICE_ID_11 = 0x11,
    SERVICE_ID_20 = 0x20,
    SERVICE_ID_22 = 0x22,
    SERVICE_ID_2E = 0x2E,
    SERVICE_ID_27 = 0x27,
    SERVICE_ID_28 = 0x28,
    SERVICE_ID_29 = 0x29,
    SERVICE_ID_31 = 0x31,
    SERVICE_ID_34 = 0x34,
    SERVICE_ID_36 = 0x36,
    SERVICE_ID_37 = 0x37,
    SERVICE_ID_3E = 0x3E,
    SERVICE_ID_85 = 0x85,
} Uds_Services_T;

typedef bool (*Request_Preconditions_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
typedef void (*Request_Handler_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
typedef void (*Request_Post_Handler_T)(void);

static inline uint8_t Get_SubFunction(const uint8_t value) { return value & 0x7F; }

static inline bool Is_Resp_Suppressed(const uint8_t value) { return (value & 0x80) != 0; }

#endif
