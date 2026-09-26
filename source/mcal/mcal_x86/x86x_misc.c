#include "x86x_misc.h"

#include <stdbool.h>

//#include "array.h"
#ifdef HAS_LOG
#include "log.h"
#endif

uint32_t critical_nesting_level = 0U;

bool Fc7300xSdkStatusToRes(uint32_t ret) {
    bool res = false;

    return res;
}

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

static const Fc73StatusInfo_t Fc73StatusInfo[] = {};

const char* RetToStr(uint32_t ret) {
    char* name = "?";
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(Fc73StatusInfo);
    for(i = 0; i < cnt; i++) {
        if(ret == Fc73StatusInfo[i].ret) {
            name = Fc73StatusInfo[i].name;
            break;
        }
    }
    return name;
}

bool microcontroller_init(void) {
    bool res = true;
    return res;
}

#ifdef HAS_LOG
bool log_fc73_ret(const facility_t facility, uint32_t ret, const char* const in_text) {
    bool res = false;
    return res;
}
#endif
