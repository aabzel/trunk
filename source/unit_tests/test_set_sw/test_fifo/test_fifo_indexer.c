#include "test_fifo_indexer.h"

#include "fifo_index.h"
#include "unit_test_check.h"

bool test_fifo_index_init(void) {
    fifo_index_info_t ri;
    memset(&ri, 0xFF, sizeof((void*)&ri));
    fifo_index_init(&ri, RI_SIZE);
    ASSERT_EQ(0, ri.end);
    ASSERT_EQ(0, ri.start);
    ASSERT_EQ(0, fifo_index_get_used(&ri));
    ASSERT_EQ(RI_SIZE, ri.size);
    ASSERT_TRUE(fifo_index_valid(&ri));
    return true;
}

bool test_fifo_index_add(void) {
    fifo_index_info_t ri;
    FifoIndex_t index;
    memset(&ri, 0xFF, sizeof(ri));
    fifo_index_init(&ri, RI_SIZE);
    uint32_t i = 0;
    for(i = 0; i < RI_SIZE; i++) {
        index = fifo_index_add(&ri);
        ASSERT_EQ(i, index);
        ASSERT_EQ(i + 1, fifo_index_get_used(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    index = fifo_index_add(&ri);
    ASSERT_EQ(RING_INVALID_INDEX, index);
    ASSERT_TRUE(fifo_index_valid(&ri));
    index = fifo_index_get(&ri);
    ASSERT_EQ(0, index);
    ASSERT_TRUE(fifo_index_valid(&ri));
    index = fifo_index_add(&ri);
    ASSERT_EQ(0, index);
    ASSERT_TRUE(fifo_index_valid(&ri));

    for(i = 1; i < 1000; i++) {
        index = fifo_index_add(&ri);
        ASSERT_EQ(RING_INVALID_INDEX, index);
        ASSERT_TRUE(fifo_index_valid(&ri));
        index = fifo_index_get(&ri);
        ASSERT_EQ(i % RI_SIZE, index);
        ASSERT_TRUE(fifo_index_valid(&ri));
        index = fifo_index_add(&ri);
        ASSERT_EQ(i % RI_SIZE, index);
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    ASSERT_TRUE(fifo_index_valid(&ri));
    return true;
}

bool test_fifo_index_get(void) {
    fifo_index_info_t ri;
    FifoIndex_t index;
    uint32_t i = 0;
    memset(&ri, 0xFF, sizeof(ri));
    fifo_index_init(&ri, RI_SIZE);
    index = fifo_index_get(&ri);
    ASSERT_EQ(RING_INVALID_INDEX, index);
    ASSERT_TRUE(fifo_index_valid(&ri));
    for(i = 0; i < RI_SIZE; i++) {
        index = fifo_index_add(&ri);
        ASSERT_EQ(i, index);
        ASSERT_EQ(i + 1, fifo_index_get_used(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    for(i = 0; i < RI_SIZE; i++) {
        index = fifo_index_get(&ri);
        ASSERT_EQ(i, index);
        ASSERT_EQ(RI_SIZE - (i + 1), fifo_index_get_used(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    index = fifo_index_get(&ri);
    ASSERT_EQ(RING_INVALID_INDEX, index);
    ASSERT_TRUE(fifo_index_valid(&ri));
    return true;
}

bool test_fifo_index_continuus_used(void) {
    fifo_index_info_t ri;
    uint32_t i = 0;
    memset(&ri, 0xFF, sizeof(ri));
    fifo_index_init(&ri, RI_SIZE);
    ASSERT_EQ(0, fifo_index_continuus_used_size(&ri));
    ASSERT_TRUE(fifo_index_valid(&ri));
    for(i = 0; i < RI_SIZE; i++) {
        fifo_index_add(&ri);
        ASSERT_EQ(i + 1, fifo_index_continuus_used_size(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    for(i = 0; i < RI_SIZE; i++) {
        fifo_index_get(&ri);
        ASSERT_EQ(RI_SIZE - (i + 1), fifo_index_continuus_used_size(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    ASSERT_EQ(0, fifo_index_continuus_used_size(&ri));
    fifo_index_add(&ri);
    for(i = 0; i < RI_SIZE * 5; i++) {
        fifo_index_add(&ri);
        fifo_index_get(&ri);
        ASSERT_EQ(1, fifo_index_continuus_used_size(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    return true;
}

bool test_fifo_index_free(void) {
    fifo_index_info_t ri;
    FifoIndex_t index;
    uint32_t i = 0;
    memset(&ri, 0xFF, sizeof(ri));
    fifo_index_init(&ri, RI_SIZE);
    for(i = 0; i < RI_SIZE * 5; i++) {
        index = fifo_index_add(&ri);
        ASSERT_EQ(i % RI_SIZE, index);
        fifo_index_free(&ri, 1);
        ASSERT_EQ(0, fifo_index_get_used(&ri));
        ASSERT_TRUE(fifo_index_valid(&ri));
    }
    fifo_index_init(&ri, RI_SIZE);
    ASSERT_TRUE(fifo_index_valid(&ri));

    fifo_index_init(&ri, RI_SIZE);
    for(i = 0; i < RI_SIZE / 2; i++) {
        index = fifo_index_add(&ri);
        ASSERT_EQ(i % RI_SIZE, index);
    }
    fifo_index_free(&ri, RI_SIZE / 2);
    ASSERT_TRUE(fifo_index_valid(&ri));
    ASSERT_EQ(0, fifo_index_get_used(&ri));

    for(i = 0; i < RI_SIZE; i++) {
        index = fifo_index_add(&ri);
    }
    fifo_index_free(&ri, RI_SIZE);
    ASSERT_TRUE(fifo_index_valid(&ri));
    ASSERT_EQ(0, fifo_index_get_used(&ri));
    return true;
}
