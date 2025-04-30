#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif /*HAS_SPI*/

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SpiConfig[] = {
   //{.num=1 , .name="SPI1",  .bit_rate_hz=2000000, .valid=true},
   {
    .num=2 , 
    .name="SPI2",  
    .bit_rate_hz = 200000,
    .bit_order=SPI_MOST_SIGNIFICANT_BIT_FIRST,
    .polarity=SPI_POLARITY_LATCH_RISING,
    .chip_select = SPI_CHIP_SEL_SW,
    .phase=SPI_PHASE_0,
    .irq_priority=1,
    .valid=true,

    .PadSck={.port=PORT_B,  .pin=10,  },
    .PadMosi={.port=PORT_B,  .pin=15,  },
    .PadMiso={.port=PORT_B,  .pin=14,  },
   },
};


SpiHandle_t SpiInstance[] = {
    //{.num=1, .valid=true},
    {.num=2, .valid=true},
};

uint32_t spi_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SpiInstance);
    cnt2 = ARRAY_SIZE(SpiConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
