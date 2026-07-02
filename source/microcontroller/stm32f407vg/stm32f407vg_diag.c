#include "stm32f407vg_diag.h"

#include "interrupt_types.h"

#define INT_NUM_INFO_DMA1                                       \
    { .int_n = DMA1_Stream0_IRQn , .name = "DMA1_Stream0", },   \
    { .int_n = DMA1_Stream1_IRQn , .name = "DMA1_Stream1", },   \
    { .int_n = DMA1_Stream2_IRQn , .name = "DMA1_Stream2", },   \
    { .int_n = DMA1_Stream3_IRQn , .name = "DMA1_Stream3", },   \
    { .int_n = DMA1_Stream4_IRQn , .name = "DMA1_Stream4", },   \
    { .int_n = DMA1_Stream5_IRQn , .name = "DMA1_Stream5", },   \
    { .int_n = DMA1_Stream6_IRQn , .name = "DMA1_Stream6", },   \
    { .int_n = DMA1_Stream7_IRQn , .name = "DMA1_Stream7", },

#define INT_NUM_INFO_DMA2                                       \
    { .int_n = DMA2_Stream0_IRQn , .name = "DMA2_Stream0", },   \
    { .int_n = DMA2_Stream1_IRQn , .name = "DMA2_Stream1", },   \
    { .int_n = DMA2_Stream2_IRQn , .name = "DMA2_Stream2", },   \
    { .int_n = DMA2_Stream3_IRQn , .name = "DMA2_Stream3", },   \
    { .int_n = DMA2_Stream4_IRQn , .name = "DMA2_Stream4", },   \
    { .int_n = DMA2_Stream5_IRQn , .name = "DMA2_Stream5", },   \
    { .int_n = DMA2_Stream6_IRQn , .name = "DMA2_Stream6", },   \
    { .int_n = DMA2_Stream7_IRQn , .name = "DMA2_Stream7", },

#define INT_NUM_INFO_DMA  INT_NUM_INFO_DMA1 INT_NUM_INFO_DMA2


#define INT_NUM_INFO_UART                            \
    { .int_n = USART1_IRQn , .name = "USART1", },    \
    { .int_n = USART2_IRQn , .name = "USART2", },    \
    { .int_n = USART3_IRQn , .name = "USART3", },    \
    { .int_n = UART4_IRQn , .name = "UART4", },      \
    { .int_n = UART5_IRQn , .name = "UART5", },      \
    { .int_n = USART6_IRQn , .name = "USART6", },

#define INT_NUM_INFO_CAN                                \
    { .int_n = CAN1_TX_IRQn , .name = "CAN1_TX", },     \
    { .int_n = CAN1_RX0_IRQn , .name = "CAN1_RX0", },   \
    { .int_n = CAN1_RX1_IRQn , .name = "CAN1_RX1", },   \
    { .int_n = CAN1_SCE_IRQn , .name = "CAN1_SCE", },   \
    { .int_n = CAN2_TX_IRQn , .name = "CAN2_TX", },     \
    { .int_n = CAN2_RX0_IRQn , .name = "CAN2_RX0", },   \
    { .int_n = CAN2_RX1_IRQn , .name = "CAN2_RX1", },   \
    { .int_n = CAN2_SCE_IRQn , .name = "CAN2_SCE", },


#define INT_NUM_INFO_EXTI                              \
    { .int_n = EXTI0_IRQn , .name = "EXTI0", },        \
    { .int_n = EXTI1_IRQn , .name = "EXTI1", },        \
    { .int_n = EXTI2_IRQn , .name = "EXTI2", },        \
    { .int_n = EXTI3_IRQn , .name = "EXTI3", },        \
    { .int_n = EXTI4_IRQn , .name = "EXTI4", },        \
    { .int_n = EXTI9_5_IRQn , .name = "EXTI9_5", },    \
    { .int_n = EXTI15_10_IRQn , .name = "EXTI15_10", },

