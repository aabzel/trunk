#ifndef TIME_PARAMS_H
#define TIME_PARAMS_H

#include "storage_types.h"
#include "time_diag.h"

#ifdef HAS_DIAG
#define PARAM_TIME_MAX_UP_TIME_PARSER  .parser = TimeMsToStr,
#else
#define PARAM_TIME_MAX_UP_TIME_PARSER
#endif

#define PARAMS_TIME                                           \
    {                                                         \
      .facility = SYS,                                        \
      .id = PAR_ID_MAX_UP_TIME,                               \
      .len = 4,                                               \
      .type = TYPE_UINT32,                                    \
      .default_value = "0",                                   \
      .name = "MaxUpTime",                                    \
       PARAM_TIME_MAX_UP_TIME_PARSER                          \
     },

#endif /* TIME_PARAMS_H */
