#include "interrupt_mcal.h"

#include <stdint.h>

#include "stm32fx_hal.h"
#include "sys_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

bool interrupt_clear(void) {
    bool res = false;
    int8_t irq_n = 0;
    for(irq_n = NonMaskableInt_IRQn; irq_n <= MAX_IRQ_NUM; irq_n++) {
        res = IS_NVIC_DEVICE_IRQ(irq_n);
        if(res) {
            HAL_NVIC_ClearPendingIRQ((IRQn_Type)irq_n);
            res = true;
        }
    }

    return res;
}

bool interrupt_control(int16_t irq_n, bool on_off) {
    bool res = true;

    if(on_off) {
        HAL_NVIC_EnableIRQ((IRQn_Type)irq_n);
    } else {
        HAL_NVIC_DisableIRQ((IRQn_Type)irq_n);
    }

    return res;
}

bool interrupt_is_active(int16_t irq_n) {
    bool res = false;
    res = (bool)NVIC_GetEnableIRQ((IRQn_Type)irq_n);
    return res;
}

uint32_t interrupt_get_isr_handler(int16_t irq_n) {
    uint32_t isr_handler = NVIC_GetVector((IRQn_Type)irq_n);
    return isr_handler;
}

bool interrupt_init_custom(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(SYS, "IntInit");
#endif
#ifdef HAS_DMA1
    //  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 10, 10);
    //  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

    //  HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 10, 10);
    // HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
#endif /*HAS_DMA1*/

#ifdef HAS_DMA2
    // HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 10, 10);
    //  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

//    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, 10, 10);
//  HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
#endif /**/

#ifdef HAS_GPIO
#ifdef HAS_EXT_INT
    // HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    // HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI1_IRQn);

    // HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    // HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    // HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI4_IRQn);

    //   HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    //   HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    // HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
#endif /*HAS_EXT_INT*/
#endif /*HAS_GPIO*/

#ifdef HAS_UART1
    //   HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
    //   HAL_NVIC_EnableIRQ(USART1_IRQn);
#endif

#ifdef HAS_UART2
    HAL_NVIC_SetPriority(USART2_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
#endif

#ifdef HAS_UART3
    HAL_NVIC_SetPriority(USART3_IRQn, 3, 3);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
#endif

#ifdef HAS_UART7
    HAL_NVIC_SetPriority(UART7_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(UART7_IRQn);
#endif

#ifdef HAS_I2C2
    HAL_NVIC_SetPriority(I2C2_EV_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);

    HAL_NVIC_SetPriority(I2C2_ER_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
#endif

#ifdef HAS_SPI1
    HAL_NVIC_SetPriority(SPI1_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(SPI1_IRQn);
#endif

#ifdef HAS_SPI2
    HAL_NVIC_SetPriority(SPI2_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(SPI2_IRQn);
#endif

#ifdef HAS_SPI3
    HAL_NVIC_SetPriority(SPI3_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(SPI3_IRQn);
#endif

#ifdef HAS_SPI4
    HAL_NVIC_SetPriority(SPI4_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(SPI4_IRQn);
#endif

#ifdef HAS_SPI5
    HAL_NVIC_SetPriority(SPI5_IRQn, 7, 7);
    HAL_NVIC_EnableIRQ(SPI5_IRQn);
#endif

#ifdef HAS_FLASH
    //   HAL_NVIC_SetPriority(FLASH_IRQn, 8, 8);
    //   HAL_NVIC_EnableIRQ(FLASH_IRQn);
#endif
#if 0
    HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
    
    HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
    
    HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
    
    HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
#endif
    //  HAL_NVIC_SetPriority(RCC_IRQn, 0, 0);
    //  HAL_NVIC_EnableIRQ(RCC_IRQn);

    res = interrupt_clear();

    __enable_irq();
    return res;
}

bool interrupt_control_all(const bool on_off) {
    bool res = false;
    if(on_off) {
#ifdef HAS_CMSIS
        __enable_irq();
        res = true;
#endif
    } else {
#ifdef HAS_CMSIS
        __disable_irq();
        res = true;
#endif
    }
    return res;
}

bool interrupt_disable(void) {
    bool res = true;
#if 0
    int8_t irq_n = 0;
    for(irq_n = 0; irq_n <= MAX_IRQ_NUM; irq_n++) {
        HAL_NVIC_DisableIRQ((IRQn_Type)irq_n);
    }
#endif
#ifdef HAS_CMSIS
    __disable_irq();
#endif
    return res;
}

bool interrupt_set_priority(int16_t irq_n, uint8_t preempt_priority) {
    bool res = true;
    NVIC_SetPriority((IRQn_Type)irq_n, (uint32_t)preempt_priority);
    return res;
}

uint32_t interrupt_get_priority1(int16_t irq_n) {
    uint32_t priority = NVIC_GetPriority((IRQn_Type)irq_n);
    return priority;
}

bool interrupt_get_priority(int16_t irq_n, uint8_t* const preempt_priority, uint8_t* const sub_priority) {
    bool res = false;
    uint32_t PreemptPriority = 0;
    uint32_t SubPriority = 0;
    HAL_NVIC_GetPriority((IRQn_Type)irq_n, NVIC_PRIORITYGROUP_0, &PreemptPriority, &SubPriority);
    *preempt_priority = (uint8_t)PreemptPriority;
    *sub_priority = (uint8_t)SubPriority;
    return res;
}
