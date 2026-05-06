#include "test_bpsk_4fs.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "debug_info.h"
#include "quad_mix_4fs.h"
#include "bpsk_4fs_mcal.h"
#include "time_mcal.h"
#include "log.h"
#include "unit_test_check.h"
#include "bit_utils.h"

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif

bool test_bpsk_4fs_utils(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0, 0 % 8);
    EXPECT_EQ(0, 8 % 8);
    EXPECT_EQ(7, 7 % 8);
    EXPECT_EQ(1, 9 % 8);

    int32_t val = 0;
    val = floorf(50.5);
    EXPECT_EQ(50, val);
    val = floorf(-50.5);
    EXPECT_EQ(-51, val);

    EXPECT_EQ(1, bit_get_u8(0x01, 0));
    EXPECT_EQ(0, bit_get_u8(0x01, 1)); //

    return res;
}

bool test_bpsk_4fs_phase_error(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    float phase_err_rad = 0.0;

    phase_err_rad = calc_carrier_phase_err_rad(1, 1);
    EXPECT_EQ_FLOAT(DEG_2_RAD(45.0f), phase_err_rad, 0.0001);

    phase_err_rad = calc_carrier_phase_err_rad(-1, -1);
    EXPECT_EQ_FLOAT(DEG_2_RAD(45.0f), phase_err_rad, 0.0001);

    phase_err_rad = calc_carrier_phase_err_rad(1,-1);
    EXPECT_EQ_FLOAT(DEG_2_RAD(-45.0f), phase_err_rad, 0.0001);

    phase_err_rad = calc_carrier_phase_err_rad(-1,1);
    EXPECT_EQ_FLOAT(DEG_2_RAD(-45.0f), phase_err_rad, 0.0001);

    phase_err_rad = calc_carrier_phase_err_rad(0,0);
    EXPECT_EQ_FLOAT(DEG_2_RAD(0.0f), phase_err_rad, 0.0001);
    return res;
}

bool test_bpsk_4fs_encode(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t SampleArray[2000] = { 0 };
    uint8_t data[2] = { 0x51, 0xa2 };
    uint32_t len = 0;
    ASSERT_TRUE(bpsk_4fs_encode(1, data, sizeof(data), SampleArray, ARRAY_SIZE(SampleArray), &len )    );
    ASSERT_TRUE(array_i32_print_v2(SampleArray, len)   );
    return true;
}

bool test_bpsk_4fs_decode(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t SampleArray[2000] = { 0 };
    uint8_t data[2] = { 0x81, 0x5F }; //1000 0001 0105 1111
    uint32_t len = 0;
    ASSERT_TRUE( bpsk_4fs_encode(1, data, sizeof(data), SampleArray, ARRAY_SIZE(SampleArray), &len )    );
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(1);
    ASSERT_NE(NULL, Node);

    uint8_t RxData[299] = { 0 };
    uint32_t data_byte_cnt = 0;
    ASSERT_TRUE(  bpsk_4fs_decode(1, SampleArray, Node->sample_cnt, RxData,    sizeof(RxData), &data_byte_cnt)  );
    LOG_INFO(TEST, "RxByes:%u", data_byte_cnt);
    ASSERT_EQ(2, data_byte_cnt);
    ASSERT_TRUE(array_u8_print_binary(RxData, data_byte_cnt));
    ASSERT_TRUE(array_is_equal(RxData, data, 2));

    return true;
}

bool test_bpsk_4fs_decode_feed(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t txSampleArray[2000] = { 0 };
    uint8_t TxData[2] = {0xfe, 0xed }; //10101010 10101010
    uint32_t len = 0;
    ASSERT_TRUE( bpsk_4fs_encode(1, TxData, sizeof(TxData), txSampleArray, ARRAY_SIZE(txSampleArray), &len )    );
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(1);
    ASSERT_NE(NULL, Node);

    array_s32_scale(txSampleArray,ARRAY_SIZE(txSampleArray),2000);

    uint8_t RxData[50] = { 0 };
    memset(RxData,0,sizeof(RxData));
    uint32_t data_byte_cnt = 0;
    //First run to sync
    ASSERT_TRUE(  bpsk_4fs_decode(1, txSampleArray, Node->sample_cnt, RxData,    sizeof(RxData), &data_byte_cnt)  );

    // second run to fetch bits
    data_byte_cnt = 0;
    memset(RxData,0,sizeof(RxData));
    ASSERT_TRUE(  bpsk_4fs_decode(1, txSampleArray, Node->sample_cnt, RxData,sizeof(RxData), &data_byte_cnt)  );
    LOG_INFO(TEST, "RxByes:%u", data_byte_cnt);
    ASSERT_EQ(2, data_byte_cnt);
    ASSERT_TRUE(array_u8_print_binary(RxData, data_byte_cnt));
    ASSERT_TRUE(array_is_equal(RxData, &TxData[0], 2));

    return true;
}

