#include "stm32f4xx_it.h"

#include "mcal_common.h"

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#ifdef HAS_SD
extern SD_HandleTypeDef hsd;
#endif /*HAS_SD*/

#ifdef HAS_CRYP_HW
void CRYP_IRQHandler(void) {
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        HAL_CRYP_IRQHandler(&CrypNode->cryp_h);
    }
}
#endif /*HAS_CRYP_HW*/

void NMI_Handler(void) {
    while(1) {
    }
}

#ifdef HAS_CAN
void CAN1_TX_IRQHandler(void) {}
void CAN1_RX0_IRQHandler(void) {}
void CAN2_TX_IRQHandler(void) {}
void CAN2_RX0_IRQHandler(void) {}
void CAN2_SCE_IRQHandler(void) {}
void CAN2_RX1_IRQHandler(void) {}
void CAN1_RX1_IRQHandler(void) {}
void CAN1_SCE_IRQHandler(void) {}
#endif
void FSMC_IRQHandler(void) {}
void WWDG_IRQHandler(void) {}
void RCC_IRQHandler(void) {}

void ADC_IRQHandler(void) {
#ifdef HAS_ADC
    AdcHandle_t* AdcNode = AdcGetNode(1);
    if(AdcNode) {
        HAL_ADC_IRQHandler(&AdcNode->adc_h);
    }
#endif /*HAS_ADC*/
}

void DMA1_Stream1_IRQHandler(void) {
#ifdef HAS_DMA1
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA1*/
}

void DMA1_Stream2_IRQHandler(void) {
#ifdef HAS_DMA1
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA1*/
}

void DMA1_Stream3_IRQHandler(void) {
#ifdef HAS_DMA1
#ifdef HAS_I2S_RX
    DmaHandle_t* DmaNode = DmaGetNode(DMA1_I2S2_RX);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif /*HAS_I2S_RX*/
#endif /*HAS_DMA1*/
}

void DMA1_Stream4_IRQHandler(void) {
#ifdef HAS_DMA1
#ifdef HAS_I2S
    DmaHandle_t* DmaNode = DmaGetNode(DMA1_I2S2_TX);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA1*/
}

void DMA1_Stream5_IRQHandler(void) {
#ifdef HAS_DMA1
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA1*/
}

void DMA1_Stream6_IRQHandler(void) {
#ifdef HAS_DMA1
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA1*/
}

void DMA1_Stream7_IRQHandler(void) {
#ifdef HAS_DMA1
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA1*/
}

void DMA2_Stream0_IRQHandler(void) {
#ifdef HAS_DMA2
#ifdef HAS_I2S
    DmaHandle_t* DmaNode = DmaGetNode(DMA2_I2S1_RX);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA2*/
}
void DMA2_Stream1_IRQHandler(void) {
#ifdef HAS_DMA2
#ifdef HAS_I2S
    DmaHandle_t* DmaNode = DmaGetNode(DMA2_I2S4_TX);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA2*/
}
void DMA2_Stream2_IRQHandler(void) {
#ifdef HAS_DMA2
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA2*/
}

void DMA2_Stream3_IRQHandler(void) {
#ifdef HAS_DMA2
#ifdef HAS_DMA
#ifdef DMA2_SDIO_RX
    DmaHandle_t* DmaNode = DmaGetNode(DMA2_SDIO_RX);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif /*DMA2_SDIO_RX*/
#endif /*DMA*/
#endif /*HAS_DMA2*/
}

void DMA2_Stream4_IRQHandler(void) {
#ifdef HAS_DMA2
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA2*/
}
void DMA2_Stream5_IRQHandler(void) {
#ifdef HAS_DMA2
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA2*/
}

void DMA2_Stream6_IRQHandler(void) {
#ifdef HAS_DMA2
#ifdef DMA2_SDIO_TX
    DmaHandle_t* DmaNode = DmaGetNode(DMA2_SDIO_TX);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif /*DMA2_SDIO_TX*/
#endif /*HAS_DMA2*/
}

void DMA2_Stream7_IRQHandler(void) {
#ifdef HAS_DMA2
#if 0
    DmaHandle_t* DmaNode = DmaGetNode(xxxxxx);
    if(DmaNode) {
        HAL_DMA_IRQHandler(&DmaNode->dma_h);
    }
#endif
#endif /*HAS_DMA2*/
}

