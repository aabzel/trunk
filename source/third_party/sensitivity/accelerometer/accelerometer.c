//**************************************************************************************************
// @Module  ACCELEROMETER
//! \file   accelerometer.c
//! \par    Platform
//!             Any PCB with and accelerometer
//! \par    Compatible
//!             Any MCU
//! \brief  Implementation of the ACCELEROMETER functionality.
//!
//! \par    Abbreviations
//!             SWC - SoftWare component
//!             MCU - microcontroller unit
//!             PCB - Printed circuit board
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

//**************************************************************************************************
//! \defgroup   ACCELEROMETER
//! \brief      Short description of Module
//! \addtogroup ACCELEROMETER
//! @{
//! \file accelerometer.c
//! \file accelerometer.h
//! \file accelerometer_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// accelerometer
#include "accelerometer.h"

// accelerometer configuration structures
#include "accelerometer_configuration.h"

// accelerometer known ASICs data base
#include "accelerometer_known_asics.h"

// miscellaneous ehal
#include "miscellaneous_ehal.h"

// miscellaneous float
#include "miscellaneous_float.h"

#ifdef PYRAMID_ACCEL_CALIB_IN_USE
// Calibration algorithm using the pyramid method
#include "pyramid_accel_calibration.h"
#endif

#ifdef ON==NVRAM_IN_USE
// nvram driver
#include "nvram_drv.h"
#endif

// software dependencies for accelerometer SWC
#include "accelerometer_dependencies.h"


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
// Declarations of local (private) functions
//**************************************************************************************************

//! \brief ACCEL init one
static STD_RESULT ACCEL_InitOne(const U8 num);

//! \brief accelerometerde init one
static STD_RESULT ACCEL_DeInitOne(const U8 num);

//! \brief accelerometerprocess one
static STD_RESULT ACCEL_ProcessOne(const U8 num);

//! \brief accelerometerread code low level
static STD_RESULT ACCEL_ReadCodeLowLevel(ACCEL_HANDLE* const Node,
                                         VECTOR_S16* const accelCode);

//! \brief ACCEL read raw low level
static STD_RESULT ACCEL_ReadRawLowLevel(ACCEL_HANDLE* const Node,
                                        VECTOR_F* const accelRaw);

static INLINE_FUN STD_RESULT ACCEL_IsValidCalibrationConfig(const ACCEL_CONFIG* const Config);

//! \brief ACCEL is valid configuration
static STD_RESULT ACCEL_IsValidConfig(const ACCEL_CONFIG* const Config);

//! \brief ACCEL Calibrate
static STD_RESULT ACCEL_Calibrate(const ACCEL_HANDLE* const Node,
                                  VECTOR_F* const accelReal);

//! \brief  Check the accelerometer calibration data for the accelerometer for correctness
static STD_RESULT ACCEL_IsValidCalibData(const ACCEL_CALIB_DATA* const Calib);

//! \brief Calculate NVRAM ID   number for this specific accelerometer
static NVRAM_DATA_ID ACCEL_NumToNvramId(const U8 accelNum);

//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************




