#ifndef UDS_BUFFERS_H
#define UDS_BUFFERS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_BUF_SIZE 514U

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

#endif
