#include "interrupt_mcal.h"

#include <stdint.h>

//#include "c_defines_generated.h"
#include "data_utils.h"
#include "debugger.h"
#include "log.h"
#ifdef HAS_CORE
#include "core_driver.h"
#endif
#include "microcontroller_drv.h"

static const IrqConfig_t IrqConfig[] = {

#ifdef HAS_I2C1
    {.name = "I2C1_EVT", .irq_n = I2C1_EVT_IRQn, .priority = 7.},
    {.name = "I2C1_ERR", .irq_n = I2C1_ERR_IRQn, .priority = 7.},
#endif

#ifdef HAS_I2C2
    {.name = "I2C2_EVT", .irq_n = I2C2_EVT_IRQn, .priority = 7.},
    {.name = "I2C2_ERR", .irq_n = I2C2_ERR_IRQn, .priority = 7.},
#endif

#ifdef HAS_I2C3
    {.name = "I2C3_EVT", .irq_n = I2C3_EVT_IRQn, .priority = 7.},
    {.name = "I2C3_ERR", .irq_n = I2C3_ERR_IRQn, .priority = 7.},
#endif

#ifdef HAS_SPI1
    {.name = "SPI1", .irq_n = SPI1_IRQn, .priority = 7.},
#endif

#ifdef HAS_SPI2
    {.name = "SPI2", .irq_n = SPI2_I2S2EXT_IRQn, .priority = 7.},
#endif

#ifdef HAS_SPI3
    {.name = "SPI3", .irq_n = SPI3_I2S3EXT_IRQn, .priority = 7.},
#endif

#ifdef HAS_SPI4
    {.name = "FLASH", .irq_n = SPI4_IRQn, .priority = 7.},
#endif

#ifdef HAS_FLASH
    {.name = "FLASH", .irq_n = FLASH_IRQn, .priority = 8.},
#endif

#ifdef HAS_DMA1
    {.name = "DMA1Ch1", .irq_n = DMA1_Channel1_IRQn, .priority = 8.},
    {.name = "DMA1Ch2", .irq_n = DMA1_Channel2_IRQn, .priority = 8.},
    {.name = "DMA1Ch3", .irq_n = DMA1_Channel3_IRQn, .priority = 8.},
    {.name = "DMA1Ch4", .irq_n = DMA1_Channel4_IRQn, .priority = 8.},
    {.name = "DMA1Ch5", .irq_n = DMA1_Channel5_IRQn, .priority = 8.},
    {.name = "DMA1Ch6", .irq_n = DMA1_Channel6_IRQn, .priority = 8.},
    {.name = "DMA1Ch7", .irq_n = DMA1_Channel7_IRQn, .priority = 8.},
#endif

#ifdef HAS_DMA2
    {.name = "DMA2Ch1", .irq_n = DMA2_Channel1_IRQn, .priority = 8.},
    {.name = "DMA2Ch2", .irq_n = DMA2_Channel2_IRQn, .priority = 8.},
    {.name = "DMA2Ch3", .irq_n = DMA2_Channel3_IRQn, .priority = 8.},
#ifdef HAS_AT32F43X
    {.name = "DMA2Ch4", .irq_n = DMA2_Channel4_IRQn, .priority = 8.},
    {.name = "DMA2Ch5", .irq_n = DMA2_Channel5_IRQn, .priority = 8.},
    {.name = "DMA2Ch6", .irq_n = DMA2_Channel6_IRQn, .priority = 8.},
    {.name = "DMA2Ch7", .irq_n = DMA2_Channel7_IRQn, .priority = 8.},
#endif // HAS_AT32F43X
#endif // HAS_DMA2

#ifdef HAS_UART1
    {.name = "USART1", .irq_n = USART1_IRQn, .priority = 1.},
#endif

#ifdef HAS_UART2
    {.name = "USART2", .irq_n = USART2_IRQn, .priority = 2.},
#endif

#ifdef HAS_UART3
    {.name = "USART3", .irq_n = USART3_IRQn, .priority = 3.},
#endif

#ifdef HAS_UART7
    {.name = "USART7", .irq_n = UART7_IRQn, .priority = 7.},
#endif

#ifdef HAS_TIMER8
    {.name = "TMR8_BRK_TMR12", .irq_n = TMR8_BRK_TMR12_IRQn, .priority = 7.},
    {.name = "TMR8_OVF_TMR13", .irq_n = TMR8_OVF_TMR13_IRQn, .priority = 7.},
    {.name = "TMR8_TRG_HALL_TMR14", .irq_n = TMR8_TRG_HALL_TMR14_IRQn, .priority = 7.},
    {.name = "TMR8_CH", .irq_n = TMR8_CH_IRQn, .priority = 7.},
#endif

};

bool interrupt_clear(void) {
    bool res = false;
    int8_t irq_n = 0;
    for(irq_n = NonMaskableInt_IRQn; irq_n <= MAX_IRQ_NUM; irq_n++) {
        NVIC_ClearPendingIRQ((IRQn_Type)irq_n);
        res = true;
    }

    return res;
}

bool interrupt_init(void) {
    bool res = true;
    LOG_WARNING(LG_INT, "IntInit");
    uint32_t cnt = ARRAY_SIZE(IrqConfig);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
#ifdef HAS_CORE
        res = core_is_valid_isr_handler(IrqConfig[i].irq_n);
        ASSERT_CRITICAL(res);
#endif
        NVIC_SetPriority(IrqConfig[i].irq_n, IrqConfig[i].priority);
        NVIC_EnableIRQ(IrqConfig[i].irq_n);
        LOG_INFO(LG_INT, "INT[%s]On", IrqConfig[i].name);
    }

    res = interrupt_clear();
    __enable_irq();
    return res;
}

bool interrupt_disable(void) {
    bool res = true;
    int8_t irq_n = 0;
    for(irq_n = NonMaskableInt_IRQn; irq_n <= MAX_IRQ_NUM; irq_n++) {
        NVIC_DisableIRQ((IRQn_Type)irq_n);
    }
    return res;
}
