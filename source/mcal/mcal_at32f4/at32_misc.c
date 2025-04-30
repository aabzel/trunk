#include "at32_misc.h"

#include <stdbool.h>

#include "array.h"
#include "log.h"

uint32_t critical_nesting_level = 0U;

bool isFromInterrupt(void) {
    bool res = false;
    /*TODO: Explore register SCB->ICSR */
    // res = ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0);
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

confirm_state OnOffToConfirmState(bool on_off) {
    confirm_state new_state = FALSE;
    switch((uint32_t)on_off) {
    case true:
        new_state = TRUE;
        break;
    case false:
        new_state = FALSE;
        break;
    default:
        new_state = FALSE;
        break;
    }
    return new_state;
}
