#ifndef TIME_MCAL_H
#define TIME_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "std_includes.h"
#include "none_blocking_pause.h"
#include "time_config.h"
#include "time_types.h"
#ifdef HAS_TIME_DIAG
#include "time_diag.h"
#endif

#ifdef X86_64
extern uint32_t g_up_time_ms;
#endif


#define HOUR_2_MS(HOUR) ((HOUR)*60U * 60U * 1000U)
#define HOUR_2_SEC(HOUR) (((float)(HOUR)) * 60.0 * 60.0)
#define DAY_2_SEC(DAYS) (((float)(DAYS)) * 86400.0)
#define WEEK_2_SEC(WEEKS) (((float)(WEEKS)) * 604800.0)
#define HOUR_2_MIN(HOUR) (((float)(HOUR)) * 60.0)
#define MIN_2_SEC(MIN) (((float)(MIN)) * 60.0)
#define MIN_2_MS(MIN) ((MIN)*60U * 1000U)
#define MIN_2_US(MIN) ((60000000 * (MIN)))
#define MIN_2_HOUR(MIN) (((float)(MIN)) / 60.0)
#define MSEC_2_HOUR(MSEC) (((float)(MSEC) / 3600000.0))
#define MSEC_2_MIN(MSEC) (((float)(MSEC)) / (1000.0 * 60.0))
#define MSEC_2_SEC(MSEC) (((float)(MSEC)) / 1000.0)
#define MSEC_2_USEC(MSEC) ((MSEC)*1000U)
#define NSEC_2_SEC(NSEC) (((float)(NSEC)) / 1000000000.0)
#define NSEC_2_USEC_U(NSEC) ((NSEC) / 1000)
#define MSEC_2_NSEC(SEC) ((float)(1000000.0 * ((float)SEC)))
#define SEC_2_DAYS(SEC) ((((float)(SEC))) / (24.0 * 3600.0))
#define SEC_2_HOUR(SEC) (((float)(SEC)) / (3600.0))
#define SEC_2_MIN(SEC) (((float)(SEC)) / (60.0))
#define SEC_2_MSEC(SEC) ((((float)(SEC)) * 1000.0))
#define SEC_2_USEC(SEC) ((1000000.0 * ((float)(SEC))))
#define SEC_2_NSEC(SEC) ((float)(1000000000.0 * ((float)(SEC))))
#define USEC_2_MSEC(USEC) (((float)(USEC)) / 1000.0)
#define USEC_2_SEC(USEC) (((float)(USEC)) / 1000000.0)
#define USEC_2_MIN(USEC) (SEC_2_MIN((USEC_2_SEC(USEC))))
#define USEC_2_HOUR(USEC) (((float)(USEC)) / 3600000000.0)
#define MIN_2_DAYS(MIN) (((float)(MIN)) / (1440.0))
#define MSEC_2_DAYS(MSEC) (((float)(MSEC)) / 86400000.0)

extern uint32_t start_time_ms;

/*API*/
const TimeConfig_t* TimeGetConfig(uint8_t num);
TimeHandle_t* TimeGetNode(uint8_t num);
bool is_valid_time(const struct tm* const date_time);
bool time_init_one(uint8_t num);
bool time_mcal_init(void);

#ifdef HAS_TIME_EXT
bool time_proc(void);
bool time_proc_one(uint8_t num);
#endif

bool is_valid_date(const struct tm* const date);
bool is_valid_time_date(const struct tm* const date_time);
bool time_uptime_2_time_date(uint32_t up_time, struct tm* const date_time);

/*getters*/
uint32_t time_get_ms(uint8_t num);
bool time_get_cur_utc(struct tm* const time);
bool time_get_time_str(char* str, uint32_t size);
bool time_get_cur(struct tm* time);
struct tm* time_get_time(void);
uint64_t time_get_ms64(void);
uint64_t time_get_us(void);
uint64_t time_one_get_us(uint8_t num);
uint32_t time_get_ms32(void);
float time_get_s(uint8_t num);

/*setters*/
bool time_delay_ms(uint32_t delay_in_ms);

/*misc*/
uint32_t time_calc_duration_ms(uint32_t start_ms);
uint32_t time_calc_diff(struct tm* date_time1, struct tm* date_time2);
bool time_sec_to_time(uint32_t sec, struct tm* const time);
bool is_time_date_equal(struct tm* date_time1, struct tm* date_time2);
bool is_time_date_equal_soft(const struct tm* const date_time1, const struct tm* const date_time2, uint32_t sec_error,
                             int32_t* real_error);
uint32_t calc_days_in_year(const struct tm* const date);
bool time_synchronize(void);
bool time_duration_init(DurationFsm_t* Duration);

bool date_parse(struct tm* date_time, char* str);

bool parse_date_from_val(uint32_t packed_date, struct tm* tm_stamp);
bool parse_date_time_from_string(char* name, struct tm* tm_stamp);
bool parse_time_from_val(uint32_t packed_time, struct tm* tm_stamp);
bool time_data_parse(struct tm* date_time, char* str);
bool time_parse(struct tm* const date_time, char* str);
uint32_t time_duration_parse(const char* const diration_str);

uint64_t sec_to_usec(float sec);
float usec_to_sec(uint64_t usec);

float sec_to_msec(float  SEC) ;//((((float)(SEC)) * 1000.0))
int calc_total_day_cnt(const struct tm* const date_time);
int32_t time_date_cmp(const struct tm* const date_time1, const struct tm* const date_time2);

bool time_wait_timeout(uint32_t start_ms,
		               uint32_t timeout_ms );

#ifdef HAS_PARSE_DURATION
uint32_t time_duration_parse(const char* const diration_str);
#endif /*HAS_PARSE_DURATION*/

#ifdef __cplusplus
}
#endif

#endif /* TIME_MCAL_H */
