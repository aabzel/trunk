#include "pdm_config.h"

#include "data_utils.h"
#include "pdm_const.h"

static int16_t pcm_buf[PDM_SAMPLES_CNT_DEFAULT];

#if(32768 < (2 * PDM_BUF_LEN_DEFAULT))
#error read 7.22.8.24 SAMPLE.MAXCNT
#endif

// only 16kHz 16bit mono/stereo
const PdmConfig_t PdmConfig[] = {
#ifdef HAS_PDM0
    {
        .num = 0,
        .valid = true,
        .name = "PDM0",
        .on = true,
        /*Bitness*/
        .frequency_hz = 1000000,
        .irq_priority = 7,
        .Gain =
            {
                .left = 0x28,
                .right = 0x28,
            },
        .ratio = 64,
        .edge = PDM_EDGE_LEFT_FALLING,
        .master_clk = PDM_MASTER_CLK_CPU_PLL,
        .mode = PDM_MODE_MONO,
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
