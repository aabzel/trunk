#include "test_dtmf.h"

#include <string.h>

#include "dtmf_drv.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_dtmf_types(void){
    LOG_INFO(DTMF, "%s()", __FUNCTION__);
    ASSERT_EQ(2,sizeof(SampleType_t));
    return true;
}

#define DTMF_NUM 1
#define DTMF_PLAY_DURATION_MS 250

bool test_dtmf_chars(void){
    LOG_INFO(DTMF, "%s()", __FUNCTION__);

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '0', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '1', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '2', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '3', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '4', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '5', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '6', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '7', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '8', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '9', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, 'A', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, 'B', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, 'C', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, 'D', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '*', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));

    ASSERT_TRUE(dtmf_send_char(DTMF_NUM, '#', DTMF_PLAY_DURATION_MS));
    ASSERT_TRUE( wait_in_loop_ms(DTMF_PLAY_DURATION_MS));
    return true;
}


