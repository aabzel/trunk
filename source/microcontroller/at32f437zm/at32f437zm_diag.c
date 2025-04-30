#include "at32f437zm_diag.h"
#include "data_utils.h"

#include "microcontroller_types.h"
#ifdef HAS_EHAL
#include "micro_controller.h"
#endif

#define INT_NAME_UART      \
    { .name = "Uart4", .int_n = UART4_IRQn, }, \
    { .name = "Uart5", .int_n = UART5_IRQn, }, \
    { .name = "Usart6", .int_n = USART6_IRQn, }, \
    { .name = "Uart7", .int_n = UART7_IRQn, }, \
    { .name = "Uart8", .int_n = UART8_IRQn, }, \
    { .name = "USART1", .int_n = USART1_IRQn, }, \
    { .name = "Usart2", .int_n = USART2_IRQn, }, \
    { .name = "Usart3", .int_n = USART3_IRQn, },


#define INT_NAME_EXTI    \
    { .name = "EXINT0", .int_n = EXINT0_IRQn, }, \
    { .name = "EXINT1", .int_n = EXINT1_IRQn, }, \
    { .name = "EXINT2", .int_n =EXINT2_IRQn, }, \
    { .name = "EXINT3", .int_n = EXINT3_IRQn, }, \
    { .name = "EXINT4", .int_n = EXINT4_IRQn, }, \
    { .name = "EXINT9_5", .int_n = EXINT9_5_IRQn, }, \
    { .name = "Exti15-10", .int_n = EXINT15_10_IRQn, },


#define INT_NAME_DMA1      \
    { .name = "EDMA_Stream1", .int_n = EDMA_Stream1_IRQn, }, \
    { .name = "EDMA_Stream2", .int_n = EDMA_Stream2_IRQn, }, \
    { .name = "EDMA_Stream3", .int_n = EDMA_Stream3_IRQn, }, \
    { .name = "EDMA_Stream4", .int_n = EDMA_Stream4_IRQn, }, \
    { .name = "EDMA_Stream5", .int_n = EDMA_Stream5_IRQn, }, \
    { .name = "EDMA_Stream6", .int_n = EDMA_Stream6_IRQn, }, \
    { .name = "EDMA_Stream7", .int_n = EDMA_Stream7_IRQn, }, \
    { .name = "EDMA_Stream8", .int_n = EDMA_Stream8_IRQn, },


#define INT_NAME_DMA2                                              \
    { .name = "DMA2_Channel1", .int_n = DMA2_Channel1_IRQn, },     \
    { .name = "DMA2_Channel2", .int_n = DMA2_Channel2_IRQn, },     \
    { .name = "DMA2_Channel3", .int_n = DMA2_Channel3_IRQn, },     \
    { .name = "DMA2_Channel4", .int_n = DMA2_Channel4_IRQn, },     \
    { .name = "DMA2_Channel5", .int_n = DMA2_Channel5_IRQn, },     \
    { .name = "DMA2_Channel6", .int_n = DMA2_Channel6_IRQn, },     \
    { .name = "DMA2_Channel7", .int_n = DMA2_Channel7_IRQn, },



#define INT_NAME_ADC    \
    { .name = "ADC1_2_3", .int_n = ADC1_2_3_IRQn, },


#define INT_NAME_SPI1    \
    { .name = "QSPI1", .int_n = QSPI1_IRQn, }, \
    { .name = "SPI1", .int_n = SPI1_IRQn, },


#define INT_NAME_SPI2     \
    { .name = "QSPI2", .int_n = QSPI2_IRQn, }, \
    { .name = "SPI2_I2S2EXT", .int_n = SPI2_I2S2EXT_IRQn, },

#define INT_NAME_SPI    \
	INT_NAME_SPI1   \
	INT_NAME_SPI2    \
    { .name = "SPI3", .int_n = SPI3_I2S3EXT_IRQn, }, \
    { .name = "SPI4", .int_n = SPI4_IRQn, },

#define INT_NAME_TIMER1     \
    { .name = "TMR1_BRK_TMR9", .int_n = TMR1_BRK_TMR9_IRQn, }, \
    { .name = "TMR1_OVF_TMR10", .int_n = TMR1_OVF_TMR10_IRQn, }, \
    { .name = "TMR1_TRG_HALL_TMR11", .int_n = TMR1_TRG_HALL_TMR11_IRQn, }, \
    { .name = "TMR1_CH", .int_n = TMR1_CH_IRQn, },

#define INT_NAME_TIMER8    \
    { .name = "TMR8_BRK_TMR12", .int_n = TMR8_BRK_TMR12_IRQn, }, \
    { .name = "TMR8_OVF_TMR13", .int_n = TMR8_OVF_TMR13_IRQn, }, \
    { .name = "Tim8TRG_COMTim14", .int_n = TMR8_TRG_HALL_TMR14_IRQn, }, \
    { .name = "Tim8_CC", .int_n = TMR8_CH_IRQn, },

#define INT_NAME_TIMER20     \
    { .name = "TMR20_OVF", .int_n = TMR20_OVF_IRQn, }, \
    { .name = "TMR20_BRK", .int_n = TMR20_BRK_IRQn, }, \
    { .name = "TMR20_TRG_HALL", .int_n = TMR20_TRG_HALL_IRQn, }, \
    { .name = "TMR20_CH", .int_n = TMR20_CH_IRQn, },

