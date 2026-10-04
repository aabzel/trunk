#ifndef PROC_APPLICATIONS_H
#define PROC_APPLICATIONS_H

#include "std_includes.h"

#ifndef HAS_APPLICATIONS
#error  "+HAS_APPLICATIONS"
#endif

#ifdef HAS_CAN_RX_HIST
#include "can_rx_hist_mcal.h"
#define CAN_RX_HIST_INIT {.init_function=can_rx_hist_mcal_init, .name="CanRxHist",},
#else
#define CAN_RX_HIST_INIT
#endif

#ifdef HAS_WAV_PLAYER
#include "wav_player_mcal.h"
#define WAV_PLAYER_INIT {.init_function=wav_player_mcal_init, .name="WavPlayer",},
#else
#define WAV_PLAYER_INIT
#endif

#ifdef HAS_CAN_DIFF
#include "can_diff_mcal.h"
#define CAN_DIFF_INIT {.init_function=can_diff_mcal_init, .name="CanDiff",},
#else
#define CAN_DIFF_INIT
#endif

#ifdef HAS_AKIP1160
#include "akip1160_mcal.h"
#define AKIP1160_INIT {.init_function=akip1160_mcal_init, .name="Akip1160",},
#else
#define AKIP1160_INIT
#endif

#ifdef HAS_GNSS_PROVE
#include "gnss_prove_mcal.h"
#define GNSS_PROVE_INIT {.init_function=gnss_prove_mcal_init, .name="GNSS_PROVE",},
#else
#define GNSS_PROVE_INIT
#endif

#ifdef HAS_CAN_TX_PLANNER
#include "can_tx_planner_mcal.h"
#define CAN_TX_PLANNER_INIT {.init_function=can_tx_planner_mcal_init, .name="CanTxPlanner",},
#else
#define CAN_TX_PLANNER_INIT
#endif

#ifdef HAS_PCAN_PRO_X_APP
#include "pcan_pro_x.h"
#define PCAN_PRO_X_INIT {.init_function = pcan_pro_x_mcal_init, .name="PcanProX",},
#else
#define PCAN_PRO_X_INIT
#endif

#ifdef HAS_AUTO_VOLUME
#include "auto_volume.h"
#define AUTO_VOLUME_INIT {.init_function=auto_volume_mcal_init, .name="AutoVolume",},
#else
#define AUTO_VOLUME_INIT
#endif

#ifdef HAS_PWM_PHASE_DEMO
#include "pwm_phase_demo_mcal.h"
#define PWM_PHASE_DEMO_INIT {.init_function=pwm_phase_demo_mcal_init, .name="PWM_PHASE_DEMO",},
#else
#define PWM_PHASE_DEMO_INIT
#endif

#ifdef HAS_IR_FM_RADIO
#include "ir_fm_radio_mcal.h"
#define IR_FM_RADIO_INIT {.init_function=ir_fm_radio_mcal_init, .name="IR_FM_RADIO",},
#else
#define IR_FM_RADIO_INIT
#endif

#ifdef HAS_ENCODER_LAMP
#include "encoder_lamp_mcal.h"
#define ENCODER_LAMP_INIT {.init_function=encoder_lamp_mcal_init, .name="EncoderLamp",},
#else
#define ENCODER_LAMP_INIT
#endif

#ifdef HAS_AUTO_BRIGHTNESS
#include "auto_brightness.h"
#define AUTO_BRIGHTNESS_INIT {.init_function=auto_brightness_mcal_init, .name="AutoBrightness",},
#else
#define AUTO_BRIGHTNESS_INIT
#endif

#ifdef HAS_SOUND_RECORDER
#include "sound_recorder_mcal.h"
#define SOUND_RECORDER_INIT {.init_function = sound_recorder_mcal_init, .name="SoundRecorder",},
#else
#define SOUND_RECORDER_INIT
#endif


#ifdef HAS_KEYLOG
#include "keylog.h"
#define KEYLOG_INIT {.init_function=keylog_mcal_init, .name="KeyLog",},
#else
#define KEYLOG_INIT
#endif

#ifdef HAS_LIGHT_NAVIGATOR
#include "light_navigator.h"

#define LIGHT_NAVIGATOR_INIT {.init_function=light_navigator_mcal_init, .name="LightNav",},
#else
#define LIGHT_NAVIGATOR_INIT
#endif

#ifdef HAS_PASTILDA
#include "pastilda.h"
#define PASTILDA_INIT   {.init_function=pastilda_mcal_init, .name="Pas~",},
#else
#define PASTILDA_INIT
#endif

#ifdef HAS_I2S_ECHO
#include "i2s_echo_mcal.h"
#define I2S_ECHO_INIT   {.init_function = i2s_echo_mcal_init, .name="I2sEcho",},
#else
#define I2S_ECHO_INIT
#endif

#ifdef HAS_CAN_CAT
#include "can_cat_mcal.h"
#define CAN_CAT_INIT   {.init_function = can_cat_mcal_init, .name="CanCat",},
#else
#define CAN_CAT_INIT
#endif

#ifdef HAS_SONAR
#include "sonar.h"
#define SONAR_INIT {.init_function=sonar_mcal_init, .name="Sonar",},
#else
#define SONAR_INIT
#endif

#ifdef HAS_DEMAGNETIZER
#include "demagnetizer.h"
#define DEMAGNETIZER_INIT {.init_function=demagnetizer_mcal_init, .name="DeMagnetizer",},
#else
#define DEMAGNETIZER_INIT
#endif

#ifdef HAS_RC_CAR
#include "rc_car_mcal.h"
#define RC_CAR_INIT {.init_function=rc_car_mcal_init, .name="RcCar",},
#else
#define RC_CAR_INIT
#endif

