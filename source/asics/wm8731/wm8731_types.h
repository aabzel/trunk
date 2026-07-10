#ifndef WM8731_TYPES_H
#define WM8731_TYPES_H

#include <stddef.h>

#include "audio_types.h"
#include "std_includes.h"
#include "wm8731_const.h"
#include "wm8731_reg_types.h"

typedef struct {
    uint8_t reg_addr;
    char* name;
} Wm8731Reg_t;

typedef struct {
    uint8_t reg_addr; // register I2S address
    Wm8731RegGeneral_t value; // register value
} Wm8731RegConfig_t;

#define WM8731_COMMON_VARIABLES                                                           \
    bool valid;                                                                           \
    char* const name;                                                                     \
    uint8_t num;                                                                          \
    uint8_t chip_addr;                                                                    \
    uint8_t i2s_rx_num;                                                                   \
    uint8_t i2s_tx_num;                                                                   \
    AudioFreq_t audio_freq_hz;                                                            \
    Wm8731Mode_t mode;                                                                    \
    Wm8731RegConfig_t* RegArray;                                                          \
    uint32_t reg_cnt;                                                                     \
    uint8_t dds_num;                                                                      \
    uint8_t i2c_num;                                                                      \
    int8_t left;                                                                          \
    int8_t right;

typedef struct {
    WM8731_COMMON_VARIABLES
} Wm8731Config_t;

typedef struct {
    WM8731_COMMON_VARIABLES
    int8_t cur_volume;
    Wm8731State_t state;
    uint32_t rec_off_time_stamp_ms;
    uint32_t play_off_time_stamp_ms;
    bool init;
} Wm8731Handle_t;

#endif /* WM8731_TYPES_H */
