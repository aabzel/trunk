#ifndef FLASH_TEST_H
#define FLASH_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifdef HAS_TEST_FLASH_WRITE
bool test_flash_write(void);
#define TEST_SUIT_FLASH_WRITE {"flash_write", test_flash_write},
#else
#define TEST_SUIT_FLASH_WRITE
#endif

bool test_flash_legal_change(void);

#define TEST_SUIT_FLASH                               \
    {"flash_legal_change", test_flash_legal_change},  \
    TEST_SUIT_FLASH_WRITE

#ifdef __cplusplus
}
#endif

#endif /* FLASH_TEST_H */
