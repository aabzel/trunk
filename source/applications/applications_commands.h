#ifndef APPLICATIONS_COMMANDS_H
#define APPLICATIONS_COMMANDS_H

#include "applications_dep.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_APPLICATIONS_COMMANDS
#error "+HAS_APPLICATIONS_COMMANDS"
#endif

#ifdef HAS_AUTO_BRIGHTNESS_COMMANDS
#include "auto_brightness_commands.h"
#else
#define AUTO_BRIGHTNESS_COMMANDS
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

#ifdef HAS_PASTILDA_COMMANDS
#include "pastilda_commands.h"
#else
#define PASTILDA_COMMANDS
#endif

#ifdef HAS_PLANETARIUM_COMMANDS
#include "planetarium_commands.h"
#else
#define PLANETARIUM_COMMANDS
#endif

#ifdef HAS_SMART_PHONE_STATION_COMMANDS
#include "sps_commands.h"
#else
#define SMART_PHONE_STATION_COMMANDS
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

#ifdef HAS_END_OF_BLOCK_COMMANDS
#include "end_of_block_commands.h"
#else
#define END_OF_BLOCK_COMMANDS
#endif


#ifdef HAS_SOUND_LOCALIZATION_COMMANDS
#include "sound_localization_commands.h"
#else
#define SOUND_LOCALIZATION_COMMANDS
#endif



#define APPLICATIONS_COMMANDS         \
    SONAR_COMMANDS                    \
    AUTO_BRIGHTNESS_COMMANDS          \
    SOUND_LOCALIZATION_COMMANDS       \
    AUTO_VERSION_COMMANDS             \
    AUTO_VOLUME_COMMANDS              \
    END_OF_BLOCK_COMMANDS              \
    C_GENERATOR_COMMANDS              \
    CODE_STYLE_CHECKER_COMMANDS       \
    GRAPHVIZ_TO_TSORT_COMMANDS        \
    LIGHT_NAVIGATOR_COMMANDS          \
    PASTILDA_COMMANDS                 \
    PLANETARIUM_COMMANDS              \
    SMART_PHONE_STATION_COMMANDS

#endif /* APPLICATIONS_COMMANDS_H */
