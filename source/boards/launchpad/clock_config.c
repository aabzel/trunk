#include "clock_config.h"


#ifdef HAS_LOG
#include "log.h"
#endif

#include "sys_config.h"
#include "clocks.h"

bool clock_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(SYS, "ClockInit. XTAL:%u Hz", XTAL_FREQ_HZ);
#endif

    return res;
}
