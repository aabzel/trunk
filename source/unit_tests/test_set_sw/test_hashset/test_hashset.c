#include "test_hashset.h"


#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "log.h"
#include "hashset.h"
#include "unit_test_check.h"

bool test_hashset_pull(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    return true;
}

bool test_hashset_push(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    HashSet_t HashSet;
    HashSetEntry_t Heap[10];

    set_log_level(HASHSET,LOG_LEVEL_DEBUG);

    ASSERT_TRUE(hashset_init(&HashSet, Heap, ARRAY_SIZE(Heap)));

    ASSERT_EQ(0, hashset_check(&HashSet,"Entry", 5));
    ASSERT_TRUE( hashset_push(&HashSet, "Entry", 5));

    ASSERT_EQ(1, hashset_check(&HashSet, "Entry", 5));

    ASSERT_TRUE( hashset_push(&HashSet, "Entry", 5));
    ASSERT_EQ(2, hashset_check(&HashSet, "Entry", 5));

    set_log_level(HASHSET,LOG_LEVEL_INFO);
    return true;
}


