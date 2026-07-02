#include "cli_diag.h"

#include <stdio.h>
#include <string.h>

#include "cli_drv.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "time_mcal.h"

const char* CliNodeToStr(const CliHandle_t* const Node) {
    if(Node) {
        uint32_t up_time_ms = time_get_ms32();
        int32_t rem_ms = CLI_WATCHDOT_EXIT_MS - ((int32_t)(up_time_ms - Node->rx_time_ms));

        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSilens:%u Ms,", text, rem_ms);
        snprintf(text, sizeof(text), "%sEcho:%u,", text, Node->echo);
        snprintf(text, sizeof(text), "%sRun:%u,", text, Node->run_cmd);
        snprintf(text, sizeof(text), "%sProc:%u Cnt,", text, Node->proc_cnt);
    }
    return text;
}

const char* CliConfigToStr(const CliConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCmdCnt:%u,", text, Config->cmd_cnt);
        snprintf(text, sizeof(text), "%sLED:%u,", text, Config->feedback_led);
        if(Config->CommandArray) {
            snprintf(text, sizeof(text), "%sCmds:%p,", text, Config->CommandArray);
        }
    }
    return text;
}

const char* CliCmdToStr(const CliCmdInfo_t* const Cmd) {
    if(Cmd) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%s%s,", text, Cmd->short_name);
        snprintf(text, sizeof(text), "%s%s,", text, Cmd->long_name);
        snprintf(text, sizeof(text), "%s%s,", text, Cmd->description);
        snprintf(text, sizeof(text), "%s%p", text, Cmd->handler);
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

bool cli_cmd_list_print(uint8_t num, const char* sub_name1, const char* sub_name2) {
    bool res = false;
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        const CliCmdInfo_t* CmdInfo = Node->CommandArray;
        cli_printf("AvailableCommands:");
        if(sub_name1) {
            cli_printf("Key1:%s" CRLF, sub_name1);
        }
        if(sub_name2) {
            cli_printf("Key2:%s" CRLF, sub_name2);
        }
        cli_putstr(CRLF);
        static const table_col_t cols[] = {{5, "Num"}, {10, "Acronym"}, {23, "CommandName"}, {13, "Description"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        while(CmdInfo->handler) {
            if(is_print_cmd(CmdInfo, sub_name1, sub_name2)) {
                char temp[150] = {0};
                memset(temp, 0, sizeof(temp));
                snprintf(temp, sizeof(temp), "%s", TSEP);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, num);
                snprintf(temp, sizeof(temp), "%s %8s " TSEP, temp, CmdInfo->short_name);
                snprintf(temp, sizeof(temp), "%s %21s " TSEP, temp, CmdInfo->long_name);
                snprintf(temp, sizeof(temp), "%s %11s " TSEP, temp, CmdInfo->description);
                cli_printf("%s" CRLF, temp);
#if 0
                cli_printf(TSEP);
                cli_printf(" %3u " TSEP, num);
                cli_printf(" %8s " TSEP, CmdInfo->short_name ? CmdInfo->short_name : "");
                cli_printf(" %21s " TSEP, CmdInfo->long_name ? CmdInfo->long_name : "");
                cli_printf(" %s ", CmdInfo->description ? CmdInfo->description : "");
                cli_printf(CRLF);
#endif
                res = true;
#ifdef HAS_NORTOS
#endif /*HAS_NORTOS*/
                num++;
            }
            CmdInfo++;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool cli_print_ascii(const uint8_t start_byte) {
    bool res = true;
    static const table_col_t cols[] = {
        {5, "Dec"},
        {11, "Bin"},
        {6, "Hex"},
        {5, "ch"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint16_t word = 0;
    for(word = start_byte; word <= 0xFF; word++) {
        uint8_t byte = (uint8_t)word;
        char temp[150] = {0};
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%s", TSEP);
        snprintf(temp, sizeof(temp), "%s %3d " TSEP, temp, byte);
        snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, utoa_bin8(byte));
        snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, byte);
        snprintf(temp, sizeof(temp), "%s [%c] " TSEP, temp, byte);
        cli_printf("%s" CRLF, temp);
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
