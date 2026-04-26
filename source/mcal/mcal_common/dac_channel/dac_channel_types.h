#ifndef DAC_CHANNEL_MCAL_TYPES_H
#define DAC_CHANNEL_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_channel_const.h"
#include "dac_const.h"
#include "gpio_types.h"
#include "lib_iqueue.h"

#ifdef HAS_DAC_CHANNEL_CUSTOM
#include "dac_channel_custom_types.h"
#else
#define DAC_CHANNEL_CUSTOM_VARIABLES
#endif

typedef union {
    uint8_t byte;
    struct {
        uint8_t dac_num:2; /* 0, 1, 2, 3*/
        uint8_t channel:5; /* 0, 1, 2, 3, 4, 5 ...    31 */
    };
} DacPad_t;

#define DAC_CHANNEL_COMMON_VARIABLES                       \
    uint8_t dac_num; /*DAC number*/                        \
    uint8_t dds_num;                                       \
    DacChannel_t channel;                                  \
    DacMode_t mode;                                        \
    float scale; /*   1.0/volt_div   */                    \
    Pad_t Pad;                                             \
    uint8_t num;                                           \
    uint32_t SampleFifoMemCnt;                             \
    uint16_t * SampleFifoMem;                              \
    bool valid;                                            \
    char* name;

typedef struct {
    DAC_CHANNEL_COMMON_VARIABLES
} DacChannelConfig_t;

typedef struct {
    DAC_CHANNEL_COMMON_VARIABLES
    DAC_CHANNEL_CUSTOM_VARIABLES
    float voltage;
    float voltage_real;
    bool new_val;
    uint32_t code;
    uint32_t read_cnt;
    iqueue_t iQueue;
    uint32_t err_cnt;
    uint32_t spin_cnt;
    bool init_done;
} DacChannelHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* DAC_MCAL_TYPES_H  */
