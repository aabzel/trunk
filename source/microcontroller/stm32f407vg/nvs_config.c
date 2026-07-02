#include "nvs_config.h"

#include "macro_utils.h"
#include "data_utils.h"

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
        .num = 1,
        .start = NVS_START,
        .size = NVS_SIZE,
        .valid = true,
    },
};


const uint8_t SECTION_NVRAM nvram_memory[NVS_SIZE]= { [0 ... (NVS_SIZE-1)] = 0xFF };

COMPONENT_GET_CNT(Nvs, nvs)
