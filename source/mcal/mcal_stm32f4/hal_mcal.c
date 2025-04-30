#include "hal_mcal.h"

#include <stdbool.h>

#include "stm32f4xx_hal_def.h"// err

uint32_t critical_nesting_level = 0U;

bool isFromInterrupt(void) {
    bool res = false;
    /*TODO: Explore register SCB->ICSR */
    // res = ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0);
    return res;
}

bool hal_init(void) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_Init();
    if(HAL_OK == ret) {
        res = true;
    }
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
