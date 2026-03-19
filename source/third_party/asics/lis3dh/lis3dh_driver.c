//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_driver.c
//! \par    Platform
//!             Any platform with ASIC LIS3DH
//! \par    Compatible
//!             Any microcontroller with I2C, SPI and GPIO
//! \brief  Implementation of the LIS3DH functionality.
//!             This is a driver for the ASIC LIS3DH.
//! \par    Abbreviations
//!             ASIC - Application-specific integrated circuit
//!             ADC - Analog-to-digital conversion
//!             FS - Full-scale
//!             GPIO - General-purpose input/output
//!             I2C - Inter-Integrated Circuit
//!             LUT - Lookup table
//!             SPI - Serial Peripheral Interface
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   LIS3DH
//! \brief      This is the LIS3DH accelerometer driver
//! \addtogroup LIS3DH
//! @{
//! \file lis3dh_driver.c
//! \file lis3dh_driver.h
//! \file lis3dh_configuration.c
//! \file lis3dh_configuration.h
//! \file lis3dh_constants.h
//! \file lis3dh_dependencies.h
//! \file lis3dh_phy_i2c.c
//! \file lis3dh_phy_i2c.h
//! \file lis3dh_phy_spi.c
//! \file lis3dh_phy_spi.h
//! \file lis3dh_register_types.h
//! \file lis3dh_type.h
//! \file lis3dh_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// string header
#include <string.h>

// Get float constants (e.g. FLT_MAX)
#include <float.h>

// compiler header (for INT_MAX)
#include <limits.h>

// header for abs() function
#include <stdlib.h>

// lis3dh driver header
#include "lis3dh_driver.h"

// lis3dh miscellaneous header
#include "lis3dh_miscellaneous.h"

// general macros header
#include "general_macros.h"

#if ON==I2C_IN_USE
// i2c drv header
#include "i2c_drv.h"
#endif

#if ON==I2C_IN_USE
#include "lis3dh_phy_i2c.h"
#endif

#if ON==SPI_IN_USE
#include "lis3dh_phy_spi.h"
#endif

//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

