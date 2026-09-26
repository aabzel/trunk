#include "stm32f4xx_it.h"

#include "mcal_common.h"

#ifdef USE_HAL_DRIVER
#include "stm32fx_hal.h"
#endif

#ifdef HAS_SD
extern SD_HandleTypeDef hsd;
#endif

#ifdef HAS_CRYP_HW
void CRYP_IRQHandler(void) {
    CrypHandle_t* CrypNode = CrypGetNode(CRYP_HW_NUM);
    if(CrypNode) {
        HAL_CRYP_IRQHandler(&CrypNode->cryp_h);
    }
}
#endif

void ADC_IRQHandler(void) {
#ifdef HAS_ADC
    AdcHandle_t* Node = NULL;
    Node = AdcGetNode(1);
    if(Node) {
        HAL_ADC_IRQHandler(&Node->adc_h);
    }

    Node = AdcGetNode(2);
    if(Node) {
        HAL_ADC_IRQHandler(&Node->adc_h);
    }

    Node = AdcGetNode(3);
    if(Node) {
        HAL_ADC_IRQHandler(&Node->adc_h);
    }
#endif
}

void NMI_Handler(void) {
    while(1) {
    }
}

#ifdef HAS_CAN_CUSTOM_INTERRUPT

#ifdef HAS_CAN1
void CAN1_TX_IRQHandler(void) { CANx_IRQHandler(1); }
void CAN1_RX0_IRQHandler(void) { CANx_IRQHandler(1); }
void CAN1_RX1_IRQHandler(void) { CANx_IRQHandler(1); }
void CAN1_SCE_IRQHandler(void) { CANx_IRQHandler(1); }
#endif

#ifdef HAS_CAN2
void CAN2_TX_IRQHandler(void) { CANx_IRQHandler(2); }
void CAN2_RX0_IRQHandler(void) { CANx_IRQHandler(2); }
void CAN2_SCE_IRQHandler(void) { CANx_IRQHandler(2); }
void CAN2_RX1_IRQHandler(void) { CANx_IRQHandler(2); }
#endif

#endif

void FSMC_IRQHandler(void) {}

void RCC_IRQHandler(void) {}

void DMA1_Stream0_IRQHandler(void) {
#ifdef HAS_DMA1
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 0,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream1_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 1,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream2_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 2,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream3_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 3,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream4_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 4,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream5_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 5,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream6_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 6,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA1_Stream7_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 1,
        .stream = 7,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream0_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 0,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream1_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 1,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream2_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 2,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream3_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 3,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream4_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 4,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream5_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 5,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream6_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 6,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void DMA2_Stream7_IRQHandler(void) {
#ifdef HAS_DMA_CHANNEL
    DmaInfoChannel_t DmaPad = {
        .dma_num = 2,
        .stream = 7,
        .channel = 0xFF,
        .name = "?",
    };
    DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        HAL_DMA_IRQHandler(&Node->dma_h);
    }
#endif
}

void FLASH_IRQHandler(void) {

#ifdef HAS_HAL_FLASH
    HAL_FLASH_IRQHandler();
#endif
}

void FPU_IRQHandler(void) {}

void TAMP_STAMP_IRQHandler(void) {}

void RTC_WKUP_IRQHandler(void) {
#ifdef HAS_RTC
    RtcHandle_t* Node = RtcGetNode(1);
    if(Node) {
        // HAL_RTCEx_WakeUpTimerIRQHandler(&Node->h_rtc);
    }
#endif
}

// void OTG_HS_WKUP_IRQHandler(void) {}
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
#endif
    while(1) {
    }
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
#ifdef HAS_SPI1
    SPIx_IRQHandler(1);
#endif

#if defined(HAS_I2S1)

#ifdef HAS_I2S1
    I2sHandle_t* I2sNode = I2sGetNode(1);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->handle);
    }
#endif /*HAS_I2S1*/
#endif
}

