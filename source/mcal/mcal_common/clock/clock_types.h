#ifndef CLOCK_TYPES_H
#define CLOCK_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_const.h"

#ifdef HAS_CLOCK_CUSTOM
#include "clock_custom_types.h"
#else
#define CLOCK_CUSTOM_TYPES
#endif

/*TODO move to clock*/
typedef struct {
    uint32_t divider;
    uint32_t period;
} ClockSetting_t;

#define CLOCK_COMMON_VARIABLE                          \
    uint32_t core_clock_hz; /*sysclk freq Hz*/         \
    bool valid;

typedef struct {
    CLOCK_COMMON_VARIABLE
    uint8_t irq_priority;
    ClockHiFreqSrc_t hf_source;
    ClockLowFreqSrc_t lf_source;
    ClockCoreSrc_t core_source;
    uint32_t pll0;
    uint32_t pll1;
} ClockConfig_t;

typedef struct {
    CLOCK_COMMON_VARIABLE
    CLOCK_CUSTOM_TYPES
    bool init_done;
    volatile uint32_t err_cnt;
    volatile uint32_t isr_cnt;
    uint32_t hfclk_started;
    uint32_t lfclk_started;
    uint32_t evt_ctto;
    uint32_t cal_done;
    uint32_t hfclkaudio_started;
    uint32_t hfclk192m_started;
} ClockHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_TYPES_H */