//! LIS3DH range info one
#define LIS3DH_RANGE_INFO_ONE(INTERAVL)                                              \
    { .valid = TRUE, .range = INTERAVL, .fullScale=LIS3DH_RANGE_##INTERAVL##G,},

//! LIS3DH range info LUT
static const LIS3DH_RANGE_INFO LIS3DH_RANGE_Info[] = {
    LIS3DH_RANGE_INFO_ONE(2)
    LIS3DH_RANGE_INFO_ONE(4)
    LIS3DH_RANGE_INFO_ONE(8)
    LIS3DH_RANGE_INFO_ONE(16)
};

//! LIS3DH rate info one
#define LIS3DH_RATE_INFO_ONE(FREQ)  { .valid = TRUE, .dataRateHz=FREQ, .odr=LIS3DH_ODR_##FREQ##HZ,},


//! LIS3DH rate info LUT
static const LIS3DH_RATE_INFO LIS3DH_RATE_Info[]={
        LIS3DH_RATE_INFO_ONE(0)
        LIS3DH_RATE_INFO_ONE(1)
        LIS3DH_RATE_INFO_ONE(10)
        LIS3DH_RATE_INFO_ONE(25)
        LIS3DH_RATE_INFO_ONE(50)
        LIS3DH_RATE_INFO_ONE(100)
        LIS3DH_RATE_INFO_ONE(200)
        LIS3DH_RATE_INFO_ONE(400)
        LIS3DH_RATE_INFO_ONE(1600)
        LIS3DH_RATE_INFO_ONE(5376)
};

//! LIS3DH ADC INFO ONE
#define LIS3DH_ADC_INFO_ONE(NUM, BITNESS)                     \
        {   .adcNum = (NUM),                                  \
            .addressHi = LIS3DH_REGISTER_OUT_ADC##NUM##_H,    \
            .addressLow = LIS3DH_REGISTER_OUT_ADC##NUM##_L,   \
            .addressLow = LIS3DH_REGISTER_OUT_ADC##NUM##_L,   \
            .bitness = (BITNESS),                             \
            .valid = TRUE,                                    \
        },

//! LIS3DH ADC INFO ALL
#define LIS3DH_ADC_INFO_ALL           \
    LIS3DH_ADC_INFO_ONE(1,10)         \
    LIS3DH_ADC_INFO_ONE(2,10)         \
    LIS3DH_ADC_INFO_ONE(3,8)

//! LIS3DH ADC Info LUT
static const LIS3DH_ADC_INFO LIS3DH_ADC_Info[] = {
    LIS3DH_ADC_INFO_ALL
};

#define LIS3DH_OPERATION_MODE_INFO_(GG,SENS,RESOL)                 \
{                                                                            \
    .fullScale = LIS3DH_RANGE_##GG,                                          \
    .sensitivity = SENS,                                                     \
    .resolutionBit = RESOL,                                                  \
},                                                                           \

//! FS bit set to 00 +/- 2G
#define LIS3DH_OPERATION_MODE_INFO_2G                     \
     LIS3DH_OPERATION_MODE_INFO_(2G,1,12)                 \
     LIS3DH_OPERATION_MODE_INFO_(2G,4,10)                 \
     LIS3DH_OPERATION_MODE_INFO_(2G,16,8)

//! FS bit set to 01 +/- 4G
#define LIS3DH_OPERATION_MODE_INFO_4G                     \
     LIS3DH_OPERATION_MODE_INFO_(4G,2,12)                 \
     LIS3DH_OPERATION_MODE_INFO_(4G,8,10)                 \
     LIS3DH_OPERATION_MODE_INFO_(4G,32,8)

//! FS bit set to 10 +/- 8G
#define LIS3DH_OPERATION_MODE_INFO_8G                                        \
     LIS3DH_OPERATION_MODE_INFO_(8G, 4, 12)   \
     LIS3DH_OPERATION_MODE_INFO_(8G, 16, 10  )           \
     LIS3DH_OPERATION_MODE_INFO_(8G, 64, 8)

//! FS bit set to 11 +/- 16G
#define LIS3DH_OPERATION_MODE_INFO_16G                                        \
     LIS3DH_OPERATION_MODE_INFO_(16G, 12, 12)  \
     LIS3DH_OPERATION_MODE_INFO_(16G, 48, 10)           \
     LIS3DH_OPERATION_MODE_INFO_(16G, 192, 8)


//!  Operating mode selection LUT. Mechanical characteristics LUT
static const LIS3DH_OP_MODE_INFO LIS3DH_OperationModeInfo[] = {
    LIS3DH_OPERATION_MODE_INFO_2G
    LIS3DH_OPERATION_MODE_INFO_4G
    LIS3DH_OPERATION_MODE_INFO_8G
    LIS3DH_OPERATION_MODE_INFO_16G
};

//! LIS3DH Resolution Info LUT
static const LIS3DH_RESOLUTION_INFO LIS3DH_ResolutionInfo[]={
    {
        .highResolutionEnable = 0,
        .lowPowerEnable = 1,
        .name = "Low-power",
        .opMode = LIS3DH_OP_MODE_LOW_POWER,
        .resolutionBit = 8,
        .valid = TRUE,
    },
    {
        .highResolutionEnable = 0,
        .lowPowerEnable = 0,
        .name = "Normal",
        .opMode = LIS3DH_OP_MODE_NORMAL,
        .resolutionBit = 10,
        .valid = TRUE,
    },
    {
        .highResolutionEnable = 1,
        .lowPowerEnable = 0,
        .name = "Hi-resol",
        .opMode = LIS3DH_OP_MODE_HIGH_RESOLUTION,
        .resolutionBit = 12,
        .valid = TRUE,
    },
};

//! LIS3DH Register Info
const ASIC_REG_INFO LIS3DH_RegInfo[] = {
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_STATUS_REG_AUX,
        .name = "STATUS_REG_AUX",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_ADC1_L,
        .name = "OUT_ADC1_L",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_ADC1_H,
        .name = "OUT_ADC1_H",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_ADC2_L,
        .name = "OUT_ADC2_L",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_ADC2_H,
        .name = "OUT_ADC2_H",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_ADC3_L,
        .name = "OUT_ADC3_L",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_ADC3_H,
        .name = "OUT_ADC3_H",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_WHO_AM_I,
        .name = "WHO_AM_I",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_TEMP_CFG_REG,
        .name = "TEMP_CFG_REG",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_STATUS_REG,
        .name = "STATUS_REG",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_X_L,
        .name = "OUT_X_L",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_X_H,
        .name = "OUT_X_H",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_Y_L,
        .name = "OUT_Y_L",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_Y_H,
        .name = "OUT_Y_H",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_Z_L,
        .name = "OUT_Z_L",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_OUT_Z_H,
        .name = "OUT_Z_H",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_FIFO_SRC_REG,
        .name = "FIFO_SRC_REG",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT1_SRC,
        .name = "INT1_SRC",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT2_SRC,
        .name = "INT2_SRC",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CLICK_SRC,
        .name = "CLICK_SRC",
        .access = STORAGE_ACCESS_READ_ONLY,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG0,
        .name = "CTRL_REG0",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG1,
        .name = "CTRL_REG1",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG2,
        .name = "CTRL_REG2",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG3,
        .name = "CTRL_REG3",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG4,
        .name = "CTRL_REG4",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG5,
        .name = "CTRL_REG5",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CTRL_REG6,
        .name = "CTRL_REG6",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_REFERENCE,
        .name = "REFERENCE",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_FIFO_CTRL_REG,
        .name = "FIFO_CTRL_REG",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT1_CFG,
        .name = "INT1_CFG",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT1_THS,
        .name = "INT1_THS",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT1_DURATION,
        .name = "INT1_DURATION",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT2_CFG,
        .name = "INT2_CFG",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT2_THS,
        .name = "INT2_THS",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_INT2_DURATION,
        .name = "INT2_DURATION",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CLICK_CFG,
        .name = "CLICK_CFG",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_CLICK_THS,
        .name = "CLICK_THS",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_TIME_LIMIT,
        .name = "TIME_LIMIT",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_TIME_LATENCY,
        .name = "TIME_LATENCY",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_TIME_WINDOW,
        .name = "TIME_WINDOW",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_ACT_THS,
        .name = "ACT_THS",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
    {
        .valid = TRUE,
        .addr = LIS3DH_REGISTER_ACT_DUR,
        .name = "ACT_DUR",
        .access = STORAGE_ACCESS_READ_WRITE,
    },
};

//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

//! \brief LIS3DH Op Mode Info Get By Op Mode AndScale
static const LIS3DH_OP_MODE_INFO* LIS3DH_GetOpModeInfoByReSc(const LIS3DH_BIT_DEPTH resolutionBit,
                                                             const LIS3DH_FULL_SCALE fullScale);

//! \brief LIS3DH is connected low level
static STD_RESULT LIS3DH_IsConnectedLowLevel(LIS3DH_HANDLE* const Node);

//! \brief LIS3DH init common
static STD_RESULT LIS3DH_InitCommon(const LIS3DH_CONFIGURATION* const Config,
                                    LIS3DH_HANDLE* const        Node);

//! \brief LIS3DH Configure Registers
static STD_RESULT LIS3DH_ConfigureRegisters(const U8 num,
                                            const LIS3DH_REGISTER_VAL* const Reg,
                                            const U32 cnt);

//! \brief LIS3DH proc link one
static STD_RESULT LIS3DH_ProcessLinkOne(const U8 num);

//! \brief LIS3DH Op Mpde And Scale To Sensitivity
static S8 LIS3DH_OpMpdeAndScaleToSensitivity(const LIS3DH_OPERATION_MODE opMode,
                                             const LIS3DH_FULL_SCALE     FullScale);

//! \brief LIS3DH Get Sensitivity Low Level
static S8 LIS3DH_GetSensitivityLowLevel(LIS3DH_HANDLE* const Node);

//! \brief LIS3DH get bitness low level
static STD_RESULT LIS3DH_GetResolutionLowLevel(LIS3DH_HANDLE* const Node,
                                               LIS3DH_BIT_DEPTH* const resolutionBit);

//! \brief LIS3DH is valid configuration
static STD_RESULT LIS3DH_IsValidConfiguration(const LIS3DH_CONFIGURATION* const Config);

//! \brief LIS3DH ADC get info
static const LIS3DH_ADC_INFO* LIS3DH_ADCGetInfo(const U8 adcNum);

//! \brief  LIS3DH get rate info by odr
static const LIS3DH_RATE_INFO* LIS3DH_RateInfo(const U8 odr);

//! \brief  LIS3DH convert data rate  in hz to odr control value
static LIS3DH_ODR LIS3DH_DataRateHzToOdrValue(const U32 dataRateHz);

//! \brief  LIS3DH convert fullscale ctrl const to measurement range in g
static U8 LIS3DH_FullScaleToMeasurementRangeG(const LIS3DH_FULL_SCALE fullScale);

//! \brief  LIS3DH odr ctrl const to data rate in hz
static U32 LIS3DH_OdrToDataRateHz(const LIS3DH_ODR odr);

//! \brief  convert LIS3DH measurement real range in G to 2bit FS code for ASIC CTRL_REG4 register
static LIS3DH_FULL_SCALE LIS3DH_RealRangeToFsCode(const U8 rangeG);

//! \brief get resolution info node by resolution bitness
static const LIS3DH_RESOLUTION_INFO* LIS3DH_GetResolutionInfoByResolution(const U8 resolutionBit);

//! \brief read from LIS3DH a continuous piece of memory
static STD_RESULT LIS3DH_ReadMemoryLowLevel(LIS3DH_HANDLE* const Node,
                                            const LIS3DH_REGISTER_ADDR regAddr,
                                            U8* const data,
                                            const U32 size);

//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! LIS3DH init all instances
//!
//! \note       None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_Init(void)
{
    STD_RESULT ret = RESULT_OK;
    U32 ok = 0;
    U32 cnt = LIS3DH_GetCnt();
    U32 i = 0;
    for (i = 0; i <= cnt; i++)
    {
        ret = LIS3DH_InitOne(LIS3DH_Configuration[i].num);
        if (RESULT_OK == ret)
        {
            ok++;
        }
    } // end of for (i = 0; i <= cnt; i++)
    if (cnt==ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of LIS3DH_Init()

//**************************************************************************************************
//! LIS3DH deinit all instances
//!
//! \note       None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
extern STD_RESULT LIS3DH_DeInit(void)
{
    STD_RESULT ret = RESULT_OK;
    U32 ok = 0;
    U32 cnt = LIS3DH_GetCnt();
    U32 i = 0;
    for (i = 0; i <= cnt; i++)
    {
        ret = LIS3DH_DeInitOne(LIS3DH_Configuration[i].num);
        if (RESULT_OK == ret)
        {
            ok++;
        }
    } // end of for (i = 0; i <= cnt; i++)
    if (cnt==ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of LIS3DH_DeInit()

//**************************************************************************************************
//! LIS3DH init one instance
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_InitOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const LIS3DH_CONFIGURATION* Config = LIS3DH_GetConfig(num);
    if (Config)
    {
        ret = LIS3DH_IsValidConfiguration(Config);
        if (RESULT_OK == ret)
        {
            ret = RESULT_NOT_OK;
            LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
            if (NULL_PTR != Node)
            {
                ret = LIS3DH_InitCommon(Config, Node);
#if ON==I2C_IN_USE
                Node->chipAddr = LIS3DH_I2C_ADDR_0;
                if (Node->sa0PinValue)
                {
                    SET_BIT_NUM(Node->chipAddr, 0);
                }
                else
                {
                    RESET_BIT_NUM(Node->chipAddr, 0);
                }
#endif

                ret = LIS3DH_IsConnectedLowLevel(Node);
                if (RESULT_OK == ret)
                {
                    Node->proc = TRUE;
                    ret = LIS3DH_ConfigureRegisters(num, Config->RegConfig, Config->cfgRegCnt);
                    if (RESULT_OK == ret)
                    {
                        ret = LIS3DH_SetDataRateHz(num, Config->dataRateHz);
                    }

                    if (RESULT_OK == ret)
                    {
                        ret = LIS3DH_SetRangeInG(num, Config->measurementRangeG);
                    }

                    if (RESULT_OK == ret)
                    {
                        ret = LIS3DH_SetResolution(num, Config->resolutionBit);
                    }

                } // end of if (RESULT_OK == ret)

                if (RESULT_OK == ret)
                {
                    Node->init = TRUE;
                }
            } // end of if (NULL_PTR != Node)
        } // end of if (RESULT_OK == ret)
    } // end of if (Config)
    return ret;
} // end of LIS3DH_InitOne()



//**************************************************************************************************
//! LIS3DH de init one instance
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_DeInitOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        Node->deInit = TRUE;
        ret = RESULT_OK;
    }

    return ret;
} // end of LIS3DH_DeInitOne()

//**************************************************************************************************
//! LIS3DH periodicaly invoke function
//!
//! \note       None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_Process(void)
{
    STD_RESULT ret = RESULT_OK;
    U32 ok = 0;
    U32 cnt = LIS3DH_GetCnt();
    U32 num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = LIS3DH_ProcessOne(num);
        if (RESULT_OK == ret)
        {
            ok++;
        }
    } // end of for (num = 0; num <= cnt; num++)
    if (cnt==ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of LIS3DH_Process()

//**************************************************************************************************
//! Process one LIS3DH accelerometer instance
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_ProcessOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const LIS3DH_CONFIGURATION* Config = LIS3DH_GetConfig(num);
    if (NULL_PTR != Config)
    {
        LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
        if (NULL_PTR != Node)
        {
            if (TRUE==Node->proc)
            {
                //! ret = LIS3DH_GetAccelerationFastLowLevel(Node, &Node->Acceleration);
                ret = LIS3DH_GetAccelerationSlowLowLevel(Node, &Node->Acceleration);
                if (RESULT_OK == ret)
                {
                    ret = LIS3DH_AdcToRealLowLevel(Node);
                    Node->unprocSample = TRUE;
                }
            } // end of if (TRUE==Node->proc)
        } // end of if (NULL_PTR != Node)
    } // end of if (NULL_PTR != Config)
    return ret;
} // end of LIS3DH_ProcessOne()


//**************************************************************************************************
//! LIS3DH get node instance
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     RAM instance of LIS3DH driver
//**************************************************************************************************
LIS3DH_HANDLE* LIS3DH_GetNode(const U8 num)
{
    LIS3DH_HANDLE* Node = NULL_PTR;
    U32 i = 0;
    U32 cnt = LIS3DH_GetCnt();
    for (i = 0; i < cnt; i++)
    {
        if (num == LIS3DH_Instance[i].num)
        {
            if (LIS3DH_Instance[i].valid)
            {
                Node = &LIS3DH_Instance[i];
                break;
            }
        } // end of if (num == LIS3DH_Instance[i].num)
    } // end of for (i = 0; i < LIS3DH_GetCnt(); i++)
    return Node;
} // end of LIS3DH_GetNode()

//**************************************************************************************************
//! LIS3DH get sensitivity
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     sensitivity
//**************************************************************************************************
S8 LIS3DH_GetSensitivity(const U8 num)
{
    S8 sensitivity = -1;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        sensitivity = LIS3DH_GetSensitivityLowLevel(Node);
    }
    return sensitivity;
} // end of LIS3DH_GetSensitivity()

//**************************************************************************************************
//! LIS3DH get operation mode cnt
//!
//! \note       None
//!
//! \return     LIS3DH operation mode cnt
//**************************************************************************************************
U32 LIS3DH_GetOperationModeCnt(void)
{
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_OperationModeInfo);
    return cnt;
} // end of LIS3DH_GetOperationModeCnt()

