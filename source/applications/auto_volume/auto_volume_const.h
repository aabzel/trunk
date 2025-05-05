#ifndef AUTO_VOLUME_CONST_H
#define AUTO_VOLUME_CONST_H

#include "time_mcal.h"

#define AUTO_VOLUME_PERIOD_US SEC_2_USEC(1)

#define AUTO_VOLUME_A_DEFAULT  (-(76.0/6.0))
#define AUTO_VOLUME_B_DEFAULT (112.0/6.0)

typedef enum{
    AUTO_VOLUME_DOWN = -1,
    AUTO_VOLUME_UP = 1,

    AUTO_VOLUME_UNDEF=0,
}AutoVolumeCmd_t;

#endif /* AUTO_VOLUME_CONST_H */
