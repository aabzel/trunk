#include "test_bpsk.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>


#include "array.h"
#include "debug_info.h"
#include "bpsk.h"
#include "log.h"
#include "unit_test_check.h"
#include "bit_utils.h"

bool test_bpsk_utils(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ(0, 0%8 );
    EXPECT_EQ(0, 8%8 );
    EXPECT_EQ(7, 7%8 );
    EXPECT_EQ(1, 9%8 );

    EXPECT_EQ(1, bit_get_u8( 0x01,   0));
    EXPECT_EQ(0, bit_get_u8( 0x01,   1));//

    return res;
}

bool test_bpsk_encode(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    SampleType_t SampleArray[8000]={0};
    uint8_t data[2]={0x55,0xaa};
    ASSERT_TRUE( bpsk_encode(1, data, sizeof(data), SampleArray, ARRAY_SIZE(SampleArray)  )   );
    return true;
}

bool test_bpsk_decode(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    SampleType_t SampleArray[8000] = {0};
    uint8_t data[2] = { 0x81, 0x5F};//1000 0001 0105 1111
    ASSERT_TRUE( bpsk_encode_to_wav(1, data,   sizeof(data), 1));

    ASSERT_TRUE( bpsk_encode(1, data, sizeof(data), SampleArray, ARRAY_SIZE(SampleArray)));
    BpskHandle_t* Node=BpskGetNode(1);
    ASSERT_NE(NULL,Node);

    //log_level_get_set(BPSK, LOG_LEVEL_DEBUG);
    uint8_t RxData[299] = {0};
    uint32_t dataByte = 0;
    ASSERT_TRUE(bpsk_decode(1, SampleArray, Node->sample_cnt, RxData,&dataByte ));
    LOG_INFO(TEST, "RxByes:%u", dataByte);
    ASSERT_EQ(2, dataByte);
    ASSERT_TRUE(print_bin(RxData, dataByte, 0));
    ASSERT_TRUE(array_is_equal(RxData,data,2));

    log_level_get_set(BPSK,   LOG_LEVEL_INFO);

    return true;
}





