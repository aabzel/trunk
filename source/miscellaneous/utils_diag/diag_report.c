#ifdef HAS_CLI

#include <inttypes.h>

#include "convert.h"
#include "device_id.h"
#include "diag_page_nums.h"
#include "diag_report.h"
#include "log_utils.h"
#include "log.h"
#include "oprintf.h"
#include "sys.h"
#include "uart_string_reader.h"
#include "writer_generic.h"
#include "writer_config.h"

bool diag_page_version(ostream_t *stream) {

#if defined(BOOTLOADER)
  oputs(stream, " BOOTLOADER");
#endif
  oputs(stream, CRLF);
  oprintf(stream, "Serial=%" PRIX64 CRLF, get_device_serial());
  return true;
}

bool diag_page_sysinfo(ostream_t *stream) {
  (void)stream; /* May be unused depending on configuration */
  return true;
}

bool diag_page_base(uint8_t page, ostream_t *stream) {
  bool res;
  switch (page) {
  case DIAG_PAGE_INDEX:
    oprintf(stream, "%u Version" CRLF, DIAG_PAGE_VERSION);
    oprintf(stream, "%u SysInfo" CRLF, DIAG_PAGE_SYSINFO);
    res = diag_page_index(stream);
    break;
  case DIAG_PAGE_VERSION:
    res = diag_page_version(stream);
    break;
#if 0
  case DIAG_PAGE_UARTS:
    res = diag_page_uarts(stream);
    break;
#endif
  default:
    res = diag_report(page, stream);
    break;
  }
  return res;
}

bool show_diag_report(uint8_t page_number) {
  bool result = true;
  int64_t char_at_start;
  flush_printf();
  char_at_start = dbg_o.total_char_count;
  if (!diag_page_base(page_number, DBG_UART_STREAM)) {
    result = false;
  }
  flush_printf();
  LOG_DEBUG(SYS, "%lld chars in report",
            dbg_o.total_char_count - char_at_start);
  return result;
}

bool diag_report(uint8_t page, ostream_t *stream) {
  (void)page;
  (void)stream;
  return false;
}

bool diag_page_index(ostream_t *stream) {
  (void)stream;
  return true;
}

#endif /*HAS_CLI*/
