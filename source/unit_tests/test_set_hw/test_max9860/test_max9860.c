#include "test_max9860.h"

#include "unit_test_check.h"

#ifdef HAS_I2S
#include "i2s_drv.h"
#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#endif /*HAS_TEST_I2S*/
#endif /*HAS_I2S*/

#include "max9860_config.h"
#include "max9860_drv.h"
#include "none_blocking_pause.h"

bool test_max9860_hash_tables(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(0x00, DvaGain2Code(10));
    ASSERT_EQ(0x00, DvaGain2Code(3));
    ASSERT_EQ(0x06, DvaGain2Code(0));
    ASSERT_EQ(0x60, DvaGain2Code(-45));
    ASSERT_EQ(0xBA, DvaGain2Code(-90));
    ASSERT_EQ(0xBC, DvaGain2Code(-100));

#if 0
    ASSERT_EQ(3,Code2Gain(0));
    ASSERT_EQ(2,Code2Gain(2));
    ASSERT_EQ(0,Code2Gain(6));
    ASSERT_EQ(-90,Code2Gain(0xBA));
    ASSERT_EQ(INT8_MIN,Code2Gain(190));
#endif

    ASSERT_TRUE(is_valid_voice_filter(0));
    ASSERT_TRUE(is_valid_voice_filter(1));
    ASSERT_TRUE(is_valid_voice_filter(2));
    ASSERT_TRUE(is_valid_voice_filter(3));
    ASSERT_TRUE(is_valid_voice_filter(4));
    ASSERT_TRUE(is_valid_voice_filter(5));
    ASSERT_FALSE(is_valid_voice_filter(6));

#ifdef HAS_MAX9860_ADC
    /*see (page 29) Left and Right Microphone PGA*/
    ASSERT_EQ(7, PgamCode2Gain(0x0D));
    ASSERT_EQ(1, PgamCode2Gain(0x13));
    ASSERT_EQ(0, PgamCode2Gain(0xFF));
    ASSERT_EQ(20, PgamCode2Gain(0));

    ASSERT_EQ(0, Gain2PgamCode(40));
    ASSERT_EQ(0, Gain2PgamCode(20));
    ASSERT_EQ(0xF, Gain2PgamCode(5));
    ASSERT_EQ(0x14, Gain2PgamCode(0));
    ASSERT_EQ(0x14, Gain2PgamCode(-10));

    ASSERT_EQ(0, Gain2PamCode(-1));
    ASSERT_EQ(1, Gain2PamCode(0));
    ASSERT_EQ(1, Gain2PamCode(1));
    ASSERT_EQ(2, Gain2PamCode(19));
    ASSERT_EQ(2, Gain2PamCode(20));
    ASSERT_EQ(2, Gain2PamCode(21));

    ASSERT_EQ(3, Gain2PamCode(29));
    ASSERT_EQ(3, Gain2PamCode(30));
    ASSERT_EQ(3, Gain2PamCode(31));

    /*Sets the level of left ADC output mixed into the DAC.*/
    ASSERT_EQ(0x01, Gain2DvstCode(0));
    ASSERT_EQ(5, Gain2DvstCode(-8));
    ASSERT_EQ(0x1F, Gain2DvstCode(-60));
    ASSERT_EQ(0, Gain2DvstCode(INT8_MIN));
    ASSERT_EQ(0x01, Gain2DvstCode(10));

    ASSERT_EQ(INT8_MIN, Code2SideToneGain(0));
    ASSERT_EQ(0, Code2SideToneGain(1));
    ASSERT_EQ(-14, Code2SideToneGain(0x08));
    ASSERT_EQ(-42, Code2SideToneGain(0x16));
    ASSERT_EQ(-60, Code2SideToneGain(0x1F));
    ASSERT_EQ(INT8_MIN, Code2SideToneGain(0x2F));

    ASSERT_EQ(INT8_MIN, PamCode2Gain(0));
    ASSERT_EQ(0, PamCode2Gain(1));
    ASSERT_EQ(20, PamCode2Gain(2));
    ASSERT_EQ(30, PamCode2Gain(3));

    ASSERT_EQ(3, AdcCode2Gain(0));
    ASSERT_EQ(0, AdcCode2Gain(3));
    ASSERT_EQ(-12, AdcCode2Gain(0xF));

    ASSERT_EQ(0, AdcGain2Code(3));
    ASSERT_EQ(1, AdcGain2Code(2));
    ASSERT_EQ(3, AdcGain2Code(0));
    ASSERT_EQ(4, AdcGain2Code(-1));
    ASSERT_EQ(0xC, AdcGain2Code(-9));
    ASSERT_EQ(0xF, AdcGain2Code(-12));

    ASSERT_FALSE(is_valid_adc_gain(4));
    ASSERT_TRUE(is_valid_adc_gain(3));
    ASSERT_TRUE(is_valid_adc_gain(0));
    ASSERT_TRUE(is_valid_adc_gain(-12));
    ASSERT_FALSE(is_valid_adc_gain(-13));
#endif

    return res;
}

