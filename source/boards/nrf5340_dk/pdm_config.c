#include "pdm_config.h"

#include <complex.h>

#include "data_utils.h"
#include "pdm_const.h"
#include "clock_utils.h"

#define PDM_TRACK_CNT 1
#define PDM_MEM_SIZE (PDM_SAMPLE_COUNT*PDM_CHANNEL_BYTE*PDM_TRACK_CNT)

static int16_t pcm_buf[PDM_MEM_SIZE];
static double complex DftMem[PDM_SAMPLE_COUNT];

#if(32768 < PDM_SAMPLES_CNT_DEFAULT)
#error read 7.22.8.24 SAMPLE.MAXCNT
#endif

// only 16kHz 16bit mono/stereo
const PdmConfig_t PdmConfig[] = {
#ifdef HAS_PDM0
    {
        .num = 0,
        .edge = PDM_EDGE_LEFT_FALLING, //.edge = PDM_EDGE_LEFT_FALLING, PDM_EDGE_LEFT_RISING
        .valid = true,
        .sample_rate_hz = 16000,/*only option for NRF5340*/
        .pcm_bit = 16, /*only option for NRF5340*/
        .name = "PDM0",
        .on = false,
        .mic_mode = MIC_MODE_SINGLE,
        .pdm_mode = PDM_MODE_MONO,
	    .buf = pcm_buf,
	    .samples_cnt = ARRAY_SIZE(pcm_buf) / 2,
        .frequency_hz = (uint32_t) MHZ_2_HZ(1.0),
        .irq_priority = 7,
        .Gain =
            {
                .left = 79,
                .right = 79,
            },
        .ratio = 64,
        .master_clk = PDM_MASTER_CLK_CPU_PLL,
        .PadClk =
            {
                .port = 1,
                .pin = 10,
            },
        .PadDin =
            {
                .port = 1,
                .pin = 11,
            },
    },
#endif
};

PdmHandle_t PdmInstance[] = {
#ifdef HAS_PDM0
    {
        .num = 0,
        .valid = true,
        .buf = pcm_buf,
        .dft_mem = DftMem,
        .samples_cnt = ARRAY_SIZE(pcm_buf) / 2,
    },
#endif
};

uint32_t pdm_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PdmInstance);
    cnt2 = ARRAY_SIZE(PdmConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
