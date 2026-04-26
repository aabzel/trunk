#ifndef GPIO_DAC_TYPES_H
#define GPIO_DAC_TYPES_H

#include "std_includes.h"
#include "gpio_dac_const.h"
#include "gpio_types.h"
#include "fifo_char_types.h"

#define GPIO_DAC_COMMON_VARIABLES                  \
    char* name;                                    \
    uint8_t num;                                   \
    Pad_t PadOut;                                  \
    uint8_t timer_num;                             \
    uint32_t sample_freq_hz;                       \
    bool valid;

typedef struct {
    GPIO_DAC_COMMON_VARIABLES
}GpioDacConfig_t;

typedef struct {
    GPIO_DAC_COMMON_VARIABLES
    bool init;
    uint32_t spin;
    FifoChar_t TxFiFo;
}GpioDacHandle_t;


#endif /* GPIO_DAC_TYPES_H */
