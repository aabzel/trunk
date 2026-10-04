#include "board_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "log.h"
#include "data_utils.h"
#include "writer_config.h"
#include "board_config.h"


bool reboot_keyboard_command(int32_t argc, char* argv[]){
    bool res = false;

    if(0==argc) {
    	res = true;
    }

    if(res) {
    	res= keyboard_reboot();
    } else {
        LOG_ERROR(MIC2026, "Usage: kbr");
    }

    return res;
}

