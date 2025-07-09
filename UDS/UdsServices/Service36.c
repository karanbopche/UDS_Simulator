

#include "UdsServices/Service36.h"

extern Uds_Transfer_Data_Request_T transferRequest;

static void Service36_Download(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const uintptr_t startAddress = transferRequest.address + transferRequest.blocksTransfered;
    const uint32_t writeSize = reqBuf->buffer.length - 2U;
    const uint32_t bytesWritten =
        Uds_Gateway_Configurations.services.service36->memWrite((void *)startAddress, &respBuf->buffer.data[2], writeSize);
    if (bytesWritten != writeSize) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REPROGRAMMING_FAILED);
    }
    transferRequest.blocksTransfered++;
    transferRequest.bytesTransfered += bytesWritten;
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, transferRequest.blocksTransfered);
}

static void Service36_Upload(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    const uintptr_t startAddress = transferRequest.address + transferRequest.blocksTransfered;
    const uint32_t remainingBytes = transferRequest.transferSize - transferRequest.bytesTransfered;
    const uint32_t readSize = remainingBytes > (sizeof(reqBuf->buffer.data) - 2U) ? (sizeof(reqBuf->buffer.data) - 2U) : readSize;
    const uint32_t bytesRead =
        Uds_Gateway_Configurations.services.service36->memRead((void *)startAddress, &respBuf->buffer.data[2], readSize);
    if (bytesRead != readSize) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REPROGRAMMING_FAILED);
    }
    transferRequest.blocksTransfered++;
    transferRequest.bytesTransfered += bytesRead;
    Uds_Buffer_Clear(&respBuf->buffer);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, reqBuf->buffer.data[0] | POSITIVE_RESPONSE_MASK);
    Uds_Buffer_Push_Uint8(&respBuf->buffer, transferRequest.blocksTransfered);
    respBuf->buffer.length += bytesRead;
}

void Service36_Handler(UDS_Request_T const *const reqBuf, UDS_Response_T *const respBuf) {
    uint8_t *downloadram_address;
    uint16_t data_index;
    uint32_t mem_offset;
    Service36_Config_T const *const config = Uds_Gateway_Configurations.services.service36;
    if (config == NULL || (reqBuf->isFunctionalRequest && !config->isFunctionalAddressSupported)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_SERVICE_NOT_SUPPORTED);
    }
    if (reqBuf->buffer.length < 3U) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_INCORRECT_MESSAGE_LENGTH_OR_INVALID_FORMAT);
    }
    if (!Is_Transfer_Started(&transferRequest)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_REQUEST_SEQUENCE_ERROR);
    }
    if ((transferRequest.transferSize - transferRequest.bytesTransfered) < (reqBuf->buffer.length - 2U)) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_TRANSFER_DATA_SUSPENDED);
    }
    if (((transferRequest.blocksTransfered + 1) % 0xFFU) != reqBuf->buffer.data[1]) {
        return Uds_Fill_Nrc(&respBuf->buffer, reqBuf->buffer.data[0], NRC_WRONG_BLOCK_SEQUENCE_COUNTER);
    }
    if (Uds_Gateway_Configurations.services.service36->preconditions &&
        !Uds_Gateway_Configurations.services.service36->preconditions(reqBuf, respBuf)) {
        return;
    }
    if (transferRequest.requestType == UDS_DOWNLOAD_REQUEST) {
        return Service36_Download(reqBuf, respBuf);
    }
    if (transferRequest.requestType == UDS_UPLOAD_REQUEST) {
        return Service36_Upload(reqBuf, respBuf);
    }
}
