#ifndef TEST_CAN_FC7300X_H
#define TEST_CAN_FC7300X_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "test_hw_dep_check.h"

bool test_can_fc7300x_types(void);

#define TEST_SUIT_CAN_FC7300X                            \
    {"can_fc7300x_types", test_can_fc7300x_types},


#ifdef __cplusplus
}
#endif

#endif /* TEST_CAN_FC7300X_H */