//**************************************************************************************************
//! LIS3DH Convert ADC values To Real acceleration sample
//!
//! \note       None
//!
//! \param[inout]  Acceleration - LIS3DH acceleration node
//! \param[in]     mgPerDigit - mg per digit
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_AdcToReal(LIS3DH_ACCELERATION* const Acceleration,
                            const S8 mgPerDigit)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Acceleration)
    {
        if (0 < mgPerDigit)
        {
            FLOAT32 scaleG = MILLI_TO_REAL(mgPerDigit);
            Acceleration->AccelReal.dx = ((FLOAT32)(Acceleration->X.s16)) * scaleG;
            Acceleration->AccelReal.dy = ((FLOAT32)(Acceleration->Y.s16)) * scaleG;
            Acceleration->AccelReal.dz = ((FLOAT32)(Acceleration->Z.s16)) * scaleG;
            ret = RESULT_OK;
        } // end of if (0 < mgPerDigit)
    } // end of if (Acceleration)
    return ret;
} // end of LIS3DH_AdcToReal()

//**************************************************************************************************
//! LIS3DH adc to real low level
//!
//! \note       None
//!
//! \param[in] Node - ASIC RAM node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_AdcToRealLowLevel(LIS3DH_HANDLE* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Node)
    {
        if (0 < Node->sensitivity)
        {
            FLOAT32 scaleG = MILLI_TO_REAL(Node->sensitivity);
            Node->Acceleration.AccelReal.dx = ((FLOAT32)(Node->Acceleration.X.s16)) * scaleG;
            Node->Acceleration.AccelReal.dy = ((FLOAT32)(Node->Acceleration.Y.s16)) * scaleG;
            Node->Acceleration.AccelReal.dz = ((FLOAT32)(Node->Acceleration.Z.s16)) * scaleG;
            ret = RESULT_OK;
        } // end of if (0 < Node->sensitivity)
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_AdcToRealLowLevel()

//**************************************************************************************************
//! LIS3DH Read ADC Code
//!
//! \note       None
//!
//! \param[in] num - ASIC node number
//! \param[in] adcNum - ADC num
//! \param[out] adcCode - ADC code
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_ReadAdcCode(const U8 num,
                              const U8 adcNum,
                              U16 * const adcCode) {
    STD_RESULT ret = RESULT_NOT_OK;
    const LIS3DH_ADC_INFO* AdcInfo = LIS3DH_ADCGetInfo(adcNum);
    if (AdcInfo)
    {
        LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
        if (Node)
        {
            U16_BIT AdcCode;
            AdcCode.u16 = 0;
            ret = LIS3DH_ReadRegisterLowLevel(Node, AdcInfo->addressLow, &AdcCode.u8[0]);
            if (RESULT_OK==ret)
            {
                ret = LIS3DH_ReadRegisterLowLevel(Node, AdcInfo->addressHi, &AdcCode.u8[1]);
                if (RESULT_OK==ret)
                {
                    ret = RESULT_NOT_OK;
                    U16 adcPureCode = AdcCode.u16 >> (LIS3DH_ACCEL_DATA_SIZE_BIT-AdcInfo->bitness);
                    Node->adcCode[adcNum-1] = adcPureCode;
                    *adcCode = adcPureCode;
                    ret = RESULT_OK;
                } // end of if (RESULT_OK==ret)
            } // end of if (RESULT_OK==ret)
        } // end of if (Node)
    } // end of if (AdcInfo)
    return ret;
} // end of LIS3DH_ReadAdcCode()

//**************************************************************************************************
//! LIS3DH get acceleration fast low level
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetAccelerationFastLowLevel(LIS3DH_HANDLE* const Node,
                                              LIS3DH_ACCELERATION* const Acceleration)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Acceleration)
    {
        S8 shift = LIS3DH_ACCEL_DATA_SIZE_BIT - Node->resolutionBit;
        if (0 < shift)
        {
            static LIS3DH_ACCEL_REGISTERS Mem = {0};
            ret = LIS3DH_ReadMemoryLowLevel(Node,
                                            LIS3DH_REGISTER_OUT_X_L ,
                                            Mem.buff,
                                            sizeof(LIS3DH_ACCEL_REGISTERS));
            if (RESULT_OK == ret)
            {
                Acceleration->X.s16 = Mem.X.s16 >> shift;
                Acceleration->Y.s16 = Mem.Y.s16 >> shift;
                Acceleration->Z.s16 = Mem.Z.s16 >> shift;
                ret = RESULT_OK;
            }
        } // end of if (0 < shift)
    } // end of if (Acceleration)
    return ret;
} // end of LIS3DH_GetAccelerationFastLowLevel()

