#include "at32f413rc_diag.h"
#include "data_utils.h"

#include "microcontroller_types.h"


#define INT_NAME_UART      \
    { .name = "USART1", .int_n = USART1_IRQn, }, \
    { .name = "USART2", .int_n = USART2_IRQn, }, \
    { .name = "USART3", .int_n = USART3_IRQn, },  \
    { .name = "UART4", .int_n = UART4_IRQn, }, \
    { .name = "UART5", .int_n = UART5_IRQn, },


#define INT_NAME_EXTI        \
    { .name = "EXINT0", .int_n = EXINT0_IRQn, }, \
    { .name = "EXINT1", .int_n = EXINT1_IRQn, }, \
    { .name = "EXINT2", .int_n =EXINT2_IRQn, }, \
    { .name = "EXINT3", .int_n = EXINT3_IRQn, }, \
    { .name = "EXINT4", .int_n = EXINT4_IRQn, }, \
    { .name = "EXINT9_5", .int_n = EXINT9_5_IRQn, }, \
    { .name = "Exti15-10", .int_n = EXINT15_10_IRQn, },


#define INT_NAME_DMA1      \
    { .name = "DMA1_Channel1", .int_n = DMA1_Channel1_IRQn, }, \
    { .name = "DMA1_Channel2", .int_n = DMA1_Channel2_IRQn, }, \
    { .name = "DMA1_Channel3", .int_n = DMA1_Channel3_IRQn, }, \
    { .name = "DMA1_Channel4", .int_n = DMA1_Channel4_IRQn, }, \
    { .name = "DMA1_Channel5", .int_n = DMA1_Channel5_IRQn, }, \
    { .name = "DMA1_Channel6", .int_n = DMA1_Channel6_IRQn, }, \
    { .name = "DMA1_Channel7", .int_n = DMA1_Channel7_IRQn, },


#define INT_NAME_DMA2                                              \
    { .name = "DMA2_Channel1", .int_n = DMA2_Channel1_IRQn, },     \
    { .name = "DMA2_Channel2", .int_n = DMA2_Channel2_IRQn, },     \
    { .name = "DMA2_Channel3", .int_n = DMA2_Channel3_IRQn, },     \
    { .name = "DMA2_Channel4_5", .int_n = DMA2_Channel4_5_IRQn, },     \
    { .name = "DMA2_Channel6_7", .int_n = DMA2_Channel6_7_IRQn, },



#define INT_NAME_ADC    \
    { .name = "ADC1_2", .int_n = ADC1_2_IRQn, },


#define INT_NAME_SPI1    \
    { .name = "SPI1", .int_n = SPI1_IRQn, },


#define INT_NAME_SPI2     \
    { .name = "SPI2", .int_n = SPI2_IRQn, },

#define INT_NAME_SPI    \
	INT_NAME_SPI1   \
	INT_NAME_SPI2

#define INT_NAME_TIMER1     \
    { .name = "TMR1_BRK_TMR9", .int_n = TMR1_BRK_TMR9_IRQn, }, \
    { .name = "TMR1_OVF_TMR10", .int_n = TMR1_OVF_TMR10_IRQn, }, \
    { .name = "TMR1_TRG_HALL_TMR11", .int_n = TMR1_TRG_HALL_TMR11_IRQn, }, \
    { .name = "TMR1_CH", .int_n = TMR1_CH_IRQn, },

#define INT_NAME_TIMER8    \
    { .name = "TMR8_BRK", .int_n = TMR8_BRK_IRQn, }, \
    { .name = "TMR8_OVF", .int_n = TMR8_OVF_IRQn, }, \
    { .name = "TMR8_TRG_HALL", .int_n = TMR8_TRG_HALL_IRQn, }, \
    { .name = "TMR8_CH", .int_n = TMR8_CH_IRQn, },


#define INT_NAME_TIMER    \
    INT_NAME_TIMER1   \
    { .name = "TMR2_GLOBAL", .int_n = TMR2_GLOBAL_IRQn, }, \
    { .name = "TMR3_GLOBAL", .int_n = TMR3_GLOBAL_IRQn, }, \
    { .name = "TMR4_GLOBAL", .int_n = TMR4_GLOBAL_IRQn, }, \
    { .name = "TMR5_GLOBAL", .int_n = TMR5_GLOBAL_IRQn, }, \
    INT_NAME_TIMER8



