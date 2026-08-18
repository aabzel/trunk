
#ifndef DS3231_DIAG_H
#define DS3231_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "ds3231_types.h"

bool diag_ds3231(uint8_t num, char* key_word1, char* key_word2);
const char* HourModeToStr(HourMode_t hour_mode);


#ifdef __cplusplus
}
#endif

#endif /* DS3231_DIAG_H */
