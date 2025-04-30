#include "spi_config.h"

#include "data_utils.h"
#include "spi_types.h"
//#include "c_defines_generated.h" //Just for macro highlight

/*constant compile-time known settings*/
const SpiConfig_t SpiConfig[] = {
#ifdef HAS_SPI3
    {.num = 3,
     .name = "DWS3000",
     .irq_priority=1,
     .polarity=SPI_POLARITY_LATCH_RISING,
     .phase = SPI_PHASE_0,
     .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
     //.base_addr=0x?????;
     .chip_select = SPI_CHIP_SEL_SW,
     .bit_rate_hz = 8000000,

     .PadSck = {.port=0, .pin=8},
     .PadCs = {.port=1, .pin=12},
     .PadMosi = {.port=0, .pin=9},
     .PadMiso = {.port=0, .pin=10},
     .valid = true,
    },
#endif /*HAS_SPI3*/

#ifdef HAS_SPI4
    {.num = 4,
     .name = "SPI4",
     .irq_priority = 1,
     .polarity = SPI_POLARITY_LATCH_RISING,
     .phase = SPI_PHASE_0,
     .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
     //.base_addr=0x?????;
     .chip_select = SPI_CHIP_SEL_SW,
     .bit_rate_hz = 100000,
     .PadSck = {.port = 0, .pin = 8},
     .PadCs = {.port = 0, .pin = 11},
     .PadMosi = {.port = 0, .pin = 9},
     .PadMiso = {.port = 0, .pin = 10},
     .valid = true,
    },
#endif /*HAS_SPI4*/
};

SpiHandle_t SpiInstance[] = {
#ifdef HAS_SPI3
    {.num = 3, .valid = true, },
#endif /*HAS_SPI3*/

#ifdef HAS_SPI4
    {.num = 4, .valid = true, },
#endif /*HAS_SPI4*/
};

uint32_t spi_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SpiInstance);
    cnt2 = ARRAY_SIZE(SpiConfig); 
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
