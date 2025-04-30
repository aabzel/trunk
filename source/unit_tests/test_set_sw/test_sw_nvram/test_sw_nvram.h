#ifndef TEST_SW_NVRAM_H
#define TEST_SW_NVRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_NVRAM
#error "+HAS_SW_NVRAM"
#endif

bool test_sw_nvram_write_same(void);
bool test_sw_nvram_write(void);
bool test_sw_nvram_write_delete_write(void);
bool test_sw_nvram_write_stress(void);
bool test_sw_nvram_double_write(void);
bool test_sw_nvram_types(void);
bool test_sw_nvram_const(void);
bool test_sw_nvram_read(void);
bool test_sw_nvram_delete(void);

#define TEST_SUIT_SW_NVRAM                                   \
    {"nvram_const", test_sw_nvram_const},                    \
    {"nvram_types", test_sw_nvram_types},                    \
    {"nvram_write", test_sw_nvram_write},                    \
    {"nvram_write_delete_write", test_sw_nvram_write_delete_write},                    \
    {"nvram_double_write", test_sw_nvram_double_write},      \
    {"nvram_read", test_sw_nvram_read},                      \
    {"nvram_delete", test_sw_nvram_delete},                  \
    {"nvram_write_same", test_sw_nvram_write_same},          \
    {"nvram_write_stress", test_sw_nvram_write_stress},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SW_NVRAM_H */
