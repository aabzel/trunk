//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   pyramid_accel_calibration_configuration.c
//! \par    Platform
//!             Any platform
//! \par    Compatible
//!             Any processor
//! \brief  Implementation of the PYRAMID_ACCEL_CALIBRATION functionality.
//!
//! \par    Abbreviations
//!             ROM -
//!             RAM -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 11.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   PYRAMID_ACCEL_CALIBRATION
//! \brief      pyramid accel calibration ROM configuration
//! \addtogroup PYRAMID_ACCEL_CALIBRATION
//! @{
//! \file pyramid_accel_calibration_configuration.c
//! \file pyramid_accel_calibration_configuration.h
//! \file pyramid_accel_calibration_configuration_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************


// pyramid_accel_calibration configuration header
#include "pyramid_accel_calibration_configuration.h"

// general macros header
#include "general_macros.h"

// general types header
#include "general_types.h"

// pyramid accel calibration cfg header
#include "pyramid_accel_calibration_cfg.h"

// pyramid accel calibration types header
#include "pyramid_accel_calibration_types.h"



//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

//! PYRAMID ACCEL CALIB ROM one calibration measurement configuration
#define PYRAMID_ACCEL_CALIB_CONFIG_ONE_AX(NUM,A_NUM)                       \
    .A##A_NUM ={                                                           \
               .dx=PYRAMID_ACCEL_CALIB_##NUM##_A##A_NUM##_DX,              \
               .dy=PYRAMID_ACCEL_CALIB_##NUM##_A##A_NUM##_DY,              \
               .dz=PYRAMID_ACCEL_CALIB_##NUM##_A##A_NUM##_DZ,              \
              },

//! PYRAMID ACCEL CALIB ROM one scale configuration
#define PYRAMID_ACCEL_CALIB_CONFIG_ONE_SCALE(NUM)                  \
    .Scale={                                                       \
            .dx=PYRAMID_ACCEL_CALIB_##NUM##_SCALE_DX,              \
            .dy=PYRAMID_ACCEL_CALIB_##NUM##_SCALE_DY,              \
            .dz=PYRAMID_ACCEL_CALIB_##NUM##_SCALE_DZ,              \
           },

//! PYRAMID ACCEL CALIB ROM one offset configuration
#define PYRAMID_ACCEL_CALIB_CONFIG_ONE_OFFSET(NUM)                 \
    .Offset={                                                      \
            .dx=PYRAMID_ACCEL_CALIB_##NUM##_OFFSET_DX,             \
            .dy=PYRAMID_ACCEL_CALIB_##NUM##_OFFSET_DY,             \
            .dz=PYRAMID_ACCEL_CALIB_##NUM##_OFFSET_DZ,             \
            },

//! PYRAMID ACCEL CALIB ROM one configuration
#define PYRAMID_ACCEL_CALIB_CONFIG_ONE(NUM)                        \
    {                                                              \
         PYRAMID_ACCEL_CALIB_CONFIG_ONE_AX(NUM,1)                  \
         PYRAMID_ACCEL_CALIB_CONFIG_ONE_AX(NUM,2)                  \
         PYRAMID_ACCEL_CALIB_CONFIG_ONE_SCALE(NUM)                 \
         PYRAMID_ACCEL_CALIB_CONFIG_ONE_OFFSET(NUM)                \
        .num = NUM,                                                \
        .name = "PYRAMID_ACCEL_CALIBYG_"#NUM,                      \
        .valid = TRUE,                                             \
    },

//! PYRAMID ACCEL CALIB ROM configurations
const PYRAMID_ACCEL_CALIB_CONFIG PYRAMID_ACCEL_CALIB_Config[] = {
#ifdef PYRAMID_ACCEL_CALIB_1_IN_USE
    PYRAMID_ACCEL_CALIB_CONFIG_ONE(1)
#endif

#ifdef PYRAMID_ACCEL_CALIB_2_IN_USE
    PYRAMID_ACCEL_CALIB_CONFIG_ONE(2)
#endif
};

//! PYRAMID ACCEL CALIB RAM nodes
PYRAMID_ACCEL_CALIB_HANDLE PYRAMID_ACCEL_CALIB_Instance[] = {
#ifdef PYRAMID_ACCEL_CALIB_1_IN_USE
    { .num = 1, .valid = TRUE, },
#endif

#ifdef PYRAMID_ACCEL_CALIB_2_IN_USE
    { .num = 2, .valid = TRUE, }
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
//! Get the number of calibration data in an assembly
//!
//! \note       None
//!
//! \return     number of calibration data sets in program
//**************************************************************************************************
U32 PYRAMID_ACCEL_CALIB_GetCnt(void)
{
    U8 cnt = 0;
    U8 cnt1 = 0;
    U8 cnt2 = 0;
    cnt1 = SIZE_OF_ARRAY(PYRAMID_ACCEL_CALIB_Config);
    cnt2 = SIZE_OF_ARRAY(PYRAMID_ACCEL_CALIB_Instance);
    if (cnt1==cnt2)
    {
        cnt = cnt1;
    }
    return cnt;
} // end of PYRAMID_ACCEL_CALIB_GetCnt()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************

//****************************************** end of file *******************************************
