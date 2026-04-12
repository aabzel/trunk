#include "dma_config.h"

#include "data_utils.h"

const DmaConfig_t DmaConfig[] = {
};

DmaHandle_t DmaInstance[] = {
};

uint32_t dma_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaInstance);
    cnt2 = ARRAY_SIZE(DmaConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}



