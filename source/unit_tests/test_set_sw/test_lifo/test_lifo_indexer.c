#include "test_lifo_indexer.h"

#include "lifo_index.h"
#include "log.h"
#include "unit_test_check.h"

bool test_lifo_index_init(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    LifoIndexInfo_t Lifo;
    memset(&Lifo, 0xFF, sizeof((void*)&Lifo));
    lifo_index_init(&Lifo, RI_SIZE);
    ASSERT_EQ(0, lifo_index_get_cnt(&Lifo));
    ASSERT_EQ(RI_SIZE, Lifo.size);
    ASSERT_TRUE(lifo_index_valid(&Lifo));
    return true;
}

bool test_lifo_index_add(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    LifoIndexInfo_t Lifo;
    LifoIndex_t index;
    memset(&Lifo, 0xFF, sizeof(Lifo));
    lifo_index_init(&Lifo, RI_SIZE);

    index = lifo_index_add(&Lifo);
    ASSERT_EQ(0, index);
    ASSERT_EQ(1, lifo_index_get_cnt(&Lifo));

    index = lifo_index_add(&Lifo);
    ASSERT_EQ(1, index);
    ASSERT_EQ(2, lifo_index_get_cnt(&Lifo));

    ASSERT_EQ(1, lifo_index_get(&Lifo));
    ASSERT_EQ(1, lifo_index_get_cnt(&Lifo));

    ASSERT_EQ(0, lifo_index_get(&Lifo));
    ASSERT_EQ(0, lifo_index_get_cnt(&Lifo));

    return true;
}

bool test_lifo_index_get_empty(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    LifoIndexInfo_t Lifo;
    // LifoIndex_t index;
    memset(&Lifo, 0xFF, sizeof(Lifo));
    lifo_index_init(&Lifo, RI_SIZE);

    ASSERT_EQ(0, lifo_index_get_cnt(&Lifo));

    ASSERT_EQ(0, lifo_index_get(&Lifo));
    ASSERT_EQ(0, lifo_index_get(&Lifo));

    return true;
}

bool test_lifo_index_overflow(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    LifoIndexInfo_t Lifo;
    LifoIndex_t index;
    lifo_index_init(&Lifo, 2);
    ASSERT_EQ(0, lifo_index_get_cnt(&Lifo));

    index = lifo_index_add(&Lifo);
    ASSERT_EQ(0, index);
    ASSERT_EQ(1, lifo_index_get_cnt(&Lifo));

    index = lifo_index_add(&Lifo);
    ASSERT_EQ(1, index);
    ASSERT_EQ(2, lifo_index_get_cnt(&Lifo));

    index = lifo_index_add(&Lifo);
    ASSERT_EQ(2, lifo_index_get_cnt(&Lifo));
    ASSERT_EQ(1, index);

    index = lifo_index_add(&Lifo);
    ASSERT_EQ(2, lifo_index_get_cnt(&Lifo));
    ASSERT_EQ(1, index);

    return true;
}
