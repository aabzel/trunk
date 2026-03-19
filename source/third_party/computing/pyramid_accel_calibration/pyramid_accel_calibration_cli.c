//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   module.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_PYRAMID_ACCEL_CALIBRATION
//! \brief  Implementation of the PYRAMID_ACCEL_CALIBRATION functionality.
//!             [text]
//! \par    Abbreviations
//!             ABBR0 -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.2024 |  1.1.0  |   AAB   | Last  release.
//! | XX.XX.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************


//**************************************************************************************************
//! \defgroup   PYRAMID_ACCEL_CALIBRATION Name of Module
//! \brief      Short description of Module
//! \addtogroup PYRAMID_ACCEL_CALIBRATION
//! @{
//! \file module.c
//! \file module.h
//! \file module_cfg.h
//! @}
//**************************************************************************************************


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "pyramid_accel_calibration_cli.h"

#include "convert.h"
#include "log.h"
#include "num_to_str.h"
#include "mcal_to_ehal.h"
#include "pyramid_accel_calibration.h"
#include "vector_cli.h"

#ifdef PYRAMID_ACCEL_CALIBRATION_DIAG_IN_USE
#include "pyramid_accel_calibration_diagnostic.h"
#endif


//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

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
//! [Description of PYRAMID_ACCEL_CALIBRATION_FunctionOne]
//!
//! \note       epac 1 0.577 0.577 -0.577    -0.577 -0.577 0.577
//!
//! \param[in]  parameterZero - [description...]
//! \param[out] parameterOne - [description...]
//!
//! \return     [Description of return value]
//**************************************************************************************************
bool PYRAMID_ACCEL_CALIB_Command(int32_t argc, char* argv[]) {
    bool res = false;
    STD_RESULT ret = RESULT_NOT_OK;

    PYRAMID_ACCEL_CALIB_HANDLE Calib = {0};

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &Calib.num);
        if (false == res) {
            LOG_ERROR(PYRAMID_ACCEL_CALIBRATION, "ParseErr [%s]", argv[0]);
        }
    }

    ret = VECTOR_ReadVfromCli(argc, argv, 1, &Calib.A1);
    if (RESULT_OK==ret)
    {
        ret = VECTOR_ReadVfromCli(  argc,   argv, 4, &Calib.A2);
    }

    if (RESULT_OK==ret)
    {
        ret = PYRAMID_ACCEL_CALIB_Calc(&Calib);
        log_res(PYRAMID_ACCEL_CALIBRATION, res, "AccelCalib");
        res = EHAL_RetToRes(ret);
        if (res) {
            LOG_INFO(PYRAMID_ACCEL_CALIBRATION, "%s", PYRAMID_ACCEL_CALIB_ToStr(&Calib));
        }
    } else {
        LOG_ERROR(PYRAMID_ACCEL_CALIBRATION, "Usage: epac A1 A1");
    }

    return res;
} // end of MODULE_FunctionZero()

//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************

//****************************************** end of file *******************************************
