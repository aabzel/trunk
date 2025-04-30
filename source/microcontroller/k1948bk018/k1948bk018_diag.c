#include "k1948bk018_diag.h"

#include "interrupt_types.h"
#include "interrupt_diag.h"
#include "macro_utils.h"

static const IntNumInfo_t IntNameLut[]={
    {.name="Timer32_0", .int_n = 0,},
    {.name="USART_0", .int_n = 1,},
    {.name="USART_1", .int_n = 2,},
    {.name="SPI_0", .int_n = 3,},
    {.name="SPI_1", .int_n = 4,},
    {.name="GPIO", .int_n = 5,},
    {.name="I2C_0", .int_n = 6,},
    {.name="I2C_1", .int_n = 7,},
    {.name="WDT", .int_n = 8,},
    {.name="Timer16_0", .int_n = 9,},
    {.name="Timer16_1", .int_n = 10, },
    {.name="Timer16_2", .int_n = 11, },
    {.name="Timer32_1", .int_n = 12, },
    {.name="Timer32_2", .int_n = 13, },
    {.name="SPIFI", .int_n = 14, },
    {.name="RTC", .int_n = 15, },
    {.name="EEPROM", .int_n = 16, },
    {.name="WDT_BUS", .int_n = 17, },
    {.name="SPIFI", .int_n = 18, },
    {.name="EEPROM", .int_n = 19, },
    {.name="DMA", .int_n = 20, },
    {.name="CLK_MON", .int_n = 21, },
    {.name="AVCC", .int_n = 22, },
    {.name="AVCC", .int_n = 23, },
    {.name="VCC_Lo", .int_n = 24, },
    {.name="VCC_Hi", .int_n = 25, },
    {.name="BAT_lo", .int_n = 26, },
    {.name="BrouwnOut", .int_n = 27, },
    {.name="Temp", .int_n = 28, },
    {.name="ADC", .int_n = 29, },
    {.name="DAC0", .int_n = 30, },
    {.name="DAC1", .int_n = 31, },
};

const char* InterruptNumToStr(int16_t int_n){
    const char* name = "?";
    uint32_t i = 0;
    for(i=0; i<ARRAY_SIZE(IntNameLut); i++) {
        if(int_n==IntNameLut[i].int_n){
            name=IntNameLut[i].name;
			break;
        }
    }
    return name;
}

bool k1948bk018_diag(void){
	bool res = false ;
    return res;
}