bool test_bpsk_4fs_decode_aaaa(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t txSampleArray[2000] = { 0 };
    uint8_t TxData[2] = {0xaa, 0xaa }; //10101010 10101010
    uint32_t len = 0;
    ASSERT_TRUE( bpsk_4fs_encode(1, TxData, sizeof(TxData), txSampleArray, ARRAY_SIZE(txSampleArray), &len )    );
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(1);
    ASSERT_NE(NULL, Node);

    uint8_t RxData[299] = { 0 };
    memset(RxData,0,sizeof(RxData));
    uint32_t data_byte_cnt = 0;
    //First run to sync
    ASSERT_TRUE(  bpsk_4fs_decode(1, txSampleArray, Node->sample_cnt, RxData,
            sizeof(RxData),
            &data_byte_cnt)  );

    // second run to fetch bits
    data_byte_cnt = 0;
    memset(RxData,0,sizeof(RxData));
    ASSERT_TRUE(  bpsk_4fs_decode(1, txSampleArray, Node->sample_cnt, RxData,    sizeof(RxData), &data_byte_cnt)  );
    LOG_INFO(TEST, "RxByes:%u", data_byte_cnt);
    ASSERT_EQ(2, data_byte_cnt);
    ASSERT_TRUE(array_u8_print_binary(RxData, data_byte_cnt));
    ASSERT_TRUE(array_is_equal(RxData, &TxData[0], 2));

    return true;
}

bool test_bpsk_4fs_decode_FFFF(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t SampleArray[2000] = { 0 };
    uint8_t data[2] = { 0xFF, 0xFF };
    uint32_t len = 0;
    ASSERT_TRUE( bpsk_4fs_encode(1, data, sizeof(data), SampleArray, ARRAY_SIZE(SampleArray), &len )    );
    Bpsk4fsHandle_t *Node = Bpsk4fsGetNode(1);
    ASSERT_NE(NULL, Node);

    uint8_t RxData[299] = { 0 };
    uint32_t data_byte_cnt = 0;
    ASSERT_TRUE(  bpsk_4fs_decode(1, SampleArray,
            Node->sample_cnt,
            RxData,
            sizeof(RxData),
            &data_byte_cnt)  );
    LOG_INFO(TEST, "RxByes:%u", data_byte_cnt);
    ASSERT_EQ(2, data_byte_cnt);
    ASSERT_TRUE(array_u8_print_binary(RxData, data_byte_cnt));
    ASSERT_TRUE(array_is_equal(RxData, data, 2));

    return true;
}

/*
 tr bpsk_4fs_perf
*/
#define SAMPLE_CNT 1024
bool test_bpsk_4fs_perf(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    Bpsk4fsHandle_t* Bpsk = Bpsk4fsGetNode(1);
    uint16_t SampleMem[SAMPLE_CNT] = {0};
    array_u16_rand(SampleMem, SAMPLE_CNT, 0, 4095);
    float sample_dur_s= 1.0f/((float)Bpsk->sampling_frequency_hz);
    LOG_INFO(TEST, "sample_dur_s: %f:", sample_dur_s);
    float dma_half_rs_dur_s = sample_dur_s* ((float)SAMPLE_CNT);
    LOG_INFO(TEST, "dma_half_rs_dur_s: %f:", dma_half_rs_dur_s);
    uint64_t dma_half_rs_dur_us =(uint64_t) SEC_2_USEC(dma_half_rs_dur_s);
    LOG_INFO(TEST, "dma_half_rs_dur_us: %llu:Sam:%u Sam", dma_half_rs_dur_us,SAMPLE_CNT);
    uint64_t start_us = time_get_us();
    ASSERT_TRUE( proc_samples_to_mem(Bpsk, SampleMem,0, SAMPLE_CNT));
    uint64_t end_us = time_get_us();
    uint64_t dutatuoin_us = end_us - start_us;
    LOG_INFO(TEST, "dutatuoin_us: %llu:", dutatuoin_us);

    ASSERT_GR_64(dutatuoin_us, dma_half_rs_dur_us, 0)

    return true;
}

#define PHA_ERR_LUT 10
bool test_bpsk_4fs_calc_phase_err(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t i = 0 ;
    for(i=-PHA_ERR_LUT;i<=PHA_ERR_LUT;i++) {
        int32_t q= 0 ;
        for(q=-PHA_ERR_LUT;q<=PHA_ERR_LUT;q++) {
            float phase_err_rad_fast = calc_carrier_phase_err_lut_rad(i, q);
            float phase_err_rad_lut = calc_carrier_phase_err_rad((float) i, (float) q);
            LOG_INFO(TEST,"I=%d,Q=%d,Atan2f:%f,LUT:%f",i,q,phase_err_rad_fast,phase_err_rad_lut);
            ASSERT_TRUE(is_float_equal_absolute(phase_err_rad_fast, phase_err_rad_lut,  0.0001f));
        }
    }
    return true;
}
