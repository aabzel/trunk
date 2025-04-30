#ifndef CRYPTO_TYPES_H
#define CRYPTO_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#ifndef HAS_CRYP
#error "Add HAS_CRYP"
#endif

#include "aes256_cbc_types.h"
#include "cryp_const.h"

#define CRYP_COMMON_VARIABLES   \
    uint8_t num;                \
    CrypKeySize_t key_size;     \
    CrypAlgorithm_t algo;       \
    bool valid;                 \
    AlgImpl_t algo_impl;

typedef struct {
    CRYP_COMMON_VARIABLES
    char name[10];
    char* init_vector;
} CrypConfig_t;

typedef struct  {
    CRYP_COMMON_VARIABLES
    uint32_t error_cnt;
    volatile uint32_t int_cnt;
    volatile uint32_t int_flag;
    volatile uint32_t in_cnt;
    volatile uint32_t out_cnt;
    uint8_t key32byte[32];
    uint32_t Key256BitQwords[8];
    uint32_t InitVectorQwords[4];
    uint8_t init_vector[16];
    bool init_done;

#ifdef HAS_CRYP_HW
    CRYP_ConfigTypeDef Conf;
    volatile CRYP_HandleTypeDef cryp_h;
#endif /*HAS_CRYP_HW*/

#ifdef HAS_AES256
    AES_ctx ctx;
#endif /*HAS_AES256*/
} CrypHandle_t;

#endif /* CRYPTO_TYPES_H */
