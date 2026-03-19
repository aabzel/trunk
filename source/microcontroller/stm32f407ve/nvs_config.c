#include "nvs_config.h"
#include "macro_utils.h"

const NvsConfig_t  SECTION_CFG_DATA NvsConfig[] = {
    {
        .start = NVS_START,
        .size = NVS_SIZE,
        .num = 1,
        .valid = true,
        .name = "NVS",
    },
};

NvsHandle_t NvsInstance[] = {
        {
          .start = NVS_START,
          .size = NVS_SIZE,
          .num = 1,
          .valid = true,
        },
};


const uint8_t SECTION_NVRAM nvram_memory[NVS_SIZE]= { [0 ... (NVS_SIZE-1)] = 0xFF };

uint32_t nvs_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(NvsConfig);
    cnt2 = ARRAY_SIZE(NvsInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