#ifdef HAS_LOOPBACK_AUDIO
#include "loopback_audio_mcal.h"
#define LOOPBACK_AUDIO_INIT {.init_function=loopback_audio_mcal_init, .name="LoopBackAudio",},
#else
#define LOOPBACK_AUDIO_INIT
#endif


#ifdef HAS_BICYCLE_HEADLAMP
#include "bicycle_headlamp_mcal.h"
#define BICYCLE_HEADLAMP_INIT {.init_function=bicycle_headlamp_mcal_init, .name="BICYCLE_HEADLAMP",},
#else
#define BICYCLE_HEADLAMP_INIT
#endif


#ifdef HAS_FW_LOADER
#include "fw_loader.h"
#define FW_LOADER_INIT {.init_function=fw_loader_mcal_init, .name="FwLoader",},
#else
#define FW_LOADER_INIT
#endif



#ifdef HAS_DASHBOARD
#include "dashboard.h"
#define DASHBOARD_INIT   {.init_function=dashboard_mcal_init, .name="dashboard",},
#else
#define DASHBOARD_INIT
#endif


#ifdef HAS_REC_PLAY
#include "rec_play_mcal.h"
#define REC_PLAY_INIT   {.init_function=rec_play_mcal_init, .name="PlayRec",},
#else
#define REC_PLAY_INIT
#endif


#ifdef HAS_GRAPHVIZ_TO_TSORT
#include "graphviz_to_tsort.h"
#define GRAPHVIZ_TO_TSORT_INIT   {.init_function=graphviz_to_tsort_mcal_init, .name="GraphvizToTsort",},
#else
#define GRAPHVIZ_TO_TSORT_INIT
#endif

#ifdef HAS_C_GENERATOR
#include "c_generator.h"
#define C_GENERATOR_INIT   {.init_function=c_generator_mcal_init, .name="cGenerator",},
#else
#define C_GENERATOR_INIT
#endif

#ifdef HAS_CODE_STYLE_CHECKER
#include "code_style_checker.h"
#define CODE_STYLE_CHECKER_INIT {.init_function=code_style_checker_mcal_init, .name="CodeStyleChecker",},
#else
#define CODE_STYLE_CHECKER_INIT
#endif

#ifdef HAS_GARLAND
#include "garland_mcal.h"
#define GARLAND_INIT {.init_function=garland_mcal_init, .name="GarLand",},
#else
#define GARLAND_INIT
#endif

#ifdef HAS_LASER_SIGHT
#include "laser_sight_mcal.h"
#define LASER_SIGHT_INIT {.init_function=laser_sight_mcal_init, .name="LaserSight",},
#else
#define LASER_SIGHT_INIT
#endif

#ifdef HAS_TICKET_SET_OPT
#include "ticket_set_opt.h"
#define TICKET_SET_OPT_INIT {.init_function=ticket_set_opt_mcal_init, .name="TICKET_SET_OPT",},
#else
#define TICKET_SET_OPT_INIT
#endif

#ifdef HAS_SOUND_LOCALIZATION
#include "sound_localization.h"
#define SOUND_LOCALIZATION_INIT {.init_function=sound_localization_mcal_init, .name="SoundLocalization",},
#else
#define SOUND_LOCALIZATION_INIT
#endif

#ifdef HAS_SMOOTH_LAMP
#include "smooth_lamp.h"
#define SMOOTH_LAMP_INIT {.init_function=smooth_lamp_mcal_init, .name="SmoothLamp",},
#else
#define SMOOTH_LAMP_INIT
#endif

#ifdef HAS_PROBING_PULSE
#include "probing_pulse_mcal.h"
#define PROBING_PULSE_INIT {.init_function=probing_pulse_mcal_init, .name="ProbingPulse",},
#else
#define PROBING_PULSE_INIT
#endif

/*Order matter*/
#define APPLICATIONS_INIT    \
    PROBING_PULSE_INIT       \
    SOUND_RECORDER_INIT      \
    WAV_PLAYER_INIT          \
    AUTO_BRIGHTNESS_INIT     \
    AUTO_VOLUME_INIT         \
    CAN_DIFF_INIT            \
    C_GENERATOR_INIT         \
    CODE_STYLE_CHECKER_INIT  \
    TICKET_SET_OPT_INIT      \
    GRAPHVIZ_TO_TSORT_INIT   \
    KEYLOG_INIT              \
    LIGHT_NAVIGATOR_INIT     \
    PASTILDA_INIT            \
    LASER_SIGHT_INIT         \
    I2S_ECHO_INIT            \
    CAN_RX_HIST_INIT         \
    CAN_TX_PLANNER_INIT      \
    SONAR_INIT               \
    PWM_PHASE_DEMO_INIT      \
    SOUND_LOCALIZATION_INIT  \
    GARLAND_INIT             \
    CAN_CAT_INIT             \
    BICYCLE_HEADLAMP_INIT    \
    GNSS_PROVE_INIT          \
    RC_CAR_INIT              \
    SMOOTH_LAMP_INIT         \
    IR_FM_RADIO_INIT         \
    DEMAGNETIZER_INIT        \
    GNSS_PROVE_INIT          \
    ENCODER_LAMP_INIT        \
    PCAN_PRO_X_INIT          \
    REC_PLAY_INIT            \
    LOOPBACK_AUDIO_INIT      \
    DASHBOARD_INIT


#ifdef HAS_SUPER_CYCLE
void applications_super_loop(uint64_t loop_start_time_us);
#endif /**/

#endif /* PROC_APPLICATIONS_H */
