#ifndef SW_UART_COMMANDS_H
#define SW_UART_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "debug_info.h"


#ifndef HAS_SW_UART
#error "+HAS_SW_UART"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

bool test_sw_uart_tx_all_command(int32_t argc, char* argv[]) ;
bool sw_uart_set_baudrate_command(int32_t argc, char* argv[]);
bool sw_uart_send_command(int32_t argc, char* argv[]);
bool sw_uart_init_command(int32_t argc, char* argv[]);
bool sw_uart_diag_command(int32_t argc, char* argv[]);

#define SW_UART_COMMANDS                                                                            \
        SHELL_CMD("test_sw_uart_tx_all", "suto", test_sw_uart_tx_all_command, "SwUartTestTxRx"),    \
        SHELL_CMD("sw_uart_baud", "sub", sw_uart_set_baudrate_command, "SwUartSetBaud"),            \
        SHELL_CMD("sw_uart_diag", "sud", sw_uart_diag_command, "SwUartDiag"),                       \
        SHELL_CMD("sw_uart_init", "sui", sw_uart_init_command, "SwUartInit"),                       \
        SHELL_CMD("sw_uart_send", "sus", sw_uart_send_command, "SwUartSend"),

#ifdef __cplusplus
}
#endif

#endif /* SW_UART_COMMANDS_H */
