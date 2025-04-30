#include "stm32f411ce.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_types.h"
#include "gpio_mcal.h"
#include "gpio_custom_const.h"

#ifdef HAS_PINS
const PinData_t PinConfig[] = {
 };
#endif

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    uint16_t cnt = 0;
    cnt = ARRAY_SIZE(PinConfig);
    return cnt;
}
#endif


bool mcu_init(void){
	bool res = true;
	return res;
}
