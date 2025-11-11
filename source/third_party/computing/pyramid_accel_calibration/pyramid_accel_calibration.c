//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   pyramid_accel_calibration.c
//! \par    Platform
//!             Any platform
//! \par    Compatible
//!             Any CPU
//! \brief  Implementation of the PYRAMID_ACCEL_CALIBRATION functionality.
//!             This software component implements accelerometer calibration using the pyramid
//!             method. This algorithm requires only two measurements.
//!             In input literally two vectors. Just 6 numbers at the input
//!             Explore math behind in at URL  https://habr.com/ru/articles/858874
//!                                            https://habr.com/ru/articles/858354
//! \par    Abbreviations
//!             CPU - Central processing unit
//!             API - application programming interface
//!             RAM - Random Access Memory
//!             ROM - Read-only memory
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 11.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   PYRAMID_ACCEL_CALIBRATION Name of Module
//! \brief      Short description of Module
//! \addtogroup PYRAMID_ACCEL_CALIBRATION
//! @{
//! \file pyramid_accel_calibration.c
//! \file pyramid_accel_calibration.h
//! \file pyramid_accel_calibration_configuration.c
//! \file pyramid_accel_calibration_configuration.h
//! \file pyramid_accel_calibration_diagnostic.c
//! \file pyramid_accel_calibration_diagnostic.h
//! \file pyramid_accel_calibration_constants.h
//! \file pyramid_accel_calibration_dependencies.h
//! \file pyramid_accel_calibration_types.h
//! \file pyramid_accel_calibration_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// header for sqrtf
#include <math.h>

// Get pyramid accel calibration API
#include "pyramid_accel_calibration.h"

// Get general macros
#include "general_macros.h"

// Get vector header
#include "vector.h"

// Get pyramid accel calibration configuration
#include "pyramid_accel_calibration_configuration.h"


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

//! \brief PYRAMID ACCEL CALIB init one instance
static STD_RESULT PYRAMID_ACCEL_CALIB_InitOne(const U8 num);

