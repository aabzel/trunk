#include "at32f4xx_int.h"

#include "mcal_common.h"
//#include "c_defines_generated.h"

void NMI_Handler(void) {}

void HardFault_Handler(void) {
    /* go to infinite loop when hard fault exception occurs */
    while(1) {
    }
}

void MemManage_Handler(void) {
    /* go to infinite loop when memory manage exception occurs */
    while(1) {
    }
}

void BusFault_Handler(void) {
    /* go to infinite loop when bus fault exception occurs */
    while(1) {
    }
}

void UsageFault_Handler(void) {
    /* go to infinite loop when usage fault exception occurs */
    while(1) {
    }
}

void SVC_Handler(void) {}

void DebugMon_Handler(void) {}

void PendSV_Handler(void) {}

void USART1_IRQHandler(void) {
#ifdef HAS_UART1
    UartIRQHandler(1);
#endif
}

void USART2_IRQHandler(void) {
#ifdef HAS_UART2
    UartIRQHandler(2);
#endif
}

void USART3_IRQHandler(void) {
#ifdef HAS_UART3
    UartIRQHandler(3);
#endif
}

void UART4_IRQHandler(void) {
#ifdef HAS_UART4
    UartIRQHandler(4);
#endif
}

void UART5_IRQHandler(void) {
#ifdef HAS_UART5
    UartIRQHandler(5);
#endif
}

void USART6_IRQHandler(void) {
#ifdef HAS_UART6
    UartIRQHandler(6);
#endif
}

void UART7_IRQHandler(void) {
#ifdef HAS_UART7
    UartIRQHandler(7);
#endif
}

void UART8_IRQHandler(void) {
#ifdef HAS_UART8
    UartIRQHandler(8);
#endif
}

void CAN1_RX0_IRQHandler(void) {
#ifdef HAS_CAN1
    CanRxFifoxIRQHandler(1, CAN_RF0MN_FLAG, CAN_RX_FIFO0);
#endif
}

void CAN1_RX1_IRQHandler(void) {
#ifdef HAS_CAN1
    CanRxFifoxIRQHandler(1, CAN_RF1MN_FLAG, CAN_RX_FIFO1);
#endif
}

void CAN1_TX_IRQHandler(void) {
#ifdef HAS_CAN1
    CanTxIRQHandler(1);
#endif
}

void CAN1_SE_IRQHandler(void) {
#ifdef HAS_CAN1
    CanSwIRQHandler(1);
#endif
}

void CAN2_RX0_IRQHandler(void) {
#ifdef HAS_CAN2
    CanRxFifoxIRQHandler(2, CAN_RF0MN_FLAG, CAN_RX_FIFO0);
#endif
}

void CAN2_RX1_IRQHandler(void) {
#ifdef HAS_CAN2
    CanRxFifoxIRQHandler(2, CAN_RF1MN_FLAG, CAN_RX_FIFO1);
#endif
}

void CAN2_TX_IRQHandler(void) {
#ifdef HAS_CAN2
    CanTxIRQHandler(2);
#endif
}

void CAN2_SE_IRQHandler(void) {
#ifdef HAS_CAN2
    CanSwIRQHandler(2);
#endif
}

// ----
void I2C1_EVT_IRQHandler(void) {
#ifdef HAS_I2C1
    I2cEvtIRQHandler(1);
#endif
}

void I2C2_EVT_IRQHandler(void) {
#ifdef HAS_I2C2
    I2cEvtIRQHandler(2);
#endif
}

void I2C3_EVT_IRQHandler(void) {
#ifdef HAS_I2C3
    I2cEvtIRQHandler(3);
#endif
}

void I2C1_ERR_IRQHandler(void) {
#ifdef HAS_I2C1
    I2cErrIRQHandler(1);
#endif
}

void I2C2_ERR_IRQHandler(void) {
#ifdef HAS_I2C2
    I2cErrIRQHandler(2);
#endif
}

void I2C3_ERR_IRQHandler(void) {
#ifdef HAS_I2C3
    I2cErrIRQHandler(3);
#endif
}
//--

/**
 * @brief  this function handles timer1 overflow handler.
 */
void TMR1_OVF_TMR10_IRQHandler(void) {
#ifdef HAS_TIMER1
    ArteryTimerOverflowIRQHandler(1);
#endif /*HAS_TIMER1*/

#ifdef HAS_TIMER10
    ArteryTimerOverflowIRQHandler(10);
#endif /*HAS_TIMER10*/
}

void TMR1_BRK_TMR9_IRQHandler(void) {
    /* TMR1 Brake and TMR9   */
#ifdef HAS_TIMER9
    ArteryTimerOverflowIRQHandler(9);
#endif /*HAS_TIMER9*/
}

void TMR1_TRG_HALL_TMR11_IRQHandler(void) {
    /* TMR1 Trigger and hall and TMR11   */
#ifdef HAS_TIMER11
    ArteryTimerOverflowIRQHandler(11);
#endif /*HAS_TIMER11*/
}

void TMR1_CH_IRQHandler(void) { /* TMR1 Channel    */
}

void TMR2_GLOBAL_IRQHandler(void) {
    /* TMR2*/
#ifdef HAS_TIMER2
    ArteryTimerOverflowIRQHandler(2);
#endif /*HAS_TIMER2*/
}
void TMR3_GLOBAL_IRQHandler(void) {
    /* TMR3*/
#ifdef HAS_TIMER3
    ArteryTimerOverflowIRQHandler(3);
#endif /*HAS_TIMER3*/
}

