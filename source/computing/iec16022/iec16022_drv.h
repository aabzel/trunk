#ifndef IEC16022_ENCODER_H
#define IEC16022_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "iec16022_const.h"
#include "iec16022_diag.h"


bool iec16022_encode(uint8_t* array, size_t size, char* file_name);

#ifdef __cplusplus
}
#endif

#endif /* IEC16022_ENCODER_H */
