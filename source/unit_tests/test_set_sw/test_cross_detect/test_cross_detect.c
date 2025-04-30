#include "test_cross_detect.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "cross_detect_drv.h"
#include "log.h"
#include "unit_test_check.h"

bool test_cross_detect_types(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CROSS_DETECT, LOG_LEVEL_DEBUG);

    ASSERT_EQ(1,sizeof(CrossDetectFault_t));
    ASSERT_EQ(1,sizeof(CrossDetectState_t));
    ASSERT_EQ(2,sizeof(CrossDetectStateMeasure_t));

    ASSERT_EQ(36,cross_detect_get_lut_size( ) );

    uint8_t pin_cnt = cross_detect_get_pin_cnt();
    ASSERT_GR(2,pin_cnt);
    set_log_level(CROSS_DETECT,LOG_LEVEL_INFO);
    return res;
}


bool test_cross_detect_functions(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CROSS_DETECT, LOG_LEVEL_DEBUG);
    /*
     *  0 1 2 3 4
     *0 x
     *1   x
     *2     x
     *3       x
     *4         x
     */
    U16Pair_t pair = {0};
    U16Pair_t out;

    pair.a=0;  pair.b=4; pair.max=5;
    out = calc_next_uniq_u16pair(pair);
    ASSERT_EQ(1, out.a);
    ASSERT_EQ(0, out.b);

    pair.a=4;  pair.b=1; pair.max=5;
    out = calc_next_uniq_u16pair(pair);
    ASSERT_EQ(4, out.a);
    ASSERT_EQ(2, out.b);

    pair.a=4;  pair.b=0; pair.max=5;
    out = calc_next_uniq_u16pair(  pair);
    ASSERT_EQ(4, out.a);
    ASSERT_EQ(1, out.b);

    pair.a=0;  pair.b=1; pair.max=5;
    out = calc_next_uniq_u16pair(  pair);
    ASSERT_EQ(0, out.a);
    ASSERT_EQ(2, out.b);


    set_log_level(CROSS_DETECT,LOG_LEVEL_INFO);
    return res;
}




