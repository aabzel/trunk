#include "rtos_commands.h"

#include <stdint.h>
#include <string.h>

#include "log.h"
#include "rtos_diag.h"
#include "rtos_drv.h"

bool rtos_diag_command(int32_t argc, char *argv[]) {
    bool res = false;
    char WriteBuffer[40*4];
    memset(WriteBuffer,0,sizeof(WriteBuffer));
    if (0==argc) {
        res = true;
    }

    if(res) {
        cli_printf("%s",WriteBuffer);
    }
    return res;
}


