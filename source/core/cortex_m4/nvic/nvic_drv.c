#include "nvic_drv.h"

#include <stdint.h>

#include "compiler_mcal.h"
#include "log.h"
#include "microcontroller_types.h"
#ifdef HAS_EHAL
#include "miscellaneous_ehal.h"
#endif

#ifdef HAS_CMSIS
//#include "core_cm4.h"
#endif

bool nvic_clear(void) {
    bool res = false;
    int8_t irq_n = 0;
    for(irq_n = NON_MASKABLE_INT_IRQ_N; irq_n <= MAX_IRQ_NUM; irq_n++) {
        // res = IS_NVIC_DEVICE_IRQ(irq_n) ;
        // if(res){
#ifdef HAS_CMSIS
        NVIC_ClearPendingIRQ((IRQn_Type)irq_n);
#endif
        res = true;
        //}
    }

    return res;
}

bool nvic_init(void) {
    bool res = true;
    LOG_INFO(SYS, "IntInit");
#ifdef HAS_CMSIS
    __enable_irq();
#endif
    return res;
}

bool nvic_disable(void) {
    bool res = true;
    int8_t irq_n = 0;
    for(irq_n = NON_MASKABLE_INT_IRQ_N; irq_n <= MAX_IRQ_NUM; irq_n++) {
#ifdef HAS_CMSIS
        NVIC_DisableIRQ((IRQn_Type)irq_n);
#endif
    }
    return res;
}

bool nvic_is_valid_irq_num(int16_t IRQn) {
    bool res = false;
    if(IRQn <= MAX_IRQ_NUM) {
        res = true;
    }
    return res;
}
