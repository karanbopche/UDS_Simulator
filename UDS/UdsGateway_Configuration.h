#ifndef UDSGATEWAY_CONFIGURATION_H
#define UDSGATEWAY_CONFIGURATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define POSITIVE_RESPONSE_MASK 0x40U
#define MAX_BUF_SIZE 514U

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

typedef enum UDS_Nrc_Tag {
    NRC_OK = 0x00,
    NRC_GENERAL_REJECT = 0x10,
    NRC_SERVICE_NOT_SUPPORTED = 0x11,
    NRC_SUBFUNCTION_NOT_SUPPORTED = 0x12,
    NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT = 0x13,
    NRC_BUSY_REPEAT_REQUEST = 0x21,
    NRC_CONDITIONS_NOT_CORRECT = 0x22,
    NRC_REQUEST_SEQUENCE_ERROR = 0x24,
    NRC_REQUEST_OUT_OF_RANGE = 0x31,
    NRC_SECURITY_ACEESS_DENIED = 0x33,
    NRC_AUTHETICATION_REQUIRED = 0x34,
    NRC_INVALID_KEY = 0x35,
    NRC_EXCEEDED_NUMBER_OF_ATTEMPTS = 0x36,
    NRC_REQUIRED_TIME_DELAY_NOT_EXPIRED = 0x37,
    NRC_CANNOT_UPLOAD_NUMBER_OF_BYTES_REQUESTED = 0x53,
    NRC_UPLOAD_DOWNLOAD_NOT_ACCEPTED = 0x70,
    NRC_TRANSFER_DATA_SUSPENDED = 0x71,
    NRC_GENERAL_PROGRAMMING_FAILURE = 0x72,
    NRC_WRONG_BLOCK_SEQUENCE_COUNTER = 0x73,
    NRC_REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING = 0x78,
    NRC_INCORRECT_BYTE_COUNT = 0x79,
    NRC_SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION = 0x7F,
    NRC_REPROGRAMMING_FAILED = 0x85,
    NRC_DEVICE_TYPE_ERROR = 0x89,
    NRC_RESPONSE_PENDING_BUT_DOES_NOT_SEND_RCRRP = 0xFF,
} UDS_Nrc_T;

typedef enum Uds_Tranfer_Request_Tag {
    UDS_NO_TRANSFER,
    UDS_UPLOAD_REQUEST,
    UDS_DOWNLOAD_REQUEST,
} Uds_Tranfer_Request_T;

typedef struct UDS_Buffer_Tag {
    uint16_t length;
    uint8_t data[MAX_BUF_SIZE];
} UDS_Buffer_T;

typedef struct UDS_Request_Tag {
    UDS_Buffer_T buffer;
    bool isFunctionalRequest;
} UDS_Request_T;

typedef struct UDS_Response_Tag {
    UDS_Buffer_T buffer;
} UDS_Response_T;

typedef struct Uds_Transfer_Data_Request_Tag {
    Uds_Tranfer_Request_T requestType;
    bool isUploadRequest;
    bool isDownloadRequest;
    uint8_t blocksTransfered;
    uint32_t bytesTransfered;
    uint32_t transferSize;
    uintptr_t address;
} Uds_Transfer_Data_Request_T;

typedef void (*Request_Handler_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);
typedef void (*Request_Post_Handler_T)(void);
typedef bool (*Request_Preconditions_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf);

typedef struct Service2E_DID_Config_Tag {
    uint16_t DID;
    Request_Handler_T callback;
} Service2E_DID_Config_T;

typedef struct Service2E_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t supportedDIDListSize;
    Service2E_DID_Config_T const *const supportedDIDList;
} Service2E_Config_T;

typedef struct Service3E_Config_Tag {
    bool isFunctionalAddressSupported;
} Service3E_Config_T;

typedef void (*Service10_Session_Callback_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                             uint8_t *currentSession);

typedef struct Service10_Session_Config_Tag {
    uint8_t sessionId;
    uint16_t sessionTimeoutTimer;
    Service10_Session_Callback_T callback;
} Service10_Session_Config_T;

