//**************************************************************************************************
// @Module  MODULE
//! \file   module.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!             [text]
//! \par    Abbreviations
//!             ABBR0 -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.XXXX |  1.1.0  |   XXX   | Last  release.
//! | XX.XX.XXXX |  1.0.0  |   XXX   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   MODULE Name of Module
//! \brief      Short description of Module
//! \addtogroup MODULE
//! @{
//! \file module.c
//! \file module.h
//! \file module_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Native header
#include "module.h"

// [Description...]
#include "another_module.h"



//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

#if (!defined COMPATIBLE_PROCESSOR_MODULE)
#error "module.c:" This program module is not compatible with the selected processor.
#endif // #if (!defined COMPATIBLE_PROCESSOR_MODULE)

#if ((MODULE_PARAMETER_ONE < x) || (y <= MODULE_PARAMETER_ONE))
#error "Wrong program configuration: MODULE_PARAMETER_ONE must be in the range [x ; y)"
#endif // #if ((MODULE_PARAMETER_ONE < x) || (y <= MODULE_PARAMETER_ONE))

#if ((MODULE_PARAMETER_TWO <= a) || (b < MODULE_PARAMETER_TWO))
#error "Wrong program configuration: MODULE_PARAMETER_TWO must be in the range (a ; b]"
#endif // #if ((MODULE_PARAMETER_TWO <= a) || (b < MODULE_PARAMETER_TWO))



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

//! [Description...]
DATA_TYPE MODULE_variableZero;

//! [Description...]
DATA_TYPE MODULE_variableOne;



//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************

//! [Description...]
typedef DATA_TYPE MODULE_DATA_TYPE_THREE;

//! [Description...]
typedef struct
{
    //! [Description of fieldZero...]
    DATA_TYPE fieldZero;
    //! [Description of fieldOne...]
    DATA_TYPE fieldOne;
} MODULE_DATA_TYPE_FOUR;

//! [Description...]
typedef union
{
    //! [Description of fieldZero_struct...]
    struct
    {
        //! [Description of fieldZero...]
        DATA_TYPE fieldZero;
        //! [Description of fieldOne...]
        DATA_TYPE fieldOne;
    } fieldZero;

    //! [Description of fieldOne...]
    DATA_TYPE fieldOne;
} MODULE_DATA_TYPE_FIVE;



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************

//! [Description...]
#define MODULE_CONST_TWO    (0x01U)

//! [Description...]
#define MODULE_CONST_THREE  (-1)

//! [Description...]
static const DATA_TYPE MODULE_constFour = 0x02U;



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

//! [Description...]
static DATA_TYPE MODULE_variableTwo;

//! [Description...]
static DATA_TYPE MODULE_variableThree;



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

//! \brief [Description...]
static DATA_TYPE MODULE_FunctionTwo(DATA_TYPE parameterZero,
                                    DATA_TYPE parameterOne);

//! \brief [Description...]
static DATA_TYPE MODULE_FunctionThree(DATA_TYPE parameterZero,
                                      DATA_TYPE parameterOne,
                                      DATA_TYPE parameterTwo);



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! [Description of MODULE_FunctionZero]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description of parameterZero]
//!
//! \return     [Description of return value]
//**************************************************************************************************
DATA_TYPE MODULE_FunctionZero(DATA_TYPE parameterZero)
{
    DATA_TYPE returnValue;

    // [Description...]
    if (a > b)
    {
        moreCnt++;
    }
    else if (a < b)
    {
        lessCnt++;
    }
    else
    {
        equalCnt++;
    }

    return returnValue;
} // end of MODULE_FunctionZero()



//**************************************************************************************************
//! [Description of MODULE_FunctionOne]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description...]
//! \param[out] parameterOne - [description...]
//!
//! \return     [Description of return value]
//**************************************************************************************************
DATA_TYPE MODULE_FunctionOne(DATA_TYPE parameterZero,
                             DATA_TYPE parameterOne)
{
    DATA_TYPE returnValue;

    // [Description...]
    DATA_TYPE idx = 0;
    for ( ; idx < MAX; idx++)
    {
        arrayResult[idx] = arrayInitial[idx];
    }

    return returnValue;
} // end of MODULE_FunctionOne()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! [Description of MODULE_FunctionTwo]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description of parameterZero]
//! \param[in]  parameterOne - [description of parameterOne]
//!
//! \return     [Description of return value]
//**************************************************************************************************
static DATA_TYPE MODULE_FunctionTwo(DATA_TYPE parameterZero,
                                    DATA_TYPE parameterOne)
{
    DATA_TYPE returnValue;

    // [Description...]
    switch (expression)
    {
        case CASE_ONE:
            caseOneCnt++;
            break;

        case CASE_TWO:
            caseTwoCnt++;
            break;

        default:
            caseDefaultCnt++;
            break;
    } // end of switch (expression)

    return returnValue;
} // end of MODULE_FunctionTwo()



//**************************************************************************************************
//! [Description of MODULE_FunctionThree]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description of parameterZero]
//! \param[in]  parameterOne - [description of parameterOne]
//! \param[out] parameterTwo - [description of parameterTwo]
//!
//! \return     [Description of return value]
//**************************************************************************************************
static DATA_TYPE MODULE_FunctionThree(DATA_TYPE parameterZero,
                                      DATA_TYPE parameterOne,
                                      DATA_TYPE parameterTwo)
{
    DATA_TYPE returnValue;

    // [Place code here]

    return returnValue;
} // end of MODULE_FunctionThree()



//****************************************** end of file *******************************************
