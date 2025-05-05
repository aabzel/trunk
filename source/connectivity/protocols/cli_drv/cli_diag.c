#include "cli_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"

const char* CliConfigToStr(const CliConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCmdCnt:%u,", text, Config->cmd_cnt);
#ifdef HAS_LED
        snprintf(text, sizeof(text), "%sLED:%u", text, Config->feedback_led);
#endif
        snprintf(text, sizeof(text), "%sCmdArray:0x%p,", text, Config->CommandArray);
    }
    return text;
}

const char* CliCmdToStr(const CliCmdInfo_t* const Cmd) {
    if(Cmd) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, Cmd->short_name);
        snprintf(text, sizeof(text), "%s%s,", text, Cmd->long_name);
        snprintf(text, sizeof(text), "%s%s,", text, Cmd->description);
        snprintf(text, sizeof(text), "%s0x%p", text, Cmd->handler);
    }
    return text;
}

bool cli_argument_diag(const int32_t argc, char* argv[]) {
    bool res = false;
    int32_t i = 0;
    strcpy(text, "");
    snprintf(text, sizeof(text), "%sargc:%d", text, argc);
    for(i = 0; i < argc; i++) {
        snprintf(text, sizeof(text), "%sargv[%d]=[%s],", text, i, argv[i]);
        res = true;
    }

    LOG_DEBUG(CLI, "%s", text);
    return res;
}
