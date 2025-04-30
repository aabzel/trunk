#include "test_iwdg.h"

#include <string.h>

#include "iwdg_drv.h"
#include "log.h"
#include "unit_test_check.h"

bool test_iwdg_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(4, sizeof(iWdgRegKey_t));
    ASSERT_EQ(4, sizeof(iWdgRegPrescaler_t));
    ASSERT_EQ(4, sizeof(iWdgRegReload_t));
    ASSERT_EQ(4, sizeof(iWdgRegStatus_t));
    ASSERT_EQ(16,sizeof(iWdgRegMap_t));
    return true;
}

bool test_iwdg_set(void) {
    LOG_INFO(LG_IWDG, "%s()", __FUNCTION__);
    ASSERT_TRUE(iwdg_set_period_ms(20000));
    return true;
}

bool test_iwdg_get(void) {
    LOG_INFO(LG_IWDG, "%s()", __FUNCTION__);
    uint32_t period_ms = iwdg_get_period_ms();
    EXPECT_GR(0, period_ms);
    return true;
}
