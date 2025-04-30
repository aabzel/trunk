#include "cli_drv.h"
/**
 *  Description : Driver for Bash-like UART console.
 *  CLI-Command Line Interface
 */

#include <ctype.h>
#include <string.h>

#ifdef HAS_MINGW
#include <conio.h> /*for kbhit getch function. Clang/cygwin64 build error*/
#endif

#ifdef HAS_PC
#include <stdio.h>

#ifndef HAS_CLANG
#endif

#endif

#ifdef HAS_CSV
#include "csv.h"
#endif

#include "code_generator.h"
#include "table_utils.h"
#include "terminal_codes.h"

#ifdef HAS_FAT_FS
#include "fat_fs_drv.h"
#endif

#ifdef HAS_RTC
#include "rtc_mcal.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

#include "data_utils.h"
#include "log.h"
#include "string_reader.h"
#include "writer_config.h"
//#include "cli_commands.h"
#include "convert.h"
#include "sys_config.h"

#ifdef HAS_LOG
#include "writer_generic.h"
#endif /*HAS_LOG*/

#ifdef HAS_UART
#include "uart_mcal.h"
#endif /*HAS_UART*/

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#include "time_mcal.h"
#endif

#include "cli_config.h"
#include "str_utils.h"
#include "string_reader.h"

COMPONENT_GET_CONFIG(Cli, cli)
COMPONENT_GET_NODE(Cli, cli)

const CliCmdInfo_t* CliCmdInfoGet(uint8_t num, const char* const name) {
    const CliCmdInfo_t* DesiredCmd = NULL;
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        CliCmdInfo_t* CmdInfo = Node->CommandArray;
        if(CmdInfo) {
            while(CmdInfo->handler) {
                if((CmdInfo->long_name && __strcasecmp(CmdInfo->long_name, name) == 0) ||
                   (CmdInfo->short_name && __strcasecmp(CmdInfo->short_name, name) == 0)) {
                    DesiredCmd = CmdInfo;
                    break;
                }
                CmdInfo++;
            }
        }
    }
    return DesiredCmd;
}

/*logic AND for keyWords */
static bool is_print_cmd(const CliCmdInfo_t* const cmd, const char* const sub_name1, const char* const sub_name2) {
    bool res = false;
    if(NULL != cmd) {
        if((NULL == sub_name1) && (NULL == sub_name2)) {
            res = true;
        } else if((NULL != sub_name1) && (NULL == sub_name2)) {
            /*one subname done*/
            res = false;
            if(NULL != cmd->short_name) {
                if(NULL != str_case_str(cmd->short_name, sub_name1)) {
                    res = true;
                }
            }
            if(NULL != cmd->long_name) {
                if(NULL != str_case_str(cmd->long_name, sub_name1)) {
                    res = true;
                }
            }
            if(NULL != cmd->description) {
                if(NULL != str_case_str(cmd->description, sub_name1)) {
                    res = true;
                }
            }
        } else if((NULL != sub_name1) && (NULL != sub_name2)) {
            /*two subnames done*/
            res = false;
            if(NULL != cmd->short_name) {
                if(NULL != str_case_str(cmd->short_name, sub_name1)) {
                    if(NULL != str_case_str(cmd->short_name, sub_name2)) {
                        res = true;
                    }
                }
            }
            if(NULL != cmd->long_name) {
                if(NULL != str_case_str(cmd->long_name, sub_name1)) {
                    if(NULL != str_case_str(cmd->long_name, sub_name2)) {
                        res = true;
                    }
                }
            }
            if(NULL != cmd->description) {
                if(NULL != str_case_str(cmd->description, sub_name1)) {
                    if(NULL != str_case_str(cmd->description, sub_name2)) {
                        res = true;
                    }
                }
            }
        }
    }

    return res;
}

