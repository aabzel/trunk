#ifndef QUAD_MIX_4FS_TYPES_H
#define QUAD_MIX_4FS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "quad_mix_4fs_const.h"
#include "dsp_types.h"
#include "sliding_integral_types.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef struct {
    int32_t LocalOcs;
    int32_t AfterMux;
    int32_t AfterFilt;
}SdrDataS32_t;

typedef int32_t QuadMix4fsSample_t;

#ifdef HAS_GPIO
#define QUAD_MIX_4FS_COMMON_GPIO_VARIABLE    Pad_t PadOkPhase;
#else
#define QUAD_MIX_4FS_COMMON_GPIO_VARIABLE
#endif


#define QUAD_MIX_4FS_COMMON_VARIABLE            \
    QUAD_MIX_4FS_COMMON_GPIO_VARIABLE           \
    uint8_t filter_num_i;                       \
    uint8_t filter_num_q;                       \
    uint32_t cut_off_freq_hz;                   \
    uint32_t filter_order;                      \
    uint32_t num;                               \
    char* name;                                 \
    bool valid;

typedef struct {
    QUAD_MIX_4FS_COMMON_VARIABLE
} QuadMix4fsConfig_t;

typedef struct {
    QUAD_MIX_4FS_COMMON_VARIABLE
    int32_t sam_num; /*up time is measured in samples */
    int32_t sample; // in
    int32_t lo_phase_n; /*0 1 2 3   or   -2 -1 0 1 */
    float phase_error_rad; // out
    uint32_t proc_cnt;
    SlidingIntegralHandle_t* pNodeFilterI;
    SlidingIntegralHandle_t* pNodeFilterQ;
    SdrDataS32_t SdrI; //out
    SdrDataS32_t SdrQ; //out
    bool init;
} QuadMix4fsHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* QUAD_MIX_4FS_TYPES_H */
