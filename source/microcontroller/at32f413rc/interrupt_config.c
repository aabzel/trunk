#include "interrupt_config.h"
#include "sys_config.h"

#include "data_utils.h"


#define  INTERRUPT_CONFIG_DMA   \
    { .irq_n =DMA1_Channel1_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel1", .priority = 7, },   \
    { .irq_n =DMA1_Channel2_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel2", .priority = 7, },   \
    { .irq_n =DMA1_Channel3_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel3", .priority = 7, },   \
    { .irq_n =DMA1_Channel4_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel4", .priority = 7, },   \
    { .irq_n =DMA1_Channel5_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel5", .priority = 7, },   \
    { .irq_n =DMA1_Channel6_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel6", .priority = 7, },   \
    { .irq_n =DMA1_Channel7_IRQn, .on_off = false,         .valid =true, .name ="DMA1_Channel7", .priority = 7, },   \
    { .irq_n =DMA2_Channel1_IRQn, .on_off = false,         .valid =true, .name ="DMA2_Channel1", .priority = 7, },   \
    { .irq_n =DMA2_Channel2_IRQn, .on_off = false,         .valid =true, .name ="DMA2_Channel2", .priority = 7, },   \
    { .irq_n =DMA2_Channel3_IRQn, .on_off = false,         .valid =true, .name ="DMA2_Channel3", .priority = 7, },   \
    { .irq_n =DMA2_Channel4_5_IRQn, .on_off = false,         .valid =true, .name ="DMA2_Channel4_5", .priority = 7, },   \
    { .irq_n =DMA2_Channel6_7_IRQn, .on_off = false,         .valid =true, .name ="DMA2_Channel6_7", .priority = 7, },

#define INTERRUPT_CONFIG_UART  \
    { .irq_n =USART1_IRQn, .on_off = true,         .valid =true, .name ="USART1", .priority = 7, },  \
    { .irq_n =USART2_IRQn, .on_off = false,         .valid =true, .name ="USART2", .priority = 7, },  \
    { .irq_n =USART3_IRQn, .on_off = false,         .valid =true, .name ="USART3", .priority = 7, },  \
    { .irq_n =UART4_IRQn, .on_off = false,         .valid =true, .name ="UART4", .priority = 7, },  \
    { .irq_n =UART5_IRQn, .on_off = false,         .valid =true, .name ="UART5", .priority = 7, },


#define INTERRUPT_CONFIG_TIMER    \
    { .irq_n =TMR1_BRK_TMR9_IRQn, .on_off = false,         .valid =true, .name ="TMR1_BRK_TMR9", .priority = 7, },   \
    { .irq_n =TMR1_OVF_TMR10_IRQn, .on_off = false,         .valid =true, .name ="TMR1_OVF_TMR10", .priority = 7, },   \
    { .irq_n =TMR1_TRG_HALL_TMR11_IRQn, .on_off = false,         .valid =true, .name ="TMR1_TRG_HALL_TMR11", .priority = 7, },   \
    { .irq_n =TMR1_CH_IRQn, .on_off = false,         .valid =true, .name ="TMR1_CH", .priority = 7, },   \
    { .irq_n =TMR2_GLOBAL_IRQn, .on_off = false,         .valid =true, .name ="TMR2_GLOBAL", .priority = 7, },   \
    { .irq_n =TMR3_GLOBAL_IRQn, .on_off = false,         .valid =true, .name ="TMR3_GLOBAL", .priority = 7, },   \
    { .irq_n =TMR4_GLOBAL_IRQn, .on_off = false,         .valid =true, .name ="TMR4_GLOBAL", .priority = 7, },   \
    { .irq_n =TMR5_GLOBAL_IRQn, .on_off = false,         .valid =true, .name ="TMR5_GLOBAL", .priority = 7, },   \
    { .irq_n =TMR8_BRK_IRQn, .on_off = false,         .valid =true, .name ="TMR8_BRK", .priority = 7, },   \
    { .irq_n =TMR8_OVF_IRQn, .on_off = false,         .valid =true, .name ="TMR8_OVF", .priority = 7, },   \
    { .irq_n =TMR8_TRG_HALL_IRQn, .on_off = false,         .valid =true, .name ="TMR8_TRG_HALL", .priority = 7, },   \
    { .irq_n =TMR8_CH_IRQn, .on_off = false,         .valid =true, .name ="TMR8_CH", .priority = 7, },


#define INTERRUPT_CONFIG_EXINT    \
    { .irq_n =EXINT0_IRQn, .on_off = false,         .valid =true, .name ="EXINT0", .priority = 7, },    \
    { .irq_n =EXINT1_IRQn, .on_off = false,         .valid =true, .name ="EXINT1", .priority = 7, },    \
    { .irq_n =EXINT2_IRQn, .on_off = false,         .valid =true, .name ="EXINT2", .priority = 7, },    \
    { .irq_n =EXINT3_IRQn, .on_off = false,         .valid =true, .name ="EXINT3", .priority = 7, },    \
    { .irq_n =EXINT4_IRQn, .on_off = false,         .valid =true, .name ="EXINT4", .priority = 7, },    \
    { .irq_n =EXINT9_5_IRQn, .on_off = false,         .valid =true, .name ="EXINT9_5", .priority = 7, },

