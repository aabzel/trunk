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

#ifndef NVRAM_DRV_H
#define NVRAM_DRV_H

//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get data types
#include "nvram_types.h"

// Get data types
#include "general_types.h"

// Get data types
#include "nvram_set_drv.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************


//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************


//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//! \brief [Description...]
STD_RESULT NVRAM_Init(void);

//! \brief [Description...]
STD_RESULT NVRAM_DeInit(void);

//! \brief [Description...]
const NVRAM_INFO* NVRAM_GetVariableInfo(const U32 nvramId);

//! \brief [Description...]
STD_RESULT NVRAM_Proc(void);

//! \brief [Description...]
STD_RESULT NVRAM_Get(NVRAM_DATA_ID nvramId, void* const outData);

//! \brief [Description...]
STORAGE_TYPE NVRAM_GetType(NVRAM_DATA_ID id);

//! \brief [Description...]
U16 NVRAM_GetTypeLen(STORAGE_TYPE typeId);

//! \brief [Description...]
U16 NVRAM_GetRealLen(NVRAM_DATA_ID id);

//! \brief [Description...]
U32 NVRAM_GetLen(NVRAM_DATA_ID nvramId);

#endif // #ifndef MODULE_H

//****************************************** end of file *******************************************
