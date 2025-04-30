#ifndef SDIO_PARAMS_H
#define SDIO_PARAMS_H

#include "param_drv.h"
#include "param_types.h"

#define PARAMS_SDIO       \
    {.facility=LG_SDIO, .id=PAR_ID_SDIO_CLOCKDIV, .len=1, .type=TYPE_UINT8, .name="ClockDiv", .default_value="100",},   /*Num*/




#endif /* SDIO_PARAMS_H  */
