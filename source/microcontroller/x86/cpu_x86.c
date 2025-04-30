#include "cpu_x86.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

#ifdef HAS_PINS
const PinData_t PinConfig[] = {
//   {.mcu_pin=1,   .pad.port=PORT_E,    .pad.pin=2,      .name="", },
};
#endif

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}
#endif

__attribute__((weak))
void SystemInit (void){
}


bool mcu_init(void){
    bool res = true;
    return res;
}
