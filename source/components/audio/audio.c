#include "audio.h"

#include "array.h"
#include "log.h"
#include "utils_math.h"

uint32_t sample_int_2_uint(int32_t sample, uint8_t bits){
    uint32_t sample_data = 0;
    uint32_t max_val = ipow(2,bits);
    sample_data = (uint32_t)    (sample + (  (int32_t)(max_val/2) )     );
    return sample_data;
}


bool audio_add_front_zeros(SampleType_t* const SampleArray,
                           uint32_t size, int32_t offset ) {
    bool res = false;
    uint32_t sample_size = sizeof(SampleType_t);
    LOG_INFO(DDS, "sample_size:%u", sample_size);
    switch(sample_size) {
        case 1: res = array_s8_add_front_zeros((int8_t*)SampleArray, size, offset); break;
        case 2: res = array_s16_add_front_zeros((int16_t*)SampleArray, size, offset); break;
        case 4: res = array_s32_add_front_zeros((int32_t*)SampleArray, size, offset); break;
        default: res = false; break;
    }
    return res;

}
