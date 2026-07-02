#ifndef CLI_TYPES_H
#define CLI_TYPES_H

#include <std_includes.h>

#include "cli_const.h"

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
    uint8_t rtc_num;              \
    bool valid;                   \
    CliCmdInfo_t* CommandArray;   \
    char * name;                  \
    uint32_t cmd_cnt;             \
    uint8_t feedback_led;

typedef struct {
    CLI_COMMON_VARIABLES
} CliConfig_t;

typedef struct {
	CLI_COMMON_VARIABLES
    bool echo;
    bool init_done;
    bool log_commands;
    bool output;
    bool run_cmd;
    uint32_t rx_time_ms;
    uint32_t cmd_len_max;
#ifdef HAS_CLI_CMD_HISTORY
    char prev_cmd[CLI_LEN_MAX_SIZE];
#endif
    char in_cmd_line[CLI_LEN_MAX_SIZE];
    uint32_t proc_cnt;

} CliHandle_t;



#endif /*CLI_TYPES_H*/
