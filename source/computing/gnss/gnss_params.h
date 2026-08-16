#ifndef GNSS_PARAMS_H
#define GNSS_PARAMS_H

#include "storage_types.h"
#include "gnss_diag.h"

#define PARAMS_GNSS                            \
    {                                          \
         .facility = GNSS,                     \
         .id = PAR_ID_TRUE_LOCATION,           \
         .len = 16,                            \
         .type = TYPE_STRUCT,                  \
         .parser = GnssCoordinateDataToStr,    \
         .name="TrueLocation",                 \
         .default_value="0, 0",                \
    },

#endif /* GNSS_PARAMS_H  */
