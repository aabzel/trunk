#include "clock_config.h"

#include "log.h"
#include "sys_config.h"
#include "clock.h"
//#include "clock_custom.h"

ClockConfig_t ClockConfig = {
    .valid = true,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};




__attribute__((weak)) bool clock_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(SYS, "ClockInit");
#endif

    return res;
}
