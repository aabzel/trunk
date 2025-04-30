
#include "board_monitor.h"

#ifdef HAS_LOG
#include "log.h"
#endif
#include "cli_config.h"
#include "log_config.h"

#define STR(x) #x
#define XSTR(x) STR(x)

#if UART_NUM_CLI!=UART_NUM_LOG
#pragma message "The value of UART_NUM_CLI: " XSTR(UART_NUM_CLI)
#pragma message "The value of UART_NUM_LOG: " XSTR(UART_NUM_LOG)
#error "Log UART and CLI UART must match"
#endif

bool board_check(void){
   bool res = true;

   return res;
}
