#ifndef TEST_MODULATOR_H
#define TEST_MODULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

bool test_modulator(void);

#define TEST_SUIT_MODULATOR            \
    {"modulator", test_modulator},   \

#ifdef __cplusplus
}
#endif

#endif /* TEST_MODULATOR_H */
