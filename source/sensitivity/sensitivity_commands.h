#ifndef SENSITIVITY_COMMANDS_H
#define SENSITIVITY_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SENSITIVITY
#error "+HAS_SENSITIVITY"
#endif

#ifndef HAS_SENSITIVITY_COMMANDS
#error "+HAS_SENSITIVITY_COMMANDS"
#endif

#ifdef HAS_BUTTON_COMMANDS
#include "button_commands.h"
#else
#define BUTTON_COMMANDS
#endif

#ifdef HAS_BIN_ADC_COMMANDS
#include "bin_adc_commands.h"
#else
#define BIN_ADC_COMMANDS
#endif

#ifdef HAS_INCREMENTAL_ENCODER_COMMANDS
#include "incremental_encoder_commands.h"
#else
#define INCREMENTAL_ENCODER_COMMANDS
#endif


#ifdef HAS_CROSS_DETECT_COMMANDS
#include "cross_detect_commands.h"
#else
#define CROSS_DETECT_COMMANDS
#endif

#ifdef HAS_GNSS_COMMANDS
#include "gnss_commands.h"
#else
#define GNSS_COMMANDS
#endif /*HAS_GNSS_COMMANDS*/

#ifdef HAS_LOAD_DETECT_COMMANDS
#include "load_detect_commands.h"
#else
#define LOAD_DETECT_COMMANDS
#endif

#ifdef HAS_LIGHT_NAVIGATOR_COMMANDS
#include "light_navigator_commands.h"
#else
#define LIGHT_NAVIGATOR_COMMANDS
#endif

#ifdef HAS_GAME_PAD_PS2_COMMANDS
#include "game_pad_ps2_commands.h"
#else
#define GAME_PAD_PS2_COMMANDS
#endif

#ifdef HAS_PDM_COMMANDS
#include "pdm_commands.h"
#else
#define PDM_COMMANDS
#endif

#ifdef HAS_DISTANCE_COMMANDS
#include "distance_commands.h"
#else
#define DISTANCE_COMMANDS
#endif

#ifdef HAS_HEALTH_MONITOR_COMMANDS
#include "health_monitor_commands.h"
#else
#define HEALTH_MONITOR_COMMANDS
#endif

#ifdef HAS_HW_VERSION_COMMANDS
#include "hw_version_commands.h"
#else
#define HW_VERSION_COMMANDS
#endif

#ifdef HAS_DCF77_COMMANDS
#include "dcf77_commands.h"
#else
#define DCF77_COMMANDS
#endif

#ifdef HAS_TIME_COMMANDS
#include "time_commands.h"
#else
#define TIME_COMMANDS
#endif

#ifdef HAS_JUMPER_CODE_COMMANDS
#include "jumper_code_commands.h"
#else
#define JUMPER_CODE_COMMANDS
#endif

#ifdef HAS_IR_RECEIVER_COMMANDS
#include "ir_receiver_commands.h"
#else
#define IR_RECEIVER_COMMANDS
#endif


#define SENSITIVITY_COMMANDS       \
    BUTTON_COMMANDS                \
    DISTANCE_COMMANDS              \
    DCF77_COMMANDS                 \
    BIN_ADC_COMMANDS               \
    IR_RECEIVER_COMMANDS           \
    INCREMENTAL_ENCODER_COMMANDS   \
    CROSS_DETECT_COMMANDS          \
    JUMPER_CODE_COMMANDS           \
    GAME_PAD_PS2_COMMANDS          \
    GNSS_COMMANDS                  \
    HEALTH_MONITOR_COMMANDS        \
    HW_VERSION_COMMANDS            \
    LOAD_DETECT_COMMANDS           \
    LIGHT_NAVIGATOR_COMMANDS       \
    PDM_COMMANDS                   \
    TIME_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* SENSITIVITY_COMMANDS_H */