void FLASH_IRQHandler(void) {

#ifdef HAS_HAL_FLASH
    HAL_FLASH_IRQHandler();
#endif
}

void FPU_IRQHandler(void) {}
void DMA1_Stream0_IRQHandler(void) {}
void TAMP_STAMP_IRQHandler(void) {}

void RTC_WKUP_IRQHandler(void) {
#ifdef HAS_RTC
    RtcHandle_t* Node = RtcGetNode(1);
    if(Node) {
        // HAL_RTCEx_WakeUpTimerIRQHandler(&Node->h_rtc);
    }
#endif
}

void UART5_IRQHandler(void) {}
//void OTG_HS_WKUP_IRQHandler(void) {}
//void UART4_IRQHandler(void) {}
//void TIM7_IRQHandler(void) {}
//void TIM6_DAC_IRQHandler(void) {}
//void TIM8_CC_IRQHandler(void) {}
//void TIM8_TRG_COM_TIM14_IRQHandler(void) {}
void TIM8_BRK_TIM12_IRQHandler(void) {}
void TIM8_UP_TIM13_IRQHandler(void) {}
void OTG_FS_WKUP_IRQHandler(void) {}

void PVD_IRQHandler(void) {
#if 0
  HAL_PWR_PVD_IRQHandler();
#endif
}

void HardFault_Handler(void) {
#if 0
    RegContext_t* stack_ptr;
    asm("TST lr, #4 \n"         // Testing the 3rd bit of the stack pointer (bitwise AND)
        "ITE EQ \n"             // Does the stack pointer value have bit 3?
        "MRSEQ %[ptr], MSP  \n" // Yes, keep the main stack pointer
        "MRSNE %[ptr], PSP  \n" // No, we keep the process stack pointer
        : [ ptr ] "=r"(stack_ptr));
    while(1) {
    }
#endif
}

void MemManage_Handler(void) {
    while(1) {
    }
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void) {
    while(1) {
    }
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
    while(1) {
    }
}

#ifdef HAS_NORTOS
/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {}
void PendSV_Handler(void) {}
#endif /*HAS_NORTOS*/

void DebugMon_Handler(void) {
    while(1) {
    }
}

/**
 * @brief This function handles Pendable request for system service.
 */

void SPI1_IRQHandler(void) {
#if defined(HAS_SPI1) || defined(HAS_I2S1)
#ifdef HAS_SPI1
    SpiHandle_t* SpiNode = SpiGetNode(1);
    if(SpiNode) {
        HAL_SPI_IRQHandler(&SpiNode->handle);
    }
#endif /*HAS_SPI1*/

#ifdef HAS_I2S1
    I2sHandle_t* I2sNode = I2sGetNode(1);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->i2s_h);
    }
#endif /*HAS_I2S1*/
#endif
}

void SPI2_IRQHandler(void) {
#if defined(HAS_SPI2) || defined(HAS_I2S2)
#ifdef HAS_SPI2
    SpiHandle_t* SpiNode = SpiGetNode(2);
    if(SpiNode) {
        HAL_SPI_IRQHandler(&SpiNode->handle);
    }
#endif /*HAS_SPI2*/
#ifdef HAS_I2S2
    I2sHandle_t* I2sNode = I2sGetNode(2);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->i2s_h);
    }
#endif /*HAS_I2S2*/
#endif
}

void SPI3_IRQHandler(void) {
#if defined(HAS_SPI3) || defined(HAS_I2S3)
#ifdef HAS_SPI3
    SpiHandle_t* SpiNode = SpiGetNode(3);
    if(SpiNode) {
        HAL_SPI_IRQHandler(&SpiNode->handle);
    }
#endif /*HAS_SPI3*/
#ifdef HAS_I2S3
    I2sHandle_t* I2sNode = I2sGetNode(3);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->i2s_h);
    }
#endif /*HAS_I2S3*/
#endif
}

void SPI4_IRQHandler(void) {
#if defined(HAS_SPI4) || defined(HAS_I2S4)
#ifdef HAS_SPI4
    SpiHandle_t* SpiNode = SpiGetNode(4);
    if(SpiNode) {
        HAL_SPI_IRQHandler(&SpiNode->handle);
    }
#endif
#ifdef HAS_I2S4
    I2sHandle_t* I2sNode = I2sGetNode(4);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->i2s_h);
    }
