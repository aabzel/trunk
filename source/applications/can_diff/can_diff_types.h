#ifndef CAN_DIFF_TYPES_H
#define CAN_DIFF_TYPES_H

#include "std_includes.h"
#include "can_diff_const.h"
#include "can_types.h"

#define CAN_DIFF_COMMON_VARIABLES                      \
    uint32_t can_id;                                   \
    uint8_t can_num;                                   \
    CanIdentifier_t id_type;                           \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    CAN_DIFF_COMMON_VARIABLES
}CanDiffConfig_t;

typedef struct {
    CAN_DIFF_COMMON_VARIABLES
    bool init;
    bool live;
    uint32_t spin;
    CanMessage_t MessageCur;
    CanMessage_t MessagePrev;
    uint8_t diffData[CAN_MAX_PAYLOAD_SIZE];
}CanDiffHandle_t;


#endif /* CAN_DIFF_TYPES_H */
