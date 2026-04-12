#include "dma_channel_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#ifdef HAS_SPI
#include "spi_mcal.h"
#include "spi_isr.h"
#endif


const DmaChannelConfig_t DmaChannelConfig[] = {

};

volatile DmaChannelHandle_t DmaChannelInstance[] = {

};

uint32_t dma_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaChannelInstance);
    cnt2 = ARRAY_SIZE(DmaChannelConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
