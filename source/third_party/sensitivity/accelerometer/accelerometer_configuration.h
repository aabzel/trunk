//**************************************************************************************************
// @Module  ACCELEROMETER
//! \file   accelerometer_configuration.h
//! \brief  Interface of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef ACCEL_CONFIG_H
#define ACCEL_CONFIG_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Get data types
#include "accelerometer_type.h"

// Get data types
#include "accelerometer_cfg.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//! Array of logical accelerometer ROM configurations
extern const ACCEL_CONFIG ACCEL_Config[ ];

//! Array of logical accelerometer RAM nodes
extern ACCEL_HANDLE ACCEL_Instance[ ];

//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief Get the number of accelerometers on the board
extern U32 ACCEL_GetCnt(void);

#endif // #ifndef MODULE_H

//****************************************** end of file *******************************************