#define INT_NUM_INFO_TIMER                                                  \
    { .int_n = TIM1_BRK_TIM9_IRQn , .name = "TIM1_BRK_TIM9", },             \
    { .int_n = TIM1_UP_TIM10_IRQn , .name = "TIM1_UP_TIM10", },             \
    { .int_n = TIM1_TRG_COM_TIM11_IRQn , .name = "TIM1tgComTIM11", },   \
    { .int_n = TIM1_CC_IRQn , .name = "TIM1_CC", },                         \
    { .int_n = TIM2_IRQn , .name = "TIM2", },                               \
    { .int_n = TIM3_IRQn , .name = "TIM3", },                               \
    { .int_n = TIM4_IRQn , .name = "TIM4", },                               \
    { .int_n = TIM5_IRQn , .name = "TIM5", },                               \
    { .int_n = TIM6_DAC_IRQn , .name = "TIM6_DAC", },                       \
    { .int_n = TIM7_IRQn , .name = "TIM7", },                               \
    { .int_n = TIM8_BRK_TIM12_IRQn , .name = "TIM8_BRK_TIM12", },           \
    { .int_n = TIM8_UP_TIM13_IRQn , .name = "TIM8_UP_TIM13", },             \
    { .int_n = TIM8_TRG_COM_TIM14_IRQn , .name = "TIM8_TRG_COM_TIM14", },   \
    { .int_n = TIM8_CC_IRQn , .name = "TIM8_CC", },

#define INT_NUM_INFO_I2C                              \
    { .int_n = I2C1_EV_IRQn , .name = "I2C1_EV", },   \
    { .int_n = I2C1_ER_IRQn , .name = "I2C1_ER", },   \
    { .int_n = I2C2_EV_IRQn , .name = "I2C2_EV", },   \
    { .int_n = I2C2_ER_IRQn , .name = "I2C2_ER", },   \
    { .int_n = I2C3_EV_IRQn , .name = "I2C3_EV", },   \
    { .int_n = I2C3_ER_IRQn , .name = "I2C3_ER", },


#define INT_NUM_INFO_SPI                        \
    { .int_n = SPI1_IRQn , .name = "SPI1", },   \
    { .int_n = SPI2_IRQn , .name = "SPI2", },   \
    { .int_n = SPI3_IRQn , .name = "SPI3", },


#define INT_NUM_INFO_USB                                                    \
    { .int_n = OTG_FS_WKUP_IRQn , .name = "OTG_FS_WKUP", },                 \
    { .int_n = OTG_FS_IRQn , .name = "OTG_FS", },                           \
    { .int_n = OTG_HS_EP1_OUT_IRQn , .name = "OTG_HS_EP1_OUT", },           \
    { .int_n = OTG_HS_EP1_IN_IRQn , .name = "OTG_HS_EP1_IN", },             \
    { .int_n = OTG_HS_WKUP_IRQn , .name = "OTG_HS_WKUP", },                 \
    { .int_n = OTG_HS_IRQn , .name = "OTG_HS", },

#define INT_NUM_INFO_RTC                                           \
    { .int_n = RTC_WKUP_IRQn , .name = "RTC_WKUP", },              \
    { .int_n = RTC_Alarm_IRQn , .name = "RTC_Alarm", },

#define INT_NUM_INFO_ETH                                  \
    { .int_n = ETH_IRQn , .name = "ETH", },               \
    { .int_n = ETH_WKUP_IRQn , .name = "ETH_WKUP", },

const IntNumInfo_t IntNumInfo[]={
    INT_NUM_INFO_DMA
    INT_NUM_INFO_UART
    INT_NUM_INFO_CAN
    INT_NUM_INFO_EXTI
    INT_NUM_INFO_TIMER
    INT_NUM_INFO_I2C
    INT_NUM_INFO_SPI
    INT_NUM_INFO_USB
    INT_NUM_INFO_RTC
    INT_NUM_INFO_ETH
    { .int_n = WWDG_IRQn , .name = "WWDG", },
    { .int_n = PVD_IRQn , .name = "PVD", },
    { .int_n = TAMP_STAMP_IRQn , .name = "TAMP_STAMP", },
    { .int_n = FLASH_IRQn , .name = "FLASH", },
    { .int_n = RCC_IRQn , .name = "RCC", },
    { .int_n = ADC_IRQn , .name = "ADC", },
    { .int_n = FSMC_IRQn , .name = "FSMC", },
    { .int_n = SDIO_IRQn , .name = "SDIO", },
    { .int_n = DCMI_IRQn , .name = "DCMI", },
    { .int_n = RNG_IRQn , .name = "RNG", },
    { .int_n = FPU_IRQn , .name = "FPU", },
};

uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}
