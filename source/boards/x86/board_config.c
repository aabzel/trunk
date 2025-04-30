#include "board_config.h"

#include "log.h"

bool board_init(void) {
    LOG_WARNING(SYS,"X86_BoardInit");
    return true;
}

bool is_ram_addr(uint32_t addr) {
    return true;
}
