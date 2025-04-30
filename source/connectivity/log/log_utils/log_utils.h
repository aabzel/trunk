#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#include "std_includes.h"
#include "log_constants.h"

#if HAS_ZEPHYR

#include "log_zephyr_bindings.h"

#else /*HAS_ZEPHYR*/

void cli_putstrln(const char* str);
void cli_putstr(const char* str);
void cli_vprintf(const char* format, va_list vlist);

#endif /*Not HAS_ZEPHYR*/


#ifdef HAS_CUSTOM_PRINTF
#define cli_stdout_stream_get get_console_stream
void wait_for_printf(void);
bool flush_printf(void);
void cli_printf(const char* format, ...);
void cli_putchar(char ch);
bool is_printf_clean(void);
//typedef void (*print_callback_t)(const char* str);
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef __cplusplus
}
#endif

#endif /* LOG_UTILS_H */
