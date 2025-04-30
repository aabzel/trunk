#ifndef PARAMS_TEST_H
#define PARAMS_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_PARAM
#error "+HAS_PARAM"
#endif

#include "test_hw_dep_check.h"

bool test_param_types(void);
bool test_param(void);
bool test_param_set_get(void);

#define TEST_SUIT_PARAM {"param", test_param}, {"param_set_get", test_param_set_get}, {"param_types", test_param_types},

#ifdef __cplusplus
}
#endif

#endif /* PARAMS_TEST_H */
