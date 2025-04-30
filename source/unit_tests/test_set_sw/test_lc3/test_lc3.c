#include "test_lc3.h"

#include "audio_diag.h"
#include "debug_info.h"
#include "log.h"
#include "time_mcal.h"
#include "sw_codec_lc3.h"
#include "sw_codec_select.h"
#include "unit_test_check.h"
#include "utils_math.h"

#define FREQ_HZ 400.0
#define AMPLITUDE 240.0

#ifdef HAS_LC3_ENCODE
bool test_lc3_encode(void) {
    LOG_INFO(LC3,"%s()",__FUNCTION__);
    int ret = -1;
    bool res = true;
    ASSERT_GR(0,PCM_NUM_BYTES_MONO);
    LOG_INFO(LC3,"PCM_NUM_BYTES_MONO: %u Byte",PCM_NUM_BYTES_MONO);
    LOG_INFO(LC3,"ENC_MAX_FRAME_SIZE: %u Byte",ENC_MAX_FRAME_SIZE);
    ASSERT_GR(0,LC3_PCM_NUM_BYTES_MONO);
    ASSERT_GR(0,ENC_MAX_FRAME_SIZE);

    int16_t pcm_in_data[PCM_NUM_BYTES_MONO/1] = { 0 };
    uint32_t t = 0;
    int16_t sample =0;
    double sample_time_s = 1.0/((double) CONFIG_AUDIO_SAMPLE_RATE_HZ);
    uint32_t sample_time_us = SEC_2_USEC(sample_time_s);
    LOG_INFO(LC3,"Sample_Time: %u us",sample_time_us);
    for(t=0; t<(PCM_NUM_BYTES_MONO/2); t++) {
		sample = (int16_t) calc_sin_sample(t*sample_time_us, FREQ_HZ, 0, AMPLITUDE, 0);
		LOG_DEBUG(LC3,"sample %d",sample);
		pcm_in_data[t]=sample;
    }
    print_mem((uint8_t*)pcm_in_data, sizeof(pcm_in_data), true, false, true, true);
    uint8_t encoded_data[ENC_MAX_FRAME_SIZE*AUDIO_CH_NUM ]={0};
    uint16_t encoded_bytes_written = 0;
    ret =  sw_codec_lc3_enc_run(pcm_in_data,
                                sizeof(pcm_in_data),
                                LC3_USE_BITRATE_FROM_INIT,
                                0,
                                sizeof(encoded_data),
                                encoded_data,
                                &encoded_bytes_written);
    ASSERT_EQ(0,ret);
    ASSERT_GR(0,encoded_bytes_written);
    LOG_INFO(LC3,"EncodeOutSize: %u Byte",encoded_bytes_written);
    print_mem(encoded_data, encoded_bytes_written, true, false, true, true);
    return res;
}
#endif

bool test_lc3(void) {
    LOG_INFO(LC3,"%s()",__FUNCTION__);
    int ret = -1;
    bool res = true;
    ASSERT_GR(0,PCM_NUM_BYTES_MONO);
    LOG_INFO(LC3,"PCM_NUM_BYTES_MONO: %u Byte",PCM_NUM_BYTES_MONO);
    ASSERT_GR(0,LC3_PCM_NUM_BYTES_MONO);
    int16_t pcm_in_data[PCM_NUM_BYTES_MONO/2] = { 0 };
    uint8_t encoded_data[ENC_MAX_FRAME_SIZE ]={0};
#ifdef HAS_LC3_ENCODE
    uint32_t t = 0;
    int16_t sample =0;
    double sample_time_s = 1.0/((double) CONFIG_AUDIO_SAMPLE_RATE_HZ);
    uint32_t sample_time_us = SEC_2_USEC(sample_time_s);
    LOG_INFO(LC3,"Sample_Time: %u us",sample_time_us);
    for(t=0; t<(PCM_NUM_BYTES_MONO/2); t++) {
		sample = (int16_t) calc_sin_sample(t*sample_time_us, FREQ_HZ, 0.0, AMPLITUDE, 0.0);
		LOG_DEBUG(LC3,"sample %d",sample);
		pcm_in_data[t]=sample;
    }
    print_mem((uint8_t*)pcm_in_data, sizeof(pcm_in_data), true, false, true, true);
    uint16_t encoded_bytes_written = 0;
    ret =  sw_codec_lc3_enc_run(pcm_in_data,
                                sizeof(pcm_in_data),
                                LC3_USE_BITRATE_FROM_INIT,
                                0,
                                sizeof(encoded_data),
                                encoded_data,
                                &encoded_bytes_written);
    ASSERT_EQ(0,ret);
    ASSERT_GR(0,encoded_bytes_written);
    ASSERT_EQ(encoded_bytes_written,sizeof(encoded_data));
    LOG_INFO(LC3,"EncodeOutSize: %u Byte",encoded_bytes_written);
    print_mem(encoded_data, encoded_bytes_written, true, false, true, true);
#endif

#ifdef HAS_LC3_DECODE
    int16_t pcm_out_data[LC3_PCM_NUM_BYTES_MONO/2];
    uint16_t pcm_data_out_size = 0;
    ret = sw_codec_lc3_dec_run(
    		encoded_data,
            sizeof(encoded_data),
            sizeof(pcm_out_data),
            0,
			pcm_out_data,
            &pcm_data_out_size,
            false);
    ASSERT_EQ(0,ret);
    ASSERT_GR(0,pcm_data_out_size);
    LOG_INFO(LC3,"DecodedPCMSize: %u Byte",pcm_data_out_size);
#endif
    print_mem((uint8_t*)pcm_out_data, pcm_data_out_size, true, false, true, true);

    uint32_t size = MIN(pcm_data_out_size,PCM_NUM_BYTES_MONO);
    LOG_INFO(LC3,"common size: %u Byte %u Sample",size,size/2);
    //ASSERT_EQ_MEM(pcm_in_data,pcm_out_data,size);
    LOG_INFO(LC3,"Origin PCM");
    audio_print_sample(pcm_in_data, size/2);
    LOG_INFO(LC3,"Decoded PCM");
    audio_print_sample(pcm_out_data, size/2);
    return res;
}

#ifdef HAS_LC3_DECODE
bool test_lc3_decode(void) {
    LOG_INFO(LC3,"%s()",__FUNCTION__);
    int ret = -1;
    bool res = true;
    uint8_t encoded_data[64];
    ASSERT_GR(0,PCM_NUM_BYTES_MONO);
    ASSERT_GR(0,LC3_PCM_NUM_BYTES_MONO);

    print_mem(encoded_data, sizeof(encoded_data), true, false, true, true);
    int16_t pcm_out_data[LC3_PCM_NUM_BYTES_MONO/2];
    memset(pcm_out_data,0,sizeof(pcm_out_data));
    uint16_t pcm_data_out_size = 0;
    ret = sw_codec_lc3_dec_run(
    		encoded_data,
            sizeof(encoded_data),
            sizeof(pcm_out_data),
            0,
			pcm_out_data,
            &pcm_data_out_size,
            false);
    ASSERT_EQ(0,ret);
    ASSERT_GR(0,pcm_data_out_size);
    LOG_INFO(LC3,"DecodeOutSize: %u Byte",pcm_data_out_size);
    ASSERT_EQ(0,ret);
    ASSERT_EQ(pcm_data_out_size, sizeof(pcm_out_data));

    print_mem((uint8_t*)pcm_out_data, pcm_data_out_size, true, false, true, true);
    return res;
}
#endif

