#include "gpio_isr.h"

#include "bit_utils.h"
#include "gpio_mcal.h"

uint32_t gpio_int_cnt = 0;

#if 0
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    gpio_int_cnt++;
#ifdef HAS_PINS
    uint8_t bit = 0;
    for(bit = 0; bit <= 15; bit++) {
        if(CHECK_BIT_NUM(GPIO_Pin, bit)) {
            PinInt_t* Node = PinIntGetNode(bit);
            if(Node) {
                Node->int_cnt++;
            }
        }
    }
#endif
}

#endif
