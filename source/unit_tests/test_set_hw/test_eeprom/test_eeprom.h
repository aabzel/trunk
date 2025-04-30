#ifndef EEPROM_TEST_H
#define EEPROM_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

bool test_eeprom_read(void);

#ifdef HAS_TEST_EEPROM_WRITE

bool test_eeprom_erase(void);
bool test_eeprom_write_safe(void);
bool test_eeprom_write(void);
bool test_eeprom_write_dword(void);
bool test_eeprom_byte_write(void);

#define TEST_SUIT_EEPROM_WRITE  \
    {"eeprom_byte_write", test_eeprom_byte_write}, \
    {"eeprom_write_dword", test_eeprom_write_dword}, \
    {"eeprom_write_safe", test_eeprom_write_safe}, \
    {"eeprom_write", test_eeprom_write},   \
    {"eeprom_erase", test_eeprom_erase},

#else
#define TEST_SUIT_EEPROM_WRITE
#endif


#define TEST_SUIT_EEPROM                               \
    {"eeprom_read", test_eeprom_read},                 \
    TEST_SUIT_EEPROM_WRITE

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_TEST_H */
