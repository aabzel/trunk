#ifndef RTC_CUSTOM_DEP_H
#define RTC_CUSTOM_DEP_H

#ifndef NRFX_RTC_ENABLED
#error "+NRFX_RTC_ENABLED"
#endif

#ifndef HAS_SENSITIVITY
#error "+HAS_SENSITIVITY"
#endif

#ifndef HAS_RTC
#error "+HAS_RTC"
#endif

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif

#ifndef HAS_CALENDAR
#error "+HAS_CALENDAR"
#endif

#endif /* RTC_CUSTOM_DEP_H  */
