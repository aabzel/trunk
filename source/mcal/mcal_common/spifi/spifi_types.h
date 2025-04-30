#ifndef SPIFI_COMMON_TYPES_H
#define SPIFI_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "spifi_const.h"
#include "sys_config.h"
#include "spifi_custom_types.h"

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif /*HAS_SPIFI*/

#define SPIFI_COMMON_VARIABLES                                  \
    uint8_t num;                                                \
    bool cache_on_off;                                          \
    uint32_t bit_rate_hz;                                       \
    uint32_t cache_limit;                                       \
    bool valid;

/* TODO Add Array of SPI-Flash ASIC OpCodes */

typedef struct {
    SPIFI_COMMON_VARIABLES
#ifdef HAS_LOG
    char* name;
#endif
} SpiFiConfig_t;

#define SPIFI_ISR_RX_VARIABLES

#define SPIFI_ISR_TX_VARIABLES

#define SPIFI_ISR_COMMON_VARIABLES                     \
    SPIFI_ISR_RX_VARIABLES                             \
    SPIFI_ISR_TX_VARIABLES

typedef struct {
    SPIFI_COMMON_VARIABLES
    SPIFI_CUSTOM_VARIABLES
    SPIFI_ISR_COMMON_VARIABLES
    bool init_done;
    IRQn_Type irq_n;
} SpiFiHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* SPIFI_COMMON_TYPES_H */
