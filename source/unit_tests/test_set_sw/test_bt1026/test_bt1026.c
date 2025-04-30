#include "test_bt1026.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bt1026_drv.h"
#include "log.h"
#include "unit_test_check.h"
#include "bt1026_config.h"
#include "audio_types.h"

bool test_bt1026_parse(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    log_level_t origin = log_level_get_set(BT1026, LOG_LEVEL_DEBUG);

    Bt1026Item.i2scfg_val = 0;
    ASSERT_TRUE(bt1026_parse_line("+I2SCFG=65", 10));
    ASSERT_EQ(65, Bt1026Item.i2scfg_val);

    set_log_level(BT1026, origin);
    return true;
}

bool test_bt1026_types(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_t origin = log_level_get_set(BT1026, LOG_LEVEL_DEBUG);

    ASSERT_EQ(1,sizeof(Bt1026I2sConfig_t));
    ASSERT_EQ(4,sizeof(SampleType_t));

    set_log_level(BT1026, origin);
    return true;
}