//!  LIS3DH read axis
#define LIS3DH_READ_AXIS(AXIS)                                                                  \
    ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_OUT_##AXIS##_L, &Accel.AXIS.u8[0]); \
    ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_OUT_##AXIS##_H, &Accel.AXIS.u8[1]); \
    Accel.AXIS.s16 = Accel.AXIS.s16 >> shift;

//**************************************************************************************************
//! LIS3DH get acceleration slow low level
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetAccelerationSlowLowLevel(LIS3DH_HANDLE* const Node,
                                              LIS3DH_ACCELERATION* const Acceleration)
{
    STD_RESULT ret = RESULT_OK;
    static LIS3DH_ACCELERATION Accel = { 0 };
    S8 shift = LIS3DH_ACCEL_DATA_SIZE_BIT - Node->resolutionBit;
    if (0 < shift)
    {
        LIS3DH_READ_AXIS(X)
        LIS3DH_READ_AXIS(Y)
        LIS3DH_READ_AXIS(Z)

        if (RESULT_OK == ret)
        {
            *Acceleration = Accel;
        }
    } // end of if (0 < shift)

    return ret;
} // end of LIS3DH_GetAccelerationSlowLowLevel()

//**************************************************************************************************
//! LIS3DH get bitness
//!
//! \note       None
//!
//! \param[in]   num - LIS3DH node instance natural number
//! \param[out]  resolutionBit - bitness in bits
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetResolution(const U8 num,
                                LIS3DH_BIT_DEPTH* const resolutionBit)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_GetResolutionLowLevel(Node, resolutionBit);
    }
    return ret;
} // end of LIS3DH_GetResolution()


//**************************************************************************************************
//! LIS3DH get data rate in hz
//!
//! \note       None
//!
//! \param[in]  num - ASIC node natural number
//! \param[out]  dataRateHz - data Rate Hz
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetDataRateHz(const U8 num,
                                U32* const dataRateHz)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        LIS3DH_REGIS_CTRL_REG1 CtrlReg1 = {0};
        ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG1, &CtrlReg1.byte );
        if (RESULT_OK==ret)
        {
            *dataRateHz = LIS3DH_OdrToDataRateHz(CtrlReg1.odr);
        }
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_GetDataRateHz()

//**************************************************************************************************
//! LIS3DH get operation mode
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetOperationMode(const U8 num,
                                   LIS3DH_OPERATION_MODE* const opMode)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_GetOperationModeLowLevel(Node, opMode);
    }
    return ret;
} // end of LIS3DH_GetOperationMode()

//**************************************************************************************************
//! LIS3DH get range in g
//!
//! \note       None
//!
//! \param[in]  num - ASIC node natural number
//! \param[in]  range - range in G
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetRange(const U8 num,
                           U8* const range)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        LIS3DH_REGIS_CTRL_REG4 CtrlReg4 = {0};
        CtrlReg4.byte = 0;
        ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG4, &CtrlReg4.byte );
        if (RESULT_OK==ret)
        {
            *range = LIS3DH_FullScaleToMeasurementRangeG(CtrlReg4.fs);
        }
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_GetRange()

//**************************************************************************************************
//! LIS3DH get precision in g
//!
//! \note       precision is how close the measurements are to each other
//!
//! \param[in]  num - ASIC node natural number
//!
//! \return     precision in g
//**************************************************************************************************
FLOAT32 LIS3DH_GetPrecision(const U8 num)
{
    FLOAT32 precisionG = FLT_MAX;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        precisionG = Node->precisionG;
    }
    return precisionG;
} // end of LIS3DH_GetPrecision()

//**************************************************************************************************
//! LIS3DH get configuration
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     LIS3DH ROM configuration
//**************************************************************************************************
const LIS3DH_CONFIGURATION* LIS3DH_GetConfig(const U8 num)
{
    LIS3DH_CONFIGURATION* Config = NULL_PTR;
    U32 i = 0;
    for (i = 0; i < LIS3DH_GetCnt(); i++)
    {
        if (num == LIS3DH_Configuration[i].num)
        {
            if (LIS3DH_Configuration[i].valid)
            {
                Config = &LIS3DH_Configuration[i];
                break;
            }
        } // end of if (num == LIS3DH_Configuration[i].num)
    } // end of for (i = 0; i < LIS3DH_GetCnt(); i++)
    return Config;
} // end of LIS3DH_GetConfig()

//**************************************************************************************************
//! LIS3DH get reg cnt
//!
//! \note       None
//!
//! \return     [Description of return value]
//**************************************************************************************************
U32 LIS3DH_GetRegCnt(void)
{
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_RegInfo);
    return cnt;
} // end of LIS3DH_GetRegCnt()