/*TODO test it*/
static bool cli_is_cli_char(char character) {
    bool res = false;
    res = is_hex_digit(character);
    if('a' <= character && character <= 'z') {
        res = true;
    }
    if('A' <= character && character <= 'Z') {
        res = true;
    }
    switch(character) {
    case ' ':
    case '{':
    case '}':
    case '[':
    case ']':
    case '>':
    case '<':
    case '(':
    case ')':
    case '.':
    case '@':
    case '#':
    case '^':
    case '%':
    case '$':
    case ',':
    case '"':
    case ':':
    case ';':
    case '_':
    case '-':
    case '|':
    case '\\':
    case '/':
    case '~':
    case '&':
    case '!':
    case '?':
    case KEY_ESC:
    case KEY_TAB:
    case KEY_BACKSPACE:
    case KEY_ENTER:
    case '+':
    case '=':
    case '*':
        res = true;
        break;
    }
    return res;
}

bool cli_echo_putchar(char ch) {
    bool res = true;
    res = cli_is_cli_char(ch);
    if(res) {
    } else {
        ch = '?';
    }
#ifdef HAS_LOG_COLOR
    if(Log.colored) {
        cli_putstr(VT_SETCOLOR_YELLOW);
    }
#endif
    (&curWriterPtr->stream)->f_putch(&curWriterPtr->stream, ch);
#ifdef HAS_LOG_COLOR
    if(Log.colored) {
        cli_putstr(VT_SETCOLOR_NORMAL);
    }
#endif
    return res;
}

#ifdef HAS_CLI_ARG_PARSER_LEGASY
bool cli_parse_args(char* cmd_line, int* argc, char** argv) {
    bool res = false;
    int argc_loc = 0;
    char* pRun = cmd_line;
    while((argc_loc < SHELL_MAX_ARG_COUNT) && (0x00 != *pRun)) {
        while(isspace((int)*pRun)) {
            pRun++;
        }
        if('\0' != *pRun) {
            argv[argc_loc] = (char*)pRun;
            argc_loc++;
            res = true;
            while(*pRun && !isspace((int)*pRun)) {
                pRun++;
            }
            if(*pRun != '\0') {
                *pRun = '\0';
                pRun++;
            }
        }
    } /*while*/
    (*argc) = argc_loc;

    return res;
}
#endif

/*
 cmd_line must be in RAM due to char replacement
 TODO: make cmd_line unchangeable
 char** argv - array of pointers
 argv - returned array of pointers to memory in cmd_line
 h vi->argc:2 ; 0:[h] 1:[vi]
 */
