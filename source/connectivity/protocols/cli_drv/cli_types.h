#ifndef CLI_TYPES_H
#define CLI_TYPES_H

#include <std_includes.h>

#include "cli_const.h"
//#include "sys_constants.h"
//#include "string_reader.h"
#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef bool (*shellcmd_t)(int32_t argc, char* argv[]);

typedef struct {
    const char* short_name;
    const char* long_name;
    const char* description;
    const shellcmd_t handler;
} CliCmdInfo_t;

#define CLI_COMMON_VARIABLES      \
    uint8_t num;                  \
    bool valid;                   \
    CliCmdInfo_t* CommandArray;   \
    uint32_t cmd_cnt;             \
    uint8_t feedback_led;

typedef struct {
    CLI_COMMON_VARIABLES
    char * name;
} CliConfig_t;

typedef struct {
	CLI_COMMON_VARIABLES
    bool echo;
    bool init_done;
    bool log_commands;
    bool run_cmd;
    uint32_t cmd_len_max;
    bool output;
#ifdef HAS_CLI_CMD_HISTORY
    char prev_cmd[CLI_LEN_MAX_SIZE];
#endif /*HAS_CLI_CLI_HISTORY*/
    char in_cmd_line[CLI_LEN_MAX_SIZE];
    uint32_t proc_cnt;

} CliHandle_t;



#endif /*CLI_TYPES_H*/