//**************************************************************************************************
//! LIS3DH get operation mode low level
//!
//! \note        None
//!
//! \param[in]   Node - ASIC RAM node
//! \param[out]  opMode - operation mode
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_GetOperationModeLowLevel(LIS3DH_HANDLE* const Node,
                                           LIS3DH_OPERATION_MODE* const opMode)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_REGIS_CTRL_REG1 CtrlReg1 = { 0 };
    ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG1, &CtrlReg1.byte);
    if (RESULT_OK == ret)
    {
        LIS3DH_REGIS_CTRL_REG4 CtrlReg4 = { 0 };
        ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG4, &CtrlReg4.byte);
        if (RESULT_OK == ret)
        {
            ret = RESULT_NOT_OK;
            U32 i = 0;
            U32 cnt = SIZE_OF_ARRAY(LIS3DH_ResolutionInfo);
            for (i = 0; i < cnt; i++)
            {
                if (LIS3DH_ResolutionInfo[i].lowPowerEnable == CtrlReg1.lpen)
                {
                    if (LIS3DH_ResolutionInfo[i].highResolutionEnable == CtrlReg4.hr)
                    {
                        *opMode = LIS3DH_ResolutionInfo[i].opMode;
                        Node->opMode = LIS3DH_ResolutionInfo[i].opMode;
                        ret = RESULT_OK;
                    }
                } // end of if (LIS3DH_ResolutionInfo[i].lowPowerEnable == CtrlReg1.lpen)
            } // end of for (i = 0; i < cnt; i++)
        } // end of if (RESULT_OK == ret)
    } // end of if (RESULT_OK == ret)
    return ret;
} // end of LIS3DH_GetOperationModeLowLevel()

//**************************************************************************************************
//! LIS3DH set data rate in Hz
//!
//! \note       None
//!
//! \param[in]  num - node natural number
//! \param[in]  dataRateHz - sample output data rate in Hz
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_SetDataRateHz(const U8 num,
                                const U32 dataRateHz)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        LIS3DH_REGIS_CTRL_REG1 CtrlReg1 = {0};
        ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG1, &CtrlReg1.byte);
        if (RESULT_OK==ret)
        {
            CtrlReg1.odr = LIS3DH_DataRateHzToOdrValue(dataRateHz);
            ret = LIS3DH_WriteRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG1, CtrlReg1.byte);
        }
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_SetDataRateHz()

//**************************************************************************************************
//! LIS3DH set measurement range in g
//!
//! \note       None
//!
//! \param[in]  num - ASIC node natural number
//! \param[in]  rangeG - rangein G
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_SetRangeInG(const U8 num,
                              const U8 rangeG) {
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if ( NULL_PTR != Node)
    {
        LIS3DH_REGIS_CTRL_REG4 CtrlReg4 = {0};
        CtrlReg4.byte = 0;
        ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG4, &CtrlReg4.byte );
        if (RESULT_OK==ret)
        {
            CtrlReg4.fs = LIS3DH_RealRangeToFsCode(rangeG);
            ret = LIS3DH_WriteRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG4, CtrlReg4.byte);
        }
    } // end of if (Node)
    return ret;
} // end of LIS3DH_SetRangeInG()

//**************************************************************************************************
//! LIS3DH set measurement resolution in bit
//!
//! \note       None
//!
//! \param[in]  num - ASIC node natural number
//! \param[in]  resolutionBit - measurement resolution in bit
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
STD_RESULT LIS3DH_SetResolution(const U8 num,
                                const LIS3DH_BIT_DEPTH resolutionBit)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        LIS3DH_RESOLUTION_INFO* Info = LIS3DH_GetResolutionInfoByResolution(resolutionBit);
        if (NULL_PTR != Info)
        {
            LIS3DH_REGIS_CTRL_REG1 CtrlReg1 = { 0 };
            ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG1, &CtrlReg1.byte);
            if (RESULT_OK == ret)
            {
                LIS3DH_REGIS_CTRL_REG4 CtrlReg4 = { 0 };
                ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG4, &CtrlReg4.byte);
                if (RESULT_OK == ret)
                {
                    CtrlReg1.lpen = Info->lowPowerEnable;
                    CtrlReg4.hr = Info->highResolutionEnable;
                    ret = LIS3DH_WriteRegisterLowLevel(Node,
                                                       LIS3DH_REGISTER_CTRL_REG1,
                                                       CtrlReg1.byte);
                    if (RESULT_OK == ret)
                    {
                        ret = LIS3DH_WriteRegisterLowLevel(Node,
                                                           LIS3DH_REGISTER_CTRL_REG4,
                                                           CtrlReg4.byte);
                    }
                } // end of if (RESULT_OK == ret)
            } // end of if (RESULT_OK == ret)
        } // end of if (Info)
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_SetResolution()

//**************************************************************************************************
//! LIS3DH is connected
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_IsConnected(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_IsConnectedLowLevel(Node);
    }
    return ret;
} // end of LIS3DH_IsConnected()

//**************************************************************************************************
//! convert LIS3DH internal register address to register info node
//!
//! \note       None
//!
//! \param[in]  regAddr - internal register address
//!
//! \return     internal register address to info node
//**************************************************************************************************
const ASIC_REG_INFO* LIS3DH_RegAddrToInfo(const LIS3DH_REGISTER_ADDR regAddr)
{
    ASIC_REG_INFO* Info = NULL;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_RegInfo);
    U32 i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (LIS3DH_RegInfo[i].valid)
        {
            if (regAddr == LIS3DH_RegInfo[i].addr)
            {
                Info = &LIS3DH_RegInfo[i];
            }
        }
    } // end of for (i = 0; i < cnt; i++)
    return Info;
} // end of LIS3DH_RegAddrToInfo()

//**************************************************************************************************
//! LIS3DH is valid register address
//!
//! \note       None
//!
//! \param[in]  regAddr - register address
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_IsValidAddr(const U8 regAddr)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const ASIC_REG_INFO* Node = LIS3DH_RegAddrToInfo(regAddr);
    if (NULL_PTR != Node)
    {
        ret = RESULT_OK;
    }

    return ret;
} // end of LIS3DH_IsValidAddr()

//**************************************************************************************************
//! LIS3DH proc link
//!
//! \note       None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_ProcessLink(void)
{
    STD_RESULT ret = RESULT_OK;
    U32 ok = 0;
    U32 cnt = LIS3DH_GetCnt();
    U32 num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = LIS3DH_ProcessLinkOne(num);
        if (RESULT_OK == ret)
        {
            ok++;
        }
    } // end of for (num = 0; num <= cnt; num++)
    if (ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of LIS3DH_ProcessLink()

//**************************************************************************************************
//! LIS3DH read acceleration
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_ReadAcceleration(const U32 num,
                                   VECTOR_F* const AccelReal)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        if (Node->unprocSample)
        {
            memcpy(AccelReal, &Node->Acceleration.AccelReal, sizeof(VECTOR_F));
            Node->unprocSample = FALSE;
            ret = RESULT_OK;
        }
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_ReadAcceleration()

//**************************************************************************************************
//! LIS3DH read register
//!
//! \note        None
//!
//! \param[in]   num - LIS3DH node instance natural number
//! \param[in]   regAddr - register address
//! \param[out]  regVal - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_ReadRegister(const U8 num,
                               const LIS3DH_REGISTER_ADDR regAddr,
                               U8* const regVal)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_ReadRegisterLowLevel(Node, regAddr, regVal);
    }
    return ret;
} // end of LIS3DH_ReadRegister()

