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
bool TimeDate2Str(const struct tm* const time_date, char* text, uint32_t size);
bool Time2Str(const struct tm* const time_date, char* const text, uint32_t size);
bool Date2Str(const struct tm* const time_date, char* text, uint32_t size);
bool UpTimeMs2Str(uint32_t up_time_ms, char* out_str, size_t size);
bool time_diag(void);

const char* TimeSrcToStr(const TimeSource_t time_source);
const char* UpTimeSec2Str(float up_time_s);
const char* Ms2Str(uint32_t time_ms);
const char* TimeMonth2Str(Month_t month);
const char* TimeDate2StrShort(const struct tm* const time_date);
const char* Time2StrShort(const struct tm* const time_date);
const char* Date2StrShort(const struct tm* const time_date);
const char* UsecToStr(uint64_t uc_sec);
const char* SecToStr(float sec);

#ifdef HAS_STR2_MONTH
const char* Month2Str(int32_t mon_value);
#endif

#ifdef __cplusplus
}
#endif

#endif /* TIME_DIAG_H */
