#include "hal_mcal.h"

#include <stdbool.h>

uint32_t critical_nesting_level = 0U;

bool isFromInterrupt(void) {
    bool res = false;
    /*TODO: Explore register SCB->ICSR */
    // res = ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0);
    return res;
}

bool hal_init(void) {
    bool res = false;
    return res;
}

void enter_critical(void) {
    if(!isFromInterrupt()) {
        if(critical_nesting_level == 0) {
            _disable_interrupt_();
        }
        critical_nesting_level++;
    }
}

void exit_critical(void) {
    if(!isFromInterrupt()) {
        if(critical_nesting_level) {
            critical_nesting_level--;
            if(critical_nesting_level == 0) {
                _enable_interrupt_();
            }
        }
    }
}

bool MIK32_HalRetToRes(const HAL_StatusTypeDef ret) {
    bool res = false;
    switch(ret) {
    case HAL_OK:
        res = true;
        break;
    case HAL_ERROR:
        res = false;
        break;
    case HAL_BUSY:
        res = false;
        break;
    case HAL_TIMEOUT:
        res = false;
        break;
    default:
        break;
    }
    return res;
}
