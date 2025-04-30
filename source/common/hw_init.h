#ifndef HW_INIT_H
#define HW_INIT_H

#include <stdbool.h>

#ifdef HAS_NRFX_CORE
#define NRFX_CORE_INIT   {.init_function=nrf_cores_init, .name="NrfCores",},
#else
#define NRFX_CORE_INIT
#endif /*HAS_NRFX_CORE*/

#ifdef HAS_TEMPERATURE
#include "temperature_drv.h"
#define TEMPERATURE_INIT   {.init_function=temperature_init, .name="Temp",},
#else
#define TEMPERATURE_INIT
#endif /*HAS_TEMPERATURE*/

#ifdef HAS_AES_ECB
#include "aes_drv.h"
#define AES_ECB_INIT   {.init_function=aes_ecb_init, .name="AesEcb",},
#else
#define AES_ECB_INIT
#endif

#ifdef HAS_CRYP_HW
#include "cryp_drv.h"
#define CRYP_HW_INIT   {.init_function=cryp_hw_init, .name="CrypHw",},
#else
#define CRYP_HW_INIT
#endif

#ifdef HAS_AXP192
#include "axp192_drv.h"
#define AXP192_INIT   {.init_function=axp192_init, .name="axp192",},
#else
#define AXP192_INIT
#endif /*HAS_AXP192*/

#ifdef HAS_BQ25171_Q1
#include "bq25171_q1_drv.h"
#define BQ25171_Q1_INIT   {.init_function=bq25171_q1_init, .name="bq251",},
#else
#define BQ25171_Q1_INIT
#endif /*HAS_BQ25171_Q1*/

#ifdef HAS_MIC2026
#include "mic2026_drv.h"
#define MIC2026_INIT   {.init_function=mic2026_init, .name="mic2026",},
#else
#define MIC2026_INIT
#endif /*HAS_IWDG*/

#define POWER_SYSTEM_INIT   \
    AXP192_INIT             \
    BQ25171_Q1_INIT         \
    MIC2026_INIT


#define SECURITY_HW_INIT     \
    AES_ECB_INIT

#ifdef HAS_INTERFACES
#include "interfaces_init.h"
#else
#define HW_WIRE_INTERFACES_INIT
#endif

#ifdef HAS_CONNECTIVITY
#include "proc_connectivity.h"
#else
#define CONNECTIVITY_HW_INIT
#endif /*HAS_CONNECTIVITY*/

#ifdef HAS_STORAGE
#include "storage_init.h"
#else
#define STORAGE_HW_INIT
#endif /*HAS_STORAGE*/


/*Order matters*/
#define HW_INIT               \
    POWER_SYSTEM_INIT         \
    SECURITY_HW_INIT          \



#endif /*HW_INIT_H*/
