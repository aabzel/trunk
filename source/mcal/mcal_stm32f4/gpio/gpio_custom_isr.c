#include "gpio_custom_isr.h"

#include "bit_utils.h"
#include "gpio_mcal.h"

uint32_t gpio_int_cnt = 0;

void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin) {
    gpio_int_cnt++;
#ifdef HAS_PINS
    uint16_t bit = 0;
    for(bit = 0; bit <= 15; bit++) {
        if(CHECK_BIT_NUM(gpio_pin, bit)) {
            PinInt_t* Node = PinIntGetNode((uint16_t) bit);
            if(Node) {
                Node->int_cnt++;
            }
        }
    }
#endif
}
