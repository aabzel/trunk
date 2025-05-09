#ifndef LOG_GENERAL_H
#define LOG_GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "log_types.h"
#include "log_config.h"
#include "shared_array.h"
#include "sys_constants.h"

#ifdef HAS_LOG_UTILS
#include "log_utils.h"
#else
#endif /*HAS_STREAM*/

#ifdef HAS_CUSTOM_PRINTF

#else
#include <stdio.h>
#define cli_printf printf
#define cli_putchar putchar
#define cli_putstr puts
#define cli_vprintf vprintf
#endif

#if defined(HAS_LOG_DIAG) && defined(HAS_DIAG)
#include "log_diag.h"
#endif

#ifdef HAS_LOG_UTILS
#include "writer_generic.h"
#endif

#ifndef HAS_TIME
//#error "+ TIME componet for time stamp"
#endif

extern Log_t Log;

#ifdef EMBEDDED_TEST
extern bool log_zero_time;
#endif

/*API*/

LogHandle_t* LogGetNode(uint8_t num);
const LogConfig_t* LogGetConfig(uint8_t num);
bool log_mcal_init(void);
bool log_res(const facility_t facility, const bool res, const char* const text);
bool log_info_res(const facility_t facility, const bool res, const char* const text);
bool log_parn_res(const facility_t facility, const bool res, const char* const in_text);

log_level_t ErrValue2LogLevel(int32_t val);
bool log_initialize(void);


bool log_level_time_stamp(bool on_off);
/*getters*/
log_level_t log_level_get(facility_t facility);
log_level_t log_level_get_set(facility_t facility, log_level_t log_level);

/*setters*/
bool log_write_prefix(log_level_t level, facility_t facility);
bool set_log_level(facility_t facility, log_level_t level);
void LOG_PARN(facility_t facility, const char* format, ...);
void LOG_DEBUG(facility_t facility, const char* format, ...);
void LOG_NOTICE(facility_t facility, const char* format, ...);
void LOG_INFO(facility_t facility, const char* format, ...);
void LOG_WARNING(facility_t facility, const char* format, ...);
void LOG_ERROR(facility_t facility, const char* format, ...);
void LOG_CRITICAL(facility_t facility, const char* format, ...);
void LOG_PROTECTED(facility_t facility, const char* format, ...);
void log_write(log_level_t level, facility_t facility, const char* format, ...);
void log_write_end(void);
#ifdef HAS_LOG_UTILS
bool log_print_conditional(log_level_t level, facility_t facility, const char* const text, const char* const key_word1,
                           const char* const key_word2);
#endif

#ifdef HAS_PC
bool stdio_send(const uint8_t * const array, const  uint32_t size);
#endif

#define SET_SYS_FACILITY (SYS)

#ifndef __BASE__
#define __BASE__ __FILE__
#endif

#ifdef __cplusplus
}
#endif

#endif /* LOG_GENERAL_H */
