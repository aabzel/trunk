#ifndef PDM_CONST_H
#define PDM_CONST_H

#include "pdm_dep.h"
#include "time_mcal.h"

#ifdef HAS_PDM_CUSTOM
#include "pdm_custom_const.h"
#endif

#define PDM_POLL_PERIOD_US MSEC_2_USEC(10)

typedef enum {
    PDM_MODE_STEREO = 1,
    PDM_MODE_MONO = 2,

    PDM_MODE_UNDEF = 0,
} PdmMode_t;

typedef enum {
    MIC_MODE_SINGLE = 1,
    MIC_MODE_CONTINUOUS = 2,

    MIC_MODE_UNDEF = 0,
} MicMode_t;

typedef enum {
    PDM_EDGE_LEFT_FALLING = 1,
    PDM_EDGE_LEFT_RISING = 2,

    PDM_EDGE_UNDEF = 0,
} PdmEdge_t;

typedef enum {
    PDM_MASTER_CLK_CPU_PLL = 1,
    PDM_MASTER_CLK_AUDIO_PLL = 2,

    PDM_MASTER_CLK_UNDEF = 0,
} PdmMasterClk_t;

#endif /* PDM_CONST_H */
