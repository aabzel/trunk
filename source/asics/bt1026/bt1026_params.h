#ifndef BT1026_PARAMS_H
#define BT1026_PARAMS_H

#include "param_drv.h"
#include "param_types.h"

#ifndef HAS_BT1026
#error "+HAS_BT1026"
#endif

#define PARAMS_BT1026       \
    {BT1026, PAR_ID_BT1026_I2S_BUS_ROLE, 1, TYPE_UINT8, "I2sBusRole"},   /*Master/Slave*/


#endif /* BT1026_PARAMS_H  */