bool cli_parse_args(char* cmd_line, int* const argc, char** argv) {
    bool res = false;
    if(argc) {
        LOG_DEBUG(CLI, "ParseArgs[%s]", cmd_line);
        size_t size = strlen(cmd_line);
        uint32_t ok = 0;
        uint32_t cnt = csv_cnt(cmd_line, ' ');
        *argc = cnt;
        LOG_DEBUG(CLI, "Tockens:%u", cnt);

        replace_char(cmd_line, ' ', 0x00);
        uint32_t i = 0;
        uint32_t offset = 0;
        for(i = 0; i < cnt; i++) {
            offset = 0;
            res = csv_fetch_text(cmd_line, size, 0x00, i, &offset);
            if(res) {
                LOG_DEBUG(CLI, "%u:[%s]", offset, &cmd_line[offset]);
                argv[i] = &cmd_line[offset];
                ok++;
            }
        }
        if(ok) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

static void cli_prompt_ll(CliHandle_t* Node) {
    LOG_DEBUG(CLI, "prompt");
    if(Node) {
        if(Node->echo) {
            char time_stamp[40] = "";
#ifdef HAS_TIME
            time_get_time_str(time_stamp, sizeof(time_stamp));
#endif
#ifdef HAS_RTC
            struct tm time_date = {0};
            bool res = rtc_get(1, &time_date);
            if(res) {
                res = TimeDate2Str(&time_date, time_stamp, sizeof(time_stamp));
            }
#endif
            cli_printf("%s%s", time_stamp, CLI_CURSOR);
        } else {
            LOG_DEBUG(CLI, "EchOff");
        }
    } else {
        LOG_DEBUG(CLI, "NodeErr");
    }
}

/*TODO test it!*/
bool cli_prepare_cmd(char* original_cmd) {
    bool res = false;
    if(original_cmd) {
        // if(size) {
        uint32_t del = 0;
        size_t size = 0;
        size = strlen(original_cmd);
        LOG_DEBUG(CLI, "OrigCommand:[%s],%u byte", original_cmd, size);

        del = str_delete_first(original_cmd, size, ' ');
        LOG_DEBUG(CLI, "DelF:[%s]:%u", original_cmd, del);

        size = strlen(original_cmd);
        del = string_delete_end(original_cmd, size, ' ');
        LOG_DEBUG(CLI, "DelB:[%s]:%u", original_cmd, del);

        size = strlen(original_cmd);
        del = string_delete_continuous_duplicat(original_cmd, ' ');
        LOG_DEBUG(CLI, "DelDupSpaces:[%s]:%u", original_cmd, del);
        size = strlen(original_cmd);
        LOG_DEBUG(CLI, "CleanCommand:[%s]:%u", original_cmd, size);
        res = true;
        //}
    }
    return res;
}

static bool cli_process_one_cmd(CliHandle_t* Node, char* original_cmd) {
    bool res = false;
    size_t cmd_len = strlen(original_cmd);
    memset(Node->in_cmd_line, 0, sizeof(Node->in_cmd_line));
    strncpy(Node->in_cmd_line, original_cmd, cmd_len);

    res = cli_prepare_cmd(Node->in_cmd_line);

    cmd_len = strlen(Node->in_cmd_line);
    LOG_DEBUG(CLI, "ProcCommand:[%s],%u byte", Node->in_cmd_line, cmd_len);
    static char* shell_argv[SHELL_MAX_ARG_COUNT];
    memset(shell_argv, 0, sizeof(shell_argv));

    if(cmd_len) {

#ifdef HAS_CLI_DEBUG
        Node->cmd_len_max = MIN(Node->cmd_len_max, cmd_len);
#endif /*HAS_CLI_DEBUG*/

#ifdef HAS_CLI_CMD_HISTORY
        if(0 < cmd_len) {
            if(cmd_len < sizeof(Node->prev_cmd)) {
                memset(Node->prev_cmd, 0x00, sizeof(Node->prev_cmd));
                strncpy(Node->prev_cmd, Node->in_cmd_line, sizeof(Node->prev_cmd));
                /*TODO: add to FIFO*/
            }
        }
#endif /*HAS_CLI_CMD_HISTORY*/
        static int cli_argc = 0;
        // const CliCmdInfo_t* CmdInfo = shell_commands;

        /*TODO: make a single function for argument parsing*/
        cli_argc = 0;
        res = cli_parse_args(Node->in_cmd_line, &cli_argc, &shell_argv[0]); // 1s
        if(res) {
            LOG_DEBUG(CLI, "Argc:%u", cli_argc);
            if(0 == cli_argc) {
                cli_prompt_ll(Node);
                res = false;
            }

            if(res) {
                const CliCmdInfo_t* CmdInfo = CliCmdInfoGet(Node->num, shell_argv[0]); // 3s
                if(CmdInfo) {
                    res = CmdInfo->handler(cli_argc - 1, shell_argv + 1);
                    if(false == res) {
                        LOG_ERROR(CLI, "CmdError:[%s] ", shell_argv[0]);
                    } else {
                        LOG_DEBUG(CLI, "CmdOk![%s]", shell_argv[0]);
                    }
                    // cli_prompt_ll(Node);
                } else {
                    LOG_ERROR(CLI, "UnknownCommand [%s]", shell_argv[0]);
                }
            }
        }
        if(res) {
            if(Node->log_commands) {

#ifdef HAS_FAT_FS

                if(1 <= cmd_len) {
                    res = fat_fs_write(CLI_HISTORY_FILE, Node->in_cmd_line);
                }

#endif
            }
        } else {
            LOG_DEBUG(CLI, "UnknownCommand [%s]", Node->in_cmd_line);
#ifdef HAS_CLI_CMD_HISTORY
            memset(&Node->prev_cmd[0], 0x00, sizeof(Node->prev_cmd));
#endif
        }
    } // len

    cli_prompt_ll(Node);

    return res;
}

bool cli_process_cmd_ll(CliHandle_t* const Node, char* const cmd_line) {
    bool res = false;
    LOG_DEBUG(CLI, "Commands:[%s]", cmd_line);

#ifdef HAS_CLI_SUB_COMMAND
    uint32_t cnt = csv_cnt(cmd_line, ';');
    LOG_DEBUG(CLI, "SubCmdCnt:%u", cnt);

    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        char SubCmd[500] = {0};
        memset(SubCmd, 0, sizeof(SubCmd));
        res = csv_parse_text(cmd_line, ';', i, SubCmd, sizeof(SubCmd));
        if(res) {
            uint32_t len = strlen(SubCmd);
            LOG_DEBUG(CLI, "i:%u,SubCmdLen:%u", i, len);
            res = cli_process_one_cmd(Node, SubCmd);
        } else {
            LOG_ERROR(CLI, "Parse:%u SubCmdErr", i);
        }
    }
    if(0 == cnt) {
        cli_prompt_ll(Node);
    }
#else
    res = cli_process_one_cmd(Node, cmd_line);
#endif

    return res;
}

bool cli_init_custom(void) {
    bool res = true;
    return res;
}

bool cli_process_cmd(uint8_t num, char* const cmd_line) {
    bool res = false;
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        if(false == Node->run_cmd) {
            Node->run_cmd = true;
            res = cli_process_cmd_ll(Node, cmd_line);
            Node->run_cmd = false;
        }
    }
    return res;
}