//**************************************************************************************************
//! LIS3DH read register low level
//!
//! \note       None
//!
//! \param[in]   Node - ASIC RAM node
//! \param[in]   regAddr - registry address
//! \param[out]  rxbyte - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_ReadRegisterLowLevel(LIS3DH_HANDLE* const Node,
                                       const LIS3DH_REGISTER_ADDR regAddr,
                                       U8* const rxbyte)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Node)
    {
        switch(Node->interface)
        {
#if ON==I2C_IN_USE
            case LIS3DH_INTERFACE_I2C: {
                ret=LIS3DH_I2C_RegReadLowLevel(Node,regAddr,rxbyte);
            } break;
#endif /*HAS_I2C*/

#if ON==SPI_IN_USE
            case LIS3DH_INTERFACE_SPI: {
                ret= LIS3DH_SPI_RegReadLowLevel(Node,regAddr,rxbyte);
            } break;
#endif
            default: {
                ret = RESULT_NOT_OK;
            }  break;
        }// end of switch(Node->interface)
    }// end of if (NULL_PTR != Node)
    return ret;
}// end of LIS3DH_ReadRegisterLowLevel()

//**************************************************************************************************
//! LIS3DH read ADC code
//!
//! \note        None
//!
//! \param[in]   num - LIS3DH node instance natural number
//! \param[out]  accelCode - accel ADC code
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
STD_RESULT LIS3DH_ReadCode(const U8 num,
                           VECTOR_S16* const accelCode)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        if (Node->unprocSample)
        {
            accelCode->dx = Node->Acceleration.X.s16;
            accelCode->dy = Node->Acceleration.Y.s16;
            accelCode->dz = Node->Acceleration.Z.s16;
            Node->unprocSample = FALSE;
            ret = RESULT_OK;
        } // end of if (Node->unprocSample)
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_ReadCode()

//**************************************************************************************************
//! Writing One Byte of Data to the LIS3DH
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//! \param[in]  regAddr - register address
//! \param[in]  regVal - One Byte of Data to write in the LIS3DH
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_WriteRegister(const U8 num,
                                const LIS3DH_REGISTER_ADDR regAddr,
                                const U8 regVal)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_WriteRegisterLowLevel(Node, regAddr, regVal);
    }
    return ret;
} // end of LIS3DH_WriteRegister()

//**************************************************************************************************
//! LIS3DH write register low level
//!
//! \note      None
//!
//! \param[in] Node - ASIC RAM node
//! \param[in] regAddr - ASIC internal register address
//! \param[in] byte - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_WriteRegisterLowLevel(LIS3DH_HANDLE* const Node,
                                        const LIS3DH_REGISTER_ADDR regAddr,
                                        const U8 byte)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_IsValidAddr(regAddr);
        if (RESULT_OK==ret)
        {
            switch(Node->interface)
            {
#if ON==I2C_IN_USE
                case LIS3DH_INTERFACE_I2C: {
                    ret = LIS3DH_I2C_RegWriteLowLevel(Node, regAddr, byte);
                } break;
#endif /*HAS_I2C*/

#if ON==SPI_IN_USE
                case LIS3DH_INTERFACE_SPI: {
                    ret = LIS3DH_SPI_RegWriteLowLevel(Node, regAddr, byte);
                } break;
#endif /*HAS_SPI*/
                default:
                    ret = RESULT_NOT_OK;
                    break;
            } // end of switch(Node->interface)
        } // end of if (RESULT_OK==ret)
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_WriteRegisterLowLevel()


//**************************************************************************************************
//! LIS3DH write register and verify it
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//! \param[in]  regAddr - register address
//! \param[in]  value - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_WriteRegisterVerify(const U8 num,
                                      const LIS3DH_REGISTER_ADDR regAddr,
                                      const U8 value)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = LIS3DH_WriteRegister(num, regAddr, value);
    if (RESULT_OK == ret)
    {
        U8 byteRead = 0;
        ret = LIS3DH_ReadRegister(num, regAddr, &byteRead);
        if (byteRead == value)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    } // end of if (RESULT_OK == ret)

    return ret;
} // end of LIS3DH_WriteRegisterVerify()

//**************************************************************************************************
//! LIS3DH resolution info get by operation mode
//!
//! \note       None
//!
//! \param[in]  opMode - operating mode selection
//!
//! \return     LIS3DH resolution info
//**************************************************************************************************
const LIS3DH_RESOLUTION_INFO* LIS3DH_ResolitionInfoByOpMode(const LIS3DH_OPERATION_MODE opMode)
{
    LIS3DH_RESOLUTION_INFO* ResolInfo = NULL_PTR;
    U32 i = 0;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_ResolutionInfo);
    for (i = 0; i < cnt; i++)
    {
        if (opMode == LIS3DH_ResolutionInfo[i].opMode)
        {
            ResolInfo = &LIS3DH_ResolutionInfo[i];
        }
    }
    return ResolInfo;
} // end of LIS3DH_OpModeInfoGetByOpMode()



//**************************************************************************************************
//! LIS3DH resolution info get by operation mode
//!
//! \note       None
//!
//! \param[in]  opMode - operating mode selection
//!
//! \return     LIS3DH operation mode info
//**************************************************************************************************
const
LIS3DH_RESOLUTION_INFO* LIS3DH_GetResolutionInfoByOpMode(const LIS3DH_OPERATION_MODE opMode)
{
    LIS3DH_RESOLUTION_INFO* Info = NULL_PTR;
    U32 cnt = LIS3DH_GetOperationModeCnt();
    U32 i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (LIS3DH_ResolutionInfo[i].valid)
        {
            if (opMode == LIS3DH_ResolutionInfo[i].opMode)
            {
                Info = &LIS3DH_ResolutionInfo[i];
            }
        }
    } // end of for (i = 0; i < cnt; i++)
    return Info;
} // end of LIS3DH_OpModeInfoGetByOpMode()


//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************

//**************************************************************************************************
//! Get LIS3DH operation mode info by resolution and measurement range
//!
//! \note       None
//!
//! \param[in]  resolutionBit - sample ADC resolution
//! \param[in]  fullScale - range of measured accelerations in g
//!
//! \return     LIS3DH operation mode info node
//**************************************************************************************************
static const LIS3DH_OP_MODE_INFO* LIS3DH_GetOpModeInfoByReSc(const LIS3DH_BIT_DEPTH resolutionBit,
                                                             const LIS3DH_FULL_SCALE fullScale)
{
    LIS3DH_OP_MODE_INFO* Info = NULL_PTR;
    U32 i = 0;
    U32 cnt = LIS3DH_GetOperationModeCnt();
    for (i = 0; i < cnt; i++)
    {
        if (resolutionBit == LIS3DH_OperationModeInfo[i].resolutionBit)
        {
            if (fullScale == LIS3DH_OperationModeInfo[i].fullScale)
            {
                Info = &LIS3DH_OperationModeInfo[i];
            }
        }
    } // end of for (i = 0; i < cnt; i++)
    return Info;
} // end of LIS3DH_GetOpModeInfoByReSc()

