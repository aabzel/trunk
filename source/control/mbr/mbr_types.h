#ifndef MBR_TYPES_H
#define MBR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mbr_const.h"

#define MBR_COMMON_VARIABLES       \
    uint32_t boot_start_address;   \
    uint8_t led_num;

typedef struct  {
    MBR_COMMON_VARIABLES
} MbrConfig_t;

typedef struct  {
    MBR_COMMON_VARIABLES
    bool init;
} MbrHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* MBR_TYPES_H */
