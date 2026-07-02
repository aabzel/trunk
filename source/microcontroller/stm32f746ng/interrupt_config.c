#include "interrupt_config.h"

#include "sys_config.h"

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif

const InterruptConfig_t InterruptConfig[] = {
    { .irq_n = SPI2_IRQn, .priority = 0, .on_off = true, .valid = true, },
    { .irq_n = USART1_IRQn, .priority = 0, .on_off = true, .valid = true, },
    { .irq_n = EXTI9_5_IRQn, .priority = 0, .on_off = true, .valid = true, },
    { .irq_n = SysTick_IRQn, .priority = 1, .on_off = true, .valid = true, },
};

uint32_t interrupt_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(InterruptConfig);
    return cnt;
}
