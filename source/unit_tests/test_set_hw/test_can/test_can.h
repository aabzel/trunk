#ifndef TEST_CAN_H
#define TEST_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

bool test_can_types(void);
bool test_can_send_std(void);


#define TEST_SUIT_CAN                     \
    {"can_types", test_can_types},        \
    {"can_send_std", test_can_send_std},


#ifdef __cplusplus
}
#endif

#endif /* TEST_CAN_H */
