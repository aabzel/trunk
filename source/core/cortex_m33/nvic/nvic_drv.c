#include "nvic_drv.h"

#include <stdint.h>

#include "log.h"
#include "sys_config.h"

bool nvic_clear(void) {
    bool res = false;
    int8_t irq_n = 0;
    for(irq_n = NonMaskableInt_IRQn; irq_n <= MAX_IRQ_NUM; irq_n++) {
        // res = IS_NVIC_DEVICE_IRQ(irq_n) ;
        // if(res){
        NVIC_ClearPendingIRQ((IRQn_Type)irq_n);
        res = true;
        //}
    }

    return res;
}

bool nvic_init(void) {
    bool res = true;
    LOG_INFO(SYS, "IntInit");

    __enable_irq();
    return res;
}

bool nvic_disable(void) {
    bool res = true;
    int8_t irq_n = 0;
    for(irq_n = NonMaskableInt_IRQn; irq_n <= MAX_IRQ_NUM; irq_n++) {
        NVIC_DisableIRQ((IRQn_Type)irq_n);
    }
    return res;
}
