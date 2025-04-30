#include "test_pdm.h"

#include <string.h>

#include "pdm_diag.h"
#include "pdm_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_pdm_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(PDM, LOG_LEVEL_DEBUG);
    bool res = true;

    set_log_level(PDM, LOG_LEVEL_INFO);
    return res;
}

bool test_pdm_hash_tables(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(PDM, LOG_LEVEL_DEBUG);
    set_log_level(PDM, LOG_LEVEL_INFO);

    return res;
}

bool test_pdm_start_stop(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(PDM, LOG_LEVEL_DEBUG);
    ASSERT_TRUE( pdm_ctrl(0, true,MIC_MODE_SINGLE));
    ASSERT_TRUE( wait_in_loop_ms(300));
    ASSERT_TRUE( pdm_ctrl(0, false,MIC_MODE_SINGLE));

    ASSERT_TRUE(  pdm_print_sample(0));
    set_log_level(PDM, LOG_LEVEL_INFO);

    return res;
}

bool test_pdm_reinit(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(PDM, LOG_LEVEL_DEBUG);
    ASSERT_TRUE( pdm_init( ));

    set_log_level(PDM, LOG_LEVEL_INFO);

    return res;
}

bool test_pdm_listen(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(PDM, LOG_LEVEL_DEBUG);

    PdmHandle_t* Node = PdmGetNode(0);
    ASSERT_NE(0, Node);

    Node->max_freq = 0.0;
    ASSERT_TRUE(pdm_listen(0,2000));

    EXPECT_TRUE(is_double_equal_absolute(1000.0, Node->max_freq, 50.0));

    set_log_level(PDM, LOG_LEVEL_INFO);

    return res;
}
