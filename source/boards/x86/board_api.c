#include "board_api.h"

#include "log.h"

bool board_init(void) {
    LOG_WARNING(SYS,"X86_BoardInit");
    return true;
}

bool is_ram_addr(uint32_t addr) {
    return true;
}

bool application_launch(uint32_t base_address){
    return false;
}


bool application_mcal_init(void){
    return true;
}