//**************************************************************************************************
//! LIS3DH Is Connected Low Level
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_IsConnectedLowLevel(LIS3DH_HANDLE* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U8         regVal = 0;
    ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_WHO_AM_I, &regVal);
    if (RESULT_OK == ret)
    {
        if (LIS3DH_ID_VALUE == regVal)
        {
            ret = RESULT_OK;
            Node->proc = TRUE;
        }
        else
        {
            Node->proc = FALSE;
            ret = RESULT_NOT_OK;
        }
    } // end of if (RESULT_OK == ret)
    return ret;
} // end of LIS3DH_IsConnectedLowLevel()

//**************************************************************************************************
//! LIS3DH Init Common
//!
//! \note       None
//!
//! \param[in]  Config - LIS3DH ASIC ROM node with configuration
//! \param[in]  Node - LIS3DH ASIC RAM node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_InitCommon(const LIS3DH_CONFIGURATION* const Config,
                                    LIS3DH_HANDLE* const        Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Config)
    {
        if (NULL_PTR != Node)
        {
            Node->resolutionBit = Config->resolutionBit;
            Node->chipAddr = Config->chipAddr;
            Node->chipSelectPort = Config->chipSelectPort;
            Node->chipSelectPin = Config->chipSelectPin;
            Node->dataRateHz = Config->dataRateHz;
            Node->interface = Config->interface;
            Node->i2cNum = Config->i2cNum;
            Node->num = Config->num;
            Node->precisionG = Config->precisionG;
            Node->sa0PinValue = Config->sa0PinValue;
            Node->spiNum = Config->spiNum;
            Node->valid = TRUE;
            ret = RESULT_OK;
        } // end of if (NULL_PTR != Node)
    } // end of if (NULL_PTR != Config)
    return ret;
} // end of LIS3DH_InitCommon()

//**************************************************************************************************
//! LIS3DH Configure Registers
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//! \param[in]  Reg - LIS3DH register info
//! \param[in]  cnt - LIS3DH register to configuration cnt
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_ConfigureRegisters(const U8 num,
                                            const LIS3DH_REGISTER_VAL* const Reg,
                                            const U32 cnt)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Reg)
    {
        U32 ok = 0;
        if (cnt)
        {
            U32 i = 0;
            for (i = 0; i < cnt; i++)
            {
                ret = LIS3DH_WriteRegisterVerify(num, Reg[i].address, Reg[i].Reg.byte);
                if (RESULT_OK == ret)
                {
                    ok++;
                }
            } // end of for (i = 0; i < cnt; i++)
        } // end of if (cnt)
        if (ok == cnt)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    } // end of if (Reg)
    return ret;
} // end of LIS3DH_ConfigureRegisters()

//**************************************************************************************************
//! LIS3DH Process Link One
//!
//! \note       None
//!
//! \param[in]  num - LIS3DH node instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_ProcessLinkOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const LIS3DH_CONFIGURATION* Config = LIS3DH_GetConfig(num);
    if (NULL_PTR != Config)
    {
        LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
        if (NULL_PTR != Node)
        {
            ret = LIS3DH_IsConnectedLowLevel(Node);
            if (RESULT_OK == ret)
            {
                Node->sensitivity = LIS3DH_GetSensitivityLowLevel(Node);
                Node->resolutionBit = 0;
                ret = LIS3DH_GetResolutionLowLevel(Node, &Node->resolutionBit);
            }
            if (FALSE==Node->init)
            {
                ret = LIS3DH_InitOne(num);
            }
        } // end of if (NULL_PTR != Node)
    } // end of  if (NULL_PTR != Config)
    return ret;
} // end of LIS3DH_ProcessLinkOne()

//**************************************************************************************************
//! LIS3DH Op mode And Scale To Sensitivity
//!
//! \note       None
//!
//! \param[in]  opMode - operation mode
//! \param[in]  FullScale - fill scale
//!
//! \return     Sensitivity
//**************************************************************************************************
static S8 LIS3DH_OpMpdeAndScaleToSensitivity(const LIS3DH_OPERATION_MODE opMode,
                                             const LIS3DH_FULL_SCALE     FullScale)
{
    S8 sensitivity = -1;
    LIS3DH_RESOLUTION_INFO* Resolution = LIS3DH_GetResolutionInfoByOpMode(opMode);
    if (NULL_PTR != Resolution)
    {
        LIS3DH_OP_MODE_INFO* OpInfo = LIS3DH_GetOpModeInfoByReSc(Resolution->resolutionBit,
                                                                 FullScale);
        if (NULL_PTR != OpInfo)
        {
            sensitivity = OpInfo->sensitivity;
        }
    } // end of  if (Resolution)
    return sensitivity;
} // end of LIS3DH_OpMpdeAndScaleToSensitivity()

//**************************************************************************************************
//! LIS3DH Get Sensitivity Low Level
//!
//! \note      None
//!
//! \param[in] Node - ASIC RAM node
//!
//! \return    Sensitivity
//**************************************************************************************************
static S8 LIS3DH_GetSensitivityLowLevel(LIS3DH_HANDLE* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    S8 sensitivity = -1;
    if (NULL_PTR != Node)
    {
        LIS3DH_REGIS_CTRL_REG4 CtrlReg4 = { 0 };
        ret = LIS3DH_ReadRegisterLowLevel(Node, LIS3DH_REGISTER_CTRL_REG4, &CtrlReg4.byte);
        if (RESULT_OK == ret)
        {
            LIS3DH_OPERATION_MODE opMode = LIS3DH_OP_MODE_UNDEF;
            ret = LIS3DH_GetOperationModeLowLevel(Node, &opMode);
            if (RESULT_OK == ret)
            {
                sensitivity = LIS3DH_OpMpdeAndScaleToSensitivity(opMode, CtrlReg4.fs);
                Node->sensitivity = sensitivity;
            }
        } // end of if (RESULT_OK == ret)
    } // end of if (NULL_PTR != Node)
    return sensitivity;
} // end of LIS3DH_GetSensitivityLowLevel()

//**************************************************************************************************
//! LIS3DH Get Bitness Low Level
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node pointer
//! \param[in]  resolutionBit - bit Depth
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_GetResolutionLowLevel(LIS3DH_HANDLE* const Node,
                                               LIS3DH_BIT_DEPTH* const resolutionBit)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_GetOperationModeLowLevel(Node, &Node->opMode);
        if (RESULT_OK == ret)
        {
            ret = RESULT_NOT_OK;
            LIS3DH_RESOLUTION_INFO* Info = LIS3DH_GetResolutionInfoByOpMode(Node->opMode);
            if (Info)
            {
                Node->resolutionBit = Info->resolutionBit;
                *resolutionBit = Info->resolutionBit;
                ret = RESULT_OK;
            }
        } // end of if (RESULT_OK == ret)
    } // end of if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_GetResolutionLowLevel()

//**************************************************************************************************
//! LIS3DH Is Valid Configuration
//!
//! \note       None
//!
//! \param[in]  Config - ROM node configuration pointer
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_IsValidConfiguration(const LIS3DH_CONFIGURATION* const Config)
{
    STD_RESULT ret = RESULT_OK;
    if (0 == Config->cfgRegCnt)
    {
        ret = RESULT_NOT_OK;
    }

    if (NULL_PTR == Config->RegConfig)
    {
        ret = RESULT_NOT_OK;
    }


    return ret;
} // end of LIS3DH_IsValidConfiguration()


