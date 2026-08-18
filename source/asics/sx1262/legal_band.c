
#include "legal_band.h"

#include <stdbool.h>
#include <stdint.h>

static bool is_in_range(uint32_t val, uint32_t down, uint32_t up) {
    bool res = false;
    if((down <= val) && (val <= up)) {
        res = true;
    }
    return res;
}

static bool is_band_legal_one(uint32_t frequency_hz, uint32_t bandwidth_hz, uint32_t down, uint32_t up) {
    bool res = true;

    uint32_t frequency_min = frequency_hz - bandwidth_hz / 2;
    uint32_t frequency_max = frequency_hz + bandwidth_hz / 2;

    res = is_in_range(frequency_min, down, up);
    res = is_in_range(frequency_max, down, up) && res;

    return res;
}

bool is_band_legal(uint32_t frequency_hz, uint32_t bandwidth_hz) {
    bool res = true;
    uint8_t ret1, ret2, ret3;

    ret1 = (uint8_t)is_band_legal_one(frequency_hz, bandwidth_hz, LEGAL_BAND_1_HZ_START, LEGAL_BAND_1_HZ_END);
    ret2 = (uint8_t)is_band_legal_one(frequency_hz, bandwidth_hz, LEGAL_BAND_2_HZ_START, LEGAL_BAND_2_HZ_END);
    ret3 = (uint8_t)is_band_legal_one(frequency_hz, bandwidth_hz, LEGAL_BAND_3_HZ_START, LEGAL_BAND_3_HZ_END);

    if(1 == (ret1 + ret2 + ret3)) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
