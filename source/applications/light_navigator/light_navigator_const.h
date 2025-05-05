#ifndef LIGHT_NAVIGATOR_CONST_H
#define LIGHT_NAVIGATOR_CONST_H

#include "time_mcal.h"
#include "light_navigator_dep.h"

/*
    calced in
    https://docs.google.com/spreadsheets/d/1BEoX17zGTKGQB5z5Mdxwz02ybATcdsci7TaQGDNvXD8/edit#gid=0
*/
#define LIGHT_NAVIGATOR_DAY_NIGHT_BORDER  (2.15) //1.5716215 < 1.95716215 < 2< 2.1< x < 2.2

#define LIGHT_NAVIGATOR_POLL_PERIOD_US SEC_2_USEC(30)
#define LIGHT_NAVIGATOR_LIGHT_TO_LAMBDA_PERIOD_US SEC_2_USEC(10)

#define LIGHT_NAVIGATOR_DRIVER_VERSION 5

#endif /* LIGHT_NAVIGATOR_CONST_H */
