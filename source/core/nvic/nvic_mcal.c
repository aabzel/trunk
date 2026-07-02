#include "nvic_drv.h"

#include <stdint.h>

#include "microcontroller.h"

#ifdef HAS_LOG
#include "log.h"
#endif

bool nvic_clear(void) {
    bool res = false;
#ifdef HAS_VENDOR_SDK
    int16_t irq_n = 0;
    for(irq_n = (int16_t)NonMaskableInt_IRQn; irq_n <= ((int16_t)MAX_IRQ_NUM); irq_n++) {
        // res = IS_NVIC_DEVICE_IRQ(irq_n) ;
        // if(res){
#ifdef HAS_CMSIS
        NVIC_ClearPendingIRQ((IRQn_Type)irq_n);
#endif
        res = true;
        //}
    }
#endif

    return res;
}

bool nvic_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(SYS, "IntInit");
#endif

#ifdef HAS_CMSIS
    __enable_irq();
#endif
    return res;
}

bool nvic_disable(void) {
    bool res = true;
#ifdef HAS_VENDOR_SDK
    int16_t irq_n = 0;
    for(irq_n = ((int16_t)NonMaskableInt_IRQn); irq_n <= ((int16_t)MAX_IRQ_NUM); irq_n++) {
#ifdef HAS_CMSIS
        NVIC_DisableIRQ((IRQn_Type)irq_n);
#endif
    }
#endif
    return res;
}

bool nvic_irq_ctrl(int16_t irq_n, const bool on_off) {
    bool res = true;
#ifdef HAS_VENDOR_SDK
#ifdef HAS_LOG
    LOG_INFO(LG_NVIC, "IRQ:%d,EN:%u", irq_n, on_off);
#endif
    if(on_off) {
        NVIC_EnableIRQ((IRQn_Type)irq_n);
    } else {
        NVIC_DisableIRQ((IRQn_Type)irq_n);
    }
#endif
    return res;
}

bool nvic_ctrl(const bool on_off) {
    bool res = true;
#ifdef HAS_VENDOR_SDK
#ifdef HAS_LOG
    LOG_INFO(LG_NVIC, "EN:%u", on_off);
#endif
    if(on_off) {
        __enable_irq();
    } else {
        __disable_irq();
    }
#endif
    return res;
}

bool nvic_is_valid_irq_num(int16_t IRQn) {
    bool res = false;
    if(IRQn <= ((int16_t)MAX_IRQ_NUM)) {
        res = true;
    }
    return res;
}
