//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   pyramid_accel_calibration.h
//! \brief  Interface of the PYRAMID_ACCEL_CALIBRATION module.
//!             This software component implements accelerometer calibration using the pyramid
//!             method. This algorithm requires only two measurements.
//!             In input literally two vectors. Just 6 numbers at the input
//!             Explore math behind in at URL  https://habr.com/ru/articles/858874
//!                                            https://habr.com/ru/articles/858354
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef PYRAMID_ACCEL_CALIBRATION_H
#define PYRAMID_ACCEL_CALIBRATION_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Get general data types
#include "general_types.h"

// Get pyramid accel calibration data types
#include "pyramid_accel_calibration_types.h"



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

//! \brief PYRAMID ACCEL CALIB Init
extern STD_RESULT PYRAMID_ACCEL_CALIB_Init(void);

//! \brief PYRAMID ACCEL CALIB DeInit
extern STD_RESULT PYRAMID_ACCEL_CALIB_DeInit(void);

//! \brief PYRAMID ACCEL CALIB Get ROM Config
extern const PYRAMID_ACCEL_CALIB_CONFIG* PYRAMID_ACCEL_CALIB_GetConfig(const U8 num);

//! \brief PYRAMID ACCEL CALIB Get RAM Node
extern PYRAMID_ACCEL_CALIB_HANDLE* PYRAMID_ACCEL_CALIB_GetNode(const U8 num);

//! \brief PYRAMID ACCEL CALIB Calculate calibration data (offset and scale)
extern STD_RESULT PYRAMID_ACCEL_CALIB_Calc(PYRAMID_ACCEL_CALIB_HANDLE* const Node);

#endif // #ifndef PYRAMID_ACCEL_CALIBRATION_H

//****************************************** end of file *******************************************
