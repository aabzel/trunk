#include "interrupt_config.h"
#include "sys_config.h"

#include "data_utils.h"


#define  INTERRUPT_CONFIG_DMA

#define INTERRUPT_CONFIG_UART


#define INTERRUPT_CONFIG_TIMER


#define INTERRUPT_CONFIG_EXINT

#define INTERRUPT_CONFIG_CAN


#define INTERRUPT_CONFIG_I2C

#define INTERRUPT_CONFIG_SPI

#define INTERRUPT_CONFIG_USB

const InterruptConfig_t InterruptConfig[] ={
    { .irq_n = SPI2_IRQn, .priority = 1, .on_off = true, .valid = true, },
    { .irq_n = USART1_IRQn, .priority = 4, .on_off = true, .valid = true, },
    { .irq_n = USART2_IRQn, .priority = 3, .on_off = true, .valid = true, },
    { .irq_n = USART6_IRQn, .priority = 4, .on_off = true, .valid = true, },
    { .irq_n = SysTick_IRQn, .priority = 1, .on_off = true, .valid = true, },
};



uint32_t interrupt_get_cnt(void) {
    uint32_t cnt =0;
    cnt =ARRAY_SIZE(InterruptConfig);
    return cnt;
}


const IntNumInfo_t IntNumInfo[] = {

};

uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}

