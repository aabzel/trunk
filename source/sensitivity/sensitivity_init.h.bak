#ifndef SENSITIVITY_INIT_H
#define SENSITIVITY_INIT_H

#include "std_includes.h"

#ifndef HAS_MCU
#warning  "+HAS_MCU"
#endif

#ifndef HAS_SENSITIVITY
#error  "+HAS_SENSITIVITY"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#define TIME_INIT {.init_function = time_mcal_init, .name="Time",},
#else
#define TIME_INIT
#endif /*TIME_INIT*/


#ifdef HAS_BUTTON
#include "button_drv.h"
#define BUTTON_INIT {.init_function=button_mcal_init, .name="Button",},
#else
#define BUTTON_INIT
#endif /*HAS_BUTTON*/

#ifdef HAS_CROSS_DETECT
#include "cross_detect_drv.h"
#define CROSS_DETECT_INIT {.init_function=cross_detect_mcal_init, .name="CrossDetect",},
#else
#define CROSS_DETECT_INIT
#endif /*HAS_CROSS_DETECT*/

#ifdef HAS_DISTANCE
#include "distance_drv.h"
#define DISTANCE_INIT {.init_function=distance_mcal_init, .name="Distance",},
#else
#define DISTANCE_INIT
#endif /*HAS_DISTANCE*/

#ifdef HAS_HEALTH_MONOTOR
#include "health_monitor.h"
#define HEALTH_MONOTOR_INIT {.init_function=health_monotor_mcal_init, .name="HEALTH_MONOTOR",},
#else
#define HEALTH_MONOTOR_INIT
#endif /*HAS_LOAD_DETECT*/

#ifdef HAS_LOAD_DETECT
#include "load_detect_drv.h"
#define LOAD_DETECT_INIT {.init_function=load_detect_mcal_init, .name="LoadDetect",},
#else
#define LOAD_DETECT_INIT
#endif /*HAS_LOAD_DETECT*/

#ifdef HAS_PHOTORESISTOR
#include "photoresistor.h"
#define PHOTORESISTOR_INIT {.init_function=photoresistor_mcal_init, .name="PhotoResistor",},
#else
#define PHOTORESISTOR_INIT
#endif /*HAS_PHOTORESISTOR*/

#ifdef HAS_HW_VERSION
#include "hw_version_drv.h"
#define HW_VERSION_INIT {.init_function=hw_version_mcal_init, .name="HwInit",},
#else
#define HW_VERSION_INIT
#endif /*HAS_HW_VERSION*/

/*order matters!*/
#define SENSITIVITY_SW_INIT  \
     HEALTH_MONOTOR_INIT     \
     BUTTON_INIT             \
     DISTANCE_INIT           \
     HW_VERSION_INIT         \
     PHOTORESISTOR_INIT      \
     CROSS_DETECT_INIT       \
     LOAD_DETECT_INIT



#endif /* SENSITIVITY_INIT_H */
