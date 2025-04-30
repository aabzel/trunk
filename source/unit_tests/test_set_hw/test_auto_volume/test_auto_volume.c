#include "test_auto_volume.h"

#include "unit_test_check.h"
#include "data_utils.h"
#include "auto_volume.h"

bool test_auto_volume_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    return res;
}

bool test_auto_volume_hash_set(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    set_log_level(AUTO_VOLUME, LOG_LEVEL_DEBUG);
    EXPECT_EQ(6 ,Dist2Volume(1.0) );
    EXPECT_EQ(-69 ,Dist2Volume(7.0) );

    EXPECT_EQ(127 ,int8_limiter(523) );
    EXPECT_EQ(56 ,int8_limiter(56) );
    EXPECT_EQ(-56 ,int8_limiter(-56) );
    EXPECT_EQ(-127 ,int8_limiter(-523) );


    set_log_level(AUTO_VOLUME,LOG_LEVEL_INFO);
    return res;
}

