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


#ifndef NVRAM_EHAL_TYPES_H
#define NVRAM_EHAL_TYPES_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************


#include "platform.h"
#include "nvram_file_ids.h"
#include "nvram_constants.h"
#include "std_includes.h"
#include "storage_constants.h"
#include "system_constants.h"

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif


//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************


typedef struct {
    /*char* units*/
    /*char* fasility (software component)*/
    NVRAM_DATA_ID id;
    U16 len;
    U32 eepromAddress;
    STORAGE_TYPE type;
    char* defaultValue;
    char* name;
} NVRAM_INFO;

typedef struct {
    STORAGE_TYPE type;
    U16 len;
} NvramTypeSize_t;

typedef const char* (*NvramBinaryToStrFun_t)(const void*  const memory);

typedef struct {
    U8 valid;
    NVRAM_DATA_ID id;
    NvramBinaryToStrFun_t BinaryToStrFun;
} NvramInterpreter_t;


//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************


//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


#endif // #ifndef NVRAM_EHAL_TYPES_H

//****************************************** end of file *******************************************
