#include "log_utils.h"

#include <stdio.h>

#ifdef HAS_LOG
#include "log.h"
#endif

#include "oprintf.h"

#include "microcontroller_drv.h"

#ifdef HAS_WRITER
#include "writer.h"
#endif

#ifdef HAS_CUSTOM_PRINTF
// print_callback_t print_callback_f;

void cli_putstr(const char* str) {
    WriterHandle_t* Writer = writer_get();
    if(Writer) {
#ifdef HAS_LOG
        oputs(&Writer->stream, str);
#endif
    }
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
void cli_putchar(char ch) {
    WriterHandle_t* Writer = writer_get();
    if(Writer) {

#ifdef HAS_LOG
        (&Writer->stream)->f_putch(&Writer->stream, ch);
#endif
    }
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
/*TODO: cli_printf -> log_printf */
void cli_printf(const char* format, ...) {
    WriterHandle_t* Writer = writer_get();
    if(Writer) {
        va_list vlist;
        va_start(vlist, format);
#ifdef HAS_LOG
        ovprintf(&Writer->stream, format, vlist);
#endif /*HAS_LOG*/
        va_end(vlist);
    }
}
#endif /*HAS_CUSTOM_PRINTF*/

#ifdef HAS_CUSTOM_PRINTF
void cli_vprintf(const char* format, va_list vlist) {
    WriterHandle_t* Writer = writer_get();
    if(Writer) {
#ifdef HAS_LOG
        ovprintf(&Writer->stream, format, vlist);
#endif
    }
}

bool is_printf_clean(void) {
    bool res = false;
    WriterHandle_t* Writer = writer_get();
    if(Writer) {
#ifdef HAS_LOG
        res = writer_clean(Writer);
#endif
    }
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
    WriterHandle_t* Writer = writer_get();
    if(Writer) {

#ifdef HAS_LOG
        while(!writer_half_clean(Writer)) {
        }
#endif
    }
}

#endif /*HAS_CUSTOM_PRINTF*/
