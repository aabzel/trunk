#include "test_i2s_artery.h"

#include "i2s_mcal.h"
#include "i2s_register_types.h"
#include "log.h"
#include "unit_test_check.h"

bool test_i2s_artery_types(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);

    ASSERT_EQ(4, sizeof(REG_SPI_CTRL1));
    ASSERT_EQ(4, sizeof(REG_SPI_CTRL2));
    ASSERT_EQ(4, sizeof(REG_SPI_STATUS));
    ASSERT_EQ(4, sizeof(REG_SPI_DATA));
    ASSERT_EQ(4, sizeof(REG_SPI_CPOLY));
    ASSERT_EQ(4, sizeof(REG_SPI_RX_CRC));
    ASSERT_EQ(4, sizeof(REG_SPI_TX_CRC));
    ASSERT_EQ(4, sizeof(REG_SPI_I2S_CTRL));
    ASSERT_EQ(4, sizeof(REG_SPI_I2S_CLK_PRESCALER));

    return true;
}
