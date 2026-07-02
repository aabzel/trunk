#include "stm32f746ng.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "interrupt_types.h"
#include "pin_types.h"

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

const IntNumInfo_t InterruptsNameDiag[] = {};

#if 0
const char* InterruptNumToStr(int16_t int_n) {
    const char* name = "?";
    uint32_t i = 0;
    for(i=0; i<ARRAY_SIZE(InterruptsNameDiag); i++) {
        if(int_n==InterruptsNameDiag[i].int_n){
            name=InterruptsNameDiag[i].name;
			break;
        }
    }
    return name;
}

bool mcu_init(void) {
    bool res = true;
    return res;
}

#endif
