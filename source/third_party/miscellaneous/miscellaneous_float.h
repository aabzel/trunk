//**************************************************************************************************
// @Module  FLOAT
//! \file   miscellaneous_float.h
//! \brief  Interface of the FLOAT module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef MISCELLANEOUS_FLOAT_H
#define MISCELLANEOUS_FLOAT_H

//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Get general data types
#include "general_types.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! bit representation of a float number
typedef union {
    //! float value
    FLOAT32 val;
    //! float value binary representation
    U32 num;
} FLOAT_WORD;

#ifndef HAS_MISCELLANEOUS_FLOAT
#error "+HAS_MISCELLANEOUS_FLOAT"
#endif

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! error for float comparing numbers
#define FLOAT_EPSILON 1E-10f



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief the function checks that two floating point numbers are equal
extern STD_RESULT
FLOAT_IsEqualAbsolute(const FLOAT32 f1, const FLOAT32 f2, const FLOAT32 precision);

//! \brief the function checks that two floating point numbers are equal
extern STD_RESULT FLOAT_IsEqual(const FLOAT32 valA, const FLOAT32 valB);

//! \brief the function checks that  floating point number is zero
extern STD_RESULT FLOAT_IsZero(const FLOAT32 value);

//! \brief function calculates percentage of fraction
extern FLOAT32 FLOAT_CalcPrecent(const FLOAT32 numerator, const FLOAT32 denominator);

//! \brief function limits the value of a number by up threshold
extern FLOAT32 FLOAT_LimiterUp(const FLOAT32 rawValue, const FLOAT32 upLimit);

//! \brief function limits the value of a number between thresholds
extern FLOAT32
FLOAT_LimiterDownUp(const FLOAT32 rawValue, const FLOAT32 downLimit, const FLOAT32 upLimit);



#endif // #ifndef MISCELLANEOUS_FLOAT_H

//****************************************** end of file *******************************************
