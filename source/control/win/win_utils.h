#ifndef WIN_OS_UTILS_H
#define WIN_OS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

#ifdef HAS_MICROCONTROLLER
#warning That code only for desktop builds
#endif

#define CSV_PLOT_SCRIPT "plot_csv_file.py"

bool win_color_init(void);
bool csv_plot_line(char* CsvFileName, uint8_t x_col, uint8_t  y_col);
void clear_tui(void);
void win_color_enable(void);
bool win_cmd_run(const char* const command);

#ifdef __cplusplus
}
#endif

#endif /* WIN_OS_UTILS_H */
