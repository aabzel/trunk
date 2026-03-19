#ifndef MAM_TYPES_H
#define MAM_TYPES_H

#include "std_includes.h"
#include "mam_const.h"
#include "control_types.h"


#ifdef HAS_MAM_CUSTOM
#include "mam_custom_types.h"
#else
#define MAM_CUSTOM_VARIABLES
#endif

/* MAM master information */
typedef union {
    uint8_t byte;
    struct {
        uint8_t core0 :1; /* 0 CPU0 */
        uint8_t core1 :1; /* 1 CPU1 */
        uint8_t core2 :1; /* 2 CPU2 */
        uint8_t enet:1;   /* 3 ENET */
        uint8_t hsm:1;    /* 4 HSM  Hardware Secure Module*/
        uint8_t dma0:1;   /* 5 DMA0 */
        uint8_t dma1:1;   /* 6 DMA1 */
        uint8_t res:1;    /* 7      */
    };
}MamMaster_t;


typedef struct {
    uint8_t num;
    MamMaster_t Masters;
    uint32_t address;
    ControlPermission_t access;
    bool valid;
    char* name;
}MamMemoryAccessConfig_t;

#define MAM_COMMON_VARIABLES                           \
    char* name;                                        \
    uint8_t num;                                       \
    uint32_t region_cnt;                               \
    MamMemoryAccessConfig_t* region;                   \
    bool interrupt_on;                                 \
    bool valid;

typedef struct {
    MAM_COMMON_VARIABLES
}MamConfig_t;

#define MAM_ISR_VARIABLES                   \
    bool processed;                         \
    bool it_done;                           \
    uint32_t it_cnt;

typedef struct {
    MAM_COMMON_VARIABLES
    MAM_CUSTOM_VARIABLES
    MAM_ISR_VARIABLES
    bool init;
    uint32_t spin;
}MamHandle_t;


#endif /* MAM_TYPES_H */
