#include "test_systick.h"

#include <string.h>

#include "clock.h"
#include "systick_mcal.h"
#include "unit_test_check.h"

bool test_systick_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
#ifdef HAS_STM32
    uint32_t SysClock = HAL_RCC_GetSysClockFreq();
    LOG_INFO(TEST, "SysClock %u Hz", SysClock);
    ASSERT_EQ(SYS_FREQ, SysClock);

    ASSERT_EQ(1, sizeof(IRQn_Type));
    ASSERT_EQ(4, sizeof(SysTickCntl_t));
    ASSERT_EQ(4, sizeof(SysTickReload_t));
    ASSERT_EQ(4, sizeof(SysTickValue_t));
    ASSERT_EQ(4, sizeof(SysTickCalibValue_t));
    ASSERT_EQ(16, sizeof(SysTickMap_t));
#endif
    return true;
}
