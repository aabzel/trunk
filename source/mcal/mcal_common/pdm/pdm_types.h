#ifndef PDM_TYPES_H
#define PDM_TYPES_H

#include <complex.h>
#include <stdbool.h>
#include <stdint.h>

#include "audio_types.h"
#include "gpio_types.h"
#include "pdm_const.h"
#include "pdm_dep.h"

#ifdef HAS_PDM_CUSTOM
#include "pdm_custom_types.h"
#endif /*HAS_PDM_CUSTOM*/

typedef struct {
    Gain_t left;
    Gain_t right;
} PdmGain_t;

#define PDM_COMMON_VARIABLES                                                                                           \
    uint8_t num;                                                                                                       \
    bool valid;                                                                                                        \
    uint32_t samples_cnt;                                                                                              \
    uint32_t sample_rate_hz;                                                                                           \
    uint8_t pcm_bit;                                                                                                   \
    MicMode_t mic_mode;

typedef struct {
    PDM_COMMON_VARIABLES
    uint32_t frequency_hz;
    char name[10];
    PdmMasterClk_t master_clk;
    PdmEdge_t edge;
    uint8_t ratio;
    PdmMode_t pdm_mode;
    PdmGain_t Gain;
    bool on;
    uint8_t irq_priority;
    int16_t* const buf;
    Pad_t PadClk;
    Pad_t PadDin;
} PdmConfig_t;

typedef struct {
    PDM_COMMON_VARIABLES
    bool in_isr;
    bool init_done;
    volatile bool rx_done;
    volatile uint32_t error_cnt;
    volatile uint32_t int_cnt;
    volatile uint32_t rx_sample_cnt;
    volatile uint8_t buf_toogle;
    volatile int16_t* buf;
    uint32_t start_cnt;
    uint32_t stop_cnt;
    double complex* dft_mem;
    double max_freq;
} PdmHandle_t;

#endif /* PDM_TYPES_H */
