#ifndef TERMINAL_CODES_H
#define TERMINAL_CODES_H

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*compose as a table */
//see https://habr.com/ru/company/macloud/blog/558316/
// \u001b[30m
#define VT_ERROR_BEEP "\a"
#define VT_SETCOLOR_BLACK    "\x1B[0;30m"
#define VT_SETCOLOR_PARANOID "\x1B[1;30m"
#define VT_SETCOLOR_RED      "\x1B[1;31m"
// \u001b[31m
#define VT_SETCOLOR_GREEN0   "\x1B[0;32m"
#define VT_SETCOLOR_GREEN    "\x1B[1;32m"
#define VT_SETCOLOR_CRITICAL "\x1B[1;33;41m"
#define VT_SETCOLOR_YELLOW0  "\x1B[0;33m"
#define VT_SETCOLOR_YELLOW   "\x1B[1;33m"
#define VT_SETCOLOR_BLUE0    "\x1B[0;34m"
#define VT_SETCOLOR_BLUE     "\x1B[1;34m"
// \u001b[34m
#define VT_SETCOLOR_NOTICE   VT_SETCOLOR_BLUE
#define VT_SETCOLOR_PURPLE   "\x1B[0;35m"
// \u001b[35m
#define VT_SETCOLOR_PINK     "\x1B[1;35m"
#define VT_SETCOLOR_CYAN     "\x1B[0;36m"
#define VT_SETCOLOR_WHITE    "\x1B[0;37m"

#define VT_SETCOLOR_RESET    "\x1b[0m"
#define VT_SETCOLOR_NORMAL   "\x1B[0m"
#define VT_CLEAR_LINE_END    "\x1B[K"
#define VT_CLEAR_SCREEN      "\x1B[2J"

#ifdef __cplusplus
}
#endif

#endif /* TERMINAL_CODES_H */
