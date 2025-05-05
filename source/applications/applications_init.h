#ifndef PROC_APPLICATIONS_H
#define PROC_APPLICATIONS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_APPLICATIONS
#error  "+HAS_APPLICATIONS"
#endif

#ifdef HAS_AUTO_VOLUME
#include "auto_volume.h"
#define AUTO_VOLUME_INIT {.init_function=auto_volume_mcal_init, .name="AutoVolume",},
#else
#define AUTO_VOLUME_INIT
#endif /*HAS_AUTO_VOLUME*/

#ifdef HAS_AUTO_BRIGHTNESS
#include "auto_brightness.h"
#define AUTO_BRIGHTNESS_INIT {.init_function=auto_brightness_mcal_init, .name="AutoBrightness",},
#else
#define AUTO_BRIGHTNESS_INIT
#endif /*HAS_AUTO_BRIGHTNESS*/

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
#endif /*HAS_LIGHT_NAVIGATOR*/

#ifdef HAS_PASTILDA
#include "pastilda.h"
#define PASTILDA_INIT   {.init_function=pastilda_mcal_init, "Pas~",},
#else
#define PASTILDA_INIT
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


#ifdef HAS_SOUND_LOCALIZATION
#include "sound_localization.h"
#define SOUND_LOCALIZATION_INIT {.init_function=sound_localization_mcal_init, .name="SoundLocalization",},
#else
#define SOUND_LOCALIZATION_INIT
#endif



#define APPLICATIONS_INIT    \
    C_GENERATOR_INIT         \
    CODE_STYLE_CHECKER_INIT  \
    GRAPHVIZ_TO_TSORT_INIT   \
    KEYLOG_INIT              \
    FW_LOADER_INIT           \
    DASHBOARD_INIT


#ifdef HAS_SUPER_CYCLE
void applications_super_loop(uint64_t loop_start_time_us);
#endif /*SUPER_LOOP*/

#endif /* PROC_APPLICATIONS_H */
