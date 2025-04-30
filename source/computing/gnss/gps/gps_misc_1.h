#ifndef GPS_UTILS_H
#define GPS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "gps_types.h"

bool gps_post_proc(uint8_t num, const char* const file_name);
void gps_generate_prn(uint8_t* dest, int prn);
uint8_t reverse_bits(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* GPS_UTILS_H */
