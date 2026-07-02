#include "test_bit_fifo.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bit_fifo_mcal.h"
#include "unit_test_check.h"

const uint8_t TestBitStream9[9]={1, 0,    1, 0,    1, 0,    1, 0,   1};
const uint8_t TestBitStream10[10]={0, 1, 1, 1, 0, 1, 1, 0,0,1};

bool test_bit_fifo_overrun(void) {
    LOG_DEBUG(TEST,"%s():", __FUNCTION__);
    BitFifoHandle_t Obj;
    uint8_t Memory[1] = {0};

    bit_fifo_init(&Obj, (uint8_t*)Memory, sizeof(Memory));

    ASSERT_TRUE(bit_fifo_push(&Obj, 1));
    ASSERT_TRUE(bit_fifo_push(&Obj, 0));
    ASSERT_TRUE(bit_fifo_push(&Obj, 1));
    ASSERT_TRUE(bit_fifo_push(&Obj, 0));

    ASSERT_TRUE(bit_fifo_push(&Obj, 1));
    ASSERT_TRUE(bit_fifo_push(&Obj, 1));
    ASSERT_TRUE(bit_fifo_push(&Obj, 0));
    ASSERT_TRUE(bit_fifo_push(&Obj, 0));

    ASSERT_FALSE(bit_fifo_push(&Obj, 1));

    return true;
}

bool test_bit_fifo_init(void) {
    LOG_DEBUG(TEST,"%s():", __FUNCTION__);
    BitFifoHandle_t Obj;
    uint8_t Memory[3] = {0};
    ASSERT_TRUE(bit_fifo_init(&Obj, (uint8_t*)Memory, sizeof(Memory)));
    ASSERT_EQ(0, bit_fifo_get_count(&Obj));

    return true;
}

bool test_bit_fifo_array(void) {
    LOG_DEBUG(TEST,"%s():", __FUNCTION__);
    BitFifoHandle_t Obj;

    uint8_t Memory[5] = {0};
    ASSERT_TRUE(bit_fifo_init(&Obj, (uint8_t*)Memory, sizeof(Memory)));

    ASSERT_TRUE(bit_fifo_push_array(&Obj, TestBitStream10, 5));

    uint8_t peek_ch =0xFF;
    ASSERT_TRUE(bit_fifo_peek(&Obj, &peek_ch));
    ASSERT_EQ(0, peek_ch);

    uint8_t getSamples[100] = {0};
    uint32_t outLen = 0;
    ASSERT_TRUE(bit_fifo_pull_array(&Obj, getSamples, sizeof(getSamples), &outLen));
    ASSERT_EQ(5, outLen);
    ASSERT_EQ_MEM(TestBitStream10, getSamples,outLen);

    return true;
}

bool test_bit_fifo_array_overrun(void) {
    LOG_DEBUG(TEST,"%s():", __FUNCTION__);
    BitFifoHandle_t Obj;

    uint8_t Memory[1] = {0};
    bit_fifo_init(&Obj, (uint8_t*)Memory, sizeof(Memory));

    ASSERT_FALSE(bit_fifo_push_array(&Obj, (uint8_t*)TestBitStream9, sizeof(TestBitStream9)));

    uint8_t peek_ch = 0;
    ASSERT_TRUE(bit_fifo_peek(&Obj, &peek_ch));
    ASSERT_EQ(1, peek_ch);

    uint32_t outLen = 0;
    uint8_t getSamples[100] = {0};
    ASSERT_TRUE(bit_fifo_pull_array(&Obj, getSamples, sizeof(getSamples), &outLen));
    ASSERT_EQ(8, outLen);
    ASSERT_EQ_MEM(TestBitStream9, getSamples,outLen);
    return true;
}

