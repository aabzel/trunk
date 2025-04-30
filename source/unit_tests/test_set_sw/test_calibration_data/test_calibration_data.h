#ifndef TEST_CALIBRATION_DATA_UTILS_H
#define TEST_CALIBRATION_DATA_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


bool test_calibration_data_types(void);
bool test_calibration_data_read(void);

#define TEST_SUIT_CALIBRATION_DATA                                         \
    {"calibration_data_types", test_calibration_data_types},              \
    {"calibration_data_read", test_calibration_data_read},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CALIBRATION_DATA_UTILS_H */
