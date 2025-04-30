#ifndef TEST_DISK_H
#define TEST_DISK_H

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"

#define DISK_BLOCK_SIZE 512

bool test_disk_read_write(void);
bool test_disk_read(void);
bool test_disk_const(void);
bool test_disk_ioctl(void);
bool test_disk_link(void);


#define TEST_SUIT_DISK                     \
    {"disk_const", test_disk_const},       \
    {"disk_ioctl", test_disk_ioctl},        \
    {"disk_read", test_disk_read},                     \
    {"disk_read_write", test_disk_read_write},

#endif /* TEST_DISK_H */
