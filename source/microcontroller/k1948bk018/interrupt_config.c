#include "interrupt_config.h"

#include "sys_config.h"
#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif


#ifdef HAS_K1948BK018
#include "K1948BK018.h"
#endif

#define  INTERRUPT_CONFIG_ADC        \
   { .name="ADC", .irq_n=INT_NUM_ADC, .priority=0, .on_off=false,},

#define  INTERRUPT_CONFIG_DAC      \
   { .name="DAC0", .irq_n=INT_NUM_DAC0, .priority=0, .on_off=false,},      \
   { .name="DAC1", .irq_n=INT_NUM_DAC1, .priority=0, .on_off=false,},

#define  INTERRUPT_CONFIG_DMA      \
   { .name="DMA", .irq_n=INT_NUM_DMA, .priority=0, .on_off=false,},

#define  INTERRUPT_CONFIG_UART      \
   {  .irq_n = INT_NUM_USART_0, .priority=0, .on_off=false,},    \
   {  .irq_n = INT_NUM_USART_1, .priority=0, .on_off=true,},




#define INTERRUPT_CONFIG_TIMER0    \
   { .name="TIMER32_0", .irq_n=INT_NUM_TIMER32_0, .priority=0, .on_off=false,},    \
   { .name="TIMER16_0", .irq_n=INT_NUM_TIMER16_0, .priority=0, .on_off=false,},

#define INTERRUPT_CONFIG_TIMER1    \
   { .name="TIMER16_1", .irq_n=INT_NUM_TIMER16_1, .priority=0, .on_off=false,},    \
   { .name="TIMER32_1", .irq_n=INT_NUM_TIMER32_1, .priority=0, .on_off=false,},

#define INTERRUPT_CONFIG_TIMER2    \
   { .name="TIMER16_2", .irq_n=INT_NUM_TIMER16_2, .priority=0, .on_off=false,},    \
   { .name="TIMER32_2", .irq_n=INT_NUM_TIMER32_2, .priority=0, .on_off=false,},


#define INTERRUPT_CONFIG_TIMER    \
    INTERRUPT_CONFIG_TIMER0   \
    INTERRUPT_CONFIG_TIMER1   \
    INTERRUPT_CONFIG_TIMER2


#define INTERRUPT_CONFIG_I2C      \
   { .name="I2C_1", .irq_n=INT_NUM_I2C_1, .priority=0, .on_off=false,},      \
   { .name="I2C_0", .irq_n=INT_NUM_I2C_0, .priority=0, .on_off=false,},

#define INTERRUPT_CONFIG_GPIO      \
   { .name="GPIO", .irq_n=INT_NUM_GPIO, .priority=0, .on_off=false,},

#define INTERRUPT_CONFIG_SPI    \
   { .name="SPI_1", .irq_n=INT_NUM_SPI_1, .priority=0, .on_off=false,},  \
   { .name="SPI_0", .irq_n=INT_NUM_SPI_0, .priority=0, .on_off=false,},


#define INTERRUPT_CONFIG_WDT      \
   { .name="WDT", .irq_n=INT_NUM_WDT, .priority=0, .on_off=false,},      \
   { .name="WDT_PER", .irq_n=INT_NUM_WDT_PER, .priority=0, .on_off=false,},      \
   { .name="WDT_SPIFI", .irq_n=INT_NUM_WDT_SPIFI, .priority=0, .on_off=false,},      \
   { .name="WDT_EEPROM", .irq_n=INT_NUM_WDT_EEPROM, .priority=0, .on_off=false,},

#define INTERRUPT_CONFIG_POWER      \
   { .name="AVCC_LOW", .irq_n=INT_NUM_AVCC_LOW, .priority=0, .on_off=false,},      \
   { .name="AVCC_UP", .irq_n=INT_NUM_AVCC_UP, .priority=0, .on_off=false,},      \
   { .name="VCC_LOW", .irq_n=INT_NUM_VCC_LOW, .priority=0, .on_off=false,},      \
   { .name="VCC_UP", .irq_n=INT_NUM_VCC_UP, .priority=0, .on_off=false,},      \
   { .name="BAT_LOW", .irq_n=INT_NUM_BAT_LOW, .priority=0, .on_off=false,},      \
   { .name="BROUWN_OUT", .irq_n=INT_NUM_BROUWN_OUT, .priority=0, .on_off=false,},

const InterruptConfig_t InterruptConfig[] ={
#if 0
   { .name="CLK_MON", .irq_n=INT_NUM_CLK_MON, .priority=0, .on_off=false,},      \
   { .name="RTC", .irq_n=INT_NUM_RTC, .priority=0, .on_off=false,},      \
   { .name="SPIFI", .irq_n=INT_NUM_SPIFI, .priority=0, .on_off=false,},      \
   { .name="EEPROM", .irq_n=INT_NUM_EEPROM, .priority=0, .on_off=false,},      \
   { .name="TEMP", .irq_n=INT_NUM_TEMP, .priority=0, .on_off=false,}, \
   INTERRUPT_CONFIG_ADC \
   INTERRUPT_CONFIG_DMA \
   INTERRUPT_CONFIG_I2C \
   INTERRUPT_CONFIG_DAC \
   INTERRUPT_CONFIG_GPIO \
   INTERRUPT_CONFIG_WDT \
   INTERRUPT_CONFIG_SPI \
   INTERRUPT_CONFIG_POWER \
   INTERRUPT_CONFIG_TIMER
#endif
   INTERRUPT_CONFIG_UART
};



uint32_t interrupt_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(InterruptConfig);
    return cnt;
}
