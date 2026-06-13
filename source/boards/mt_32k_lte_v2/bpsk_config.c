#include "bpsk_config.h"

#include "data_utils.h"
#include "bpsk_const.h"
#include "dsp_const.h"

const BpskConfig_t BpskConfig[] = {
    {
        .amplitude = 30000,
        .bit_rate = 100, // 50-100-to fast for audio
        .LogFileName = "BpskDecodeLog.csv",
        .dds_num = 1,
        .quadrature_mixer_num = 1,
        .pid_phase_err_num = 1,
        .name = "BPSK1",
        .bit_order = BIT_ORDER_MSB,
        .decimator_num = 1,
        .carrier_frequency_hz = 2000,
        .filter_loop_num = 4,
        .filter_loop_cuf_off_freq_hz = 200,
        .filter_loop_type = DSP_FILTER_TYPE_IIR,
        .filter_order = 400,
        .num = 1,
        .sample_size_bit = 16,
        .sampling_frequency_hz = 8000,
        .valid = true,
    },
};

BpskHandle_t BpskInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Bpsk,bpsk)
