#include "test_set.h"

#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "log.h"
#include "set.h"
#include "unit_test_check.h"

bool test_set_push(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(SET, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(set_init_one(1));

    SetItem_t* Node = SetGetNode(1);
    ASSERT_NE(NULL,Node);

    ASSERT_FALSE(set_check_ll(Node,"Entry", 5) );
    ASSERT_TRUE( set_push_ll(Node, "Entry", 5) );

    ASSERT_TRUE(set_check_ll(Node, "Entry", 5) );

    ASSERT_TRUE( set_push_ll(Node, "Entry", 5) );
    ASSERT_TRUE( set_check_ll(Node, "Entry", 5) );

    set_log_level(SET, LOG_LEVEL_INFO);
    return true;
}


