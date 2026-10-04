#ifndef APPLICATIONS_COMMANDS_H
#define APPLICATIONS_COMMANDS_H

#include "applications_dep.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_APPLICATIONS_COMMANDS
#error "+HAS_APPLICATIONS_COMMANDS"
#endif

#ifdef HAS_BICYCLE_HEADLAMP_COMMANDS
#include "bicycle_headlamp_commands.h"
#else
#define BICYCLE_HEADLAMP_COMMANDS
#endif

#ifdef HAS_LOOPBACK_AUDIO_COMMANDS
#include "loopback_audio_commands.h"
#else
#define LOOPBACK_AUDIO_COMMANDS
#endif

#ifdef HAS_LASER_SIGHT_COMMANDS
#include "laser_sight_commands.h"
#else
#define LASER_SIGHT_COMMANDS
#endif

#ifdef HAS_PWM_PHASE_DEMO_COMMANDS
#include "pwm_phase_demo_commands.h"
#else
#define PWM_PHASE_DEMO_COMMANDS
#endif


#ifdef HAS_AUTO_BRIGHTNESS_COMMANDS
#include "auto_brightness_commands.h"
#else
#define AUTO_BRIGHTNESS_COMMANDS
#endif

#ifdef HAS_CAN_TX_PLANNER_COMMANDS
#include "can_tx_planner_commands.h"
#else
#define CAN_TX_PLANNER_COMMANDS
#endif

#ifdef HAS_ENCODER_LAMP_COMMANDS
#include "encoder_lamp_commands.h"
#else
#define ENCODER_LAMP_COMMANDS
#endif

#ifdef HAS_CAN_RX_HIST_COMMANDS
#include "can_rx_hist_commands.h"
#else
#define CAN_RX_HIST_COMMANDS
#endif

#ifdef HAS_IR_FM_RADIO_COMMANDS
#include "ir_fm_radio_commands.h"
#else
#define IR_FM_RADIO_COMMANDS
#endif

#ifdef HAS_GNSS_PROVE_COMMANDS
#include "gnss_prove_commands.h"
#else
#define GNSS_PROVE_COMMANDS
#endif

#ifdef HAS_AUTO_VOLUME_COMMANDS
#include "auto_volume_commands.h"
#else
#define AUTO_VOLUME_COMMANDS
#endif

#ifdef HAS_AUTO_VERSION_COMMANDS
#include "auto_version_commands.h"
#else
#define AUTO_VERSION_COMMANDS
#endif

#ifdef HAS_SONAR_COMMANDS
#include "sonar_commands.h"
#else
#define SONAR_COMMANDS
#endif

#ifdef HAS_SED_COMMANDS
#include "sed_commands.h"
#else
#define SED_COMMANDS
#endif

#ifdef HAS_GARLAND_COMMANDS
#include "garland_commands.h"
#else
#define GARLAND_COMMANDS
#endif

#ifdef HAS_PASTILDA_COMMANDS
#include "pastilda_commands.h"
#else
#define PASTILDA_COMMANDS
#endif

#ifdef HAS_PROBING_PULSE_COMMANDS
#include "probing_pulse_commands.h"
#else
#define PROBING_PULSE_COMMANDS
#endif

#ifdef HAS_PLANETARIUM_COMMANDS
#include "planetarium_commands.h"
#else
#define PLANETARIUM_COMMANDS
#endif

#ifdef HAS_SOUND_RECORDER_COMMANDS
#include "sound_recorder_commands.h"
#else
#define SOUND_RECORDER_COMMANDS
#endif

#ifdef HAS_LIGHT_NAVIGATOR_COMMANDS
#include "light_navigator_commands.h"
#else
#define LIGHT_NAVIGATOR_COMMANDS
#endif

#ifdef HAS_GRAPHVIZ_TO_TSORT_COMMANDS
#include "graphviz_to_tsort_commands.h"
#else
#define GRAPHVIZ_TO_TSORT_COMMANDS
#endif

#ifdef HAS_DEMAGNETIZER_COMMANDS
#include "demagnetizer_commands.h"
#else
#define DEMAGNETIZER_COMMANDS
#endif

#ifdef HAS_C_GENERATOR_COMMANDS
#include "c_generator_commands.h"
#else
#define C_GENERATOR_COMMANDS
#endif

