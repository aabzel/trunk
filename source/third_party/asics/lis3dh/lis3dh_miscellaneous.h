//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_miscellaneous.h
//! \brief  Interface of the LIS3DH module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_MISC_H
#define LIS3DH_MISC_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// platform
#include "platform.h"

// general_types
#include "general_types.h"

// storage constants
#include "storage_constants.h"

// Get i2c mcal API
//#include "i2c_mcal.h"
//! gpio custom const
#include "gpio_custom_const.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! data type for extracting and inserting individual bytes in word
typedef union
{
    //! 16 bit, signed, word
    S16 s16;
    //! 16 bit, unsigned, word
    U16 u16;
    //! 8 bit, unsigned,
    U8 u8[2];
    //! 8 bit, signed,
    S8 s8[2];
} U16_BIT;

//! ASIC REG INFO
typedef struct {
    //! valid
    U8 valid;
    //! name
    char* name;
    //! access
    STORAGE_ACCESS access;
    //! addr
    U8 addr;
}ASIC_REG_INFO;


//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! xxxxx
#define SET_BIT_NUM(VAL, BIT) ((VAL) |= (1U << (BIT)))

//! xxxxxxxx
#define RESET_BIT_NUM(VAL, BIT) ((VAL) &= ~(1U << (BIT)))

//! xxxxxx
#define MILLI_TO_REAL(MILLI) (((FLOAT32)(MILLI)) / 1000.0)


#endif /* LIS3DH_MISC_H */

//****************************************** end of file *******************************************
