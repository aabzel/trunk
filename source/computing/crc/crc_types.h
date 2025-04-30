#ifndef CRC_TYPES_H
#define CRC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    uint8_t calc;
    uint8_t read;
} __attribute__((__packed__)) Crc8_t;

typedef struct {
    uint16_t calc;
    uint16_t read;
} __attribute__((__packed__)) Crc16_t;

typedef struct {
    uint32_t calc;
    uint32_t read;
}__attribute__((__packed__))  Crc32_t;


#ifdef __cplusplus
}
#endif

#endif /* CRC_TYPES_H */