static bool cli_is_cmd_unique(uint8_t num, const CliCmdInfo_t* const CmdPtr) {
    bool res = false;
    uint32_t cnt = 0;
    // LOG_INFO(CLI, "%s", __FUNCTION__);
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        const CliCmdInfo_t* CmdInfo = Node->CommandArray;
        int ret = 0;
        while(CmdInfo->handler) {
            ret = strcmp(CmdInfo->short_name, CmdPtr->short_name);
            if(0 == ret) {
                cnt++;
            }
            CmdInfo++;
        }
        if(1 == cnt) {
            res = true;
        } else {
            LOG_ERROR(CLI, "Cmd [%s] Spot %u times", CmdPtr->short_name, cnt);
            res = false;
        }
    }
    // LOG_INFO(CLI, "%s Done", __FUNCTION__);
    return res;
}

/*Run-Time check to spot flash memory leak!*/
static bool cli_check_unique_commands(uint8_t num) {
    bool res = false, out_res = true;
    LOG_INFO(CLI, "%s,Num:%u", __FUNCTION__, num);
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        LOG_INFO(CLI, "%s:%u", __FUNCTION__, __LINE__);
        uint32_t cnt = 0;
        const CliCmdInfo_t* CmdInfo = Node->CommandArray;
        if(CmdInfo) {
            while(CmdInfo->handler) {
                // LOG_INFO(CLI, "%s:%u", __FUNCTION__,__LINE__ );
                res = cli_is_cmd_unique(num, CmdInfo);
                if(false == res) {
#ifdef HAS_CLI_DIAG
                    LOG_ERROR(CLI, "DuplicateCmd:%s", CliCmdToStr(CmdInfo));
#endif
                    out_res = false;
                } else {
                    cnt++;
                }
                CmdInfo++;
            }
        }
        if(res) {
            LOG_INFO(CLI, "All %u CommandsUnique", cnt);
        } else {
            LOG_ERROR(CLI, "NotAll %u CommandsUnique", cnt);
        }
    }
    LOG_INFO(CLI, "%s Done", __FUNCTION__);
    return out_res;
}

