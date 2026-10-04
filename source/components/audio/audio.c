#include "audio.h"

#include "array.h"
#include "log.h"
#include "time_mcal.h"
#include "utils_math.h"

uint32_t sample_int_2_uint(int32_t sample, uint8_t bits) {
    uint32_t sample_data = 0;
    uint32_t max_val = ipow(2, bits);
    sample_data = (uint32_t)(sample + ((int32_t)(max_val / 2)));
    return sample_data;
}

bool audio_is_valid_frequency(const uint32_t audio_frequency_hz) {
    bool res = false;
    switch(audio_frequency_hz) {
    case AUDIO_FREQ_8K:
        res = true;
        break;
    case AUDIO_FREQ_11K:
        res = true;
        break;
    case AUDIO_FREQ_16K:
        res = true;
        break;
    case AUDIO_FREQ_22K:
        res = true;
        break;
    case AUDIO_FREQ_32K:
        res = true;
        break;
    case AUDIO_FREQ_41K:
        res = true;
        break;
    case AUDIO_FREQ_48K:
        res = true;
        break;
    case AUDIO_FREQ_44K:
        res = true;
        break;
    case AUDIO_FREQ_88K:
        res = true;
        break;
    case AUDIO_FREQ_96K:
        res = true;
        break;
    case AUDIO_FREQ_176K:
        res = true;
        break;
    case AUDIO_FREQ_192K:
        res = true;
        break;
    case AUDIO_FREQ_384K:
        res = true;
        break;
    case AUDIO_FREQ_768K:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

uint32_t audio_duration_to_samples(uint32_t sampling_frequency_hz, float duratuin_s) {
    uint32_t samples = 0;
    float sample_ditation_s = 1.0f / ((float)sampling_frequency_hz);
    samples = (uint32_t)(duratuin_s / sample_ditation_s);
    LOG_INFO(AUDIO, "FS:%u [Hz],Duration:%f [s],offset:%u [Sam]", sampling_frequency_hz, duratuin_s, samples);
    return samples;
}

float audio_samples_to_duration_s(const uint32_t sampling_frequency_hz, const uint32_t samples) {
    float duration_s = 0.0f;
    float sample_ditation_s = 1.0f / ((float)sampling_frequency_hz);
    duration_s = sample_ditation_s * ((float)samples);
    return duration_s;
}

bool audio_add_front_zeros(SampleType_t* const SampleArray, uint32_t size, int32_t offset) {
    bool res = false;
    uint32_t sample_size = sizeof(SampleType_t);
    LOG_INFO(AUDIO, "sample_size:%u", sample_size);
    switch(sample_size) {
    case 1:
        res = array_s8_add_front_zeros((int8_t*)SampleArray, size, offset);
        break;
    case 2:
        res = array_s16_add_front_zeros((int16_t*)SampleArray, size, offset);
        break;
    case 4:
        res = array_s32_add_front_zeros((int32_t*)SampleArray, size, offset);
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool wav_file_name_generate(char* file_name, uint32_t size, uint32_t param, float duration_s) {
    bool res = false;
    if(file_name) {
        uint32_t up_time_ms = time_get_ms32();
        uint32_t duration_ms = 1000.0 * duration_s;
        snprintf(file_name, size, "R_%u_UT%u_%uMs.wav", param, up_time_ms, duration_ms);
        res = true;
    }
    return res;
}

float audio_sample_tof_path_m(const uint32_t sampling_frequency_hz, const float speed_mps) {
    float sample_dur_s = 1.0f / ((float)sampling_frequency_hz);
    float path_m = sample_dur_s * speed_mps;
    LOG_INFO(AUDIO, "Fs:%u Hz,V:%f m/s,S:%f m,", sampling_frequency_hz, speed_mps, path_m);
    return path_m;
}