/* TMR4*/
void TMR4_GLOBAL_IRQHandler(void) {
#ifdef HAS_TIMER4
    ArteryTimerOverflowIRQHandler(4);
#endif /*HAS_TIMER4*/
}

/* TMR8 Brake and TMR12  */
void TMR8_BRK_TMR12_IRQHandler(void) {
#ifdef HAS_TIMER8
    ArteryTimerOverflowIRQHandler(8);
#endif /*HAS_TIMER8*/

#ifdef HAS_TIMER12
    ArteryTimerOverflowIRQHandler(12);
#endif /*HAS_TIMER12*/
}

/* TMR8 Overflow and TMR13     */
void TMR8_OVF_TMR13_IRQHandler(void) {
#ifdef HAS_TIMER8
    ArteryTimerOverflowIRQHandler(8);
#endif /*HAS_TIMER8*/

#ifdef HAS_TIMER13
    ArteryTimerOverflowIRQHandler(13);
#endif /*HAS_TIMER13*/
}

/* TMR8 Trigger and hall and TMR14   */
void TMR8_TRG_HALL_TMR14_IRQHandler(void) {
#ifdef HAS_TIMER8
    ArteryTimerOverflowIRQHandler(8);
#endif /*HAS_TIMER8*/

#ifdef HAS_TIMER14
    ArteryTimerOverflowIRQHandler(14);
#endif /*HAS_TIMER14*/
}

/* TMR8 Channel    */
void TMR8_CH_IRQHandler(void) {
#ifdef HAS_TIMER8
    ArteryTimerOverflowIRQHandler(8);
#endif /*HAS_TIMER8*/
}

/* TMR5*/
void TMR5_GLOBAL_IRQHandler(void) {
#ifdef HAS_TIMER5
    ArteryTimerOverflowIRQHandler(5);
#endif /*HAS_TIMER5*/
}

/* TMR6 & DAC*/
void TMR6_DAC_GLOBAL_IRQHandler(void) {
#ifdef HAS_TIMER6
    ArteryTimerOverflowIRQHandler(6);
#endif /*HAS_TIMER6*/
}

/* TMR7*/
void TMR7_GLOBAL_IRQHandler(void) {
#ifdef HAS_TIMER7
    ArteryTimerOverflowIRQHandler(7);
#endif /*HAS_TIMER7*/
}

/* TMR20 Brake     */
void TMR20_BRK_IRQHandler(void) {}

/* TMR20 Overflow  */
void TMR20_OVF_IRQHandler(void) {
#ifdef HAS_TIMER20
    ArteryTimerOverflowIRQHandler(20);
#endif /*HAS_TIMER20*/
}

void EXINT0_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(0);
#endif
}

void EXINT1_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(1);
#endif
}

void EXINT2_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(2);
#endif
}

void EXINT3_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(3);
#endif
}

void EXINT4_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(4);
#endif
}

void EXINT9_5_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(5);
    EXINTx_IRQHandler(6);
    EXINTx_IRQHandler(7);
    EXINTx_IRQHandler(8);
    EXINTx_IRQHandler(9);
#endif
}

void EXINT15_10_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(10);
    EXINTx_IRQHandler(11);
    EXINTx_IRQHandler(12);
    EXINTx_IRQHandler(13);
    EXINTx_IRQHandler(14);
    EXINTx_IRQHandler(15);
#endif
}

void ADC1_2_3_IRQHandler(void) {
#ifdef HAS_ADC1
    AdcIRQHandler(1);
#endif

#ifdef HAS_ADC2
    AdcIRQHandler(2);
#endif

#ifdef HAS_ADC3
    AdcIRQHandler(3);
#endif
}
void DMA1_Channel1_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(1, 1);
#endif
}

void DMA1_Channel2_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(1, 2);
#endif
}

void DMA1_Channel3_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(1, 3);
#endif
}

void DMA1_Channel4_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(1, 4);
#endif
}

void DMA1_Channel5_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(1, 5);
#endif
}

void DMA2_Channel1_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(2, 1);
#endif
}

void DMA2_Channel2_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(2, 2);
#endif
}

void DMA2_Channel3_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(2, 3);
#endif
}

void DMA2_Channel4_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(2, 4);
#endif
}

void DMA2_Channel5_IRQHandler(void) {
#ifdef HAS_DMA
    DMAxChannelyIRQHandler(2, 5);
#endif
}

void SPI1_IRQHandler(void) {
#ifdef HAS_SPI1
    SpiIRQHandler(1);
#endif
}

void SPI2_I2S2EXT_IRQHandler(void) {
#ifdef HAS_I2S2
    I2sIRQHandler(2);
#endif

#ifdef HAS_SPI2
    SpiIRQHandler(2);
#endif
}

void SPI3_I2S3EXT_IRQHandler(void) {
#ifdef HAS_I2S3
    I2sIRQHandler(3);
#endif

#ifdef HAS_SPI3
    SpiIRQHandler(3);
#endif
}

void SPI4_IRQHandler(void) {
#ifdef HAS_SPI4
    SpiIRQHandler(4);
#endif
}

#if defined(HAS_I2S2) && defined(HAS_SPI2)
#error Both not alowed!
#endif

#if defined(HAS_I2S3) && defined(HAS_SPI3)
#error Both not alowed!
#endif

void SysTick_Handler(void) {
#ifdef HAS_SYSTICK_INT
    SysTickIntHandler();
#endif /**/
}

void TMR20_TRG_HALL_IRQHandler(void) { /* TMR20 Trigger and hall*/
}

void TMR20_CH_IRQHandler(void) { /* TMR20 Channel   */
}
