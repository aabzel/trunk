#ifndef CLI_CONST_H
#define CLI_CONST_H

#include "cli_dep.h"
#include "time_mcal.h"

#define CLI_HISTORY_FILE "hist.txt"
#define CLI_MANAGER_NAME "CLI"
#define CLI_CURSOR "-->"
#define CLI_UART CONFIG_UART_0
#define CLI_LEN_MAX_SIZE 40
#define SHELL_MAX_ARG_COUNT 12
#define CLI_PERIOD_US MSEC_2_USEC(3000)

typedef enum {
    KEY_TAB = 0x09,
    KEY_BACKSPACE = 0x08, // \b
    KEY_SPACE = 0x20, //  ' '
    KEY_ESC = 0x1B,
    KEY_ENTER = 0x0D,
    KEY_LINE_FEED = 0x0A,

    KEY_UNDEF =  0,
}KeyCode_t;

#define SHELL_CMD(LONG_CMD, SHORT_CMD, FUNC, DESCRIPTION)                      \
    { .short_name = SHORT_CMD, .long_name = LONG_CMD, .description = DESCRIPTION, .handler = FUNC }


#define COMMANDS_END SHELL_CMD(NULL, NULL, NULL, NULL)




#endif /*CLI_CONST_H*/