#define INT_NAME_TIMER    \
    INT_NAME_TIMER1   \
    { .name = "TMR2_GLOBAL", .int_n = TMR2_GLOBAL_IRQn, }, \
    { .name = "TMR3_GLOBAL", .int_n = TMR3_GLOBAL_IRQn, }, \
    { .name = "TMR4_GLOBAL", .int_n = TMR4_GLOBAL_IRQn, }, \
    { .name = "Tim5", .int_n = TMR5_GLOBAL_IRQn, }, \
    { .name = "Tim6_DAC", .int_n = TMR6_DAC_GLOBAL_IRQn, }, \
    { .name = "Tim7", .int_n = TMR7_GLOBAL_IRQn, }, \
    INT_NAME_TIMER8      \
    INT_NAME_TIMER20



#define INT_NAME_CAN1   \
    { .name = "CAN1_TX", .int_n = CAN1_TX_IRQn, }, \
    { .name = "CAN1_RX0", .int_n = CAN1_RX0_IRQn, }, \
    { .name = "CAN1_RX1", .int_n = CAN1_RX1_IRQn, }, \
    { .name = "CAN1_SE", .int_n = CAN1_SE_IRQn, },

#define INT_NAME_CAN2   \
    { .name = "Can2TX", .int_n = CAN2_TX_IRQn, }, \
    { .name = "Can2_RX0", .int_n = CAN2_RX0_IRQn, }, \
    { .name = "Can2_RX1", .int_n = CAN2_RX1_IRQn, }, \
    { .name = "Can2SCE", .int_n = CAN2_SE_IRQn, },

#define INT_NAME_CAN    \
    INT_NAME_CAN1 \
    INT_NAME_CAN2


#define INT_NAME_I2C    \
    { .name = "I2C1_EVT", .int_n = I2C1_EVT_IRQn, }, \
    { .name = "I2C1_ERR", .int_n = I2C1_ERR_IRQn, }, \
    { .name = "I2C2_EVT", .int_n = I2C2_EVT_IRQn, }, \
    { .name = "I2C2_ERR", .int_n = I2C2_ERR_IRQn, }, \
    { .name = "I2C3Ev", .int_n = I2C3_EVT_IRQn, }, \
    { .name = "I2C3_ER", .int_n = I2C3_ERR_IRQn, },

#define INT_NAME_CORE \
    { .name = "HardFault", .int_n = HardFault_IRQn, }, \
    { .name = "SysTick", .int_n = SysTick_IRQn, }, \
    { .name = "NonMaskableInt", .int_n = NonMaskableInt_IRQn, \   }, \
    { .name = "PVM", .int_n = PVM_IRQn, \   }, \
    { .name = "MemoryManagement", \ .int_n = MemoryManagement_IRQn, \   }, \
    { .name = "DebugMonitor", .int_n = DebugMonitor_IRQn, }, \
    { .name = "PendSV", .int_n = PendSV_IRQn, }, \
    { .name = "Reset", .int_n = Reset_IRQn, }, \
    { .name = "BusFault", .int_n = BusFault_IRQn, }, \
    { .name = "UsageFault", .int_n = UsageFault_IRQn, }, \
    { .name = "SVCall", .int_n = SVCall_IRQn, },


#define INT_NAME_AT32_SPECIFIC_INTERRUPT      \
    { .name = "PVM", .int_n = PVM_IRQn, }, \
        { .name = "ERTC_WKUP", .int_n = ERTC_WKUP_IRQn, }, \
        { .name = "FLASH", .int_n = FLASH_IRQn, }, \
        { .name = "CRM", .int_n = CRM_IRQn, }, \
        { .name = "TAMP_STAMP", .int_n = TAMP_STAMP_IRQn, },

#define INT_NAME_SDIO   \
    { .name = "SDIO", .int_n = SDIO1_IRQn, }, \
    { .name = "SDIO2", .int_n = SDIO2_IRQn, },

#define INT_NAME_USB      \
    { .name = "OTGFS1", .int_n = OTGFS1_IRQn, }, \
    { .name = "OTGFS1_WKUP", .int_n = OTGFS1_WKUP_IRQn, }, \
    { .name = "OTGFS2", .int_n = OTGFS2_IRQn, }, \
    { .name = "OTGFS2_WKUP", .int_n = OTGFS2_WKUP_IRQn, },

#define INT_NAME_ETHERNET \
    { .name = "ERTCAlarm", .int_n = ERTCAlarm_IRQn, }, \
    { .name = "EMAC", .int_n = EMAC_IRQn, }, \
    { .name = "EMAC_WKUP", .int_n = EMAC_WKUP_IRQn, },

#define INT_NAME_LUT_ALL     \
    INT_NAME_EXTI   \
    INT_NAME_AT32_SPECIFIC_INTERRUPT   \
    INT_NAME_I2C   \
    INT_NAME_TIMER   \
    INT_NAME_ETHERNET   \
    INT_NAME_ADC   \
    INT_NAME_SDIO   \
    INT_NAME_CAN   \
    INT_NAME_UART   \
    INT_NAME_DMA1   \
    INT_NAME_DMA2   \
    INT_NAME_USB  \
    INT_NAME_SPI     \
    { .name = "FPU", .int_n = FPU_IRQn, }, \
    { .name = "ACC", .int_n = ACC_IRQn, }, \
    { .name = "DMAMUX", .int_n = DMAMUX_IRQn, }, \
    { .name = "XMC", .int_n = XMC_IRQn, }, \
    { .name = "DVP", .int_n = DVP_IRQn, }, \
    { .name = "WWDG", .int_n = WWDT_IRQn, },



static const IntName_t IntNumInfoName[] = {  INT_NAME_LUT_ALL
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
