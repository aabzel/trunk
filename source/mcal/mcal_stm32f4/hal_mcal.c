#include "hal_mcal.h"

#include "std_includes.h"
#include "stm32f4xx_hal_def.h" // err
#ifdef HAS_LOG
#include "log.h"
#endif

uint32_t critical_nesting_level = 0U;

bool HAL_retToRes(const HAL_StatusTypeDef ret) {
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
        res = false;
        break;
    }
    return res;
}

bool isFromInterrupt(void) {
    bool res = false;
    /*TODO: Explore register SCB->ICSR */
    // res = ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0);
    return res;
}

bool hal_init(void) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_Init();
    res = HAL_retToRes(ret);
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


void Error_Handler(void) {
#ifdef HAS_LOG
    LOG_ERROR(SYS, "Error");
#endif
    __disable_irq();
    while(1) {
    }
}
