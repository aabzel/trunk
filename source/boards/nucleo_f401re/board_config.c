#include "board_config.h"

#include "log.h"

bool board_init(void) {
    bool res = true;
    set_log_level(SYS, LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall: %u Hz", XTAL_FREQ_HZ);
    return res;
}