void SPI2_IRQHandler(void) {
#ifdef HAS_SPI2
    SPIx_IRQHandler(2);
#endif

#if defined(HAS_I2S2)

#ifdef HAS_I2S2
    I2sHandle_t* I2sNode = I2sGetNode(2);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->handle);
    }
#endif /*HAS_I2S2*/
#endif
}

void SPI3_IRQHandler(void) {
#ifdef HAS_SPI3
    SPIx_IRQHandler(3);
#endif

#if defined(HAS_I2S3)
#ifdef HAS_I2S3
    I2sHandle_t* I2sNode = I2sGetNode(3);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->handle);
    }
#endif /*HAS_I2S3*/
#endif
}

void SPI4_IRQHandler(void) {
#ifdef HAS_SPI4
    SPIx_IRQHandler(4);
#endif

#if defined(HAS_I2S4)

#ifdef HAS_I2S4
    I2sHandle_t* I2sNode = I2sGetNode(4);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->handle);
    }
#endif
#endif
}

void WWDG_IRQHandler(void) {
    //   HAL_WWDG_IRQHandler(&hwwdg);
}

void SPI5_IRQHandler(void) {
#ifdef HAS_SPI5
    SPIx_IRQHandler(5);
#endif

#if defined(HAS_I2S5)

#ifdef HAS_I2S5
    I2sHandle_t* I2sNode = I2sGetNode(5);
    if(I2sNode) {
        HAL_I2S_IRQHandler(&I2sNode->handle);
    }
#endif
#endif
}

void SysTick_Handler(void) {
    HAL_IncTick();
#ifdef HAS_SYSTICK_INTERRUPT
    SysTickIntHandler();
#endif
}

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
        HAL_SD_IRQHandler(&Node->Handle);
    }
#endif
}

void USART1_IRQHandler(void) {
#ifdef HAS_UART1
    UartHandle_t* Node = UartGetNode(1);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void USART2_IRQHandler(void) {
#ifdef HAS_UART2
    UartHandle_t* Node = UartGetNode(2);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void USART3_IRQHandler(void) {
#ifdef HAS_UART3
    UartHandle_t* Node = UartGetNode(3);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void UART4_IRQHandler(void) {
#ifdef HAS_UART4
    UartHandle_t* Node = UartGetNode(4);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void UART5_IRQHandler(void) {
#ifdef HAS_UART5
    UartHandle_t* Node = UartGetNode(5);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void USART6_IRQHandler(void) {
#ifdef HAS_UART6
    UartHandle_t* Node = UartGetNode(6);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void UART7_IRQHandler(void) {
#ifdef HAS_UART7
    UartHandle_t* Node = UartGetNode(7);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void UART8_IRQHandler(void) {
#ifdef HAS_UART8
    UartHandle_t* Node = UartGetNode(8);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void USART9_IRQHandler(void) {
#ifdef HAS_UART8
    UartHandle_t* Node = UartGetNode(9);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

void USART10_IRQHandler(void) {
#ifdef HAS_UART8
    UartHandle_t* Node = UartGetNode(10);
    if(Node) {
        HAL_UART_IRQHandler(&Node->uart_h);
    }
#endif
}

/*External interrupts*/
void EXTI0_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(0);
#endif
}

void EXTI1_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(1);
#endif
}

void EXTI2_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(2);
#endif
}

void EXTI3_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(3);
#endif
}

void EXTI4_IRQHandler(void) {
#ifdef HAS_EXT_INT
    EXINTx_IRQHandler(4);
#endif
}

void EXTI9_5_IRQHandler(void) {
#ifdef HAS_EXT_INT
    uint8_t gpio_pin = exti_get_pin();
    EXINTx_IRQHandler(gpio_pin);
#endif
}

void EXTI15_10_IRQHandler(void) {
#ifdef HAS_EXT_INT
    uint8_t gpio_pin = exti_get_pin();
    EXINTx_IRQHandler(gpio_pin);
#endif
}

/**
 * @brief This function handles USB On The Go HS End Point 1 In global interrupt.
 */
void OTG_HS_EP1_IN_IRQHandler(void) {
#ifdef HAS_USB_INTERRUPT
    UsbHandle_t* Node = NULL;
    Node = UsbGetNodeBySpeed(USB_MCAL_SPEED_HS);
    if(Node) {
#ifdef HAS_USB_DEVICE
        if(USB_MCAL_ROLE_DEVICE == Node->role) {
            HAL_PCD_IRQHandler(&Node->PcdHandle);
        }
#endif

#ifdef HAS_USB_HOST
        if(USB_MCAL_ROLE_HOST == Node->role) {
            HAL_HCD_IRQHandler(&Node->hhcd_USB_OTG);
        }
#endif
    }
#endif
}

/* HW Timers */

void TIM1_UP_TIM10_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER1
    TIMx_IRQHandler(1);
#endif

#ifdef HAS_TIMER10
    TIMx_IRQHandler(10);
#endif
#endif
}

void TIM1_TRG_COM_TIM11_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER1
    TIMx_IRQHandler(1);
#endif

#ifdef HAS_TIMER11
    TIMx_IRQHandler(11);
#endif
#endif
}

void TIM1_CC_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER1
    TIMx_IRQHandler(1);
#endif
#endif
}

void TIM2_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER2
    //#error ererer
    TIMx_IRQHandler(2);
#endif
#endif
}

void TIM3_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER3
    TIMx_IRQHandler(3);
#endif
#endif
}

