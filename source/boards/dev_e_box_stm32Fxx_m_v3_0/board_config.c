#include "board_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

const Wire_t Wires[] = {
};

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS, LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall: %u Hz", XTAL_FREQ_HZ);
#endif
    return res;
}

