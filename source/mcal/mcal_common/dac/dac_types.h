#ifndef DAC_COMMON_TYPES_H
#define DAC_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dac_const.h"
#include "dac_custom_types.h"
#include "sys_config.h"

#define DAC_COMMON_VARIABLES                                                                                           \
    uint8_t num;                                                                                                       \
    uint32_t bit_rate_hz;                                                                                              \
    bool valid;

typedef struct {
    DAC_COMMON_VARIABLES
    // uint32_t base_addr;
    char* name;
    bool interrupt_on;
#ifdef HAS_GPIO
    Pad_t Pad; /*Some MCU DAC has HW chip select capability*/
#endif /*HAS_GPIO*/
} DacConfig_t;

#define DAC_ISR_VARIABLES                          \
    volatile bool tx_done;                         \
    volatile uint32_t error_cnt;                   \
    volatile uint32_t tx_cnt;                      \
    volatile uint32_t it_cnt;

typedef struct {
    DAC_COMMON_VARIABLES

    DAC_ISR_VARIABLES

    DAC_CUSTOM_VARIABLES

    uint32_t base_addr;

    bool init_done;
} DacHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* DAC_COMMON_TYPES_H */
