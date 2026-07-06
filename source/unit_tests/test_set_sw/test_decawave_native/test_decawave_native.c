#include "test_decawave_native.h"

#include "decawave_native.h"
#include "log.h"
#include "system.h"
#include "unit_test_check.h"

bool test_decawave_native_types(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE_NATIVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE_NATIVE, LOG_LEVEL_DEBUG);

    EXPECT_EQ(2, sizeof(DecaWaveNativeFrame_t));
    EXPECT_EQ(12, sizeof(DecaWaveBlinkFrame_t));
    EXPECT_EQ(5, sizeof(DecaWaveRangingInitMessage_t));
    EXPECT_EQ(22, sizeof(DecaWaveRangingInitFrame_t));

    set_log_level(DECAWAVE_NATIVE, LOG_LEVEL_INFO);

    return res;
}

bool test_decawave_native_nodes(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE_NATIVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE_NATIVE, LOG_LEVEL_DEBUG);

    EXPECT_NE(0, DecaWaveNativeGetConfig(1));
    EXPECT_NE(0, DecaWaveNativeGetNode(1));

    set_log_level(DECAWAVE_NATIVE, LOG_LEVEL_INFO);
    return res;
}




