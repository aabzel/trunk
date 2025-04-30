#include "win_utils.h"

#include <windows.h>

#include <Assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef HAS_STRING
#include "convert.h"
#endif
#include "log.h"

void clear_tui(void) { system("cmd /c cls"); }

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void win_color_enable(void) {
#if defined WIN32 || defined _WIN32 || defined WIN64 || defined _WIN64
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // References:
    // SetConsoleMode() and ENABLE_VIRTUAL_TERMINAL_PROCESSING?
    // https://stackoverflow.com/questions/38772468/setconsolemode-and-enable-virtual-terminal-processing

    // Windows console with ANSI colors handling
    // https://superuser.com/questions/413073/windows-console-with-ansi-colors-handling
#endif
}

static const char* CmdRetToStr(int ret) {
    char* name = "?";
    switch(ret) {
    case 0:
        name = "Ok";
        break;
    default:
        name = "Err";
        break;
    }
    return name;
}

// https://www.techonthenet.com/c_language/standard_library_functions/stdlib_h/system.php
bool win_cmd_run(const char* const command) {
    bool res = false;
    if(command) {
        LOG_DEBUG(PC, "ExeCmd:[%s],Size:%u", command, strlen(command));
        int ret = system(command);
        if(0 == ret) {
            res = true;
        } else {
            LOG_ERROR(PC, "Ret,%d=%s", ret, CmdRetToStr(ret));
        }
    }
    return res;
}

bool win_color_init(void) {
    bool res = true;
    srand(time(NULL));
    win_color_enable();
    return res;
}