#endif /*HAS_I2S4*/
#endif
}

void SPI5_IRQHandler(void) {
#if defined(HAS_SPI5) || defined(HAS_I2S5)
#ifdef HAS_SPI5
    SpiHandle_t* SpiNode = SpiGetNode(5);
    if(SpiNode) {
        HAL_SPI_IRQHandler(&SpiNode->handle);
    }
#endif /**/
#ifdef HAS_I2S5
    I2sHandle_t* I2sNode = I2sGetNode(5);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->i2s_h);
    }
#endif /*HAS_I2S5*/
#endif
}

#ifdef HAS_NORTOS
void SysTick_Handler(void) {
    HAL_IncTick();
#ifdef HAS_SYSTICK_INT
    SysTickIntHandler();
#endif /**/
}
#endif /*HAS_NORTOS*/

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles SDIO global interrupt.
 */
void SDIO_IRQHandler(void) {
#ifdef HAS_SDIO
    SdioHandle_t* Node = SdioGetNode(1);
    if(Node) {
        Node->it_cnt++;
        HAL_SD_IRQHandler(&Node->sdio_h);
    }
#endif /*HAS_SDIO*/
}

void USART1_IRQHandler(void) {
#ifdef HAS_UART1
    UartHandle_t* Node = UartGetNode(1);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif /*HAS_UART1*/
}

void USART2_IRQHandler(void) {
#ifdef HAS_UART2
    UartHandle_t* Node = UartGetNode(2);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif /*HAS_UART2*/
}

void USART3_IRQHandler(void) {
#ifdef HAS_UART3
    UartHandle_t* Node = UartGetNode(3);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif /*HAS_UART3*/
}

void USART6_IRQHandler(void) {
#ifdef HAS_UART6
    UartHandle_t* Node = UartGetNode(6);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif /*HAS_UART6*/
}

void EXTI0_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
#endif
}

void EXTI1_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
#endif
}

void EXTI2_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
#endif
}

void EXTI3_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
#endif /**/
}

void EXTI4_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
#endif /**/
}

void EXTI9_5_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
#endif /**/
}

void EXTI15_10_IRQHandler(void) {
#ifdef HAS_EXTI
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
#endif /*HAS_EXTI*/
}

void OTG_FS_IRQHandler(void) {
#ifdef HAS_USB
    UsbHandle_t* Node = NULL;
#ifdef HAS_USB_DEVICE
    // HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
    Node = UsbGetNodeBySpeed(USB_SPEED_FS);
    if(Node) {
        HAL_PCD_IRQHandler(&Node->hpcd_USB_OTG);
    }
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    Node = UsbGetNodeBySpeed(USB_SPEED_FS);
    if(Node) {
        HAL_HCD_IRQHandler(&Node->hhcd_USB_OTG);
    }
#endif /*HAS_USB_HOST*/
#endif
}

void OTG_HS_EP1_OUT_IRQHandler(void) {
#ifdef HAS_USB
    UsbHandle_t* Node = NULL;
    Node = UsbGetNodeBySpeed(USB_SPEED_HS);
    if(Node) {
#ifdef HAS_USB_DEVICE
        // HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
        if(USB_ROLE_DEVICE == Node->role) {
            HAL_PCD_IRQHandler(&Node->hpcd_USB_OTG);
        }
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
        if(USB_ROLE_HOST == Node->role) {
            HAL_HCD_IRQHandler(&Node->hhcd_USB_OTG);
        }
#endif
    }
#endif /*HAS_USB*/
}

/**
 * @brief This function handles USB On The Go HS End Point 1 In global interrupt.
 */
void OTG_HS_EP1_IN_IRQHandler(void) {
#ifdef HAS_USB
    UsbHandle_t* Node = NULL;
    Node = UsbGetNodeBySpeed(USB_SPEED_HS);
    if(Node) {
#ifdef HAS_USB_DEVICE
        // HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
        if(USB_ROLE_DEVICE == Node->role) {
            HAL_PCD_IRQHandler(&Node->hpcd_USB_OTG);
        }
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
        if(USB_ROLE_HOST == Node->role) {
            HAL_HCD_IRQHandler(&Node->hhcd_USB_OTG);
        }
#endif
    }
#endif
}

