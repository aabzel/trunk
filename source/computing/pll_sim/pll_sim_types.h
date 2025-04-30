#ifndef PLL_SIM_PLL_SIM_TYPES_H
#define PLL_SIM_PLL_SIM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "pll_sim_const.h"

typedef struct {
    double i;
    double q;
}IqSample_t;

#define PLL_SIM_COMMON_VARIABLES          \
	double lo_frequency_hz;               \
    double vco_p;                         \
    double vco_i;                         \
    double vco_d;                         \
    double out_frequency_hz;              \
	uint32_t sample_frequency_hz;         \
	uint32_t divider;                     \
	uint8_t fir_num;                      \
    uint8_t num;                          \
    char* name;                           \
    bool valid;

typedef struct {
    PLL_SIM_COMMON_VARIABLES
    double sample_time_s;
    double fb_frequency_hz;
    double up_time_s;
    double phase_err_deg;
    double vco_in_deg;
    double vco_in_diff_deg;
    double vco_in_prev_deg;
    double vco_in_int_deg;
    IqSample_t Lo;
    IqSample_t SfbCur;
    IqSample_t sOut;
    IqSample_t SfbOld;
    uint32_t sample_cnt;
}PllSimHandle_t;

typedef struct {
    PLL_SIM_COMMON_VARIABLES
}PllSimConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* PLL_SIM_PLL_SIM_TYPES_H */
