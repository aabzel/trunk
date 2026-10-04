#ifndef TASKS_APPLICATIONS_H
#define TASKS_APPLICATIONS_H

#ifdef HAS_CAN_RX_HIST_PROC
#include "can_rx_hist_mcal.h"
#define CAN_RX_HIST_TASK {.name="CAN_RX_HIST", .period_us=CAN_RX_HIST_PERIOD_US, .limiter.function=can_rx_hist_proc,},
#else
#define CAN_RX_HIST_TASK
#endif

#ifdef HAS_GNSS_PROVE_PROC
#include "gnss_prove_mcal.h"
#define GNSS_PROVE_TASK {.name="GNSS_PROVE", .period_us=GNSS_PROVE_PERIOD_US, .limiter.function=gnss_prove_proc,},
#else
#define GNSS_PROVE_TASK
#endif

#ifdef HAS_ENCODER_LAMP_PROC
#include "encoder_lamp_mcal.h"
#define ENCODER_LAMP_TASK {.name="EncoderLamp", .period_us=ENCODER_LAMP_PERIOD_US, .limiter.function=encoder_lamp_proc,},
#else
#define ENCODER_LAMP_TASK
#endif


#ifdef HAS_AUTO_VOLUME_PROC
#include "auto_volume.h"
#define AUTO_VOLUME_TASK {.name="AUTO_VOLUME", .period_us=AUTO_VOLUME_PERIOD_US, .limiter.function=auto_volume_proc,},
#else
#define AUTO_VOLUME_TASK
#endif

#ifdef HAS_PWM_PHASE_DEMO_PROC
#include "pwm_phase_demo_mcal.h"
#define PWM_PHASE_DEMO_TASK { .name="PwmPhaseDemo", \
                              .period_us=PWM_PHASE_DEMO_PERIOD_US, \
                              .limiter.function=pwm_phase_demo_proc,},
#else
#define PWM_PHASE_DEMO_TASK
#endif

#ifdef HAS_LASER_SIGHT_PROC
#include "laser_sight_mcal.h"
#define LASER_SIGHT_TASK {.name="LaserSight", .period_us=LASER_SIGHT_PERIOD_US, .limiter.function=laser_sight_proc,},
#else
#define LASER_SIGHT_TASK
#endif

#ifdef HAS_AUTO_VERSION_PROC
#include "auto_version.h"
#define AUTO_VERSION_TASK {.name="AUTO_VERSION", .period_us=AUTO_VERSION_PERIOD_US, .limiter.function=auto_version_proc,},
#else
#define AUTO_VERSION_TASK
#endif

#ifdef HAS_AKIP1160_PROC
#include "akip1160_mcal.h"
#define AKIP1160_TASK {.name="Akip1160", .period_us=AKIP1160_PERIOD_US, .limiter.function=akip1160_proc,},
#else
#define AKIP1160_TASK
#endif

#ifdef HAS_DEMAGNETIZER_PROC
#include "demagnetizer.h"
#define DEMAGNETIZER_TASK {.name="DEMAGNETIZER", .period_us=DEMAGNETIZER_PERIOD_US, .limiter.function=demagnetizer_proc,},
#else
#define DEMAGNETIZER_TASK
#endif

#ifdef HAS_LOOPBACK_AUDIO_PROC
#include "loopback_audio_mcal.h"
#define LOOPBACK_AUDIO_TASK {.name="LoopBackAudio", .period_us=LOOPBACK_AUDIO_PERIOD_US, .limiter.function=loopback_audio_proc,},
#else
#define LOOPBACK_AUDIO_TASK
#endif


#ifdef HAS_SMOOTH_LAMP_PROC
#include "smooth_lamp.h"
#define SMOOTH_LAMP_TASK {.name="SmoothLamp", .period_us=SMOOTH_LAMP_PERIOD_US, .limiter.function=smooth_lamp_proc,},
#else
#define SMOOTH_LAMP_TASK
#endif

#ifdef HAS_CAN_DIFF_PROC
#include "can_diff_mcal.h"
#define CAN_DIFF_TASK {.name="CanDiff", .period_us=CAN_DIFF_PERIOD_US, .limiter.function=can_diff_proc,},
#else
#define CAN_DIFF_TASK
#endif

#ifdef HAS_AUTO_BRIGHTNESS_PROC
#include "auto_brightness.h"
#define AUTO_BRIGHTNESS_TASK {.name="AUTO_BRIGHTNESS", .period_us=AUTO_BRIGHTNESS_PERIOD_US, .limiter.function=auto_brightness_proc,},
#else
#define AUTO_BRIGHTNESS_TASK
#endif

#ifdef HAS_REC_PLAY_PROC
#include "rec_play_mcal.h"
#define REC_PLAY_TASK {.name="REC_PLAY", .period_us=REC_PLAY_PERIOD_US, .limiter.function=rec_play_proc,},
#else
#define REC_PLAY_TASK
#endif

#ifdef HAS_I2S_ECHO_PROC
#include "i2s_echo_mcal.h"
#define I2S_ECHO_TASK {.name="I2S_ECHO", .period_us=I2S_ECHO_PERIOD_US, .limiter.function=i2s_echo_proc,},
#else
#define I2S_ECHO_TASK
#endif


