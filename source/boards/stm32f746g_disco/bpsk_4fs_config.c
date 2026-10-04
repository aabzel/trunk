#include "bpsk_4fs_config.h"

#include "data_utils.h"
#include "bpsk_4fs_const.h"
#include "dsp_const.h"
#include "code_generator.h"

static uint8_t RxDataArray[5] = {0};

const Bpsk4fsConfig_t Bpsk4fsConfig[] = {
    {
        .num = 1,
        .bit_rx_phase = 0,
        .valid = true,
        .adc_num = 1,
        .dc_cut_filter_num = 1,
        .BinDataArray = RxDataArray,
        .data_size_bytes = ARRAY_SIZE(RxDataArray),
        .bit_rate = 25, // 50-100-to fast for audio
        .pid_num = 1,
        .name = "Bpsk4fs1",
        .bit_order = BIT_ORDER_MSB,
        .quad_mix_4fs_num = 1,
        .decimator_num = 1,
        .carrier_frequency_hz = 250,
        .sampling_frequency_hz = 1000,
        .filter_loop_type = DSP_FILTER_TYPE_SAMPLE_SUM,
        .sample_size_bit = 32,
        .PadData = {.port=PORT_E, .pin=1,},
        .PadClk = {.port=PORT_E, .pin=4,},

        .amplitude = 1,
        .pid_phase_err_num = 1,
        .filter_loop_num = 4,
        .filter_loop_cuf_off_freq_hz = 200,
        .filter_order = 10,

        .dds_num = 1,
        .LogFileName = "Bpsk4fsDecodeLog.csv",
    },
};

Bpsk4fsHandle_t Bpsk4fsInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Bpsk4fs, bpsk_4fs)
