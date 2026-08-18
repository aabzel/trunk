#ifndef LEGAL_BAND_H
#define LEGAL_BAND_H

#include <stdbool.h>
#include <stdint.h>

#define LEGAL_BAND_1_HZ_START 864000000
#define LEGAL_BAND_1_HZ_END 865000000

#define LEGAL_BAND_2_HZ_START 866000000
#define LEGAL_BAND_2_HZ_END 868000000

#define LEGAL_BAND_3_HZ_START 868700000
#define LEGAL_BAND_3_HZ_END 869200000

bool is_band_legal(uint32_t frequency_hz, uint32_t bandwidth_hz);

#endif /* LEGAL_BAND_H  */
