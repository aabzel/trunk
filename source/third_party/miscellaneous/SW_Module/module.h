//**************************************************************************************************
// @Module  MODULE
//! \file   module.h
//! \brief  Interface of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.XXXX |  1.1.0  |   XXX   | Last  release.
//! | XX.XX.XXXX |  1.0.0  |   XXX   | First release.
//**************************************************************************************************

#ifndef MODULE_H
#define MODULE_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get data types
#include "compiler.h"

// Get generic definitions
#include "general.h"

// Get configuration of the program module
#include "module_cfg.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! [Description...]
typedef DATA_TYPE MODULE_DATA_TYPE_ZERO;

//! [Description...]
typedef enum
{
    //! [Description of MODULE_DATA_TYPE_ONE_CONST_ZERO...]
    MODULE_DATA_TYPE_ONE_CONST_ZERO,
    //! [Description of MODULE_DATA_TYPE_ONE_CONST_ONE...]
    MODULE_DATA_TYPE_ONE_CONST_ONE,
    //! [Description of MODULE_DATA_TYPE_ONE_CONST_TWO...]
    MODULE_DATA_TYPE_ONE_CONST_TWO,
    //! [Description of MODULE_DATA_TYPE_ONE_CONST_THREE...]
    MODULE_DATA_TYPE_ONE_CONST_THREE,
} MODULE_DATA_TYPE_ONE;

//! [Description...]
typedef struct
{
    //! [Description of fieldZero...]
    DATA_TYPE fieldZero;
    //! [Description of fieldOne...]
    DATA_TYPE fieldOne;
} MODULE_DATA_TYPE_TWO;



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! [Description...]
#define MODULE_CONST_ZERO   (0x00U)

//! [Description...]
#define MODULE_CONST_ONE    (1U)



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//! [Description...]
extern DATA_TYPE MODULE_variableZero;

//! [Description...]
extern DATA_TYPE MODULE_variableOne;



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief [Description...]
extern DATA_TYPE MODULE_FunctionZero(DATA_TYPE parameterZero);

//! \brief [Description...]
extern DATA_TYPE MODULE_FunctionOne(DATA_TYPE parameterZero,
                                    DATA_TYPE parameterOne);



#endif // #ifndef MODULE_H

//****************************************** end of file *******************************************
