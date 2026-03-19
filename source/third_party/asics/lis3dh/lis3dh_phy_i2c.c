//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_phy_i2c.c
//! \par    Platform
//!             Any platform with ASIC LIS3DH
//! \par    Compatible
//!             Any microcontroller with I2C, and GPIO
//! \brief  Implementation of the LIS3DH functionality.
//!             This is a I2C PHY for the ASIC LIS3DH.
//! \par    Abbreviations
//!             ASIC - Application-specific integrated circuit
//!             I2C - Inter-Integrated Circuit
//!             PHY - Physical layer
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   LIS3DH Name of Module
//! \brief      Short description of Module
//! \addtogroup LIS3DH
//! @{
//! \file lis3dh_phy_i2c.c
//! \file lis3dh_phy_i2c.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// lis3dh phy i2c
#include "lis3dh_phy_i2c.h"

// i2c drv
#include "i2c_drv.h"

// i2c drv
#include "i2c_mcal.h"

// lis3dh driver
#include "lis3dh_driver.h"

//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) variables
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



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! Read LIS3DH register by I2C
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//! \param[in]  regAddr - register address
//! \param[out]  regVal - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_I2C_RegReadLowLevel(LIS3DH_HANDLE* const  Node,
                                      const LIS3DH_REGISTER_ADDR regAddr,
                                      U8 *const regVal) {
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Node)
    {
        ret = I2C_ReadByte(Node->i2cNum, Node->chipAddr, regAddr, regVal);
    }
    return ret;
} // end of LIS3DH_I2C_RegReadLowLevel()

//**************************************************************************************************
//! read from LIS3DH a continuous piece of memory by I2C
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
STD_RESULT LIS3DH_I2C_ReadMemoryLowLevel(LIS3DH_HANDLE* const Node,
                                         const LIS3DH_REGISTER_ADDR regAddr,
                                         U8* const data,
                                         const U32 size)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if ( NULL_PTR!=Node )
    {

    }
    return ret;
} // end of LIS3DH_I2C_ReadMemoryLowLevel()

//**************************************************************************************************
//! Write LIS3DH register by I2C
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//! \param[in]  regAddr - register address
//! \param[in]  regVal - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_I2C_RegWriteLowLevel(LIS3DH_HANDLE* const Node,
                                       const LIS3DH_REGISTER_ADDR regAddr,
                                       const U8 regVal) {
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR != Node)
    {
        ret = LIS3DH_IsValidAddr(regAddr);
        if (RESULT_OK == ret)
        {
            U8 buff[2] = { regAddr, regVal };
            ret = I2C_ChipWrite(Node->i2cNum, Node->chipAddr, buff, sizeof(buff));
        }
    } // end of  if (NULL_PTR != Node)
    return ret;
} // end of LIS3DH_I2C_RegWriteLowLevel()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//****************************************** end of file *******************************************