bool help_dump_key(uint8_t num, const char* sub_name1, const char* sub_name2) {
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
        static const table_col_t cols[] = {{5, "Num"}, {10, "Acronym"}, {22, "CommandName"}, {13, "Description"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        while(CmdInfo->handler) {
            if(is_print_cmd(CmdInfo, sub_name1, sub_name2)) {
                cli_printf(TSEP);
                cli_printf(" %3u " TSEP, num);
                cli_printf(" %8s " TSEP, CmdInfo->short_name ? CmdInfo->short_name : "");
                cli_printf(" %20s " TSEP, CmdInfo->long_name ? CmdInfo->long_name : "");
                cli_printf(" %s ", CmdInfo->description ? CmdInfo->description : "");
                cli_printf(CRLF);
                res = true;
#ifdef HAS_NORTOS
                // wait_in_loop_ms(1);
#endif /*HAS_NORTOS*/
                num++;
            }
            CmdInfo++;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool cli_set_echo(uint8_t num, bool echo_val) {
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        Node->echo = echo_val;
    }
    return true;
}

bool cli_get_echo(uint8_t num) {
    bool res = false;
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        res = Node->echo;
    }
    return res;
}

bool cli_toggle_echo(uint8_t num) {
    bool res = false;
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        Node->echo = !Node->echo;
        res = true;
    }
    return res;
}

#ifdef HAS_RTOS
void cli_thread(void* arg) {
    for(;;) {
        cli_proc();
#ifdef HAS_FREE_RTOS
        vTaskDelay(200 / portTICK_RATE_MS);
#endif /*HAS_FREE_RTOS*/
    }
}
#endif

#if 0
bool cli_proc_one(uint8_t num) {
    bool res = false;
    CliHandle_t* Node = CliGetNode(num);
    if(Node) {
        Node->proc_cnt++;

#ifdef HAS_PC
        // int character = getch();
        int is_pressed = 0;
        is_pressed = kbhit(); /*Works with MinGW (32bit)*/
        if(is_pressed) {
            char key_char = _getch();
            LOG_DEBUG(CLI, "0x%x=%u=[%c]", key_char, key_char, key_char);
            string_reader_rx_callback(&Node->Reader, key_char);
            res = true;
        }
#endif /*HAS_PC*/

    }
    return res;
}
#endif

static bool CliIsValidConfig(const CliConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }

    if(0 == Config->CommandArray) {
        LOG_ERROR(CLI, "NoCmds");
        res = false;
    }

    if(0 == Config->cmd_cnt) {
        LOG_ERROR(CLI, "CmdCntErr");
        res = false;
    }

    if(!Config->valid) {
        LOG_ERROR(CLI, "NoValid");
        res = false;
    }
    return res;
}

bool cli_init_one(uint8_t num) {
    bool res = false;
    const CliConfig_t* Config = CliGetConfig(num);
    if(Config) {
#ifdef HAS_CLI_DIAG
        LOG_WARNING(CLI, "%s", CliConfigToStr(Config));
#endif
        res = CliIsValidConfig(Config);
        if(res) {
            CliHandle_t* Node = CliGetNode(num);
            if(Node) {
                LOG_WARNING(CLI, "Init: %u", num);
                Node->num = Config->num;
                Node->feedback_led = Config->feedback_led;
                Node->CommandArray = Config->CommandArray;
                Node->cmd_cnt = Config->cmd_cnt;
                Node->valid = true;
                LOG_INFO(CLI, "%u Commands", Node->cmd_cnt);

                set_log_level(CLI, LOG_LEVEL_PROTECTED);
#ifdef HAS_CLI_CMD_HISTORY
                memset(&Node->prev_cmd[0], 0x00, sizeof(Node->prev_cmd));
#endif
                res = writer_init();
                Node->echo = true;
                Node->cmd_len_max = 0;
                Node->output = true;
                // Node->cmd_cnt = cli_commands_get_cnt();
                set_log_level(CLI, LOG_LEVEL_NOTICE);
                res = cli_check_unique_commands(num);
                if(res) {
                    LOG_INFO(CLI, "All %u CommandsUnique!", Node->cmd_cnt);
                    res = true;
                } else {
                    LOG_ERROR(CLI, "DuplicandCommands", Node->cmd_cnt);
                    res = false;
                }
                Node->init_done = true;
                set_log_level(CLI, LOG_LEVEL_INFO);
            } // CliGetNode
        }     // CliIsValidConfig
    }
    return res;
}

// COMPONENT_PROC_PATTERT(CLI, CLI, cli)

COMPONENT_INIT_PATTERT(CLI, CLI, cli)
