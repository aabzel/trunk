#ifndef BIN_DAC_TYPES_H
#define BIN_DAC_TYPES_H

#include "std_includes.h"
#include "bin_dac_const.h"
#include "dma_channel_general_types.h"
#include "gpio_types.h"
#include "bit_fifo_types.h"

#ifdef HAS_BIN_DAC_CUSTOM
#include "bin_dac_custom_types.h"
#else
#define BIN_DAC_CUSTOM_VARIABLES
#endif

#define BIN_DAC_COMMON_VARIABLES                       \
    char* name;                                        \
    uint8_t timer_num;                                 \
    uint32_t part_size;                                \
    uint32_t tx_fifo_mem_size;                         \
    uint32_t sample_freq_hz;                           \
    uint32_t data_array_size;                          \
    DmaInfoChannel_t DmaChPad;                         \
    uint8_t* TxFifoMem;                                \
    uint32_t* GpioPortDataArray;                       \
    uint8_t num;                                       \
    Pad_t debugPad;                                    \
    Pad_t outPad;                                      \
    bool valid;

typedef struct {
    BIN_DAC_COMMON_VARIABLES
}BinDacConfig_t;

typedef struct {
    BIN_DAC_COMMON_VARIABLES
    BIN_DAC_CUSTOM_VARIABLES
    bool init;
    bool busy;
    uint32_t pull_error_cnt;
    uint32_t start_cnt;
    uint32_t busy_cnt;
    BitFifoHandle_t TxFifo;
    uint32_t spin;
}BinDacHandle_t;


#endif /* BIN_DAC_TYPES_H */
