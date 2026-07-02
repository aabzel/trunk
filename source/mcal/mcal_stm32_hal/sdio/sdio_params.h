#ifndef SDIO_PARAMS_H
#define SDIO_PARAMS_H


#include "storage_types.h"
#include "common_diag.h"

#define PARAMS_SDIO              \
    {                            \
    .facility = LG_SDIO,         \
    .id = PAR_ID_SDIO_CLOCKDIV,  \
    .parser = U8DecToStr,        \
    .len = 1,                    \
    .type = TYPE_UINT8,          \
    .name = "ClockDiv",          \
    .default_value = "90",       \
    },   /*Num*/




#endif /* SDIO_PARAMS_H  */