// 60 - too loudly
#define TEST_DAC_NUM 1
bool test_max9860_play_freq(double freq, uint16_t amplitude, uint32_t duration_ms) {
    LOG_INFO(TEST, CRLF CRLF "Max9860Play Freq: %f Hz Amplitude: %u Duration:%u ms", freq, amplitude, duration_ms);
    bool res = true;

    ASSERT_GR(0, amplitude);
    ASSERT_GR(0, freq);
    ASSERT_GR(0, duration_ms);
    // EXPECT_TRUE(max9860_volume_set(-10));
#ifdef HAS_I2S_TEST
    ASSERT_TRUE(test_i2s_play_freq(Max9860Config.i2s_num, freq, amplitude, duration_ms));
#else
    LOG_ERROR(I2S, "NoI2Stests");
    res = false;
#endif /*HAS_I2S*/

    return res;
}

bool test_max9860_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(2, sizeof(SampleType_t));
    ASSERT_EQ(2, sizeof(Max9860RegVal_t));

    ASSERT_EQ(1, sizeof(Max9860Reg00InterruptStatus_t));
    ASSERT_EQ(1, sizeof(Max9860Reg01Gain_t));
    ASSERT_EQ(1, sizeof(Max9860Reg02IntEnable_t));
    ASSERT_EQ(1, sizeof(Max9860Reg03SystemClock_t));
    ASSERT_EQ(2, sizeof(Max9860Reg04StereoAudioClockControl_t));
    ASSERT_EQ(1, sizeof(Max9860Reg06If1_t));
    ASSERT_EQ(1, sizeof(Max9860Reg07If2_t));
    ASSERT_EQ(1, sizeof(Max9860Reg08DigitalFilter_t));
    ASSERT_EQ(1, sizeof(Max9860Reg09DacLevAdj_t));
    ASSERT_EQ(1, sizeof(Max9860Reg0AAdcOutLevel_t));
    ASSERT_EQ(1, sizeof(Max9860Reg0BDacGainSidetone_t));
    ASSERT_EQ(1, sizeof(Max9860Reg0CMicrophoneGain_t));
    ASSERT_EQ(1, sizeof(Max9860Reg0EMicrophoneAgc_t));
    ASSERT_EQ(1, sizeof(Max9860Reg0FNoiseGateMicAgc_t));
    ASSERT_EQ(1, sizeof(Max9860Reg10SysShutdown_t));

    ASSERT_EQ(1, sizeof(Max9860RegUniversal_t));

    return res;
}

bool test_max9860_freq_play(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(test_max9860_play_freq(1000.0, 1000, 2000));
    ASSERT_TRUE(test_max9860_play_freq(2000.0, 1000, 2000));
    ASSERT_TRUE(test_max9860_play_freq(3000.0, 1000, 2000));
    return res;
}

bool test_max9860_volume_play(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(max9860_attenuation_set(-20));
    ASSERT_TRUE(max9860_play_1kHz_tone_limited(100, 0, 1000));
    ASSERT_TRUE(max9860_play_1kHz_tone_limited(1000, 0, 1000));
    ASSERT_TRUE(max9860_play_1kHz_tone_limited(10000, 0, 1000));
    ASSERT_TRUE(max9860_play_1kHz_tone_limited(30000, 0, 1000));
    return res;
}

bool test_max9860_set_vol(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(MAX9860, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    bool res = true;
    ASSERT_TRUE(max9860_volume_set(3));
    ASSERT_TRUE(max9860_volume_set(-90));

    ASSERT_FALSE(max9860_volume_set(-100));
    ASSERT_FALSE(max9860_volume_set(7));

    set_log_level(MAX9860, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_max9860_sidetone(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    return res;
}

bool test_max9860_reinit(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(max9860_init());
    return res;
}

bool test_max9860_connected(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(max9860_is_connected());
    return res;
}

bool test_max9860_reg_write_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    Max9860Reg03SystemClock_t Reg;
    Reg.byte = 0;

    Reg.psclk = PSCLK_MCLK_10MHZ_20MHZ; /*MCLK Prescaler*/
    Reg.f16khz = 1;                     /*16kHz Mode*/
    Reg.freq = 1;                       /*Integer Clock Mode*/
    ASSERT_TRUE(max9860_reg_set_verify(MAX9860_REG_SYSTEM_CLOCK, Reg.byte));

    return res;
}

bool test_max9860_sample(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(0x75300000, max9860_pcm_2_32bit_sample(30000));
    ASSERT_EQ(0, max9860_pcm_2_32bit_sample(0));
    ASSERT_EQ(0x8AD00000, max9860_pcm_2_32bit_sample(-30000));
    return res;
}
