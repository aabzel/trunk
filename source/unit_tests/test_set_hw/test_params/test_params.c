#include "test_params.h"

#include <stdbool.h>
#include <stdint.h>

#include "param_drv.h"
#include "param_types.h"
#include "unit_test_check.h"

bool test_param(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
#if 0
    set_log_level(PARAM, LOG_LEVEL_DEBUG);
    uint8_t value[5] = {0x0f, 0xc0, 0xca, 0x89, 0x36};
    char str[40] = "";
    ASSERT_TRUE(param_val2str(value, 1, TYPE_UINT8, str, sizeof(str)));
    ASSERT_STREQ(" 15", str);
    ASSERT_TRUE(param_val2str(value, 1, TYPE_INT8, str, sizeof(str)));
    ASSERT_STREQ(" 15", str);

    ASSERT_TRUE(param_val2str(&value[1], 4, TYPE_UINT32, str, sizeof(str)));
    ASSERT_STREQ("915000000", str);
    set_log_level(PARAM, LOG_LEVEL_INFO);
#endif
    return true;
}

static bool test_param_set_get_ll(uint8_t id, uint8_t test_data) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t wr_data = 0x55;
    uint8_t rd_data = 0;
    set_log_level(PARAM, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(param_set(id, &wr_data));
    ASSERT_TRUE(param_get(id, &rd_data));
    set_log_level(PARAM, LOG_LEVEL_INFO);
    ASSERT_EQ(rd_data, wr_data);
    return true;
}

bool test_param_set_get(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(PARAM, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(test_param_set_get_ll(PAR_ID_TEST_ID1, 0x55));
    ASSERT_TRUE(test_param_set_get_ll(PAR_ID_TEST_ID1, 0xAA));
    set_log_level(PARAM, LOG_LEVEL_INFO);
    return true;
}

bool test_param_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1, sizeof(Id_t));
    ASSERT_EQ(1, sizeof(StorageType_t));

    return true;
}
