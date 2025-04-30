#include "watchdog_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "watchdog_custom.h"
#include "watchdog_custom_diag.h"


bool watchdog_raw_reg_command(int32_t argc, char* argv[]){
    bool res = false ;
    res = watchdog_raw_reg();
    return res;

}

bool watchdog_reg_map_command(int32_t argc, char* argv[]) {
    bool res = watchdog_diag_low_level();
    return res;
}



