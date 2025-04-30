#ifndef TEST_PASTILDA_UTILS_H
#define TEST_PASTILDA_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_pastilda_master_key_enter(void);
bool test_pastilda_types(void);

#define TEST_SUIT_PASTILDA                                 \
    {"pas~MasterKeyIn", test_pastilda_master_key_enter},   \
    {"pas~Types", test_pastilda_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_PASTILDA_UTILS_H */
