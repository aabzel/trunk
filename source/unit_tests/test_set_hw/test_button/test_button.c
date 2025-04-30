#include "test_button.h"

#include <string.h>

#include "log.h"
#include "clock.h"
#include "unit_test_check.h"
#include "button_drv.h"

bool test_button_types(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
    ASSERT_EQ(1, sizeof(Pad_t));
    ASSERT_EQ(1, sizeof(ButtonState_t));
    return true;
}

bool test_button_get(void){
    LOG_INFO(BUTTON, "%s()", __FUNCTION__);
    bool res = true;
    uint32_t i = 0;
    uint32_t button_cnt = button_get_cnt();
    LOG_INFO(BUTTON, "Cnt %u", button_cnt);
    ASSERT_EQ( BUTTON_COUNT, button_cnt);

    for(i = 1; i <= button_cnt; i++) {
    	LOG_INFO(BUTTON, "%u TestGet", i);
        ButtonState_t ButtonState=button_get(i);
        EXPECT_EQ( BUTTON_STATE_UNPRESSED, ButtonState);
    }

    return res;
}
