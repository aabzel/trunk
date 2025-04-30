#ifndef NVS_TEST_H
#define NVS_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_nvs_write(void);

#define TEST_SUIT_NVS {"nvs_write", test_nvs_write},

#ifdef __cplusplus
}
#endif

#endif /* NVS_TEST_H */
