#ifndef SW_INIT_H
#define SW_INIT_H

#include <stdbool.h>

#ifdef HAS_HEAP
#include "heap_allocator.h"
#define HEAP_INIT {.init_function=h_init, .name="Heap",},
#else
#define HEAP_INIT
#endif /**/

#ifdef HAS_INDICATION
#include "indication.h"
#define INDICATION_INIT {.init_function=indication_init, .name="Ind",},
#else
#define INDICATION_INIT
#endif /**/


#ifdef HAS_ANT_MUX
#define ANT_MUX_INIT {.init_function=ant_mux_init, .name="AntMux",},
#else
#define ANT_MUX_INIT
#endif /*HAS_BLE_CAN_SAT*/

#ifdef HAS_PROTOCOLS
#include "protocols_init.h"
#else
#define PROTOCOLS_INIT
#endif /* */

#ifdef HAS_APPLICATIONS
#include "applications_init.h"
#else
#define APPLICATIONS_INIT
#endif /*HAS_APPLICATIONS*/


#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#define HEALTH_MONITOR_INIT {.init_function=health_monotor_init, .name="HM",},
#else
#define HEALTH_MONITOR_INIT
#endif /*HAS_HEALTH_MONITOR*/

#ifdef HAS_PWR_MUX
#define PWR_MUX_INIT {.init_function=pwr_src_init, .name="PWR_MUX",},
#else
#define PWR_MUX_INIT
#endif /*HAS_PWR_MUX*/

#ifdef HAS_TASK
#include "task_info.h"

#ifdef HAS_LOG
#define TASK_INIT_NAME .name = "task",
#else
#define TASK_INIT_NAME
#endif

#define TASK_INIT {.init_function=task_init, TASK_INIT_NAME},
#else
#define TASK_INIT
#endif /*HAS_TASK*/


#ifdef HAS_GPIO_PWM
#include "gpio_pwm_drv.h"
#define GPIO_PWM_INIT {.init_function=gpio_pwm_init, .name="GPIO_PWM",},
#else
#define GPIO_PWM_INIT
#endif /* */

#ifdef HAS_STORAGE
#else
#define STORAGE_INIT
#endif /*HAS_STORAGE*/

#ifdef HAS_CALENDAR
#include "calendar.h"
#define CALENDAR_INIT {.init_function=calendar_init, .name="calendar",},
#else
#define CALENDAR_INIT
#endif /*HAS_CALENDAR*/

#ifdef HAS_CONNECTIVITY
#else
#define CONNECTIVITY_INIT
#define SERIAL_INIT
#endif /*HAS_CONNECTIVITY*/

#ifdef HAS_DISPLAY
#include "display_drv.h"
#define DISPLAY_INIT {.init_function=display_init, .name="Display",},
#else
#define DISPLAY_INIT
#endif /*HAS_DISPLAY*/

#ifdef HAS_MULTIMEDIA
#else
#define MULTIMEDIA_INIT
#endif /*HAS_MULTIMEDIA*/

#ifdef HAS_COMPUTING
#include "computing_init.h"
#else
#define COMPUTING_INIT
#endif /*HAS_COMPUTING*/

#ifdef HAS_SUPER_CYCLE
#include "super_cycle.h"

#ifdef HAS_LOG
#define SUPER_CYCLE_INIT_NAME .name = "SuperCycle",
#else
#define SUPER_CYCLE_INIT_NAME
#endif

#define SUPER_CYCLE_INIT               \
    {                                  \
	 .init_function=super_cycle_init,  \
	 SUPER_CYCLE_INIT_NAME             \
    },
#else
#define SUPER_CYCLE_INIT
#endif /*HAS_SUPER_CYCLE*/

//#ifdef HAS_RTOS
//#include "rtos_drv.h"
//#define RTOS_INIT {.init_function=rtos_init, .name="rtos",},
//#else
//#define RTOS_INIT
//#endif /*HAS_RTOS*/

#ifdef HAS_MULTIMEDIA
#include "proc_multimedia.h"
#else
#define MULTIMEDIA_INIT
#endif

#ifdef HAS_APPLICATIONS
#include "applications_init.h"
#else
#define APPLICATIONS_INIT
#endif

#ifdef HAS_SENSITIVITY
#include "sensitivity_init.h"
#else
#define SENSITIVITY_SW_INIT
#endif


#define SW_INIT            \
    HEAP_INIT              \
    SUPER_CYCLE_INIT       \
    TASK_INIT              \
    INDICATION_INIT        \
    ANT_MUX_INIT           \
    SENSITIVITY_SW_INIT    \
    GPIO_PWM_INIT          \
    CALENDAR_INIT          \
    SERIAL_INIT            \
    DISPLAY_INIT           \
    MULTIMEDIA_INIT        \
    COMPUTING_INIT         \
    APPLICATIONS_INIT


#endif /*SW_INIT_H*/
