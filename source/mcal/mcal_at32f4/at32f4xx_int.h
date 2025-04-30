/**
 **************************************************************************
 * @file     artery_at32f4xx_int.h
 * @brief    header file of main interrupt service routines.
 **************************************************************************
 *                       Copyright notice & Disclaimer
 *
 * The software Board Support Package (BSP) that is made available to
 * download from Artery official website is the copyrighted work of Artery.
 * Artery authorizes customers to use, copy, and distribute the BSP
 * software and its related documentation for the purpose of design and
 * development in conjunction with Artery microcontrollers. Use of the
 * software is governed by this copyright notice and the following disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
 * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
 * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
 * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
 * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 **************************************************************************
 */

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AT32F435_437_INT_H
#define __AT32F435_437_INT_H

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/
#include "artery_at32f4xx.h"

/* exported types ------------------------------------------------------------*/
/* exported constants --------------------------------------------------------*/
/* exported macro ------------------------------------------------------------*/
/* exported functions ------------------------------------------------------- */


void ADC1_2_3_IRQHandler(void);
void BusFault_Handler(void);
void CAN1_RX0_IRQHandler(void);
void CAN1_RX1_IRQHandler(void);
void CAN1_SE_IRQHandler(void) ;
void CAN1_TX_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
void CAN2_RX1_IRQHandler(void);
void CAN2_SE_IRQHandler(void);
void CAN2_TX_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void) ;
void DMA1_Channel2_IRQHandler(void) ;
void DMA1_Channel3_IRQHandler(void) ;
void DMA1_Channel4_IRQHandler(void) ;
void DMA1_Channel5_IRQHandler(void) ;
void DMA2_Channel1_IRQHandler(void) ;
void DMA2_Channel2_IRQHandler(void) ;
void DMA2_Channel3_IRQHandler(void) ;
void DMA2_Channel4_IRQHandler(void) ;
void DMA2_Channel5_IRQHandler(void) ;
void DebugMon_Handler(void);
void EXINT0_IRQHandler(void);
void EXINT15_10_IRQHandler(void);
void EXINT1_IRQHandler(void) ;
void EXINT2_IRQHandler(void) ;
void EXINT3_IRQHandler(void) ;
void EXINT4_IRQHandler(void);
void EXINT9_5_IRQHandler(void);
void HardFault_Handler(void);
void I2C1_ERR_IRQHandler(void) ;
void I2C1_EVT_IRQHandler(void);
void I2C2_ERR_IRQHandler(void);
void I2C2_EVT_IRQHandler(void) ;
void I2C3_ERR_IRQHandler(void) ;
void I2C3_EVT_IRQHandler(void);
void MemManage_Handler(void);
void NMI_Handler(void);
void PendSV_Handler(void);
void SPI1_IRQHandler(void) ;
void SPI2_I2S2EXT_IRQHandler(void) ;
void SPI3_I2S3EXT_IRQHandler(void);
void SPI4_IRQHandler(void);
void SVC_Handler(void);
void SysTick_Handler(void);
void TMR1_BRK_TMR9_IRQHandler(void) ;
void TMR1_CH_IRQHandler(void);
void TMR1_OVF_TMR10_IRQHandler(void);
void TMR1_TRG_HALL_TMR11_IRQHandler(void);
void TMR20_BRK_IRQHandler(void);
void TMR20_CH_IRQHandler(void);
void TMR20_OVF_IRQHandler(void);
void TMR20_TRG_HALL_IRQHandler(void);
void TMR2_GLOBAL_IRQHandler(void);
void TMR3_GLOBAL_IRQHandler(void);
void TMR4_GLOBAL_IRQHandler(void) ;
void TMR5_GLOBAL_IRQHandler(void) ;
void TMR6_DAC_GLOBAL_IRQHandler(void);
void TMR7_GLOBAL_IRQHandler(void) ;
void TMR8_BRK_TMR12_IRQHandler(void);
void TMR8_CH_IRQHandler(void);
void TMR8_OVF_TMR13_IRQHandler(void);
void TMR8_TRG_HALL_TMR14_IRQHandler(void);
void UART4_IRQHandler(void) ;
void UART5_IRQHandler(void);
void UART7_IRQHandler(void) ;
void UART8_IRQHandler(void);
void USART1_IRQHandler(void) ;
void USART2_IRQHandler(void) ;
void USART3_IRQHandler(void) ;
void USART6_IRQHandler(void) ;
void UsageFault_Handler(void);

#ifdef __cplusplus
}
#endif

#endif
