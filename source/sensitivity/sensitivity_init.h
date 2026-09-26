#ifndef SENSITIVITY_INIT_H
#define SENSITIVITY_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

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
#endif

#ifdef HAS_BIN_ADC
#include "bin_adc_mcal.h"
#define BIN_ADC_INIT {.init_function=bin_adc_mcal_init, .name="BinAdc",},
#else
#define BIN_ADC_INIT
#endif

#ifdef HAS_BUTTON
#include "button_mcal.h"
#define BUTTON_INIT {.init_function=button_mcal_init, .name="Button",},
#else
#define BUTTON_INIT
#endif

#ifdef HAS_CROSS_DETECT
#include "cross_detect_mcal.h"
#define CROSS_DETECT_INIT {.init_function=cross_detect_mcal_init, .name="CrossDetect",},
#else
#define CROSS_DETECT_INIT
#endif

#ifdef HAS_JUMPER_CODE
#include "jumper_code_mcal.h"
#define JUMPER_CODE_INIT {.init_function=jumper_code_mcal_init, .name="JumperCode",},
#else
#define JUMPER_CODE_INIT
#endif


#ifdef HAS_GAME_PAD_PS2
#include "game_pad_ps2.h"
#define GAME_PAD_PS2_INIT {.init_function=game_pad_ps2_mcal_init, .name="GamePadPs2",},
#else
#define GAME_PAD_PS2_INIT
#endif

#ifdef HAS_DCF77
#include "dcf77_mcal.h"
#define DCF77_INIT {.init_function=dcf77_mcal_init, .name="Dcf77",},
#else
#define DCF77_INIT
#endif

#ifdef HAS_DISTANCE
#include "distance_mcal.h"
#define DISTANCE_INIT {.init_function=distance_mcal_init, .name="Distance",},
#else
#define DISTANCE_INIT
#endif

#ifdef HAS_HEALTH_MONOTOR
#include "health_monitor.h"
#define HEALTH_MONOTOR_INIT {.init_function=health_monotor_mcal_init, .name="HEALTH_MONOTOR",},
#else
#define HEALTH_MONOTOR_INIT
#endif

#ifdef HAS_LOAD_DETECT
#include "load_detect_mcal.h"
#define LOAD_DETECT_INIT {.init_function=load_detect_mcal_init, .name="LoadDetect",},
#else
#define LOAD_DETECT_INIT
#endif

#ifdef HAS_PHOTORESISTOR
#include "photoresistor.h"
#define PHOTORESISTOR_INIT {.init_function=photoresistor_mcal_init, .name="PhotoResistor",},
#else
#define PHOTORESISTOR_INIT
#endif

#ifdef HAS_INCREMENTAL_ENCODER
#include "incremental_encoder_mcal.h"
#define INCREMENTAL_ENCODER_INIT {.init_function=incremental_encoder_mcal_init, .name="IncrementalEncoder",},
#else
#define INCREMENTAL_ENCODER_INIT
#endif


#ifdef HAS_HW_VERSION
#include "hw_version_mcal.h"
#define HW_VERSION_INIT {.init_function=hw_version_mcal_init, .name="HwInit",},
#else
#define HW_VERSION_INIT
#endif

#ifdef HAS_IR_RECEIVER
#include "ir_receiver_mcal.h"
#define IR_RECEIVER_INIT {.init_function=ir_receiver_mcal_init, .name="IrRec",},
#else
#define IR_RECEIVER_INIT
#endif

/*order matters!*/
#define SENSITIVITY_SW_INIT    \
     BIN_ADC_INIT              \
     HEALTH_MONOTOR_INIT       \
     BUTTON_INIT               \
     DISTANCE_INIT             \
     GAME_PAD_PS2_INIT         \
     DCF77_INIT                \
     HW_VERSION_INIT           \
     INCREMENTAL_ENCODER_INIT  \
     PHOTORESISTOR_INIT        \
     CROSS_DETECT_INIT         \
     JUMPER_CODE_INIT          \
     IR_RECEIVER_INIT          \
     LOAD_DETECT_INIT


#ifdef __cplusplus
}
#endif


#endif /* SENSITIVITY_INIT_H */