#ifdef HAS_BICYCLE_HEADLAMP_PROC
#include "bicycle_headlamp_mcal.h"
#define BICYCLE_HEADLAMP_TASK {.name="BICYCLE_HEADLAMP", .period_us=BICYCLE_HEADLAMP_PERIOD_US, .limiter.function=bicycle_headlamp_proc,},
#else
#define BICYCLE_HEADLAMP_TASK
#endif


#ifdef HAS_GARLAND_PROC
#include "garland_mcal.h"
#define GARLAND_TASK {.name="garland", .period_us=GARLAND_PERIOD_US, .limiter.function=garland_proc,},
#else
#define GARLAND_TASK
#endif

#ifdef HAS_SONAR_PROC
#include "sonar.h"
#define SONAR_TASK {.name="Sonar", .period_us=SONAR_PERIOD_US, .limiter.function=sonar_proc,},
#else
#define SONAR_TASK
#endif

#ifdef HAS_KEYLOG_PROC
#include "keylog.h"
#define KEYLOG_TASK {.name="KEYLOG", .period_us=KEYLOG_PERIOD_US, .limiter.function=keylog_proc,},
#else
#define KEYLOG_TASK
#endif

#ifdef HAS_RC_CAR_PROC
#include "rc_car_mcal.h"
#define RC_CAR_TASK {.name="RC_CAR", .period_us=RC_CAR_PERIOD_US, .limiter.function=rc_car_proc,},
#else
#define RC_CAR_TASK
#endif

#ifdef HAS_PCAN_PRO_X_PROC
#include "pcan_pro_x.h"
#define PCAN_PRO_X_TASK {.name="PcanProx", .period_us=PCAN_PRO_X_POLL_PERIOD_US, .limiter.function=pcan_pro_x_proc,},
#else
#define PCAN_PRO_X_TASK
#endif

#ifdef HAS_CAN_TX_PLANNER_PROC
#include "can_tx_planner_mcal.h"
#define CAN_TX_PLANNER_TASK                                \
    {                                                      \
    .name = "CanTxPlanner",                                \
    .period_us = CAN_TX_PLANNER_PERIOD_US,                 \
    .limiter.function = can_tx_planner_proc,               \
    },
#else
#define CAN_TX_PLANNER_TASK
#endif

#ifdef HAS_IR_FM_RADIO_PROC
#include "ir_fm_radio_mcal.h"
#define IR_FM_RADIO_TASK {.name="IR_FM_RADIO", .period_us=IR_FM_RADIO_PERIOD_US, .limiter.function=ir_fm_radio_proc,},
#else
#define IR_FM_RADIO_TASK
#endif

#ifdef HAS_LIGHT_NAVIGATOR_PROC
#include "light_navigator.h"

#define LIGHT_NAVIGATOR_TASKS                                                  \
    {   \
     .name="LightToPhi", \
     .period_us=LIGHT_NAVIGATOR_POLL_PERIOD_US,\
     .limiter.function=light_navigator_proc,   \
     }, \
    { \
         .name="MaxLightToLambda", \
         .period_us=LIGHT_NAVIGATOR_LIGHT_TO_LAMBDA_PERIOD_US, \
         .limiter.function=light_navigator_light_to_lambda_proc,\
    },

#else
#define LIGHT_NAVIGATOR_TASKS
#endif

#ifdef HAS_DASHBOARD_PROC
#include "dashboard.h"
#define DASHBOARD_TASK {.name="DASHBOARD", .period_us=DASHBOARD_POLL_PERIOD_US, .limiter.function=dashboard_proc,},
#else
#define DASHBOARD_TASK
#endif

#ifdef HAS_SOUND_RECORDER_PROC
#include "sound_recorder_mcal.h"
#define SOUND_RECORDER_TASK {.name="SOUND_RECORDER", .period_us=SOUND_RECORDER_POLL_PERIOD_US, .limiter.function=sound_recorder_proc,},
#else
#define SOUND_RECORDER_TASK
#endif


#ifdef HAS_WAV_PLAYER_PROC
#include "wav_player_mcal.h"
#define WAV_PLAYER_TASK {.name="WAV_PLAYER", .period_us=WAV_PLAYER_POLL_PERIOD_US, .limiter.function=wav_player_proc,},
#else
#define WAV_PLAYER_TASK
#endif

#define APPLICATIONS_TASKS  \
    AUTO_VERSION_TASK       \
    CAN_TX_PLANNER_TASK     \
    SOUND_RECORDER_TASK     \
    I2S_ECHO_TASK           \
    REC_PLAY_TASK           \
    LOOPBACK_AUDIO_TASK     \
    PWM_PHASE_DEMO_TASK     \
    CAN_RX_HIST_TASK        \
    GNSS_PROVE_TASK         \
    CAN_DIFF_TASK           \
    AUTO_VOLUME_TASK        \
    ENCODER_LAMP_TASK       \
    IR_FM_RADIO_TASK        \
    LASER_SIGHT_TASK        \
    WAV_PLAYER_TASK         \
    AUTO_BRIGHTNESS_TASK    \
    GARLAND_TASK            \
    DASHBOARD_TASK          \
    BICYCLE_HEADLAMP_TASK   \
    SMOOTH_LAMP_TASK        \
    DEMAGNETIZER_TASK       \
    RC_CAR_TASK             \
    KEYLOG_TASK             \
    SONAR_TASK              \
    LIGHT_NAVIGATOR_TASKS

#endif /* TASKS_APPLICATIONS_H */
