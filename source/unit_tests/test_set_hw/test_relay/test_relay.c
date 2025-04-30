#include "test_relay.h"

#include <stdbool.h>
#include <stdint.h>


#include "data_utils.h"
#include "relay_drv.h"
#include "cli_utils.h"
#include "log.h"
#include "unit_test_check.h"


#ifndef HAS_RELAY
#error "It is needed to add HAS_RELAY option"
#endif

bool test_relay_one(DI_index_E di_index,DO_index_E do_index,DO_state_E state) {
    DI_state_E orig_state;
    DI_state_E read_state;
    orig_state = DI_getInputState(  di_index);
    EXPECT_NE(DI_state_UNDEF, orig_state);

    DO_setOutputState(  do_index,   state);

    read_state= DI_getInputState(  di_index);
    EXPECT_NE(DI_state_UNDEF, read_state);

    EXPECT_EQ(read_state, state)  ;

    DO_setOutputState(  do_index, (DO_state_E)  orig_state);
    return true;
}

bool test_relay(void) {
    EXPECT_TRUE(test_relay_one(DI_index_00 , DO_index_00, DO_state_ON));
    EXPECT_TRUE(test_relay_one(DI_index_00 , DO_index_00, DO_state_OFF));

    EXPECT_TRUE(test_relay_one(DI_index_01 , DO_index_01, DO_state_ON));
    EXPECT_TRUE(test_relay_one(DI_index_01 , DO_index_01, DO_state_OFF));

    EXPECT_TRUE(test_relay_one(DI_index_02 , DO_index_02, DO_state_ON));
    EXPECT_TRUE(test_relay_one(DI_index_02 , DO_index_02, DO_state_OFF));

    EXPECT_TRUE(test_relay_one(DI_index_03 , DO_index_03, DO_state_ON));
    EXPECT_TRUE(test_relay_one(DI_index_03 , DO_index_03, DO_state_OFF));

    EXPECT_TRUE(test_relay_one(DI_index_04 , DO_index_04, DO_state_ON));
    EXPECT_TRUE(test_relay_one(DI_index_04 , DO_index_04, DO_state_OFF));
    return true;
}