#define INTERRUPT_CONFIG_CAN    \
    { .irq_n =CAN1_RX1_IRQn, .on_off = false,         .valid =true, .name ="CAN1_RX1", .priority = 7, },    \
    { .irq_n =CAN1_SE_IRQn, .on_off = false,         .valid =true, .name ="CAN1_SE", .priority = 7, },    \
    { .irq_n =USBFS_H_CAN1_TX_IRQn, .on_off = false,         .valid =true, .name ="USBFS_H_CAN1_TX", .priority = 7, },    \
    { .irq_n =USBFS_L_CAN1_RX0_IRQn, .on_off = false,         .valid =true, .name ="USBFS_L_CAN1_RX0", .priority = 7, },    \
    { .irq_n =CAN2_TX_IRQn, .on_off = false,         .valid =true, .name ="CAN2_TX", .priority = 7, },    \
    { .irq_n =CAN2_RX0_IRQn, .on_off = false,         .valid =true, .name ="CAN2_RX0", .priority = 7, },    \
    { .irq_n =CAN2_RX1_IRQn, .on_off = false,         .valid =true, .name ="CAN2_RX1", .priority = 7, },    \
    { .irq_n =CAN2_SE_IRQn, .on_off = false,         .valid =true, .name ="CAN2_SE", .priority = 7, },


#define INTERRUPT_CONFIG_I2C    \
    { .irq_n = I2C1_EVT_IRQn, .on_off = false,         .valid =true, .name ="I2C1_EVT", .priority = 7, },   \
    { .irq_n = I2C1_ERR_IRQn, .on_off = false,         .valid =true, .name ="I2C1_ERR", .priority = 7, },   \
    { .irq_n = I2C2_EVT_IRQn, .on_off = false,         .valid =true, .name ="I2C2_EVT", .priority = 7, },   \
    { .irq_n = I2C2_ERR_IRQn, .on_off = false,         .valid =true, .name ="I2C2_ERR", .priority = 7, },

#define INTERRUPT_CONFIG_SPI   \
    { .irq_n = SPI1_IRQn, .on_off = false,         .valid =true, .name ="SPI1", .priority = 7, },   \
    { .irq_n = SPI2_IRQn, .on_off = false,         .valid =true, .name ="SPI2", .priority = 7, },


#define INTERRUPT_CONFIG_USB   \
    { .irq_n = USBFSWakeUp_IRQn, .on_off = false,         .valid =true, .name ="USBFSWakeUp", .priority = 7, },   \
    { .irq_n = USBFS_MAPH_IRQn, .on_off = false,         .valid =true, .name ="USBFS_MAPH", .priority = 7, },   \
    { .irq_n = USBFS_MAPL_IRQn, .on_off = false,         .valid =true, .name ="USBFS_MAPL", .priority = 7, },

const InterruptConfig_t InterruptConfig[] ={
   INTERRUPT_CONFIG_EXINT    \
   INTERRUPT_CONFIG_CAN     \
   INTERRUPT_CONFIG_DMA \
   INTERRUPT_CONFIG_I2C \
   INTERRUPT_CONFIG_SPI \
   INTERRUPT_CONFIG_TIMER    \
   INTERRUPT_CONFIG_USB  \
   INTERRUPT_CONFIG_UART
    { .irq_n = ADC1_2_IRQn, .on_off = false,         .valid =true, .name ="ADC1_2", .priority = 7, },
    { .irq_n = ACC_IRQn, .on_off = false,         .valid =true, .name ="ACC", .priority = 7, },
    { .irq_n = CRM_IRQn, .on_off = false,         .valid =true, .name ="CRM", .priority = 7, },
    { .irq_n = EXINT15_10_IRQn, .on_off = false,         .valid =true, .name ="EXINT15_10", .priority = 7, },
	{ .irq_n = FLASH_IRQn, .on_off = false,         .valid =true, .name ="FLASH", .priority = 7, },
    { .irq_n = PVM_IRQn, .on_off = false,         .valid =true, .name ="PVM", .priority = 7, },
    { .irq_n = RTC_IRQn, .on_off = false,         .valid =true, .name ="RTC", .priority = 7, },
    { .irq_n = RTCAlarm_IRQn, .on_off = false,         .valid =true, .name ="RTCAlarm", .priority = 7, },
    { .irq_n = SDIO1_IRQn, .on_off = false,         .valid =true, .name ="SDIO1", .priority = 7, },
	{ .irq_n = SysTick_IRQn, .on_off = true,         .valid =true, .name ="SysTick", .priority = 7, },
    { .irq_n = TAMPER_IRQn, .on_off = false,         .valid =true, .name ="TAMPER", .priority = 7, },
    { .irq_n = WWDT_IRQn, .on_off = false,         .valid =true, .name ="WWDT", .priority = 7, },
};

uint32_t interrupt_get_cnt(void) {
    uint32_t cnt =0;
    cnt =ARRAY_SIZE(InterruptConfig);
    return cnt;
}
