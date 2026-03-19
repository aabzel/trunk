//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_phy_i2c.h
//! \brief  Interface of the LIS3DH module.
//!             API for LIS3DH I2C PHY
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_PHY_I2C_H
#define LIS3DH_PHY_I2C_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// platform types
#include "platform.h"

// Get data types
#include "general_types.h"

// include lis3dh types
#include "lis3dh_type.h"


//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief Read LIS3DH register by I2C
extern STD_RESULT LIS3DH_I2C_RegReadLowLevel(LIS3DH_HANDLE* const Node,
                                             const LIS3DH_REGISTER_ADDR regAddr,
                                             U8 *const regVal);

//! \brief Read LIS3DH register by I2C
extern STD_RESULT LIS3DH_I2C_ReadMemoryLowLevel(LIS3DH_HANDLE* const Node,
                                                const LIS3DH_REGISTER_ADDR regAddr,
                                                U8 *const data,
                                                const U32 size);

//! \brief Write LIS3DH register by I2C
extern STD_RESULT LIS3DH_I2C_RegWriteLowLevel(LIS3DH_HANDLE* const Node,
                                              const LIS3DH_REGISTER_ADDR regAddr,
                                              const U8 regVal);


#endif // #ifndef LIS3DH_PHY_I2C_H

//****************************************** end of file *******************************************
