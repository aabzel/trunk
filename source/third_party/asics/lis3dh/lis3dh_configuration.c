//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_configuration.c
//! \par    Platform
//!             Any platform with ASIC LIS3DH
//! \par    Compatible
//!             Any MCU with I2C, SPI and GPIO
//! \brief  Listing configuration structures for LIS3DH ASIC
//!
//! \par    Abbreviations
//!             ASIC - Application-specific integrated circuit
//!             I2C - Inter-Integrated Circuit
//!             MCU - MicroControllerUnit
//!             PCB - Printed circuit board
//!             SPI - Serial Peripheral Interface
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   LIS3DH
//! \brief      lis3dh configuration files
//! \addtogroup LIS3DH
//! @{
//! \file lis3dh_configuration.c
//! \file lis3dh_configuration.h
//! \file lis3dh_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

//! lis3dh configuration
#include "lis3dh_configuration.h"

//! general macros
#include "general_macros.h"

//! lis3dh type
#include "lis3dh_type.h"

//! GPIO type
#include "gpio_drv.h"



//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************



//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************


//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

//! LIS3DH Raw generalized default register values
static const LIS3DH_REGISTER_VAL MemoryBlob[] = {
    {
     .address=LIS3DH_REGISTER_CTRL_REG1,
     .Reg.CtrlReg1={ .xen = LIS3DH_SUBSYS_ENABLED,
                     .yen = LIS3DH_SUBSYS_ENABLED,
                     .zen = LIS3DH_SUBSYS_ENABLED,
                     .lpen = 0,
                     .odr = LIS3DH_DATA_SPEED_50_HZ, },
    },
    {
     .address=LIS3DH_REGISTER_CTRL_REG2,
     .Reg.CtrlReg2={ .hpm = LIS3DH_FILT_HIGH_PASS_NORMAL, },
    },
    {
     .address=LIS3DH_REGISTER_CTRL_REG4,
     .Reg.CtrlReg4={ .fs = LIS3DH_RANGE_16G,
                     .sim = 0,
                     .st = LIS3DH_SELFTEST_NORMAL,
                     .hr = 1,
                     .bdu = 1,
                     .ble = 0,},
    },
    {
     .address=LIS3DH_REGISTER_CTRL_REG5,
     .Reg.CtrlReg5={ .fifo_en = LIS3DH_SUBSYS_ENABLED,
                     .d4d_int2 = 0,
                     .d4d_int1 = 0,
                     .lir_int2 = 0,
                     .lir_int1 = 0,
                     .boot=0, },
    },
    {
     .address = LIS3DH_REGISTER_TEMP_CFG_REG,
     .Reg.TempCfg = { .temp_en = LIS3DH_TEMP_ENABLED,
                      .adc_en  = LIS3DH_ADC_ENABLED, },
    },
};

//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

//! LIS3DH configuration one
#define LIS3DH_CONFIGURATION_ONE(NUM)                                     \
            {                                                             \
                .RegConfig = MemoryBlob,                                  \
                .cfgRegCnt = SIZE_OF_ARRAY(MemoryBlob),                   \
                .chipAddr = LIS3DH_I2C_ADDR_1,                            \
                .chipSelectPin = LIS3DH_##NUM##_CHIP_SELECT_PIN,          \
                .chipSelectPort = LIS3DH_##NUM##_CHIP_SELECT_PORT ,       \
                .dataRateHz = LIS3DH_##NUM##_DATA_RATE_HZ,                \
                .measurementRangeG = LIS3DH_##NUM##_MEASUREMENT_RANGE_G,  \
                .precisionG = LIS3DH_PRECISION_G,                         \
                .i2cNum = LIS3DH_##NUM##_I2C_NUM,                         \
                .interface = LIS3DH_##NUM##_INTERFACE,                    \
                .name = "LIS3DH_"#NUM,                                    \
                .num = NUM,                                               \
                .resolutionBit = LIS3DH_##NUM##_RESOLUTION_BIT,           \
                .sa0PinValue = LIS3DH_##NUM##_SA0_PIN_VALUE,              \
                .spiNum = LIS3DH_##NUM##_SPI_NUM,                         \
                .valid = TRUE,                                            \
            },


//! LIS3DH ROM Configuration (Default settings)
const LIS3DH_CONFIGURATION LIS3DH_Configuration[] = {
#if ON == LIS3DH_1_IN_USE
    LIS3DH_CONFIGURATION_ONE(1)
#endif

#if ON == LIS3DH_2_IN_USE
    LIS3DH_CONFIGURATION_ONE(2)
#endif
};

//! LIS3DH RAM node
LIS3DH_HANDLE LIS3DH_Instance[] = {
#if ON == LIS3DH_1_IN_USE
    {
        .num = 1,
        .valid = TRUE,
    },
#endif

#if ON == LIS3DH_2_IN_USE
    {
        .num = 2,
        .valid = TRUE,
    }
#endif
};

//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! Get quantity of LIS3DH ASICS on the electronic board (PCB)
//!
//! \note       None
//!
//! \return     quantity of LIS3DH ASICS on the electronic board PCB
//**************************************************************************************************
U32 LIS3DH_GetCnt(void)
{
    U32 quantity = 0;
    quantity = SIZE_OF_ARRAY(LIS3DH_Configuration);
    return quantity;
} // end of LIS3DH_GetCnt()



//****************************************** end of file *******************************************
