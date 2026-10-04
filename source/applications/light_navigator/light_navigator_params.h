#ifndef LIGHT_NAVIGATOR_PARAMS_H
#define LIGHT_NAVIGATOR_PARAMS_H

#include <time.h>

#include "storage_types.h"
#include "time_diag.h"

#define PARAMS_LIGHT_NAVIGATOR                                                                                          \
    {.facility=LIGHT_NAVIGATOR, \
    .id=PAR_ID_DAWN_1,  \
    .len=sizeof( struct tm ),  \
    .default_value="00:00:00",   \
    .parser = TimeDataToStr,\
    .type=TYPE_TIME_DATE,  \
    .name="Dawn1", \
    },      \
    {.facility=LIGHT_NAVIGATOR, \
        .id=PAR_ID_SUNSET_1, \
        .len=sizeof( struct tm ), \
        .default_value="00:00:00",\
        .parser = TimeDataToStr,\
        .type=TYPE_TIME_DATE, \
        .name="SunSet1" ,\
    },  \
    {.facility=LIGHT_NAVIGATOR, \
            .id=PAR_ID_DAWN_2, \
                .default_value="00:00:00",   \
            .len=sizeof( struct tm ),  \
            .parser = TimeDataToStr,\
            .type=TYPE_TIME_DATE, \
            .name="Dawn2",\
    },      \
    {.facility=LIGHT_NAVIGATOR, \
                .id=PAR_ID_SUNSET_2, \
                    .default_value="00:00:00",   \
                .len=sizeof( struct tm ), \
                .parser = TimeDataToStr,\
                .type=TYPE_TIME_DATE, \
                .name="SunSet2", \
    },


#endif /* LIGHT_NAVIGATOR_PARAMS_H  */
