#ifndef MPU_TYPES_H
#define MPU_TYPES_H

#include "std_includes.h"
#include "mpu_const.h"


#ifdef HAS_MPU_CUSTOM
#include "mpu_custom_types.h"
#else
#define MPU_CUSTOM_VARIABLES
#endif

typedef union {
    uint8_t byte;
    struct {
        uint8_t read:1;       /*bit0: 1-Allow read */
        uint8_t write:1;      /*bit1: 1-Allow write */
        uint8_t execute:1;    /*bit2: 1-Allow write */
        uint8_t cached:1;     /*bit3: 1-Allow caching */
        uint8_t shareable:1;  /*bit4: 1-Allow Shareable */
        uint8_t bufferable:1; /*bit5: 1-Allow bufferable */
        uint8_t res1:2;
    };
    struct {
        uint8_t perm:6;
        uint8_t res2:2;
    };
}MpuPermission_t;

typedef struct {
    uint32_t start;
    uint32_t size;
    bool on_off;
    bool valid;
    MpuPermission_t permission;
    char* name;
    uint8_t num;
}MpuRegionConfig_t;

#define MPU_COMMON_VARIABLES             \
    char* name;                          \
    uint8_t num;                         \
    bool interrupt_on;                   \
    MpuRegionConfig_t* Region;           \
    uint8_t region_cnt;                  \
    bool valid;


#define MPU_ISR_VARIABLES             \
    uint32_t it_cnt;                  \
    bool it_done ;


typedef struct {
    MPU_COMMON_VARIABLES
}MpuConfig_t;

typedef struct {
    MPU_COMMON_VARIABLES
    MPU_CUSTOM_VARIABLES
    MPU_ISR_VARIABLES
    bool init;
    uint32_t spin;
}MpuHandle_t;


#endif /* MPU_TYPES_H */