//**************************************************************************************************
//! Accelerometer initialization procedure
//!
//! \note       None
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_Init(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32 ok = 0;
    U32 cnt = ACCEL_GetCnt();
    U8 num = 0;
    for(num = 0; num <= cnt; num++)
    {
        ret = ACCEL_InitOne(num);
        if (RESULT_OK==ret)
        {
            ok++;
        }
    }// end of for(num = 0; num <= cnt; num++)

    if (cnt==ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of ACCEL_Init()


//**************************************************************************************************
//!  De init all accelerometers
//!
//! \note       None
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_DeInit(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32 ok = 0;
    U32 cnt = ACCEL_GetCnt();
    U8 num = 0;
    for(num = 0; num <= cnt; num++)
    {
        ret = ACCEL_DeInitOne(num);
        if (RESULT_NOT_OK==ret)
        {
            ok++;
        }
    } // end of for(num = 0; num <= cnt; num++)

    if (cnt==ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of ACCEL_DeInit()

//**************************************************************************************************
//! Procedure for periodic polling of accelerometers
//!
//! \note       None
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_Process(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32 ok = 0;
    U32 cnt = ACCEL_GetCnt();
    U8 num = 0;
    for(num = 0; num <= cnt; num++)
    {
        ret = ACCEL_ProcessOne(num);
        if (RESULT_NOT_OK==ret)
        {
            ok++;
        }
    } // end of for(num = 0; num <= cnt; num++)
    if (ok)
    {
        ret = RESULT_OK;
    } else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of ACCEL_Process()

//**************************************************************************************************
//! Get accelerometer RAM node
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//!
//! \return     accelerometer RAM node
//**************************************************************************************************
ACCEL_HANDLE* ACCEL_GetNode(const U8 num)
{
    ACCEL_HANDLE* Node = NULL_PTR;
    U32 i = 0;
    U32 cnt = ACCEL_GetCnt();
    for(i = 0; i < cnt; i++)
    {
        if (num == ACCEL_Instance[i].num)
        {
            if (ACCEL_Instance[i].valid)
            {
                Node = &ACCEL_Instance[i];
                break;
            }
        } // end of if (num == ACCEL_Instance[i].num)
    } // end of for(i = 0; i < cnt; i++)
    return Node;
} // end of ACCEL_GetNode()

//**************************************************************************************************
//! get accelerometer ROM node configuration
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//!
//! \return     accelerometerROM node configuration
//**************************************************************************************************
const ACCEL_CONFIG* ACCEL_GetConfig(const U8 num)
{
    const ACCEL_CONFIG* Config = NULL_PTR;
    U32 cnt = ACCEL_GetCnt();
    U32 i = 0;
    for(i = 0; i < cnt; i++)
    {
        if (num == ACCEL_Config[i].num)
        {
            if (ACCEL_Config[i].valid)
            {
                Config = &ACCEL_Config[i];
                break;
            }
        } // end of if (num == ACCEL_Config[i].num)
    } // end of for(i = 0; i < cnt; i++)
    return Config;
} // end of ACCEL_GetConfig()


//**************************************************************************************************
//! Read the latest sample of real acceleration
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//! \param[in]  accelReal - sample of real acceleration
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_Read(const U8 num,
                      VECTOR_F* const accelReal)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Node = ACCEL_GetNode(num);
    if (NULL_PTR!= Node)
    {
        ret = ACCEL_ReadRawLowLevel(Node, accelReal);
        if (RESULT_OK == ret)
        {
            ret = ACCEL_Calibrate(Node, accelReal);
        }
    } // end of if (NULL_PTR!= Node)
    return ret;
} // end of ACCEL_Read()

//**************************************************************************************************
//! Read the accelerometer ADC code
//!
//! \note       None
//!
//! \param[in]   num - accelerometer logical number on the PCB
//! \param[out]  accelCode - accelerometer ADC integer value
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_ReadCode(const U8 num,
                          VECTOR_S16* const accelCode)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Node = ACCEL_GetNode(num);
    if (NULL_PTR!= Node)
    {
        ret = ACCEL_ReadCodeLowLevel(Node, &Node->adcCode);
        if (RESULT_OK == ret)
        {
            *accelCode = Node->adcCode;
        }
    } // end of if (NULL_PTR!= Node)
    return ret;
} // end of ACCEL_ReadCode()

//**************************************************************************************************
//! set accelerometer axis offset
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//! \param[in]  AxisOffset - accelerometer offset vector
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_SetAxisOffset(const U8 num,
                               const VECTOR_F* const AxisOffset)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Node = ACCEL_GetNode(num);
    if (NULL_PTR!= Node)
    {
        Node->offset = *AxisOffset;
    }
    return ret;
} // end of ACCEL_SetAxisOffset()

//**************************************************************************************************
//! set accelerometer axis scale
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//! \param[in]  axisScale - axis scale vector
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_SetAxisScale(const U8 num,
                              const VECTOR_F* const axisScale)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Node = ACCEL_GetNode(num);
    if (NULL_PTR!= Node)
    {
        Node->scale = *axisScale;
    }
    return ret;
} // end of ACCEL_SetAxisScale()

//**************************************************************************************************
//! Apply calibration calculated by pyramid method
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//! \param[in]  calibNum - pyramidal calibration set logical number
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_DeployPyramidCalib(const U8 num,
                                    const U8 calibNum)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Accel = ACCEL_GetNode(num);
    if (NULL_PTR != Accel)
    {
#ifdef PYRAMID_ACCEL_CALIB_IN_USE
        PYRAMID_ACCEL_CALIB_HANDLE* Calib = PYRAMID_ACCEL_CALIB_GetNode(calibNum);
        if (NULL_PTR != Calib)
        {
            ret = ACCEL_SetAxisOffset(num, (VECTOR_F*) &Calib->Offset);
            if (RESULT_OK==ret)
            {
                ret = ACCEL_SetAxisScale( num, (VECTOR_F*) &Calib->Scale);
            }
        } // end of if (NULL_PTR != Calib)
#endif
    } // end of if (NULL_PTR != Accel)
    return ret;
} // end of ACCEL_DeployPyramidCalib()