typedef struct Service10_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t p2Timer;
    uint16_t p2MaxTimer;
    uint16_t s3TimerProgrammingSession;
    uint16_t s3TimerExtendedSession;
    Request_Preconditions_T preconditions;
    uint16_t customSessionsListSize;
    Service10_Session_Config_T const *const customSessionsList;
} Service10_Config_T;

typedef struct Service11_SubFunction_Config_Tag {
    uint8_t subFunctionId;
    Request_Handler_T subFunctionHandler;
    Request_Post_Handler_T postHandler;
} Service11_SubFunction_Config_T;

typedef struct Service11_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t supportedSubFunctionsListSize;
    Service11_SubFunction_Config_T const *const supportedSubFunctionsList;
} Service11_Config_T;

typedef struct Service22_DID_Config_Tag {
    uint16_t didId;
    Request_Preconditions_T preconditions;
    void (*didCallback)(UDS_Buffer_T *resultBuffer);
} Service22_DID_Config_T;

typedef struct Service22_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t supportedDIDListSize;
    Service22_DID_Config_T const *const supportedDIDList;
} Service22_Config_T;

typedef void (*Security_Callback_T)(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf,
                                    uint16_t *currentSecuriyLevel);

typedef struct Service27_SubFunctions_Tag {
    uint8_t subFunctionId;
    Security_Callback_T subFunctionCallback;
} Service27_SubFunctions_T;

typedef struct Service27_Config_Tag {
    bool isFunctionalAddressSupported;
    uint16_t securityLevelListSize;
    Service27_SubFunctions_T const *const securitylevelsList;
} Service27_Config_T;

typedef struct Service28_SubFunction_Config_Tag {
    uint8_t subFunctionId;
    Request_Handler_T subfunctionHandler;
} Service28_SubFunction_Config_T;

typedef struct Service28_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
    uint16_t supportedSubFunctionListSize;
    Service28_SubFunction_Config_T const *const supportedSubFunctionList;
} Service28_Config_T;

typedef enum Service31_RoutineControl_Tag {
    SERVICE_31_START_ROUTINE = 0x01,
    SERVICE_31_STOP_ROUTINE = 0x02,
    SERVICE_31_REQUEST_ROUTINE_RESULT = 0x03,
} Service31_RoutineControl_T;

typedef struct Service31_RID_Config_Tag {
    uint16_t RID;
    Request_Handler_T routineHandler;
    Request_Handler_T postResponseHandler;
} Service31_RID_Config_T;

typedef struct Service31_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
    uint16_t supportedRIDsListSize;
    Service31_RID_Config_T const *const supportedRIDsList;
} Service31_Config_T;

typedef struct Service34_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
} Service34_Config_T;

typedef uint32_t (*Memory_Write_Callback_T)(void *const address, void const *const data, const uint32_t size);
typedef uint32_t (*Memory_Read_Callback_T)(const void *address, void *const data, const uint32_t size);
typedef struct Service36_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Preconditions_T preconditions;
    Memory_Write_Callback_T memWrite;
    Memory_Read_Callback_T memRead;
} Service36_Config_T;

typedef struct Service37_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Post_Handler_T tranferCompleteCallback;
} Service37_Config_T;

typedef struct Service85_SubFunction_Config_Tag {
    uint8_t subFunctionId;
    Request_Handler_T subFunctionHandler;
} Service85_SubFunction_Config_T;

typedef struct Service85_Config_Tag {
    bool isFunctionalAddressSupported;
    Request_Post_Handler_T enableDtcCallback;
    Request_Post_Handler_T disableDtcCallback;
    uint16_t customSubFunctionsListSize;
    Service85_SubFunction_Config_T const *const customSubFunctionsList;
} Service85_Config_T;

typedef uint16_t (*Uds_Receive_Request_Callback_T)(uint8_t *const data);
typedef void (*Uds_Send_Response_Callback_T)(uint8_t const *const data, const uint16_t length);