#ifdef HAS_CODE_STYLE_CHECKER_COMMANDS
#include "code_style_checker_commands.h"
#else
#define CODE_STYLE_CHECKER_COMMANDS
#endif

#ifdef HAS_SMOOTH_LAMP_COMMANDS
#include "smooth_lamp_commands.h"
#else
#define SMOOTH_LAMP_COMMANDS
#endif

#ifdef HAS_I2S_ECHO_COMMANDS
#include "i2s_echo_commands.h"
#else
#define I2S_ECHO_COMMANDS
#endif


#ifdef HAS_PCAN_PRO_X_COMMANDS
#include "pcan_pro_x_commands.h"
#else
#define PCAN_PRO_X_COMMANDS
#endif

#ifdef HAS_CAN_DIFF_COMMANDS
#include "can_diff_commands.h"
#else
#define CAN_DIFF_COMMANDS
#endif

#ifdef HAS_WAV_PLAYER_COMMANDS
#include "wav_player_commands.h"
#else
#define WAV_PLAYER_COMMANDS
#endif

#ifdef HAS_END_OF_BLOCK_COMMANDS
#include "end_of_block_commands.h"
#else
#define END_OF_BLOCK_COMMANDS
#endif

#ifdef HAS_TICKET_SET_OPT_COMMANDS
#include "ticket_set_opt_commands.h"
#else
#define TICKET_SET_OPT_COMMANDS
#endif

#ifdef HAS_SOUND_LOCALIZATION_COMMANDS
#include "sound_localization_commands.h"
#else
#define SOUND_LOCALIZATION_COMMANDS
#endif

#ifdef HAS_GEARBOX_COMMANDS
#include "gearbox_commands.h"
#else
#define GEARBOX_COMMANDS
#endif

#ifdef HAS_CAN_CAT_COMMANDS
#include "can_cat_commands.h"
#else
#define CAN_CAT_COMMANDS
#endif

#ifdef HAS_REC_PLAY_COMMANDS
#include "rec_play_commands.h"
#else
#define REC_PLAY_COMMANDS
#endif


#ifdef HAS_FW_LOADER_COMMANDS
#include "fw_loader_commands.h"
#else
#define FW_LOADER_COMMANDS
#endif

#define APPLICATIONS_COMMANDS         \
    AUTO_BRIGHTNESS_COMMANDS          \
    AUTO_VOLUME_COMMANDS              \
    PROBING_PULSE_COMMANDS            \
    FW_LOADER_COMMANDS                \
    CAN_CAT_COMMANDS                  \
    CAN_DIFF_COMMANDS                 \
    CAN_RX_HIST_COMMANDS              \
    CAN_TX_PLANNER_COMMANDS           \
    GNSS_PROVE_COMMANDS               \
    CODE_STYLE_CHECKER_COMMANDS       \
    REC_PLAY_COMMANDS                 \
    I2S_ECHO_COMMANDS                 \
    LOOPBACK_AUDIO_COMMANDS           \
    C_GENERATOR_COMMANDS              \
    DEMAGNETIZER_COMMANDS             \
    ENCODER_LAMP_COMMANDS             \
    END_OF_BLOCK_COMMANDS             \
    PWM_PHASE_DEMO_COMMANDS           \
    GARLAND_COMMANDS                  \
    GEARBOX_COMMANDS                  \
    BICYCLE_HEADLAMP_COMMANDS         \
    GRAPHVIZ_TO_TSORT_COMMANDS        \
    IR_FM_RADIO_COMMANDS              \
    LASER_SIGHT_COMMANDS              \
    LIGHT_NAVIGATOR_COMMANDS          \
    SOUND_RECORDER_COMMANDS           \
    PASTILDA_COMMANDS                 \
    PCAN_PRO_X_COMMANDS               \
    PLANETARIUM_COMMANDS              \
    SED_COMMANDS                      \
    SMOOTH_LAMP_COMMANDS              \
    SONAR_COMMANDS                    \
    SOUND_LOCALIZATION_COMMANDS       \
    WAV_PLAYER_COMMANDS               \
    TICKET_SET_OPT_COMMANDS


#endif /* APPLICATIONS_COMMANDS_H */
