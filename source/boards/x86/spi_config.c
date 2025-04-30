#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif /*HAS_SPI*/

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SpiConfig[] = {
};

SpiHandle_t SpiInstance[] = {
};

uint32_t spi_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SpiInstance);
    cnt2 = ARRAY_SIZE(SpiConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
