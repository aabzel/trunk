//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   module.h
//! \brief  Interface of the PYRAMID_ACCEL_CALIBRATION module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#ifndef PYRAMID_ACCEL_CALIBRATION_COMMANDS_H
#define PYRAMID_ACCEL_CALIBRATION_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "std_includes.h"

#ifndef HAS_CLI
#define "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#define "+HAS_DIAG"
#endif

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


bool PYRAMID_ACCEL_CALIB_Command(int32_t argc, char* argv[]);

#define PYRAMID_ACCEL_CALIBRATION_CLI                                                            \
    SHELL_CMD("pyramid_accel_calib", "epac", PYRAMID_ACCEL_CALIB_Command, "PyramidAccelCalib"),

#ifdef __cplusplus
}
#endif

#endif // #ifndef PYRAMID_ACCEL_CALIBRATION_COMMANDS_H

//****************************************** end of file *******************************************
