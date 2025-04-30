#ifndef TEST_AUTO_VOLUME_H
#define TEST_AUTO_VOLUME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "audio_types.h"
#include "test_hw_dep_check.h"

#ifndef HAS_AUTO_VOLUME
#error "+HAS_AUTO_VOLUME"
#endif

#ifndef HAS_TEST_AUTO_VOLUME
#error "+HAS_AUTO_VOLUME_TESTS"
#endif

bool test_auto_volume_hash_set(void);
bool test_auto_volume_types(void);

#define TEST_SUIT_AUTO_VOLUME                       \
		{"auto_volume_types", test_auto_volume_types},     \
		{"auto_volume_hash_set", test_auto_volume_hash_set},

#ifdef __cplusplus
}
#endif

#endif /* TEST_AUTO_VOLUME_H */
