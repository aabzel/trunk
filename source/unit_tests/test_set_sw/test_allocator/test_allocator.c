#include "test_allocator.h"

#include <stdbool.h>
#include <stdint.h>

#include "heap_allocator.h"
#include "unit_test_check.h"

bool test_allocator_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
#ifdef HAS_CLANG
    EXPECT_EQ(8, sizeof(void*));
    EXPECT_EQ(16, sizeof(MemoryChunkHeader_t));
#else
    EXPECT_EQ(4, sizeof(void*));
    EXPECT_EQ(8, sizeof(MemoryChunkHeader_t));
#endif
    return res;
}

bool test_allocator_malloc(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    void* addr = h_malloc(1);
    ASSERT_NE(NULL, addr);
    ASSERT_TRUE(h_free(addr));
    return true;
}

bool test_allocator_malloc_zero(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    void* addr = h_malloc(0);
    ASSERT_EQ(NULL, addr);
    return true;
}

bool test_allocator_malloc_over(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    void* addr = h_malloc(TOTAL_HEAP_SIZE * 2);
    ASSERT_EQ(NULL, addr);
    return true;
}

bool test_allocator_stress(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    size_t size = 0;
    void* addr = NULL;
    ;
    size_t max_size = (0.8 * ((double)TOTAL_HEAP_SIZE));
    LOG_INFO(TEST, "MaxSize: %u Byte", max_size);
    for(size = 1; size < max_size; size *= 2) {
        LOG_INFO(TEST, "Try Size:%u Byte", size);
        addr = h_malloc(size);
        ASSERT_NE(NULL, addr);
        LOG_INFO(TEST, "Addr 0x%p", addr);
        ASSERT_TRUE(h_free(addr));
    }

    return true;
}

bool test_allocator_malloc_several(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t orig_cnt = h_count();

    void* addr1 = h_malloc(1);
    ASSERT_NE(NULL, addr1);
    ASSERT_EQ(orig_cnt + 1, h_count());

    void* addr2 = h_malloc(2);
    ASSERT_NE(NULL, addr2);
    ASSERT_EQ(orig_cnt + 2, h_count());

    void* addr3 = h_malloc(3);
    ASSERT_NE(NULL, addr3);
    ASSERT_EQ(orig_cnt + 3, h_count());

    ASSERT_TRUE(h_free(addr1));
    ASSERT_EQ(orig_cnt + 2, h_count());

    ASSERT_TRUE(h_free(addr2));
    ASSERT_EQ(orig_cnt + 1, h_count());

    ASSERT_TRUE(h_free(addr3));
    ASSERT_EQ(orig_cnt, h_count());

    return true;
}
