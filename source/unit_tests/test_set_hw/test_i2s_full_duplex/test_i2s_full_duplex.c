#include "test_i2s_full_duplex.h"

#include "i2s_full_duplex.h"
#include "log.h"
#include "time_mcal.h"
#include "unit_test_assert.h"

bool test_i2s_full_duplex_proc_duration(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);

    I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(1);
    ASSERT_NE(0, Node);
    uint64_t start = time_get_us();
    ASSERT_TRUE(i2s_full_duplex_data_proc_ll(Node, 1));
    uint64_t end = time_get_us();
    uint64_t duration = end - start;
    LOG_INFO(I2S, "Duration:%llu us", duration);
    ASSERT_GR(duration, 5000)
    return true;
}