//**************************************************************************************************
//! Save calibration data
//!
//! \note       None
//!
//! \param[in]  accelNum - accelerometer logical number on the PCB
//! \param[in]  Calibration - calibration data for accelerometer
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT ACCEL_SaveCalibData(const U8 accelNum,
                               const ACCEL_CALIB_DATA* const Calibration)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = ACCEL_IsValidCalibData(Calibration);
    if (RESULT_OK==ret)
    {
        ret = RESULT_NOT_OK;
#ifdef ON==NVRAM_IN_USE
        NVRAM_DATA_ID nvramId = ACCEL_NumToNvramId(accelNum);
        ret = NVRAM_Set(nvramId,Calibration);
#endif
    } // end of if (RESULT_OK==ret)
    return ret;
} // end of ACCEL_SaveCalibData()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! accel init one
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_InitOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const ACCEL_CONFIG* Config = ACCEL_GetConfig(num);
    if (NULL_PTR != Config)
    {
        ret = ACCEL_IsValidConfig(Config);
        if (RESULT_OK==ret)
        {
            ACCEL_HANDLE* Node = ACCEL_GetNode(num);
            if (NULL_PTR!= Node)
            {
                Node->accelNum = Config->accelNum;
                Node->accelPhy = Config->accelPhy;
                Node->name = Config->name;
                Node->offset = Config->offset;
                Node->precision = Config->precision;
                Node->scale = Config->scale;
#ifdef ON==NVRAM_IN_USE
                ACCEL_CALIB_DATA Calibration = {0};
                NVRAM_DATA_ID nvramId = ACCEL_NumToNvramId(num);
                ret = NVRAM_Get(nvramId, &Calibration);
                if (RESULT_OK==ret)
                {
                    Node->offset = Calibration.offset;
                    Node->scale = Calibration.scale;
                }
#endif

                Node->valid = TRUE;
                ret = RESULT_OK;
            } // end of if (NULL_PTR!= Node)
        } // end of if (RESULT_OK==ret)
    } // end of if (NULL_PTR != Config)

    return ret;
} // end of ACCEL_InitOne()

//**************************************************************************************************
//! deactivate accelerometer by its logical number
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_DeInitOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Node = ACCEL_GetNode(num);
    if (NULL_PTR!= Node)
    {
        Node->deInit = TRUE;
        ret = RESULT_OK;
    }

    return ret;
} // end of ACCEL_DeInitOne()

//**************************************************************************************************
//! poll accelerometer by number
//!
//! \note       None
//!
//! \param[in]  num - accelerometer logical number on the PCB
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_ProcessOne(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_HANDLE* Node = ACCEL_GetNode(num);
    if (NULL_PTR != Node)
    {
        ret = ACCEL_Read(num, &Node->Acceleration);
    }
    return ret;
} // end of ACCEL_ProcessOne()

//**************************************************************************************************
//! Get accelerometer raw ADC data
//!
//! \note       None
//!
//! \param[in]  Node - acceleration RAM node
//! \param[in]  accelCode - accelerometer integer sample
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_ReadCodeLowLevel(ACCEL_HANDLE* const Node,
                                                    VECTOR_S16* const accelCode)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch(Node->accelPhy)
    {
#ifdef LIS3DH_IN_USE
        case ACCELEROMETER_PHY_LIS3DH:
        {
            ret = LIS3DH_ReadCode(Node->accelNum,(VECTOR_S16*) accelCode);
        } break;
#endif

#ifdef QMA6100P_IN_USE
        case ACCELEROMETER_PHY_QMA6100P:
        {
            ret = QMA6100P_ReadCode(Node->accelNum, (VECTOR_S16*) accelCode);
        } break;
#endif

    default:
        ret = RESULT_NOT_OK;
        break;
    } // end of switch(Node->accelPhy)

    return ret;
} // end of ACCEL_ReadCodeLowLevel()

//**************************************************************************************************
//! read accelerometer raw g vector low level
//!
//! \note       None
//!
//! \param[in]  Node - acceleration RAM node
//! \param[out] accelRaw - accelerometer raw g vector
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_ReadRawLowLevel(ACCEL_HANDLE* const Node,
                                                   VECTOR_F* const accelRaw)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch(Node->accelPhy)
    {
#ifdef LIS3DH_IN_USE
        case ACCELEROMETER_PHY_LIS3DH:
        {
            ret = LIS3DH_ReadAcceleration(Node->accelNum,(VECTOR_F*) &Node->Acceleration);
        } break;
#endif

#ifdef QMA6100P_IN_USE
        case ACCELEROMETER_PHY_QMA6100P:
        {
            ret = QMA6100P_ReadAcceleration(Node->accelNum, (VECTOR_F*) &Node->Acceleration);
        } break;
#endif

    default:
        ret = RESULT_NOT_OK;
        break;
    } // end of switch(Node->accelPhy)

    if (RESULT_OK==ret)
    {
        if (accelRaw)
        {
            *accelRaw = Node->Acceleration;
        }
    } // end of if (RESULT_OK==ret)

    return ret;
} // end of ACCEL_ReadRawLowLevel()

