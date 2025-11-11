//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   pyramid_accel_calibration_types.h
//! \brief  Types of the PYRAMID_ACCEL_CALIBRATION module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 11.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef PYRAMID_ACCEL_CALIBRATION_TYPES_H
#define PYRAMID_ACCEL_CALIBRATION_TYPES_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Get pyramid accel calibration constants
#include "pyramid_accel_calibration_constants.h"

// Get vector data types
#include "vector_type.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! pyramid accel calibration common EHAL VARIABLES
#define PYRAMID_ACCEL_CALIBRATION_COMMON_EHAL_VARIABLES  \
    VECTOR_F A1;                                         \
    VECTOR_F A2;                                         \
    VECTOR_F Offset;                                     \
    VECTOR_F Scale;                                      \
    U8 num;                                              \
    char* name;                                          \
    U8 valid;

//! PYRAMID ACCEL CALIB config ROM type
typedef struct {
    PYRAMID_ACCEL_CALIBRATION_COMMON_EHAL_VARIABLES
}PYRAMID_ACCEL_CALIB_CONFIG;

//! PYRAMID ACCEL CALIB item RAM type
typedef struct {
    PYRAMID_ACCEL_CALIBRATION_COMMON_EHAL_VARIABLES
    U8 init;
    U8 deInit;
}PYRAMID_ACCEL_CALIB_HANDLE;



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************


//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************



#endif // #ifndef PYRAMID_ACCEL_CALIBRATION_TYPES_H

//****************************************** end of file *******************************************
