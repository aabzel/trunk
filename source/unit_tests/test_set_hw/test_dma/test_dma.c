#include "test_dma.h"

#include <string.h>

#include "clock.h"
#include "unit_test_check.h"
#include "dma_drv.h"

bool test_dma_types(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(4, sizeof(DmaLowIntStatusReg_t));
    ASSERT_EQ(4, sizeof(DmaHighIntStatusReg_t));
    ASSERT_EQ(4, sizeof(DmaLowIntFlagClearReg_t));
    ASSERT_EQ(4, sizeof(DmaHighIntFlagClearReg_t));
    
    ASSERT_EQ(1, sizeof(DmaStreamClearIntReg_t));
    ASSERT_EQ(1, sizeof(DmaStreamIntStatusReg_t));

    return true;
}

