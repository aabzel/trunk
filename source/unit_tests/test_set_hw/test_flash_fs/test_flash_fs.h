#ifndef FLASH_FS_TEST_H
#define FLASH_FS_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

bool test_flash_fs_set_get_const(void);
bool test_flash_fs_set_get_set(void);
bool test_flash_fs_inval(void);
bool test_flash_fs_types(void);

#define TEST_SUIT_FLASH_FS_BASE             \
    {"flash_fs_set_get_const", test_flash_fs_set_get_const}, \
    {"flash_fs_types", test_flash_fs_types}, \
    {"flash_fs_set_get_set", test_flash_fs_set_get_set}, \
    {"flash_fs_inval", test_flash_fs_inval},

#ifdef HAS_TEST_SUIT_FLASH_FS_EXT
bool test_flash_fs_toggle(void);
#define TEST_SUIT_FLASH_FS_EXT             \
    {"flash_fs_toggle", test_flash_fs_toggle},
#else
#define TEST_SUIT_FLASH_FS_EXT
#endif

#define TEST_SUIT_FLASH_FS      \
        TEST_SUIT_FLASH_FS_BASE \
        TEST_SUIT_FLASH_FS_EXT

#ifdef __cplusplus
}
#endif

#endif /* FLASH_FS_TEST_H */
