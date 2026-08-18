#ifndef BH1750_PARAMS_H
#define BH1750_PARAMS_H

#include "param_drv.h"
#include "param_types.h"

#ifndef HAS_BH1750
#error "+HAS_BH1750"
#endif

#define PARAMS_BH1750       \
    {BH1750, PAR_ID_BH1750_I2S_BUS_ROLE, 1, TYPE_UINT8, "I2sBusRole"},   /*Master/Slave*/


#endif /* BH1750_PARAMS_H  */
