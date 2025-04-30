#ifndef WIN_OS_UTILS_H
#define WIN_OS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifdef HAS_MICROCONTROLLER
#warning That code only for desktop builds
#endif

bool win_color_init(void);
void clear_tui(void);
void win_color_enable(void);
bool win_cmd_run(const char* const command);

#ifdef __cplusplus
}
#endif

#endif /* WIN_OS_UTILS_H */
