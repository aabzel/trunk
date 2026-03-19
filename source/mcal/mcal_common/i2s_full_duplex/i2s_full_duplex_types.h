#ifndef I2S_FULL_DUPLEX_H
#define I2S_FULL_DUPLEX_H

#include "std_includes.h"

#include "i2s_full_duplex_const.h"
#include "audio_types.h"
#include "gpio_types.h"

#define I2S_FULL_DUPLEX_COMMON_VARIABLES     \
    bool valid;                              \
    char* name;                              \
    Pad_t DebugPadTx;                        \
    Pad_t DebugPadRx;                        \
    uint8_t num;                             \
    uint8_t echo_effect_num;                 \
    uint8_t timer_num;                       \
    uint8_t i2s_tx_num;                      \
    uint8_t i2s_rx_num;


typedef struct {
    I2S_FULL_DUPLEX_COMMON_VARIABLES
}I2sFullDuplexConfig_t;

#define I2S_FULL_DUPLEX_ISR_VARIABLES                 \
    volatile SampleType_t Buffer[I2S_COMMON_BUFFER_CHANNELS_CNT];              \
    volatile uint32_t proc_cnt;                 \
    volatile uint32_t start_cnt;                \
    volatile uint32_t stop_cnt;                 \
    volatile uint32_t tx_done_cnt;              \
    volatile uint32_t rx_done_cnt;              \
    volatile uint32_t tx_half_cnt;              \
    volatile uint32_t rx_half_cnt;              \
    volatile uint32_t last_input_time_stamp;    \
    volatile I2sFullDuplexInputs_t input;       \
    volatile I2sFullDuplexState_t state;

typedef struct {
    I2S_FULL_DUPLEX_COMMON_VARIABLES
	I2S_FULL_DUPLEX_ISR_VARIABLES
    I2sFullDuplexState_t prev_state;
    bool init_done;
    bool on_off;
    uint32_t error_cnt;
} I2sFullDuplexHandle_t;

#endif /* I2S_FULL_DUPLEX_H */
