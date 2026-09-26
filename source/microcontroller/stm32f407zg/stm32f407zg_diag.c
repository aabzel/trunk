#include "stm32f407zg_diag.h"

#include "interrupt_types.h"

#define INT_NUM_INFO_ALL                \
  { .int_n = ADC_IRQn                  , .name = "ADC", }, \
  { .int_n = CAN1_TX_IRQn              , .name = "CAN1tX", }, \
  { .int_n = CAN1_RX0_IRQn             , .name = "CAN1RX0", }, \
  { .int_n = CAN1_RX1_IRQn             , .name = "CAN1RX1", }, \
  { .int_n = CAN1_SCE_IRQn             , .name = "CAN1SCE", }, \
  { .int_n = CAN2_TX_IRQn              , .name = "CAN2tX", }, \
  { .int_n = CAN2_RX0_IRQn             , .name = "CAN2RX0", }, \
  { .int_n = CAN2_RX1_IRQn             , .name = "CAN2RX1", }, \
  { .int_n = CAN2_SCE_IRQn             , .name = "CAN2SCE", }, \
  { .int_n = DCMI_IRQn                 , .name = "DCMI", }, \
  { .int_n = DMA1_Stream0_IRQn         , .name = "DMA1stream0", }, \
  { .int_n = DMA1_Stream1_IRQn         , .name = "DMA1stream1", }, \
  { .int_n = DMA1_Stream2_IRQn         , .name = "DMA1stream2", }, \
  { .int_n = DMA1_Stream3_IRQn         , .name = "DMA1stream3", }, \
  { .int_n = DMA1_Stream4_IRQn         , .name = "DMA1stream4", }, \
  { .int_n = DMA1_Stream5_IRQn         , .name = "DMA1stream5", }, \
  { .int_n = DMA1_Stream6_IRQn         , .name = "DMA1stream6", }, \
  { .int_n = DMA1_Stream7_IRQn         , .name = "DMA1stream7", }, \
  { .int_n = DMA2_Stream0_IRQn         , .name = "DMA2stream0", }, \
  { .int_n = DMA2_Stream1_IRQn         , .name = "DMA2stream1", }, \
  { .int_n = DMA2_Stream2_IRQn         , .name = "DMA2stream2", }, \
  { .int_n = DMA2_Stream3_IRQn         , .name = "DMA2stream3", }, \
  { .int_n = DMA2_Stream4_IRQn         , .name = "DMA2stream4", }, \
  { .int_n = DMA2_Stream5_IRQn         , .name = "DMA2stream5", }, \
  { .int_n = DMA2_Stream6_IRQn         , .name = "DMA2stream6", }, \
  { .int_n = DMA2_Stream7_IRQn         , .name = "DMA2stream7", }, \
  { .int_n = ETH_IRQn                  , .name = "Ethernet", }, \
  { .int_n = ETH_WKUP_IRQn             , .name = "EthernetWakeup", }, \
  { .int_n = EXTI0_IRQn                , .name = "Exti0", }, \
  { .int_n = EXTI1_IRQn                , .name = "Exti1", }, \
  { .int_n = EXTI2_IRQn                , .name = "Exti2", }, \
  { .int_n = EXTI3_IRQn                , .name = "Exti3", }, \
  { .int_n = EXTI4_IRQn                , .name = "Exti4", }, \
  { .int_n = EXTI9_5_IRQn              , .name = "Ext9_5", }, \
  { .int_n = EXTI15_10_IRQn            , .name = "Ext15_10", }, \
  { .int_n = FLASH_IRQn                , .name = "FLASH", }, \
  { .int_n = FPU_IRQn                  , .name = "FPU", }, \
  { .int_n = FSMC_IRQn                 , .name = "FSMC", }, \
  { .int_n = I2C1_EV_IRQn              , .name = "I2C1event", }, \
  { .int_n = I2C1_ER_IRQn              , .name = "I2C1error", }, \
  { .int_n = I2C2_EV_IRQn              , .name = "I2C2event", }, \
  { .int_n = I2C2_ER_IRQn              , .name = "I2C2error", }, \
  { .int_n = I2C3_EV_IRQn              , .name = "I2C3event", }, \
  { .int_n = I2C3_ER_IRQn              , .name = "I2C3error", }, \
  { .int_n = OTG_FS_IRQn               , .name = "USB_OTG_FS", }, \
  { .int_n = OTG_HS_EP1_OUT_IRQn       , .name = "USB_OTG_HSEndPoint1Out", }, \
  { .int_n = OTG_HS_EP1_IN_IRQn        , .name = "USB_OTG_HSEndPoint1In", }, \
  { .int_n = OTG_HS_WKUP_IRQn          , .name = "USB_OTG_HSwakeup", }, \
  { .int_n = OTG_HS_IRQn               , .name = "USB_OTG_HS", }, \
  { .int_n = PVD_IRQn                  , .name = "PVD", }, \
  { .int_n = RCC_IRQn                  , .name = "RCC", },   \
  { .int_n = RNG_IRQn                  , .name = "RNG", }, \
  { .int_n = RTC_WKUP_IRQn             , .name = "RTCWakeup", }, \
  { .int_n = RTC_Alarm_IRQn            , .name = "RTCAlarm", }, \
  { .int_n = SPI1_IRQn                 , .name = "SPI1", }, \
  { .int_n = SPI2_IRQn                 , .name = "SPI2", }, \
  { .int_n = SPI3_IRQn                 , .name = "SPI3", }, \
  { .int_n = TAMP_STAMP_IRQn           , .name = "TamperTimeStamp", }, \
  { .int_n = TIM1_BRK_TIM9_IRQn        , .name = "TIM1BreakTIM9", }, \
  { .int_n = TIM1_UP_TIM10_IRQn        , .name = "TIM1UpdateTIM10", }, \
  { .int_n = TIM1_TRG_COM_TIM11_IRQn   , .name = "TIM1TriggerCommutationTIM11", }, \
  { .int_n = TIM1_CC_IRQn              , .name = "TIM1CaptureCompare", }, \
  { .int_n = TIM2_IRQn                 , .name = "TIM2", }, \
  { .int_n = TIM3_IRQn                 , .name = "TIM3", }, \
  { .int_n = TIM4_IRQn                 , .name = "TIM4", }, \
  { .int_n = OTG_FS_WKUP_IRQn          , .name = "USB_OTG_FS", }, \
  { .int_n = SDIO_IRQn                 , .name = "SDIO", }, \
  { .int_n = TIM6_DAC_IRQn             , .name = "TIM6_DAC", }, \
  { .int_n = TIM7_IRQn                 , .name = "TIM7", }, \
  { .int_n = TIM8_BRK_TIM12_IRQn       , .name = "TIM8BreakTIM12", }, \
  { .int_n = TIM8_UP_TIM13_IRQn        , .name = "TIM8UpdateTIM13", }, \
  { .int_n = TIM8_TRG_COM_TIM14_IRQn   , .name = "TIM8TrgCommTIM14", }, \
  { .int_n = TIM8_CC_IRQn              , .name = "TIM8CaptureCompare", }, \
  { .int_n = TIM5_IRQn                 , .name = "TIM5", }, \
  { .int_n = USART1_IRQn               , .name = "USART1", }, \
  { .int_n = USART2_IRQn               , .name = "USART2", }, \
  { .int_n = USART3_IRQn               , .name = "USART3", }, \
  { .int_n = UART4_IRQn                , .name = "UART4", }, \
  { .int_n = UART5_IRQn                , .name = "UART5", }, \
  { .int_n = USART6_IRQn               , .name = "USART6", }, \
  { .int_n = WWDG_IRQn                 , .name = "WindowWatchDog", },


const IntNumInfo_t IntNumInfo[]={
    INT_NUM_INFO_ALL
};

uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}


