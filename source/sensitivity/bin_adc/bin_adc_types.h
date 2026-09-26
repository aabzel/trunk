#ifndef BIN_ADC_TYPES_H
#define BIN_ADC_TYPES_H

#include "std_includes.h"
#include "dma_channel_general_types.h"
#include "gpio_types.h"
#include "bin_adc_const.h"

#ifdef HAS_BIN_ADC_CUSTOM
#include "bin_adc_custom_types.h"
#else
#define BIN_ADC_CUSTOM_VARIABLES
#endif

#define BIN_ADC_COMMON_VARIABLES                       \
    char* name;                                        \
    bool on_off;                                       \
    uint8_t num;                                       \
    uint8_t timer_num;                                 \
    uint32_t sample_freq_hz;                           \
    volatile uint16_t* GpioPortDataArray;              \
    uint32_t data_array_size;                          \
    DmaInfoChannel_t DmaChPad;                         \
    Pad_t debugPad;                                    \
    Pad_t inPad;                                       \
    bool valid;

typedef struct {
    BIN_ADC_COMMON_VARIABLES
}BinAdcConfig_t;

typedef struct {
    BIN_ADC_COMMON_VARIABLES
    BIN_ADC_CUSTOM_VARIABLES
    bool busy;
    bool init;
    uint32_t busy_cnt;
    uint32_t start_cnt;
    uint32_t spin;
}BinAdcHandle_t;


#endif /* BIN_ADC_TYPES_H */
