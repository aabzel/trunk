#include "test_circular_buffer_indexer.h"

#include "circular_buffer_word.h"
#include "circular_buffer_index.h"
#include "unit_test_check.h"
#include "unit_test_assert.h"

#define RI_SIZE 10

bool test_circular_buffer_index_init(void) {
    LOG_INFO(CIRCULAR_BUFFER, "%s():", __FUNCTION__);
    CircularBufferIndexInfo_t ri;
    memset(&ri, 0xFF, sizeof((void*)&ri));
    circular_buffer_index_init(&ri, RI_SIZE);

    return true;
}

bool test_circular_buffer_index_add(void) {
    LOG_INFO(CIRCULAR_BUFFER, "%s():", __FUNCTION__);
    return true;
}
/*
 tsr circular_buffer_word+
  tsr circular_buffer+
 */
bool test_circular_buffer_word_get(void){
    LOG_INFO(CIRCULAR_BUFFER, "%s():", __FUNCTION__);

    CircularBufferWord_t Obj={0};
    int16_t Heap[10] = {0};
    ASSERT_TRUE( circular_buffer_word_init(   &Obj, Heap, ARRAY_SIZE(Heap)   )   );

    ASSERT_TRUE(  circular_buffer_word_push(&Obj,   1)   );
    ASSERT_TRUE(  circular_buffer_word_push(&Obj,   2)   );
    ASSERT_TRUE(  circular_buffer_word_push(&Obj,   3)   );

    int16_t sample = 0;
    ASSERT_TRUE( circular_buffer_word_get(&Obj, 0, &sample)   );
    ASSERT_EQ(3, sample);

    ASSERT_TRUE( circular_buffer_word_get(&Obj, -1, &sample)   );
    ASSERT_EQ(2, sample);

    ASSERT_TRUE( circular_buffer_word_get(&Obj, -2, &sample)   );
    ASSERT_EQ(1, sample);

    return true;
}

bool test_circular_buffer_index_get(void) {
    LOG_INFO(CIRCULAR_BUFFER, "%s():", __FUNCTION__);
    ASSERT_EQ(7, circular_buffer_index_calc_phy_index(8, 0, -1));
    ASSERT_EQ(3, circular_buffer_index_calc_phy_index(8, 4, -1));
    ASSERT_EQ(0, circular_buffer_index_calc_phy_index(10, 0, 0));
    ASSERT_EQ(9, circular_buffer_index_calc_phy_index(10, 9, 0));
    ASSERT_EQ(9, circular_buffer_index_calc_phy_index(10, 0, 9));
    ASSERT_EQ(8, circular_buffer_index_calc_phy_index(10, 4, 4));
    ASSERT_EQ(8, circular_buffer_index_calc_phy_index(10, 9, 9));
    ASSERT_EQ(0, circular_buffer_index_calc_phy_index(5, 1, 4));

    return true;
}
