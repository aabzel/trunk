#include "stm32f407vg.h"

#include <stdint.h>

#include "data_utils.h"
#include "gpio_custom_const.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "hal_mcal.h"
#include "interrupt_types.h"
#include "pin_types.h"

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
#endif

bool mcu_init(void) {
    bool res = true;
    res = microcontroller_custom_init();
    return res;
}
