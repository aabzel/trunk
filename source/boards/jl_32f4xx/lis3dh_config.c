#include "lis3dh_config.h"

#include "data_utils.h"
#include "lis3dh_types.h"

static const Lis3dhRegVal_t MemoryBlob[] = {
    {.addr=LIS3DH_REG_CTRL_REG1, .Reg.CtrlReg1={ .xen = 1, .yen = 1, .zen = 1, .lpen= 0, .odr=LIS3DH_DATA_RATE_100_HZ, },},
    {.addr=LIS3DH_REG_CTRL_REG2, .Reg.CtrlReg2={ .hpm = LIS3DH_HIGH_PASS_FILT_NORMAL, },},
    {.addr=LIS3DH_REG_CTRL_REG5, .Reg.CtrlReg5={ .fifo_en=1, .d4d_int2=0, .d4d_int1=0, .lir_int2=0, .lir_int1=0,  .boot=0,},},
    {.addr=LIS3DH_REG_FIFO_CTRL_REG, .Reg.FifoCtrlReg={ .fm=LIS3DH_FIFO_MODE_STREAM, .fth = 0, .tr  = 0, },},
    {.addr=LIS3DH_REG_CTRL_REG4, .Reg.CtrlReg4={ .fs=LIS3DH_FULL_SCALE_16G, .sim = LIS3DH_SERIAL_IF_MODE_SPI, .st=LIS3DH_SELF_TEST_NORMAL, .hr=1, .bdu=0, .ble=0,},},
};


#define LIS3DH_CONFIG_ONE_I2C                                             \
                             {                                            \
                             .num = 1,                                    \
                             .i2c_num = 2,                                \
                             .interface = LIS3DH_IF_I2C,                  \
                             .sa0_pin_value = 0,                          \
                             .RegConfig = MemoryBlob,                     \
                             .cfg_reg_cnt = ARRAY_SIZE(MemoryBlob),       \
                             .chip_addr = LIS3DH_I2C_ADDR_1,              \
                             .name = "LIS3DHYG",                          \
                             .valid = true,                               \
                             },

#define LIS3DH_CONFIG_ONE_SPI                                            \
                             {                                           \
                             .num = 1,                                   \
                             .spi_num = 4,                               \
                             .interface = LIS3DH_IF_SPI,                 \
                             .ChipSelect = {.port = PORT_G, .pin = 14,}, \
                             .RegConfig = MemoryBlob,                    \
                             .cfg_reg_cnt = ARRAY_SIZE(MemoryBlob),      \
                             .name = "LIS3DHYG",                         \
                             .valid = true,                              \
                             },

const Lis3dhConfig_t Lis3dhConfig[] = {
    LIS3DH_CONFIG_ONE_SPI
};

Lis3dhHandle_t Lis3dhInstance[] = {
    {
        .num = 1,
        .valid = true,
        .init = false,
    }
};

uint32_t lis3dh_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(Lis3dhConfig);
    return cnt;
}