#define INT_NAME_CAN1   \
    { .name = "USBFS_H_CAN1_TX", .int_n = USBFS_H_CAN1_TX_IRQn, }, \
    { .name = "USBFS_L_CAN1_RX0", .int_n = USBFS_L_CAN1_RX0_IRQn, }, \
    { .name = "CAN1_RX1", .int_n = CAN1_RX1_IRQn, }, \
    { .name = "CAN1_SE", .int_n = CAN1_SE_IRQn, },

#define INT_NAME_CAN2   \
    { .name = "CAN2_TX", .int_n = CAN2_TX_IRQn, }, \
    { .name = "CAN2_RX0", .int_n = CAN2_RX0_IRQn, }, \
    { .name = "CAN2_RX1", .int_n = CAN2_RX1_IRQn, }, \
    { .name = "CAN2_SE", .int_n = CAN2_SE_IRQn, }, \
    { .name = "CAN2_SE", .int_n = CAN2_SE_IRQn, },

#define INT_NAME_CAN    \
    INT_NAME_CAN1 \
    INT_NAME_CAN2


#define INT_NAME_I2C    \
    { .name = "I2C1_EVT", .int_n = I2C1_EVT_IRQn, }, \
    { .name = "I2C1_ERR", .int_n = I2C1_ERR_IRQn, }, \
    { .name = "I2C2_EVT", .int_n = I2C2_EVT_IRQn, }, \
    { .name = "I2C2_ERR", .int_n = I2C2_ERR_IRQn, },

#define INT_NAME_CORE \
    { .name = "PVM", .int_n = PVM_IRQn, \   }, \
    { .name = "Reset", .int_n = Reset_IRQn, }, \
    { .name = "NonMaskableInt", .int_n = NonMaskableInt_IRQn, \   }, \
    { .name = "HardFault", .int_n = HardFault_IRQn, }, \
    { .name = "MemoryManagement", \ .int_n = MemoryManagement_IRQn, \   }, \
    { .name = "BusFault", .int_n = BusFault_IRQn, }, \
    { .name = "UsageFault", .int_n = UsageFault_IRQn, }, \
    { .name = "SVCall", .int_n = SVCall_IRQn, }, \
    { .name = "DebugMonitor", .int_n = DebugMonitor_IRQn, }, \
    { .name = "PendSV", .int_n = PendSV_IRQn, },  \
    { .name = "SysTick", .int_n = SysTick_IRQn, },


#define INT_NAME_AT32_SPECIFIC_INTERRUPT              \
    { .name = "PVM", .int_n = PVM_IRQn, },            \
    { .name = "FLASH", .int_n = FLASH_IRQn, },        \
    { .name = "TAMPER", .int_n = TAMPER_IRQn, }, \
    { .name = "CRM", .int_n = CRM_IRQn, },

#define INT_NAME_SDIO   \
    { .name = "SDIO1", .int_n = SDIO1_IRQn, },

#define INT_NAME_USB                                             \
    { .name = "USBFSWakeUp", .int_n = USBFSWakeUp_IRQn, },  \
    { .name = "USBFS_MAPH", .int_n = USBFS_MAPH_IRQn, },    \
    { .name = "USBFS_MAPL", .int_n = USBFS_MAPL_IRQn, },


#define INT_NAME_RTC                                         \
    { .name = "RTC", .int_n = RTC_IRQn, },                   \
    { .name = "RTCAlarm", .int_n = RTCAlarm_IRQn, },

#define INT_NAME_LUT_ALL                  \
    INT_NAME_EXTI                         \
    INT_NAME_AT32_SPECIFIC_INTERRUPT      \
    INT_NAME_I2C                          \
    INT_NAME_TIMER                        \
    INT_NAME_RTC                          \
    INT_NAME_ADC                          \
    INT_NAME_SDIO                         \
    INT_NAME_CAN                          \
    INT_NAME_UART                         \
    INT_NAME_DMA1                         \
    INT_NAME_DMA2                         \
    INT_NAME_USB                          \
    INT_NAME_SPI                          \
    { .name = "ACC", .int_n = ACC_IRQn, }, \
    { .name = "WWDG", .int_n = WWDT_IRQn, },


static const IntName_t IntNumInfoName[] = {
    INT_NAME_LUT_ALL
};

const char* InterruptNumberToStr(int8_t int_n) {
    const char* name = "?";
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(IntNumInfoName); i++) {
        if(int_n == IntNumInfoName[i].int_n) {
            name = IntNumInfoName[i].name;
            break;
        }
    }
    return name;
}
