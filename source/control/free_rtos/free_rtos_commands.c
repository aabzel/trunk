#include "free_rtos_commands.h"

#include <stdint.h>
#include <string.h>

#include "log.h"
#include "free_rtos_diag.h"
#include "free_rtos_drv.h"
#include "FreeRTOS.h"
#include "task.h"

bool free_rtos_diag_command(int32_t argc, char *argv[]) {
    bool res = false;
    char WriteBuffer[40*4];
    memset(WriteBuffer,0,sizeof(WriteBuffer));
    if (0==argc) {
        res = true;
    }

    if(res) {
        vTaskList( WriteBuffer );
        cli_printf("%s",WriteBuffer);
    }
    return res;
}


