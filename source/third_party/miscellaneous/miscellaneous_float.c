//**************************************************************************************************
// @Module  FLOAT
//! \file   miscellaneous_float.c
//! \par    Platform
//!             Any
//! \par    Compatible
//!             Any
//! \brief  Implementation of the FLOAT functionality.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   FLOAT
//! \brief      Short description of Module
//! \addtogroup FLOAT
//! @{
//! \file float.c
//! \file float.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// miscellaneous float
#include "miscellaneous_float.h"



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
// Declarations of local (private) functions
//**************************************************************************************************



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! the function checks that two floating point numbers are equal
//!
//! \note       None
//!
//! \param[in]  f1 - first value
//! \param[in]  f2 - second value
//! \param[out] precision - precision
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT FLOAT_IsEqualAbsolute(const FLOAT32 f1, const FLOAT32 f2, const FLOAT32 precision)
{
    STD_RESULT ret = RESULT_NOT_OK;
    FLOAT_WORD w1;
    FLOAT_WORD w2;
    w1.val = f1;
    w2.val = f2;
    if (w1.num == w2.num)
    {
        ret = RESULT_OK;
    }
    else
    {
        if ((f1 - precision) < f2)
        {
            if (f2 < (f1 + precision))
            {
                ret = RESULT_OK;
            }
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    } // end of if(w1.num != w2.num)
    return ret;
} // end of FLOAT_IsEqualAbsolute()

//**************************************************************************************************
//! the function checks that two floating point numbers are equal
//!
//! \note       None
//!
//! \param[in]  valA - value A
//! \param[in]  valB - value B
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT FLOAT_IsEqual(const FLOAT32 valA, const FLOAT32 valB)
{
    return FLOAT_IsEqualAbsolute(valA, valB, FLOAT_EPSILON);
} // end of FLOAT_IsEqual()

//**************************************************************************************************
//! the function checks that  floating point number is zero
//!
//! \note       None
//!
//! \param[in]  value - in value
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT FLOAT_IsZero(const FLOAT32 value)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = FLOAT_IsEqualAbsolute(0.0, value, FLOAT_EPSILON);
    return ret;
} // end of FLOAT_IsZero()

//**************************************************************************************************
//! function calculates percentage of fraction
//!
//! \note       None
//!
//! \param[in]  numerator - numerator
//! \param[in]  denominator - denominator
//!
//! \return     percentage of fraction
//**************************************************************************************************
FLOAT32 FLOAT_CalcPrecent(const FLOAT32 numerator, const FLOAT32 denominator)
{
    FLOAT32 precent = 0.0;
    precent = (100.0 * numerator) / denominator;
    return precent;
} // end of FLOAT_CalcPrecent()

//**************************************************************************************************
//! function limits the value of a number by up threshold
//!
//! \note       None
//!
//! \param[in]  rawValue - raw value
//! \param[in]  upLimit - up Limit
//!
//! \return     limited value
//**************************************************************************************************
FLOAT32 FLOAT_LimiterUp(const FLOAT32 rawValue, const FLOAT32 upLimit)
{
    FLOAT32 limitedValue = rawValue;
    if (upLimit < rawValue)
    {
        limitedValue = upLimit;
    }
    return limitedValue;
} // end of FLOAT_LimiterUp()

//**************************************************************************************************
//! function limits the value of a number between thresholds
//!
//! \note       None
//!
//! \param[in]  rawValue - raw value
//! \param[in]  downLimit - down Limit
//! \param[out] upLimit - up Limit
//!
//! \return     limited value
//**************************************************************************************************
FLOAT32 FLOAT_LimiterDownUp(const FLOAT32 rawValue, const FLOAT32 downLimit, const FLOAT32 upLimit)
{
    FLOAT32 limitedValue = rawValue;
    if (downLimit < upLimit)
    {
        if (upLimit < rawValue)
        {
            limitedValue = upLimit;
        }
        if (rawValue < downLimit)
        {
            limitedValue = downLimit;
        }
    } // end of if(downLimit < upLimit)
    return limitedValue;
} // end of FLOAT_LimiterDownUp()

//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************


//****************************************** end of file *******************************************
