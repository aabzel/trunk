#ifndef TIME_DIAG_H
#define TIME_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <time.h>
#include <stddef.h>

#include "std_includes.h"
#include "time_types.h"

bool print_time_date(const char* const prefix, const struct tm* const time_date, bool is_one_line);
bool print_time(const struct tm* const time_date);
bool TimeDate2CsvStr(const struct tm* const time_date, char* text, uint32_t size);
bool TimeDateToStrExt(const struct tm* const time_date, char* const in_text, uint32_t size);
bool TimeToStr(const struct tm* const time_date, char* const text, uint32_t size);
bool DateToStr(const struct tm* const time_date, char* text, uint32_t size);
bool UpTimeMsToStr(uint32_t up_time_ms, char* out_str, size_t size);
bool time_diag(void);

const char* TimeDataToStr(const void * const data);
const char* TimeSrcToStr(const TimeSource_t time_source);
const char* UpTimeSecToStr(float up_time_s);
const char* MsToStr(uint32_t time_ms);
const char* TimeMonthToStr(Month_t month);
const char* TimeDateToStrShort(const struct tm* const time_date);
const char* TimeToStrShort(const struct tm* const time_date);
const char* DateToStrShort(const struct tm* const time_date);
const char* UsecToStr(const uint64_t uc_sec);
const char* TimeMsToStr(const void* const data);
const char* SecToStr(float sec);

#ifdef HAS_STR2_MONTH
const char* MonthToStr(int32_t mon_value);
#endif

#ifdef __cplusplus
}
#endif

#endif /* TIME_DIAG_H */
