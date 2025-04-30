#include "bpsk_config.h"

#include "data_utils.h"
#include "bpsk_const.h"
#include "dsp_const.h"

const BpskConfig_t BpskConfig[] = {
    {
        .amplitude = 30000,
        .bit_rate = 16, // 50-100-to fast for audio
        .LogFileName = "BpskDecodeLog.csv",
        .dds_num = 1,
        .quadrature_mixer_num = 1,
        .pid_phase_err_num = 1,
        .name = "BPSK1",
        .bit_order = BIT_ORDER_MSB,
        .decimator_num = 1,
        .carrier_frequency_hz = 1000,
        .filter_loop_num = 4,
        .filter_loop_cuf_off_freq_hz = 5,
        .filter_loop_type = DSP_FILTER_TYPE_IIR,
        .filter_order = 400,
        .num = 1,
        .sample_size_bit = 16,
        .sampling_frequency_hz = 44100,
        .valid = true,
    },
};

BpskHandle_t BpskInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t bpsk_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(BpskInstance);
    cnt2 = ARRAY_SIZE(BpskConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
