//**************************************************************************************************
// @Module  DDS
//! \file   dds_configiration.c
//! \par    Platform
//!             This code can work on any platform with I2S, DAC or WAV files.
//! \par    Compatible
//!             This code can work on any platform with I2S, DAC or WAV files.
//! \brief  Implementation of the DDS functionality.
//!
//! \par    Abbreviations
//!             DDS - direct digital synthesis
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   DDS Name of Module
//! \brief      Short description of Module
//! \addtogroup DDS
//! @{
//! \file dds_configiration.c
//! \file dds_configiration.h
//! \file dds_cfg.h
//! @}
//**************************************************************************************************


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "general_macros.h"
#include "general_types.h"

#include "dds_cfg.h"
#include "dds_configuration.h"


//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

// None



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

#ifdef DDS_1_IN_USE
static DDS_SAMPLE_TYPE DDS_1_StaticSampleArray[DDS_1_SAMPLE_CNT] = { 0 };
#endif

#ifdef DDS_2_IN_USE
static DDS_SAMPLE_TYPE DDS_1_StaticSampleArray[DDS_2_SAMPLE_CNT] = { 0 };
#endif

#ifdef DDS_3_IN_USE
static DDS_SAMPLE_TYPE DDS_3_StaticSampleArray[DDS_3_SAMPLE_CNT] = { 0 };
#endif

//! DDS ROM DDS_CONFIGURATION ONE
#define DDS_CONFIGURATION_ONE(NUMBER)                                 \
    {                                                                 \
        .amplitude = DDS_##NUMBER##_AMPLITUDE,                        \
        .arraySize = SIZE_OF_ARRAY(DDS_##NUMBER##_StaticSampleArray), \
        .ddsSignal = DDS_##NUMBER##_SIGNAL,                           \
        .dutyCycle = DDS_##NUMBER##_DUTY_CYCLE,                       \
        .framePerSec = DDS_##NUMBER##_FRAME_PER_SEC,                  \
        .frequency = DDS_##NUMBER##_FREQUENCY,                        \
        .name = DDS_##NUMBER##_NAME,                                  \
        .num = NUMBER,                                                \
        .offset = DDS_##NUMBER##_OFFSET,                              \
        .phaseMs = DDS_##NUMBER##_PHASE_MS,                           \
        .player = DDS_##NUMBER##_PLAYER,                              \
        .samplePattern = DDS_##NUMBER##_FRAME_PATTERN,                \
        .sampleBitness = DDS_##NUMBER##_SAMPLE_BITNESS,               \
        .txSampleArray = DDS_##NUMBER##_StaticSampleArray,            \
        .valid = TRUE,                                                \
    },

#ifdef DDS_1_IN_USE
#define DDS_CONFIGURATION_1 DDS_CONFIGURATION_ONE(1)
#else
#define DDS_CONFIGURATION_1
#endif

#ifdef DDS_2_IN_USE
#define DDS_CONFIGURATION_2 DDS_CONFIGURATION_ONE(2)
#else
#define DDS_CONFIGURATION_2
#endif

#ifdef DDS_3_IN_USE
#define DDS_CONFIGURATION_3 DDS_CONFIGURATION_ONE(3)
#else
#define DDS_CONFIGURATION_3
#endif

//! DDS ROM  CONFIGURATION ALL
#define DDS_CONFIGURATION_ALL \
    DDS_CONFIGURATION_1       \
    DDS_CONFIGURATION_2       \
    DDS_CONFIGURATION_3

//! DDS ROM Instance
const DDS_CONFIG DDS_Configuration[] = { DDS_CONFIGURATION_ALL };

//! DDS RAM Instance
DDS_HANDLE DDS_Instance[] = {
#ifdef DDS_1_IN_USE
    {
        .num = 1,
        .valid = TRUE,
    },
#endif

#ifdef DDS_2_IN_USE
    {
        .num = 2,
        .valid = TRUE,
    },
#endif

#ifdef DDS_3_IN_USE
    {
        .num = 3,
        .valid = TRUE,
    },
#endif
};

//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************

// None



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************

// None



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

// None



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

// None



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! DDS get number of configured dds instances
//!
//! \note       get number of configured dds instances
//!
//! \param[in]  None
//!
//! \return     number of configured DDS instances
//**************************************************************************************************
U32 DDS_GetCnt(void)
{
    U32 cnt = 0;
    U32 cntConf = SIZE_OF_ARRAY(DDS_Configuration);
    U32 cntInts = SIZE_OF_ARRAY(DDS_Instance);
    if (cntConf == cntInts)
    {
        cnt = cntInts;
    }
    return cnt;
}


//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************

// None



//****************************************** end of file *******************************************
