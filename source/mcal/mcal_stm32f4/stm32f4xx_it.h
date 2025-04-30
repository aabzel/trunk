#ifndef STM32F4XX_ISR_PROTOTYPES_H
#define STM32F4XX_ISR_PROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

void OTG_HS_EP1_OUT_IRQHandler(void);
void OTG_HS_EP1_IN_IRQHandler(void);
void OTG_HS_IRQHandler(void);
void TAMP_STAMP_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);
void DMA1_Stream0_IRQHandler(void);
void ADC_IRQHandler(void);
void UART5_IRQHandler(void);
void FSMC_IRQHandler(void);
void HASH_RNG_IRQHandler(void);

void BusFault_Handler(void);
void DebugMon_Handler(void);
void HardFault_Handler(void);
void NMI_Handler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void MemManage_Handler(void);
void UsageFault_Handler(void);
void TIM8_UP_TIM13_IRQHandler(void);
void OTG_FS_WKUP_IRQHandler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WWDG_IRQHandler(void);
void RCC_IRQHandler(void);
void OTG_FS_IRQHandler(void);
void PVD_IRQHandler(void);
void EXTI4_IRQHandler(void);

void CRYP_IRQHandler(void);
#ifdef HAS_CRYP
#endif

void SDIO_IRQHandler(void);
#ifdef HAS_SDIO
#endif

void FLASH_IRQHandler(void);
#ifdef HAS_FLASH
#endif
void FPU_IRQHandler(void);

void SPI1_IRQHandler(void);
#if defined(HAS_SPI1) || defined(HAS_I2S1)
#endif /**/

void SPI2_IRQHandler(void);
#if defined(HAS_SPI2) || defined(HAS_I2S2)
#endif /**/

void SPI3_IRQHandler(void);
#if defined(HAS_SPI3) || defined(HAS_I2S3)
#endif /**/

void SPI4_IRQHandler(void);
#if defined(HAS_SPI4) || defined(HAS_I2S4)
#endif /**/

void SPI5_IRQHandler(void);
#if defined(HAS_SPI5) || defined(HAS_I2S5)
#endif /**/

#ifdef HAS_UART
void USART1_IRQHandler(void);
#ifdef HAS_UART1
#endif /*HAS_UART1*/
void USART2_IRQHandler(void);
#ifdef HAS_UART2
#endif /*HAS_UART2*/
#ifdef HAS_UART3
void USART3_IRQHandler(void);
#endif /*HAS_UART3*/
void USART4_IRQHandler(void);
#ifdef HAS_UART4
#endif /*HAS_UART4*/
void USART5_IRQHandler(void);
#ifdef HAS_UART5
#endif /*HAS_UART5*/
void USART6_IRQHandler(void);
#ifdef HAS_UART6
#endif /*HAS_UART6*/
void USART7_IRQHandler(void);
#ifdef HAS_UART7
#endif /*HAS_UART7*/
void USART8_IRQHandler(void);
#ifdef HAS_UART8
#endif /*HAS_UART8*/
void USART9_IRQHandler(void);
#ifdef HAS_UART9
#endif /*HAS_UART9*/
void USART10_IRQHandler(void);
#ifdef HAS_UART10
#endif /*HAS_UART10*/
#endif /*HAS_UART*/

void I2C1_ER_IRQHandler(void);
void I2C1_EV_IRQHandler(void);
#ifdef HAS_I2C1
#endif /**/

void I2C2_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
#ifdef HAS_I2C2
#endif /**/

void I2C3_ER_IRQHandler(void);
void I2C3_EV_IRQHandler(void);
#ifdef HAS_I2C3
#endif /**/

void TIM1_BRK_TIM9_IRQHandler(void);
void TIM1_UP_TIM10_IRQHandler(void);
void TIM1_TRG_COM_TIM11_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM5_IRQHandler(void);
#ifdef HAS_TIMER
#endif /*HAS_TIMER*/

void DMA1_Stream1_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
void DMA1_Stream7_IRQHandler(void);
#ifdef HAS_DMA1
#endif /*HAS_DMA1*/

void DMA2_Stream0_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream4_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);
#ifdef HAS_DMA2
#endif /*HAS_DMA2*/

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
#ifdef HAS_EXTI
#endif /*HAS_EXTI*/

#ifdef __cplusplus
}
#endif

#endif /* STM32F4XX_ISR_PROTOTYPES_H */