//**************************************************************************************************
//! Check the configuration for the accelerometer
//!
//! \note       None
//!
//! \param[in]  Config - accelerometer ROM configuration node
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_IsValidCalibrationConfig(const ACCEL_CONFIG* const Config)
{
    STD_RESULT ret = RESULT_OK;
    if (RESULT_OK==ret)
    {
        ret = FLOAT_IsEqualAbsolute(1.0, Config->scale.dx, 0.3);
    }

    if (RESULT_OK==ret)
    {
        ret = FLOAT_IsEqualAbsolute(1.0, Config->scale.dy, 0.3);
    }

    if (RESULT_OK==ret)
    {
        ret = FLOAT_IsEqualAbsolute(1.0, Config->scale.dz, 0.3);
    }

    if (RESULT_OK==ret)
    {
        ret = FLOAT_IsEqualAbsolute(0.0, Config->offset.dx, 0.4);
    }

    if (RESULT_OK==ret)
    {
        ret = FLOAT_IsEqualAbsolute(0.0, Config->offset.dy, 0.4);
    }

    if (RESULT_OK==ret)
    {
        ret = FLOAT_IsEqualAbsolute(0.0, Config->offset.dz, 0.4);
    }
    return ret;
} // end of ACCEL_IsValidCalibrationConfig()

//**************************************************************************************************
//! ACCEL is valid configuration
//!
//! \note       None
//!
//! \param[in]  Config - accelerometerROM configuration node
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_IsValidConfig(const ACCEL_CONFIG* const Config)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Config)
    {
        if (Config->accelPhy)
        {
            ret = RESULT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        ret = ACCEL_IsValidCalibrationConfig(Config);
    }
    return ret;
} // end of ACCEL_IsValidConfig()

//**************************************************************************************************
//! Calibrate one acceleration sample
//!
//! \note       None
//!
//! \param[in]     Node - acceleration RAM node
//! \param[inout]  accelReal - acceleration sample
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static INLINE_FUN STD_RESULT ACCEL_Calibrate(const ACCEL_HANDLE* const Node,
                                             VECTOR_F* const accelReal)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (NULL_PTR!= Node)
    {
        accelReal->dx = (Node->scale.dx * accelReal->dx) + Node->offset.dx;
        accelReal->dy = (Node->scale.dy * accelReal->dy) + Node->offset.dy;
        accelReal->dz = (Node->scale.dz * accelReal->dz) + Node->offset.dz;
        ret = RESULT_OK;
    }
    return ret;
} // end of ACCEL_Calibrate()

//**************************************************************************************************
//! check the accelerometer calibration data for the accelerometer for correctness
//!
//! \note       None
//!
//! \param[in]  Calib - calibration data for accelerometer
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static STD_RESULT ACCEL_IsValidCalibData(const ACCEL_CALIB_DATA* const Calib)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Calib)
    {
        U32 okCnt = 0;
        UpdateOkCnt(FLOAT_IsEqualAbsolute(1.0, Calib->scale.dx, 0.3), &okCnt ) ;
        UpdateOkCnt(FLOAT_IsEqualAbsolute(1.0, Calib->scale.dy, 0.3), &okCnt ) ;
        UpdateOkCnt(FLOAT_IsEqualAbsolute(1.0, Calib->scale.dz, 0.3), &okCnt ) ;

        UpdateOkCnt(FLOAT_IsEqualAbsolute(0.0, Calib->offset.dx, 0.4), &okCnt );
        UpdateOkCnt(FLOAT_IsEqualAbsolute(0.0, Calib->offset.dy, 0.4), &okCnt )  ;
        UpdateOkCnt(FLOAT_IsEqualAbsolute(0.0, Calib->offset.dz, 0.4), &okCnt ) ;

        if (6==okCnt)
        {
            ret = RESULT_OK;
        }else
		{
            ret = RESULT_NOT_OK;
        }
    }
    return ret;
} // end of ACCEL_IsValidCalibData()

#ifdef NVRAM_IN_USE
//**************************************************************************************************
//! Calculate NVRAM ID   number for this specific accelerometer
//!
//! \note       None
//!
//! \param[in]  accelNum - accelerometer logical number on the PCB
//!
//! \return     accelerometer  NVRAM ID number
//**************************************************************************************************
static  NVRAM_DATA_ID ACCEL_NumToNvramId(const U8 accelNum)
{
    NVRAM_DATA_ID nvramId = 0;
    switch(accelNum)
    {
        case 1: nvramId = NVRAM_ID_ACCEL_CALIB1; break;
        case 2: nvramId = NVRAM_ID_ACCEL_CALIB2; break;
        default: nvramId = NVRAM_ID_UNDEF; break;
    }
    return nvramId;
} // end of ACCEL_NumToNvramId()
#endif

//****************************************** end of file *******************************************
