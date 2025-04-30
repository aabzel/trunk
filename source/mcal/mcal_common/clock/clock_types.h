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


typedef struct {
    bool valid;
    uint8_t irq_priority;
    ClockHiFreqSrc_t hf_source;
    ClockLowFreqSrc_t lf_source;
    uint32_t core_clock_mhz;
} ClockConfig_t;

typedef struct {
    bool valid;
    bool init_done;
    volatile uint32_t err_cnt;
    volatile uint32_t isr_cnt;
    uint32_t hfclk_started;
    uint32_t lfclk_started;
    uint32_t evt_ctto;
    uint32_t cal_done;
    uint32_t hfclkaudio_started;
    uint32_t hfclk192m_started;
    CLOCK_CUSTOM_TYPES
} ClockHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_TYPES_H */
