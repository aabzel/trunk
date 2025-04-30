#ifndef DTMF_IF_TYPES_H
#define DTMF_IF_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "dtmf_const.h"
#include "audio_types.h"

#define DTMF_COMMON_VAR         \
    uint8_t i2s_num;            \
    uint8_t dac_num;            \
    uint8_t num;                \
    SampleType_t amplitude;     \
    bool valid;

typedef struct {
    DTMF_COMMON_VAR
    char *name;
}DtmfConfig_t;

typedef struct {
    DTMF_COMMON_VAR
    SampleType_t* tx_sample;
    bool debug;
}DtmfHandle_t;

typedef struct {
    char letter;
    uint8_t code;
    uint16_t freq_small_hz;
    uint16_t freq_big_hz;
    uint32_t min_period_ns;
}DtmfKeyPadFreq_t;


#endif /* DTMF_IF_TYPES_H  */
