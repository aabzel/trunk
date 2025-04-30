
#ifndef SET_TYPEES_H
#define SET_TYPEES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "set_const.h"

#ifndef HAS_SET
#error "+HAS_SET"
#endif

#ifndef HAS_CRC16
#error "+HAS_CRC16"
#endif


typedef struct {
    uint16_t preamble; /*0x5354*/
    uint16_t inv_preamble; /**/
    uint32_t size; /*payload size*/
    uint16_t crc16; /*payload crc16*/
} __attribute__((packed)) SetHeader_t;

#define SET_COMMON_VARIABLE   \
    uint8_t num;              \
    uint8_t nvram_num;        \
    bool valid;

typedef struct {
    SET_COMMON_VARIABLE
} SetConfig_t;

typedef struct {
    SET_COMMON_VARIABLE
    //uint32_t size; /*Size of static binary space*/
    //uint8_t* memory; /*Spase for raw data*/
    uint32_t err_cnt;
    uint32_t push_cnt;
    uint32_t delete_cnt;
    bool init;
} SetItem_t;

#ifdef __cplusplus
}
#endif

#endif /* SET_TYPEES_H */