void TIM4_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER4
    TIMx_IRQHandler(4);
#endif
#endif
}

void TIM5_IRQHandler(void) {
#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER5
    TIMx_IRQHandler(5);
#endif
#endif
}
#ifdef HAS_TIMER_INTERRUPT
#endif // HAS_TIMER_INTERRUPT

void TIM6_DAC_IRQHandler(void) {

#ifdef HAS_TIMER_INTERRUPT
#ifdef HAS_TIMER6
    TIMx_IRQHandler(6);
#endif
#endif

#ifdef HAS_DAC_INTERRUPT
    DACx_IRQHandler(1);
#endif
}

#ifdef HAS_TIMER_INTERRUPT
void TIM7_IRQHandler(void) {
#ifdef HAS_TIMER7
    TIMx_IRQHandler(7);
#endif
}
#endif

#ifdef HAS_TIMER_INTERRUPT
void TIM8_UP_TIM13_IRQHandler(void) {
#ifdef HAS_TIMER8
    TIMx_IRQHandler(8);
#endif

#ifdef HAS_TIMER13
    TIMx_IRQHandler(13);
#endif
}
#endif // HAS_TIMER_INTERRUPT

#ifdef HAS_TIMER_INTERRUPT
void TIM8_BRK_TIM12_IRQHandler(void) {
#ifdef HAS_TIMER8
    TIMx_IRQHandler(8);
#endif

#ifdef HAS_TIMER12
    TIMx_IRQHandler(12);
#endif
}
#endif // HAS_TIMER_INTERRUPT

#ifdef HAS_TIMER_INTERRUPT
void TIM8_CC_IRQHandler(void) {
#ifdef HAS_TIMER8
    TIMx_IRQHandler(8);
#endif
}

void TIM8_TRG_COM_TIM14_IRQHandler(void) {
#ifdef HAS_TIMER8
    TIMx_IRQHandler(8);
#endif

#ifdef HAS_TIMER14
    TIMx_IRQHandler(14);
#endif
}
#endif // HAS_TIMER_INTERRUPT

#ifdef HAS_TIMER_INTERRUPT
void TIM1_BRK_TIM9_IRQHandler(void) {

#ifdef HAS_TIMER1
    TIMx_IRQHandler(1);
#endif

#ifdef HAS_TIMER9
    TIMx_IRQHandler(9);
#endif
}
#endif

void I2C1_ER_IRQHandler(void) {
#ifdef HAS_I2C1
    I2cHandle_t* Node = I2cGetNode(1);
    if(Node) {
        HAL_I2C_ER_IRQHandler(&Node->i2c_h);
    }
#endif
}

