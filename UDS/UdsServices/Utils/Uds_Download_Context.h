#ifndef UDS_DOWNLOAD_CONTEXT_H
#define UDS_DOWNLOAD_CONTEXT_H

#include <stdint.h>

typedef enum Uds_Tranfer_Request_Tag {
    UDS_NO_TRANSFER,
    UDS_UPLOAD_REQUEST,
    UDS_DOWNLOAD_REQUEST,
} Uds_Tranfer_Request_T;

typedef struct Uds_Transfer_Data_Request_Tag {
    Uds_Tranfer_Request_T requestType;
    bool isUploadRequest;
    bool isDownloadRequest;
    uint8_t blocksTransfered;
    uint32_t bytesTransfered;
    uint32_t transferSize;
    uintptr_t address;
} Uds_Transfer_Data_Request_T;

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

#endif
