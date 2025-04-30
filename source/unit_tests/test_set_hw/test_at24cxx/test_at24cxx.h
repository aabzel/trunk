#ifndef TEST_AT24CXX_H
#define TEST_AT24CXX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_AT24CXX
#error "+HAS_AT24CXX"
#endif

#ifndef HAS_TEST_AT24CXX
#error "+HAS_TEST_AT24CXX"
#endif

#define AT24C02_TEST_INSTANCE 1

bool test_at24cxx_errase(void);
bool test_at24cxx_read(void);
bool test_at24cxx_write(void);
bool test_at24cxx_write_inc(void);
bool test_at24cxx_write2(void);
bool test_at24cxx_write_byte(void);
bool test_at24cxx_write_page(void);
bool test_at24cxx_write_null(void);
bool test_at24cxx_write0(void);
bool test_at24cxx_read_null(void);
bool test_at24cxx_read0(void);
bool test_at24cxx_connect(void);

#define TEST_SUIT_AT24CXX                                \
        {"at24cxx_connect", test_at24cxx_connect},       \
        {"at24cxx_write_page", test_at24cxx_write_page}, \
        {"at24cxx_read0", test_at24cxx_read0},           \
        {"at24cxx_write_byte", test_at24cxx_write_byte}, \
        {"at24cxx_write_inc", test_at24cxx_write_inc}, \
        {"at24cxx_read_null", test_at24cxx_read_null},   \
        {"at24cxx_read", test_at24cxx_read},             \
        {"at24cxx_write_null", test_at24cxx_write_null}, \
        {"at24cxx_write2", test_at24cxx_write2},         \
        {"at24cxx_write", test_at24cxx_write},           \
        {"at24cxx_write0", test_at24cxx_write0},         \
        {"at24cxx_errase", test_at24cxx_errase},

#ifdef __cplusplus
}
#endif

#endif /* TEST_AT24CXX_H */