void I2C1_EV_IRQHandler(void) {
#ifdef HAS_I2C1
    I2cHandle_t* Node = I2cGetNode(1);
    if(Node) {
        HAL_I2C_EV_IRQHandler(&Node->i2c_h);
    }
#endif
}

void I2C2_ER_IRQHandler(void) {
#ifdef HAS_I2C2
    I2cHandle_t* Node = I2cGetNode(2);
    if(Node) {
        HAL_I2C_ER_IRQHandler(&Node->i2c_h);
    }
#endif
}

void I2C2_EV_IRQHandler(void) {
#ifdef HAS_I2C2
    I2cHandle_t* Node = I2cGetNode(2);
    if(Node) {
        HAL_I2C_EV_IRQHandler(&Node->i2c_h);
    }
#endif
}

void I2C3_EV_IRQHandler(void) {
#ifdef HAS_I2C3
    I2cHandle_t* Node = I2cGetNode(3);
    if(Node) {
        HAL_I2C_EV_IRQHandler(&Node->i2c_h);
    }
#endif
}

void I2C3_ER_IRQHandler(void) {
#ifdef HAS_I2C3
    I2cHandle_t* Node = I2cGetNode(3);
    if(Node) {
        HAL_I2C_ER_IRQHandler(&Node->i2c_h);
    }
#endif
}

void HASH_RNG_IRQHandler(void) {
#ifdef HAS_RNG1
    RngHandle_t* Node = RngGetNode(1);
    if(Node) {
        HAL_RNG_IRQHandler(&Node->Handler);
    }
#endif
}

void RTC_Alarm_IRQHandler(void) {
    // HAL_RTC_AlarmIRQHandler(&hrtc);
}

/*USB*/

void OTG_FS_IRQHandler(void) {
#ifdef HAS_USB_INTERRUPT
    UsbHandle_t* Node = NULL;
#ifdef HAS_USB_DEVICE
    // HAL_PCD_IRQHandler(&PcdHandle_FS);
    Node = UsbGetNodeBySpeed(USB_MCAL_SPEED_FS);
    if(Node) {
        HAL_PCD_IRQHandler(&Node->PcdHandle);
    }
#endif

#ifdef HAS_USB_HOST
    Node = UsbGetNodeBySpeed(USB_MCAL_SPEED_FS);
    if(Node) {
        HAL_HCD_IRQHandler(&Node->hhcd_USB_OTG);
    }
#endif
#endif
}

void OTG_HS_EP1_OUT_IRQHandler(void) {
#ifdef HAS_USB_INTERRUPT
    UsbHandle_t* Node = NULL;
    Node = UsbGetNodeBySpeed(USB_MCAL_SPEED_HS);
    if(Node) {
#ifdef HAS_USB_DEVICE
        if(USB_MCAL_ROLE_DEVICE == Node->role) {
            HAL_PCD_IRQHandler(&Node->PcdHandle);
        }
#endif

#ifdef HAS_USB_HOST
        if(USB_MCAL_ROLE_HOST == Node->role) {
            HAL_HCD_IRQHandler(&Node->hhcd_USB_OTG);
        }
#endif
    }
#endif
}

void OTG_HS_IRQHandler(void) {
#ifdef HAS_USB_INTERRUPT
    UsbHandle_t* Node = NULL;
    Node = UsbGetNodeBySpeed(USB_MCAL_SPEED_HS);
    if(Node) {
#ifdef HAS_USB_DEVICE
        // HAL_PCD_IRQHandler(&PcdHandle_HS);
        if(USB_MCAL_ROLE_DEVICE == Node->role) {
            HAL_PCD_IRQHandler((PCD_HandleTypeDef*)&(Node->PcdHandle));
        }
#endif

#ifdef HAS_USB_HOST
        if(USB_MCAL_ROLE_HOST == Node->role) {
            HAL_HCD_IRQHandler(&(Node->hhcd_USB_OTG));
        }
#endif
    }
#endif
}
