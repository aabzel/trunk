#include "log_utils.h"

#include <stdio.h>

#ifdef HAS_BOARD
#include "log_config.h"
#endif /*HAS_BOARD*/

#ifdef HAS_LOG
#include "log.h"
#include "terminal_codes.h"
#include "writer_config.h"
#include "writer_generic.h"
#endif

#ifdef HAS_UART
//#include "uart_drv.h"
#endif

#ifdef HAS_CUSTOM_PRINTF
// print_callback_t print_callback_f;

void cli_putstr(const char* str) {
#ifdef HAS_LOG
    oputs(&curWriterPtr->stream, str);
#endif
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
void cli_putchar(char ch) {
#ifdef HAS_LOG
    (&curWriterPtr->stream)->f_putch(&curWriterPtr->stream, ch);
#endif
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
/*TODO: cli_printf -> log_printf */
void cli_printf(const char* format, ...) {
    va_list vlist;
    va_start(vlist, format);
#ifdef HAS_LOG
    ovprintf(&curWriterPtr->stream, format, vlist);
#endif /*HAS_LOG*/
    va_end(vlist);
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
void cli_vprintf(const char* format, va_list vlist) {
#ifdef HAS_LOG
    ovprintf(&curWriterPtr->stream, format, vlist);
#endif
}

bool is_printf_clean(void) {
    bool res = false;
#ifdef HAS_LOG
    res = writer_clean(curWriterPtr);
#endif
    return res;
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
void cli_putstrln(const char* str) {
#ifdef HAS_LOG
    cli_putstr(str);
    cli_putstr(CRLF);
#endif
}

void wait_for_printf(void) {
#ifdef HAS_LOG
    while(!writer_half_clean(curWriterPtr)) {
    }
#endif
}

#endif /*HAS_CUSTOM_PRINTF*/
