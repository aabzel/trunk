#ifndef BQ24079_CONST_H
#define BQ24079_CONST_H

#include "time_mcal.h"
#include "bq24079_dep.h"

#define BQ24079_DRIVER_VERSION 2
#define BQ24079_PERIOD_US  SEC_2_USEC(0.5)

typedef enum {
    BQ24079_100_MA =0,
    BQ24079_500_MA =1,
    BQ24079_SET_ILIM =2,
    BQ24079_STANDBY =3,

    BQ24079_UNDEF=7,

}Bq24079Settings_t;

#endif /* BQ24079_CONST_H */
