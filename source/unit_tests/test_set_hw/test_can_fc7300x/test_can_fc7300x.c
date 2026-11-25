#include "test_can_fc7300x.h"

#include "can_mcal.h"
#include "log.h"
#include "unit_test_check.h"

bool test_can_fc7300x_types(void) {
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    ASSERT_EQ(4, sizeof(CanRegERFCR_t));
    ASSERT_EQ(4, sizeof(CanRegMCR_t));
    ASSERT_EQ(4, sizeof(CanRegIFLAG1_t));
    ASSERT_EQ(4, sizeof(CanRegIMASK1_t));
    ASSERT_EQ(4, sizeof(CanRegCTRL1_t));
    ASSERT_EQ(4, sizeof(CanRegCTRL2_t));
    ASSERT_EQ(4, sizeof(CanRegENCBT_t));
    ASSERT_EQ(4, sizeof(CanRegTIMER_t));
    ASSERT_EQ(4, sizeof(CanRegECR_t));
    ASSERT_EQ(4, sizeof(CanMessageBufferId_t));
    ASSERT_EQ(4, sizeof(CanRegFDCTRL_t));
    ASSERT_EQ(4, sizeof(CanStdFiltElement_t));
    ASSERT_EQ(4, sizeof(CanStdFiltElement0_t));
    ASSERT_EQ(4, sizeof(CanStdFiltElement1_t));
    ASSERT_EQ(4, sizeof(CanStdFiltElement2_t));
    ASSERT_EQ(4, sizeof(CanRegESR1_t));
    ASSERT_EQ(4, sizeof(CanRegERFSR_t));
    ASSERT_EQ(8, sizeof(CanExtFiltElement0_t));
    ASSERT_EQ(8, sizeof(CanExtFiltElement1_t));
    ASSERT_EQ(8, sizeof(CanExtFiltElement2_t));
    ASSERT_EQ(8, sizeof(CanExtFiltElement_t));
    ASSERT_EQ(4, sizeof(CanRegCBT_t));
    ASSERT_EQ(80, sizeof(CanEnhancedRxFIFOStructure_t));
    ASSERT_EQ(72, sizeof(CanMessageBufferLayOut_t));
    return true;
}
