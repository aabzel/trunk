#ifndef TEST_I2S_ARTERY_H
#define TEST_I2S_ARTERY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"


#ifndef HAS_I2S
#error "+HAS_I2S"
#endif


bool test_i2s_artery_types(void);

#define TEST_SUIT_I2S_ARTERY                        \
    {"i2s_artery_types", test_i2s_artery_types},



#ifdef __cplusplus
}
#endif

#endif /* TEST_I2S_ARTERY_H */
