#include "board_config.h"

#include "log.h"

bool board_init(void) {
    LOG_WARNING(SYS,"X86_BoardInit");
    return true;
}

bool board_boost(bool on_off) {
    bool res = true;
    return res;
}

#if 0
bool is_ram_addr(uint32_t addr) {
    return true;
}
#endif
