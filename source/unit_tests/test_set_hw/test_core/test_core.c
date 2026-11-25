#include "test_core.h"

#include <string.h>

#include "core_driver.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

#ifdef HAS_CORE_DIAG
#include "core_diag.h"
#endif

bool test_core_is_interrupt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    bool is_interrupt = core_is_interrupt();
    EXPECT_FALSE(is_interrupt);

    return res;
}

