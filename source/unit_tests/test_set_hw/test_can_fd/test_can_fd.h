#ifndef TEST_CAN_FD_H
#define TEST_CAN_FD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

bool test_can_fd_baudrate(void);
bool test_can_fd_cfg(void);
bool test_can_fd_clock(void);
bool test_can_fd_hash(void);
bool test_can_fd_loopback_0_5(void);
bool test_can_fd_loopback_5_0(void);
bool test_can_fd_send_std(void);
bool test_can_fd_types(void);

#define TEST_SUIT_CAN_FD                                     \
    {"can_fd_cfg", test_can_fd_cfg},                         \
    {"can_fd_hash", test_can_fd_hash},                       \
    {"can_fd_clock", test_can_fd_clock},                     \
    {"can_fd_types", test_can_fd_types},                     \
    {"can_fd_send_std", test_can_fd_send_std},               \
    {"can_fd_loopback_0_5", test_can_fd_loopback_0_5},       \
    {"can_fd_loopback_5_0", test_can_fd_loopback_5_0},       \
    {"can_fd_baudrate", test_can_fd_baudrate},


#ifdef __cplusplus
}
#endif

#endif /* TEST_CAN_FD_H */
