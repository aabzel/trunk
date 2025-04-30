#ifndef TEST_DTMF_H
#define TEST_DTMF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"

#ifndef HAS_DTMF
#error "It is needed HAS_DTMF option for that component"
#endif

bool test_dtmf_types(void);
bool test_dtmf_chars(void);

#define TEST_SUIT_DTMF                                \
    {"dtmf_types", test_dtmf_types},                  \
    {"dtmf_chars", test_dtmf_chars},

#ifdef __cplusplus
}
#endif

#endif /* TEST_DTMF_H */
