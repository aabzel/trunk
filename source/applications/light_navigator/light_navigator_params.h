#ifndef LIGHT_NAVIGATOR_PARAMS_H
#define LIGHT_NAVIGATOR_PARAMS_H

#include <time.h>

#include "param_types.h"

#define PARAMS_LIGHT_NAVIGATOR                                                                                          \
    {.facility=LIGHT_NAVIGATOR, .id=PAR_ID_DAWN_1, .len=sizeof( struct tm ), .type=TYPE_TIME_DATE, .name="Dawn1"},      \
    {.facility=LIGHT_NAVIGATOR, .id=PAR_ID_SUNSET_1, .len=sizeof( struct tm ), .type=TYPE_TIME_DATE, .name="SunSet1"},  \
    {.facility=LIGHT_NAVIGATOR, .id=PAR_ID_DAWN_2, .len=sizeof( struct tm ), .type=TYPE_TIME_DATE, .name="Dawn2"},      \
    {.facility=LIGHT_NAVIGATOR, .id=PAR_ID_SUNSET_2, .len=sizeof( struct tm ), .type=TYPE_TIME_DATE, .name="SunSet2"},


#endif /* LIGHT_NAVIGATOR_PARAMS_H  */
