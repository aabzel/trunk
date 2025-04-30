#include "test_pastilda.h"

#include <string.h>

#include "keyboard.h"
#include "log.h"
#include "pastilda.h"
#include "unit_test_check.h"
#include "utils_math.h"

bool test_pastilda_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

   // ASSERT_EQ(MAX_PASS_LEN, sizeof(Pastilda.password));
    return true;
}

bool test_pastilda_master_key_enter(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
#if 0
    KeyBoard_t key = {0};
    ASSERT_TRUE(pastilda_init_node(&Pastilda));

    key = Char2KeyCode('s');
    ASSERT_TRUE(pastilda_key_proc(&Pastilda, key));

    key.key_code[0] = KEY_CODE_TILDE;
    key.modifier.left_ctrl = 1;
    ASSERT_TRUE(pastilda_key_proc(&Pastilda, key));

    ASSERT_EQ(PAS_TILDA_STATE_KEEPAS, Pastilda.state);

    key.modifier.left_ctrl = 0;
    char test_pass[] = "qwerty";
    uint32_t i = 0;
    for(i = 0; i < strlen(test_pass); i++) {
        key = Char2KeyCode(test_pass[i]);
        ASSERT_TRUE(pastilda_key_proc(&Pastilda, key));
    }
    ASSERT_STREQ("qwerty", Pastilda.password);
    key.modifier.byte = 0;
    key.key_code[0] = KEY_CODE_ENTER_LEFT;
    ASSERT_TRUE(pastilda_key_proc(&Pastilda, key));

    ASSERT_EQ(PAS_TILDA_STATE_BYPASS, Pastilda.state);

    key = Char2KeyCode('e');
    ASSERT_TRUE(pastilda_key_proc(&Pastilda, key));

    ASSERT_EQ(0, sum_calc_u8((uint8_t*)Pastilda.password, MAX_PASS_LEN));
#endif

    return true;
}