//**************************************************************************************************
//! LIS3DH ADC Get Info
//!
//! \note       None
//!
//! \param[in]  adcNum - adc Num
//!
//! \return     LIS3DH ADC INFO node
//**************************************************************************************************
static const LIS3DH_ADC_INFO* LIS3DH_ADCGetInfo(const U8 adcNum)
{
    LIS3DH_ADC_INFO* Info = NULL_PTR;
    U32 i = 0;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_ADC_Info);
    for(i = 0; i < cnt; i++)
    {
        if (adcNum == LIS3DH_ADC_Info[i].adcNum)
        {
            if (LIS3DH_ADC_Info[i].valid)
            {
                Info = &LIS3DH_ADC_Info[i];
                break;
            }
        }// end of if (adcNum == LIS3DH_ADC_Info[i].adcNum)
    }// end of for(i = 0; i < cnt; i++)
    return Info;
}// end of LIS3DH_ADCGetInfo()


//**************************************************************************************************
//! LIS3DH Get rate Info
//!
//! \note       None
//!
//! \param[in]  adcNum - adc Num
//!
//! \return     LIS3DH rate info node
//**************************************************************************************************
static const LIS3DH_RATE_INFO* LIS3DH_RateInfo(const U8 odr)
{
    LIS3DH_RATE_INFO* Info = NULL_PTR;
    U32 i = 0;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_RATE_Info);
    for(i = 0; i < cnt; i++)
    {
        if (odr == LIS3DH_RATE_Info[i].odr)
        {
            if (LIS3DH_RATE_Info[i].valid)
            {
                Info = &LIS3DH_RATE_Info[i];
                break;
            }
        } // end of if (odr == LIS3DH_RATE_Info[i].odr)
    } // end of for(i = 0; i < cnt; i++)
    return Info;
}// end of LIS3DH_RateInfo()

//**************************************************************************************************
//! convert LIS3DH data rate hz to odr value
//!
//! \note       None
//!
//! \param[in]  dataRateHz - data rate hz
//!
//! \return     odr bit field value
//**************************************************************************************************
static LIS3DH_ODR LIS3DH_DataRateHzToOdrValue(const U32 dataRateHz)
{
    LIS3DH_ODR odr = LIS3DH_ODR_UNDEF_HZ;
    S32 dataRateHzS = dataRateHz;
    S32 minDiffHz = INT_MAX;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_RATE_Info);
    U32 i = 0;
    for(i = 0; i < cnt; i++)
    {
        if (LIS3DH_RATE_Info[i].valid)
        {
            S32 diff = abs(dataRateHzS-((S32)LIS3DH_RATE_Info[i].dataRateHz));
            if (diff < minDiffHz)
            {
                minDiffHz = diff;
                odr = LIS3DH_RATE_Info[i].odr;
            }
        } // end of if (LIS3DH_RATE_Info[i].valid)
    } // end of for(i = 0; i < cnt; i++)
    return odr;
} // end of LIS3DH_DataRateHzToOdrValue()

//**************************************************************************************************
//! convert LIS3DH Full scale to measurement range g
//!
//! \note       None
//!
//! \param[in]  fullScale - range of measured accelerations
//!
//! \return     measurement range g
//**************************************************************************************************
static U8 LIS3DH_FullScaleToMeasurementRangeG(const LIS3DH_FULL_SCALE fullScale) {
    U8 range = 0;
    U32 i = 0;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_RANGE_Info);
    for(i = 0; i < cnt; i++)
    {
        if (fullScale == LIS3DH_RANGE_Info[i].fullScale)
        {
            if (LIS3DH_RANGE_Info[i].valid)
            {
                range = LIS3DH_RANGE_Info[i].range;
                break;
            }
        }// end of if (fullScale == LIS3DH_RANGE_Info[i].fullScale)
    }// end of for(i = 0; i < cnt; i++)
    return range;
} // end of LIS3DH_FullScaleToMeasurementRangeG()

//**************************************************************************************************
//! convert LIS3DH odr to data rate hz
//!
//! \note       None
//!
//! \param[in]  odr - output data rate
//!
//! \return     data rate hz
//**************************************************************************************************
static U32 LIS3DH_OdrToDataRateHz(const LIS3DH_ODR odr)
{
    U32 dataRateHz = 0;
    const LIS3DH_RATE_INFO* RateInfo = LIS3DH_RateInfo(odr);
    if (RateInfo)
    {
        dataRateHz = RateInfo->dataRateHz;
    }
    return dataRateHz;
} // end of LIS3DH_OdrToDataRateHz()

//**************************************************************************************************
//! convert LIS3DH measurement real range in G to 2bit FS code for ASIC CTRL_REG4 register
//!
//! \note       None
//!
//! \param[in]  rangeG - range in g
//!
//! \return     FS code for ASIC CTRL_REG4 register
//**************************************************************************************************
static LIS3DH_FULL_SCALE LIS3DH_RealRangeToFsCode(const U8 rangeG)
{
    LIS3DH_FULL_SCALE fullScale = 0;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_RANGE_Info);
    U32 i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (rangeG == LIS3DH_RANGE_Info[i].range)
        {
            if (LIS3DH_RANGE_Info[i].valid)
            {
                fullScale = LIS3DH_RANGE_Info[i].fullScale;
                break;
            }
        }// end of if (rangeG == LIS3DH_RANGE_Info[i].range)
    }// end of for (i = 0; i < cnt; i++)
    return fullScale;
} // end of LIS3DH_RealRangeToFsCode()

//**************************************************************************************************
//! get resolution info node by resolution bitness
//!
//! \note       None
//!
//! \param[in]  resolutionBit - resolution in bit
//!
//! \return     resolution info node
//**************************************************************************************************
static const LIS3DH_RESOLUTION_INFO* LIS3DH_GetResolutionInfoByResolution(const U8 resolutionBit)
{
    LIS3DH_RESOLUTION_INFO* Info = NULL_PTR;
    U32 cnt = SIZE_OF_ARRAY(LIS3DH_ResolutionInfo);
    U32 i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (LIS3DH_ResolutionInfo[i].valid)
        {
            if (resolutionBit==LIS3DH_ResolutionInfo[i].resolutionBit)
            {
                Info = &LIS3DH_ResolutionInfo[i ];
                break;
            }
        } // end of if (LIS3DH_ResolutionInfo[i].valid)
    } // end of for (i = 0; i < cnt; i++)
    return Info;
} // end of LIS3DH_GetResolutionInfoByResolution()

//**************************************************************************************************
//! read from LIS3DH a continuous piece of memory
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//! \param[in]  regAddr - register start address
//! \param[in]  size - number of bytes to read
//! \param[out] data - array to read into
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT LIS3DH_ReadMemoryLowLevel(LIS3DH_HANDLE* const Node,
                                            const LIS3DH_REGISTER_ADDR regAddr,
                                            U8* const data,
                                            const U32 size)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch(Node->interface)
    {
#if ON==I2C_IN_USE
        case LIS3DH_INTERFACE_I2C:
        {
            ret = LIS3DH_I2C_ReadMemoryLowLevel(Node, regAddr, data, size);
        } break;
#endif
        case LIS3DH_INTERFACE_SPI:
        {
            ret = LIS3DH_SPI_ReadMemoryLowLevel(Node, regAddr, data, size);
        } break;
        default: ret = RESULT_NOT_OK; break;
    } // end of switch(Node->interface)
    return ret;
} // end of LIS3DH_ReadMemoryLowLevel()

//****************************************** end of file *******************************************
