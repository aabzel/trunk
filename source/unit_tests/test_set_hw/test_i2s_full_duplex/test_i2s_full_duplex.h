#ifndef TEST_I2S_FULL_DUPLEX_H
#define TEST_I2S_FULL_DUPLEX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "test_hw_dep_check.h"


bool test_i2s_full_duplex_proc_duration(void);


#define TEST_SUIT_I2S_FULL_DUPLEX                    \
    {"i2s_full_duplex_proc_duration", test_i2s_full_duplex_proc_duration},


#ifdef __cplusplus
}
#endif

#endif /* TEST_I2S_FULL_DUPLEX_H */
