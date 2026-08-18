#ifndef BT1026_TYPES_H
#define BT1026_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "audio_types.h"
#include "bt1026_const.h"
#include "gpio_types.h"
#include "i2s_types.h"

#ifdef HAS_LIMITER
#include "limiter.h"
#endif

#ifndef HAS_BT1026
#error "+HAS_BT1026"
#endif

#ifndef HAS_LIMITER
#error "+HAS_LIMITER"
#endif

#define BT1026_COMMON_VAR                                                                                              \
    Pad_t sys_ctrl;                                                                                                    \
    Pad_t reset;                                                                                                       \
    uint8_t uart_num;                                                                                                  \
    uint8_t i2s_num;                                                                                                   \
    uint8_t num;                                                                                                       \
    bool valid;

typedef struct {
    BT1026_COMMON_VAR
    I2sDataFormat_t digital_format;
    AudioFreq_t audio_freq;
    I2sRole_t i2s_role;
} Bt1026Config_t;

typedef struct {
    BT1026_COMMON_VAR
    char tx_text[40];
    char cur_line[BT1026_MAX_LINE_SZ];
    char fix_line[BT1026_MAX_LINE_SZ];
    uint32_t line_cnt;
    uint32_t pos;
    uint32_t digital_rate;
    uint32_t ack_cnt;
    uint32_t write_cnt;
    uint32_t ok_cnt;
    uint32_t err_cnt;
    uint32_t rx_cnt;
    uint32_t cfg_cnt;
    uint32_t spin;
    uint32_t ping_start_ms;
    uint16_t err_code;
    uint8_t i2scfg_val;
    bool ack;
    bool init;
    bool wait_ack;
    bool reboot_done;
    bool i2s_on;
#ifdef HAS_LIMITER
    // Limiter_t LinkLimiter;
    // Limiter_t DiagLimiter;
#endif /*HAS_LIMITER*/

#if defined(HAS_PCM_16_BIT) || defined(HAS_PCM_32_BIT)
    SampleType_t rx_sample[2];
    SampleType_t tx_sample[2];
#endif /*HAS_PCM_16_BIT or HAS_PCM_32_BIT*/

    I2sDataFormat_t real_digital_format;
    AudioFreq_t real_audio_freq;
    I2sRole_t real_i2s_role;
} Bt1026Handle_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t status : 1;
        uint8_t role : 1;
        uint8_t sample_rate : 1;
        uint8_t format : 2;
        uint8_t resolution : 2;
        uint8_t res : 1;
    };
} Bt1026I2sConfig_t;

#endif /* BT1026_TYPES_H */
