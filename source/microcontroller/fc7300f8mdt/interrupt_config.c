#include "interrupt_config.h"

#include "sys_config.h"
#include "data_utils.h"

#define  INTERRUPT_CONFIG_ADC

#define  INTERRUPT_CONFIG_DMA


#define INTERRUPT_CONFIG_UART                                                    \
    { .irq_n = FCUART1_IRQn, .on_off = true,  .valid = true, .priority = 7, },   \
    { .irq_n = FCUART2_IRQn, .on_off = true,  .valid = true, .priority = 7, },   \
    { .irq_n = FCUART3_IRQn, .on_off = true,  .valid = true, .priority = 7, },


#define INTERRUPT_CONFIG_TMR_CH


#define INTERRUPT_CONFIG_TIMER0


#define INTERRUPT_CONFIG_TIMER1

#define INTERRUPT_CONFIG_TIMER2

#define INTERRUPT_CONFIG_TIMER5


#define INTERRUPT_CONFIG_TIMER4


#define INTERRUPT_CONFIG_TIMER3

#define INTERRUPT_CONFIG_TIMER    \
    INTERRUPT_CONFIG_TMR_CH  \
    INTERRUPT_CONFIG_TIMER0   \
    INTERRUPT_CONFIG_TIMER1   \
    INTERRUPT_CONFIG_TIMER2   \
    INTERRUPT_CONFIG_TIMER3   \
    INTERRUPT_CONFIG_TIMER4   \
    INTERRUPT_CONFIG_TIMER5




#define INTERRUPT_CONFIG_CAN0
#define INTERRUPT_CONFIG_CAN1
#define INTERRUPT_CONFIG_CAN2
#define INTERRUPT_CONFIG_CAN3
#define INTERRUPT_CONFIG_CAN4
#define INTERRUPT_CONFIG_CAN5
#define INTERRUPT_CONFIG_CAN6
#define INTERRUPT_CONFIG_CAN7
#define INTERRUPT_CONFIG_CAN8
#define INTERRUPT_CONFIG_CAN9
#define INTERRUPT_CONFIG_CAN10

#define INTERRUPT_CONFIG_CAN   \
    INTERRUPT_CONFIG_CAN0  \
    INTERRUPT_CONFIG_CAN1  \
    INTERRUPT_CONFIG_CAN2  \
    INTERRUPT_CONFIG_CAN3  \
    INTERRUPT_CONFIG_CAN4  \
    INTERRUPT_CONFIG_CAN5  \
    INTERRUPT_CONFIG_CAN6  \
    INTERRUPT_CONFIG_CAN7  \
    INTERRUPT_CONFIG_CAN8  \
    INTERRUPT_CONFIG_CAN9  \
    INTERRUPT_CONFIG_CAN10


#define INTERRUPT_CONFIG_I2C


#define INTERRUPT_CONFIG_GPIO

#define INTERRUPT_CONFIG_SPI


#define INTERRUPT_CONFIG_RESERVED

const InterruptConfig_t InterruptConfig[] ={
#if 0
    { .irq_n = NMI_IRQn, .on_off = false,  .valid = true, .name ="NMI", .priority = 7, },
    { .irq_n = HardFault_IRQn, .on_off = false,  .valid = true, .name ="HardFault", .priority = 7, },
    { .irq_n = NotAvail_IRQn, .on_off = false,  .valid = true, .name ="NotAvail", .priority = 7, },
    { .irq_n = MemManage_IRQn, .on_off = false,  .valid = true, .name ="MemManage", .priority = 7, },
    { .irq_n = UsageFault_IRQn, .on_off = false,  .valid = true, .name ="UsageFault", .priority = 7, },
    { .irq_n = SVC_IRQn, .on_off = false,  .valid = true, .name ="SVC", .priority = 7, },
    { .irq_n = BusFault_IRQn, .on_off = false,  .valid = true, .name ="BusFault", .priority = 7, },
    { .irq_n = DebugMon_IRQn, .on_off = false,  .valid = true, .name ="DebugMon", .priority = 7, },
    { .irq_n = PendSV_IRQn, .on_off = false,  .valid = true, .name ="PendSV", .priority = 7, },
#endif
    { .irq_n = SysTick_IRQn, .on_off = true,  .valid = true, .priority = 7,    },
    { .irq_n = MB_IRQn, .on_off = true,  .valid = true, .priority = 7,    },
   INTERRUPT_CONFIG_UART \
   INTERRUPT_CONFIG_CAN     \
   INTERRUPT_CONFIG_DMA \
   INTERRUPT_CONFIG_I2C \
   INTERRUPT_CONFIG_ADC \
   INTERRUPT_CONFIG_GPIO \
   INTERRUPT_CONFIG_SPI \
   INTERRUPT_CONFIG_RESERVED \
   INTERRUPT_CONFIG_TIMER    \

};


uint32_t interrupt_get_cnt(void) {
    uint32_t cnt =0;
    cnt = ARRAY_SIZE(InterruptConfig);
    return cnt;

}