void OTG_HS_IRQHandler(void) {
#ifdef HAS_USB
    UsbHandle_t* Node = UsbGetNodeBySpeed(USB_SPEED_HS);
    if(Node) {
#ifdef HAS_USB_DEVICE
        // HAL_PCD_IRQHandler(&hpcd_USB_OTG_HS);
        if(USB_ROLE_DEVICE == Node->role) {
            HAL_PCD_IRQHandler(&(Node->hpcd_USB_OTG));
        }
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
        if(USB_ROLE_HOST == Node->role) {
            HAL_HCD_IRQHandler(&(Node->hhcd_USB_OTG));
        }
#endif
    }
#endif
}

void TIM1_UP_TIM10_IRQHandler(void) {
#if defined(HAS_TIMER1) || defined(HAS_TIMER10)
#ifdef HAS_TIMER1
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(1);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER1*/
#ifdef HAS_TIMER10
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(10);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER10*/
#endif /*  HAS_TIMER1 HAS_TIMER10  */
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
#if defined(HAS_TIMER1) || defined(HAS_TIMER11)
    TimerHandle_t* Node = NULL;
#ifdef HAS_TIMER1
    Node = TimerGetNode(1);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER10*/
#ifdef HAS_TIMER11
    Node = TimerGetNode(11);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER11*/
#endif /**/
}

void TIM1_CC_IRQHandler(void) {
#ifdef HAS_TIMER1
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(1);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER1*/
}

void TIM2_IRQHandler(void) {
#ifdef HAS_TIMER2
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(2);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER2*/
}

void TIM3_IRQHandler(void) {
#ifdef HAS_TIMER3
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(3);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER3*/
}

void TIM4_IRQHandler(void) {
#ifdef HAS_TIMER4
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(4);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER4*/
}

void TIM5_IRQHandler(void) {
#ifdef HAS_TIMER5
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(5);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER5*/
}

void TIM1_BRK_TIM9_IRQHandler(void) {
#if defined(HAS_TIMER1) || defined(HAS_TIMER9)
    TimerHandle_t* Node = NULL;
#ifdef HAS_TIMER1
    Node = TimerGetNode(1);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER1*/

#ifdef HAS_TIMER9
    Node = TimerGetNode(9);
    if(Node) {
        HAL_TIM_IRQHandler(&Node->timer_h);
    }
#endif /*HAS_TIMER9*/
#endif /*HAS_TIMER1 or HAS_TIMER9*/
}

void I2C1_ER_IRQHandler(void) {
#ifdef HAS_I2C1
    I2cHandle_t* Node = I2cGetNode(1);
    if(Node) {
        HAL_I2C_ER_IRQHandler(&Node->i2c_h);
    }
#endif /**/
}

void I2C1_EV_IRQHandler(void) {
#ifdef HAS_I2C1
    I2cHandle_t* Node = I2cGetNode(1);
    if(Node) {
        HAL_I2C_EV_IRQHandler(&Node->i2c_h);
    }
#endif /*HAS_I2C1*/
}

void I2C2_ER_IRQHandler(void) {
#ifdef HAS_I2C2
    I2cHandle_t* Node = I2cGetNode(2);
    if(Node) {
        HAL_I2C_ER_IRQHandler(&Node->i2c_h);
    }
#endif /*HAS_I2C2*/
}

void I2C2_EV_IRQHandler(void) {
#ifdef HAS_I2C2
    I2cHandle_t* Node = I2cGetNode(2);
    if(Node) {
        HAL_I2C_EV_IRQHandler(&Node->i2c_h);
    }
#endif /*HAS_I2C2*/
}

void I2C3_EV_IRQHandler(void) {
#ifdef HAS_I2C3
    I2cHandle_t* Node = I2cGetNode(3);
    if(Node) {
        HAL_I2C_EV_IRQHandler(&Node->i2c_h);
    }
#endif /**/
}

void I2C3_ER_IRQHandler(void) {
#ifdef HAS_I2C3
    I2cHandle_t* Node = I2cGetNode(3);
    if(Node) {
        HAL_I2C_ER_IRQHandler(&Node->i2c_h);
    }
#endif /*HAS_I2C3*/
}

void HASH_RNG_IRQHandler(void) {
    // HAL_RNG_IRQHandler(&hrng);
}

//void RTC_Alarm_IRQHandler(void) {}
