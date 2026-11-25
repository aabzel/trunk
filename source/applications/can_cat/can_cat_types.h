#ifndef CAN_CAT_TYPES_H
#define CAN_CAT_TYPES_H

#include "std_includes.h"
#include "can_cat_const.h"


#ifdef HAS_CAN_CAT_CUSTOM
#include "can_cat_custom_types.h"
#else
#define CAN_CAT_CUSTOM_VARIABLES
#endif

#define CAN_CAT_COMMON_VARIABLES                  \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    CAN_CAT_COMMON_VARIABLES
}CanCatConfig_t;

typedef struct {
    CAN_CAT_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}CanCatHandle_t;


#endif /* CAN_CAT_TYPES_H */