//! \brief PYRAMID ACCEL CALIB de init one instance
static STD_RESULT PYRAMID_ACCEL_CALIB_DeInitOne(const U8 num);



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! PYRAMID_ACCEL_CALIB init all instances
//!
//! \note       None
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT PYRAMID_ACCEL_CALIB_Init(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32 ok = 0;
    U32 num = 0;
    U32 cnt = PYRAMID_ACCEL_CALIB_GetCnt();
    for(num = 0; num <= cnt; num++)
    {
        ret = PYRAMID_ACCEL_CALIB_InitOne(num);
        if (RESULT_OK==ret)
        {
            ok++;
        }
    } // end of for(num = 0; num <= cnt; num++)

    if (ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of PYRAMID_ACCEL_CALIB_Init()

//**************************************************************************************************
//! PYRAMID_ACCEL_CALIB de init all instances
//!
//! \note       None
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT PYRAMID_ACCEL_CALIB_DeInit(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32 ok = 0;
    U32 num = 0;
    U32 cnt = PYRAMID_ACCEL_CALIB_GetCnt();
    for(num = 0; num <= cnt; num++)
    {
        ret = PYRAMID_ACCEL_CALIB_DeInitOne(num);
        if (RESULT_OK==ret)
        {
            ok++;
        }
    } // end of for(num = 0; num <= cnt; num++)

    if (ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of PYRAMID_ACCEL_CALIB_DeInit()

//**************************************************************************************************
//! Get ROM node
//!
//! \note       None
//!
//! \param[in]  num - calibration data serial natural number
//!
//! \return     ROM node
//**************************************************************************************************
const PYRAMID_ACCEL_CALIB_CONFIG* PYRAMID_ACCEL_CALIB_GetConfig(const U8 num)
{
    const PYRAMID_ACCEL_CALIB_CONFIG* Config = NULL_PTR;
    U32 i = 0;
    U32 cnt = PYRAMID_ACCEL_CALIB_GetCnt();
    for(i = 0; i < cnt; i++)
    {
        if (num == PYRAMID_ACCEL_CALIB_Config[i].num)
        {
            if (PYRAMID_ACCEL_CALIB_Config[i].valid)
            {
                Config = &PYRAMID_ACCEL_CALIB_Config[i];
                break;
            }
        } // end of if (num == PYRAMID_ACCEL_CALIB_Config[i].num)
    } // end of for(i = 0; i < cnt; i++)
    return Config;
} // end of PYRAMID_ACCEL_CALIB_GetConfig()

//**************************************************************************************************
//! Get a RAM node of the calibration data
//!
//! \note       None
//!
//! \param[in]  num - calibration data serial natural number
//!
//! \return     RAM node
//**************************************************************************************************
PYRAMID_ACCEL_CALIB_HANDLE* PYRAMID_ACCEL_CALIB_GetNode(const U8 num)
{
    PYRAMID_ACCEL_CALIB_HANDLE* Node = NULL_PTR;
    U32 i = 0;
    U32 cnt = PYRAMID_ACCEL_CALIB_GetCnt();
    for(i = 0; i < cnt; i++)
    {
        if (num == PYRAMID_ACCEL_CALIB_Instance[i].num)
        {
            if (PYRAMID_ACCEL_CALIB_Instance[i].valid)
            {
                Node = &PYRAMID_ACCEL_CALIB_Instance[i];
                break;
            }
        } // end of if (num == PYRAMID_ACCEL_CALIB_Instance[i].num)
    } // end of for(i = 0; i < cnt; i++)
    return Node;
} // end of PYRAMID_ACCEL_CALIB_GetNode()

//**************************************************************************************************
//! Calculate calibration coefficients
//!
//! \note       None
//!
//! \param[in]  Node - RAM node
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT PYRAMID_ACCEL_CALIB_Calc(PYRAMID_ACCEL_CALIB_HANDLE* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Node)
    {
        FLOAT32 abs1 = VECTOR_CalcNormF(&Node->A1);
        if (0.0 < abs1)
        {
            FLOAT32 abs2 = VECTOR_CalcNormF(&Node->A2);
            if (0.0 < abs2)
            {
                ret = RESULT_OK;
            }
        } // end of if (0.0 < abs1)
    } // end of if (Node)

    if (RESULT_OK==ret)
    {
        FLOAT32 splitCoeff = 1.0 / sqrtf(3.0);
        Node->Scale.dx = 2.0 * splitCoeff / (Node->A1.dx - Node->A2.dx);
        Node->Scale.dy = 2.0 * splitCoeff / (Node->A1.dy - Node->A2.dy);
        Node->Scale.dz = -2.0 * splitCoeff / (Node->A1.dz - Node->A2.dz);

        Node->Offset.dx = splitCoeff * (Node->A1.dx + Node->A2.dx) / (Node->A2.dx - Node->A1.dx);
        Node->Offset.dy = splitCoeff * (Node->A1.dy + Node->A2.dy) / (Node->A2.dy - Node->A1.dy);
        Node->Offset.dz = splitCoeff * (Node->A1.dz + Node->A2.dz) / (Node->A1.dz - Node->A2.dz);
    } // end of if (RESULT_OK==ret)
    return ret;
} // end of PYRAMID_ACCEL_CALIB_Calc()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! PYRAMID ACCEL CALIB init one instance
//!
//! \note       None
//!
//! \param[in]  num - calibration data instance serial natural number
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static STD_RESULT PYRAMID_ACCEL_CALIB_InitOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const PYRAMID_ACCEL_CALIB_CONFIG* Config = PYRAMID_ACCEL_CALIB_GetConfig(num);
    if (Config)
    {
        PYRAMID_ACCEL_CALIB_HANDLE* Node = PYRAMID_ACCEL_CALIB_GetNode(num);
        if (Node)
        {
            Node->A1 = Config->A1;
            Node->A2 = Config->A2;
            Node->num = Config->num;
            Node->Offset = Config->Offset;
            Node->Scale = Config->Scale;
            Node->name = Config->name;
            ret = PYRAMID_ACCEL_CALIB_Calc(Node);
            Node->valid = TRUE;
            Node->init = TRUE;
            Node->deInit = FALSE;
        } // end of if (Node)
    } // end of if (Config)
    return ret;
} // end of PYRAMID_ACCEL_CALIB_InitOne()

//**************************************************************************************************
//! PYRAMID ACCEL CALIB de init one instance
//!
//! \note       None
//!
//! \param[in]  num - calibration data instance serial natural number
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static STD_RESULT PYRAMID_ACCEL_CALIB_DeInitOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    PYRAMID_ACCEL_CALIB_HANDLE* Node = PYRAMID_ACCEL_CALIB_GetNode(num);
    if (Node)
    {
        Node->deInit = TRUE;
    } // end of if (Node)
    return ret;
} // end of PYRAMID_ACCEL_CALIB_DeInitOne()

//****************************************** end of file *******************************************
