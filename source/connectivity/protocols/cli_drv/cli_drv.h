#ifndef CLI_DRIVER_H
#define CLI_DRIVER_H
/*
 * driver for Bash like UART console. Shell.
 * command line interface (CLI)
 */

#include "std_includes.h"
#include "cli_config.h"
#include "cli_diag.h"
#include "cli_types.h"

//#define NEW_LINE   '??/n'

const CliConfig_t* CliGetConfig(uint8_t num);
CliHandle_t* CliGetNode(uint8_t num);
const CliCmdInfo_t* CliCmdInfoGet(uint8_t num, const char* const name);

bool cli_init_custom(void);
bool cli_prepare_cmd(char* original_cmd);
// Arrow_t cli_arrows_parse(char cur_char);
bool cli_mcal_init(void);
bool cli_init_one(uint8_t num);
//bool cli_proc_one(uint8_t num);
//bool cli_proc(void);
bool cli_echo_putchar(char ch);
bool cli_parse_args(char* cmd_line, int* const argc, char** argv);
bool cli_set_echo(uint8_t num, bool echo_val);
bool cli_get_echo(uint8_t num);
bool cli_toggle_echo(uint8_t num);
bool cli_process_cmd(uint8_t num, char* const cmd_line);
bool cli_process_cmd_ll(CliHandle_t* const Node, char* const cmd_line);
bool help_dump_key(uint8_t num, const char* subName1, const char* subName2);
#ifdef HAS_RTOS
void cli_thread(void* arg);
void cli_create_task(void);
#endif

#endif /*CLI_DRIVER_H*/
