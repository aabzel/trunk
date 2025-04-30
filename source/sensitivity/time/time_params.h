#ifndef TIME_PARAMS_H
#define TIME_PARAMS_H

#include "param_types.h"

#define PARAMS_TIME                                           \
    {.facility=SYS, .id=PAR_ID_MAX_UP_TIME, .len=4, .type=TYPE_UINT32, .default_value="0", .name="MaxUpTime"}, /*min*/

#endif /* TIME_PARAMS_H */
