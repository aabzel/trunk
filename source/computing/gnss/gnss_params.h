#ifndef GNSS_PARAMS_H
#define GNSS_PARAMS_H

#include "param_types.h"

#define PARAMS_GNSS                                        \
    {.facility=GNSS, .id=PAR_ID_TRUE_LOCATION, .len=16, .type=TYPE_STRUCT, .name="TrueLocation", .default_value="0",},




#endif /* GNSS_PARAMS_H  */
