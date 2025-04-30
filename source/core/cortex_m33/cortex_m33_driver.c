#include "cortex_m33_driver.h"

#include "log.h"
#include "core_select.h"
#include "cmsis_gcc.h"
#include "core_cm33.h"

bool cortex_m33_reboot(void) {
    LOG_WARNING(SYS, "RebootARMCortex-M33");
    __disable_irq();
    NVIC_SystemReset();
    return true;
}


