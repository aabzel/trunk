//**************************************************************************************************
// @Module  ACCELEROMETER
//! \file   accelerometer_configuration.c
//! \par    Platform
//!             Any platform with accelerometer
//! \par    Compatible
//!             Any PCB with accelerometer
//! \brief  Main configuration structure of accelerometer
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   ACCELEROMETER
//! \brief      Short description of ACCELEROMETER
//! \addtogroup ACCELEROMETER
//! @{
//! \file accelerometer_configuration.c
//! \file accelerometer_configuration.h
//! \file accelerometer_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Native header
#include "general_macros.h"

// Native header
#include "general_types.h"

// Native header
#include "accelerometer_configuration.h"



//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

#define ACCEL_DEFAULT_CALIBRATION          \
     .scale = {.dx = 1.0, .dy = 1.0, .dz = 1.0},   \
     .offset = {.dx = 0.0, .dy = 0.0, .dz = 0.0},


#define ACCEL_CONFIG_ONE(NUM)                           \
    {                                                   \
     .num = NUM,                                        \
     .accelPhy = ACCELEROMETER_##NUM##_PHY,             \
     .accelNum = ACCELEROMETER_##NUM##_PHY_NUM,         \
      ACCEL_DEFAULT_CALIBRATION                         \
     .name = ACCELEROMETER_##NUM##_NAME,                \
     .precision = ACCELEROMETER_##NUM##_PRECISION,      \
     .valid = TRUE,                                     \
    },


const ACCEL_CONFIG ACCEL_Config[ ] = {
#ifdef ACCELEROMETER_1_IN_USE
    ACCEL_CONFIG_ONE(1)
#endif

#ifdef ACCELEROMETER_2_IN_USE
    ACCEL_CONFIG_ONE(2)
#endif
};

ACCEL_HANDLE ACCEL_Instance[ ] = {
#ifdef ACCELEROMETER_1_IN_USE
    {.num = 1, .valid = TRUE,},
#endif

#ifdef ACCELEROMETER_2_IN_USE
    {.num = 2, .valid = TRUE,},
#endif
};


//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************



//**************************************************************************************************
// Definitions of static global (private) variables
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
//! Get the number of accelerometers on the board
//!
//! \note       None
//!
//! \return     number of accelerometers on the board
//**************************************************************************************************
U32 ACCEL_GetCnt(void) {
    U32 cnt = 0;
    U32 cnt1 = 0;
    U32 cnt2 = 0;
    cnt1 = SIZE_OF_ARRAY(ACCEL_Instance);
    cnt2 = SIZE_OF_ARRAY(ACCEL_Config);
    if(cnt1==cnt2)
    {
        cnt = cnt1;
    }
    return cnt;
} // end of ACCELEROMETER_FunctionThree()


//****************************************** end of file *******************************************
