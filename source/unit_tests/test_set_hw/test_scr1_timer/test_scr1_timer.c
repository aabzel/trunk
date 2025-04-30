#include "test_scr1_timer.h"

#include "log.h"
#include "scr1_timer.h"
#include "scr1_timer_types.h"
#include "unit_test_check.h"

bool test_scr1_timer_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    // Sort it

    ASSERT_EQ(4, sizeof(Scr1TimerRegCTRL_t));
    ASSERT_EQ(4, sizeof(Scr1TimerRegDIV_t));
    ASSERT_EQ(4, sizeof(Scr1TimerRegMTIME_t));
    ASSERT_EQ(4, sizeof(Scr1TimerRegMTIMEH_t));
    ASSERT_EQ(4, sizeof(Scr1TimerRegMTIMECMP_t));
    ASSERT_EQ(4, sizeof(Scr1TimerRegMTIMECMPH_t));

    return true;
}
