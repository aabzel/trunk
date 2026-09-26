#ifndef DATE_MCAL_H
#define DATE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "std_includes.h"
#include "time_config.h"
#include "time_types.h"

#define DAY_2_SEC(DAYS) (((float)(DAYS)) * 86400.0f)
#define WEEK_2_SEC(WEEKS) (((float)(WEEKS)) * 604800.0f)
#define SEC_2_DAYS(SEC) ((((float)(SEC))) / (24.0f * 3600.0f))
#define MIN_2_DAYS(MIN) (((float)(MIN)) / (1440.0f))
#define MSEC_2_DAYS(MSEC) (((float)(MSEC)) / 86400000.0f)

/*getters*/
bool is_valid_date(const struct tm* const date);
bool is_valid_time_date(const struct tm* const date_time);
int32_t time_calc_diff(struct tm* date_time1, struct tm* date_time2);
bool is_time_date_equal(struct tm* date_time1, struct tm* date_time2);
bool is_time_date_equal_soft(const struct tm* const date_time1, const struct tm* const date_time2, uint32_t sec_error,
                             int32_t* real_error);
uint32_t calc_days_in_year(const struct tm* const date);


/* setters */
bool date_parse(struct tm* const date_time, const char* const str);
bool date_parse_rus( struct tm* const date_time, const char* const str) ;
bool parse_date_from_val(uint32_t packed_date, struct tm* tm_stamp);
bool time_data_parse(struct tm* date_time, char* str);


int32_t time_date_cmp(const struct tm* const date_time1, const struct tm* const date_time2);



#ifdef __cplusplus
}
#endif

#endif /* DATE_MCAL_H */
