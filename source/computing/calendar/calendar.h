#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

bool calendar_init(void);
bool calendar_gettime(struct tm* const date_time);
uint32_t calendar_settime(const struct tm* const date_time);
uint32_t TimeDateToSeconds(const struct tm* const time_date);
bool SecondsToTimeDate(uint32_t sec, struct tm* time_date);

#endif /* CALENDAR_H  */
