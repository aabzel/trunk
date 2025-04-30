#ifndef DIAG__REPORT_H
#define DIAG__REPORT_H

#include <stdbool.h>

#ifdef HAS_DIAG_PAGE
#include "diag_page_commands.h"
#include "diag_page_nums.h"
#else /* HAS_DIAG_PAGE */

#include "ostream.h"

bool diag_report(uint8_t page, ostream_t *stream);
bool diag_page_base(uint8_t page, ostream_t *stream);
bool diag_page_version(ostream_t *stream);
bool diag_page_sysinfo(ostream_t *stream);
bool diag_page_index(ostream_t *stream);
bool show_diag_report(uint8_t page_number);
bool dump_diag_report(uint8_t page_number);
bool cmd_diag_report(int32_t argc, char *argv[]);

#define DIAG_COMMANDS                                                          \
  SHELL_CMD("DiagReport", "dr", cmd_diag_report, "Diagnostics report"),

#endif /* HAS_DIAG_PAGE */

#endif /* DIAG__REPORT_H */