typedef struct Uds_Services_Config_Tag {
    Service10_Config_T const *const service10;
    Service11_Config_T const *const service11;
    Service22_Config_T const *const service22;
    Service27_Config_T const *const service27;
    Service28_Config_T const *const service28;
    Service2E_Config_T const *const service2E;
    Service3E_Config_T const *const service3E;
    Service31_Config_T const *const service31;
    Service34_Config_T const *const service34;
    Service36_Config_T const *const service36;
    Service37_Config_T const *const service37;
    Service85_Config_T const *const service85;
} Uds_Services_Config_T;

typedef struct Uds_Config_Tag {
    Uds_Send_Response_Callback_T send;
    Uds_Receive_Request_Callback_T receive;
    Uds_Services_Config_T services;
} Uds_Config_T;

extern Uds_Config_T const Uds_Gateway_Configurations;

static inline void Uds_Buffer_Clear(UDS_Buffer_T *const buffer) { buffer->length = 0U; }

static inline void Uds_Buffer_Push_Uint8(UDS_Buffer_T *const buffer, const uint8_t value) {
    buffer->data[buffer->length++] = value;
}

static inline void Uds_Buffer_Push_Uint16(UDS_Buffer_T *const buffer, const uint16_t value) {
    buffer->data[buffer->length++] = (value >> 8) & 0xFF;
    buffer->data[buffer->length++] = value & 0xFF;
}

static inline void Uds_Buffer_Push_Uint32(UDS_Buffer_T *const buffer, const uint32_t value) {
    buffer->data[buffer->length++] = (value >> 24) & 0xFF;
    buffer->data[buffer->length++] = (value >> 16) & 0xFF;
    buffer->data[buffer->length++] = (value >> 8) & 0xFF;
    buffer->data[buffer->length++] = value & 0xFF;
}

static inline void Uds_Fill_Nrc(UDS_Buffer_T *const buffer, const uint8_t serviceId, const UDS_Nrc_T nrc) {
    buffer->length = 0;
    buffer->data[buffer->length++] = 0x7F;
    buffer->data[buffer->length++] = serviceId;
    buffer->data[buffer->length++] = (uint8_t)nrc;
}

static inline void Fill_uint16(uint8_t *const buffer, const uint16_t value) {
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
}

static inline void Fill_uint32(uint8_t *const buffer, const uint32_t value) {
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

static inline uint16_t Fetch_uint16(uint8_t const *const buffer) { return (buffer[0] << 8) | buffer[1]; }

static inline uint32_t Fetch_uint32(uint8_t const *const buffer) {
    return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}

static inline uint8_t Get_SubFunction(const uint8_t value) { return value & 0x7F; }

static inline bool Is_Resp_Suppressed(const uint8_t value) { return (value & 0x80) != 0; }

static inline void Initiate_Uds_Download(Uds_Transfer_Data_Request_T *const transfer, const uint32_t address,
                                         const uint32_t size) {
    transfer->address = address;
    transfer->transferSize = size;
    transfer->blocksTransfered = 0U;
    transfer->bytesTransfered = 0U;
    transfer->requestType = UDS_DOWNLOAD_REQUEST;
}

static inline void Initiate_Uds_Upload(Uds_Transfer_Data_Request_T *const transfer, const uint32_t address, const uint32_t size) {
    transfer->address = address;
    transfer->transferSize = size;
    transfer->blocksTransfered = 0U;
    transfer->bytesTransfered = 0U;
    transfer->requestType = UDS_UPLOAD_REQUEST;
}

static inline void Stop_Uds_Transfer(Uds_Transfer_Data_Request_T *const transfer) {
    transfer->address = 0U;
    transfer->transferSize = 0U;
    transfer->blocksTransfered = 0U;
    transfer->bytesTransfered = 0U;
    transfer->requestType = UDS_NO_TRANSFER;
}

static inline bool Is_Transfer_Started(Uds_Transfer_Data_Request_T *const transfer) {
    return transfer->requestType != UDS_NO_TRANSFER;
}

#ifdef __cplusplus
}
#endif

#endif // UDSGATEWAY_CONFIGURATION_H
