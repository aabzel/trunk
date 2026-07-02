#include "ext_int_custom_isr.h"

#include "ext_int_isr.h"

bool EXINTx_IRQHandler(const uint8_t pin_num) {
    bool res = false;
    res = ext_int_irq_handler(pin_num);
    HAL_GPIO_EXTI_IRQHandler(1 << pin_num);
    return res;
}

void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin) {
}


