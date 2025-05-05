#ifndef TASKS_APPLICATIONS_H
#define TASKS_APPLICATIONS_H

#ifdef HAS_AUTO_VOLUME_PROC
#include "auto_volume.h"
#define AUTO_VOLUME_TASK {.name="AUTO_VOLUME", .period_us=AUTO_VOLUME_PERIOD_US, .limiter.function=auto_volume_proc,},
#else /*HAS_AUTO_VOLUME_PROC*/
#define AUTO_VOLUME_TASK
#endif /*HAS_AUTO_VOLUME_PROC*/

#ifdef HAS_AUTO_VERSION_PROC
#include "auto_version.h"
#define AUTO_VERSION_TASK {.name="AUTO_VERSION", .period_us=AUTO_VERSION_PERIOD_US, .limiter.function=auto_version_proc,},
#else /*HAS_AUTO_VERSION_PROC*/
#define AUTO_VERSION_TASK
#endif /*HAS_AUTO_VERSION_PROC*/

#ifdef HAS_AUTO_BRIGHTNESS_PROC
#include "auto_brightness.h"
#define AUTO_BRIGHTNESS_TASK {.name="AUTO_BRIGHTNESS", .period_us=AUTO_BRIGHTNESS_PERIOD_US, .limiter.function=auto_brightness_proc,},
#else /*HAS_AUTO_BRIGHTNESS_PROC*/
#define AUTO_BRIGHTNESS_TASK
#endif /*HAS_AUTO_BRIGHTNESS_PROC*/

#ifdef HAS_SONAR_PROC
#include "sonar.h"
#define SONAR_TASK {.name="Sonar", .period_us=SONAR_PERIOD_US, .limiter.function=sonar_proc,},
#else /*HAS_SONAR_PROC*/
#define SONAR_TASK
#endif /*HAS_SONAR_PROC*/


#ifdef HAS_KEYLOG_PROC
#include "keylog.h"
#define KEYLOG_TASK {.name="KEYLOG", .period_us=KEYLOG_PERIOD_US, .limiter.function=keylog_proc,},
#else /*HAS_KEYLOG_PROC*/
#define KEYLOG_TASK
#endif /*HAS_KEYLOG_PROC*/

#ifdef HAS_LIGHT_NAVIGATOR_PROC
#include "light_navigator.h"

#define LIGHT_NAVIGATOR_TASKS                                                  \
    {.name="LightToPhi", .period_us=LIGHT_NAVIGATOR_POLL_PERIOD_US, .limiter.function=light_navigator_proc,}, \
    {.name="MaxLightToLambda", .period_us=LIGHT_NAVIGATOR_LIGHT_TO_LAMBDA_PERIOD_US, .limiter.function=light_navigator_light_to_lambda_proc,},

#else /*HAS_LIGHT_NAVIGATOR*/
#define LIGHT_NAVIGATOR_TASKS
#endif /*HAS_LIGHT_NAVIGATOR*/

#ifdef HAS_DASHBOARD_PROC
#include "dashboard.h"
#define DASHBOARD_TASK {.name="DASHBOARD", .period_us=DASHBOARD_POLL_PERIOD_US, .limiter.function=dashboard_proc,},
#else /*HAS_DASHBOARD*/
#define DASHBOARD_TASK
#endif /*HAS_DASHBOARD*/

#define APPLICATIONS_TASKS  \
    AUTO_VERSION_TASK       \
    AUTO_VOLUME_TASK        \
    AUTO_BRIGHTNESS_TASK    \
    DASHBOARD_TASK          \
    KEYLOG_TASK             \
    SONAR_TASK              \
    LIGHT_NAVIGATOR_TASKS

#endif /* TASKS_APPLICATIONS_H */
