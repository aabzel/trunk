//**************************************************************************************************
// @Module  DDS
//! \file   dds_types.h
//! \brief  Types of the Direct Digital Synthesis module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef DDS_TYPES_H
#define DDS_TYPES_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "dds_constants.h"
#include "platform.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! DDS Sample type
typedef S16 DDS_SAMPLE_TYPE;

//! DDS common variable for RAM and ROM nodes
#define DDS_COMMON_VARIABLE           \
    U8                 num;           \
    U8                 valid;         \
    FLOAT32            phaseMs;       \
    FLOAT32            dutyCycle;     \
    FLOAT32            frequency;     \
    FLOAT32            frequency2;    \
    DDS_SAMPLE_TYPE    amplitude;     \
    DDS_SAMPLE_TYPE    offset;        \
    DDS_SAMPLE_TYPE*   txSampleArray; \
    U32                arraySize;     \
    DDS_PLAYER         player;        \
    DDS_SIGNAL         ddsSignal;     \
    U32                framePerSec;   \
    U8                 sampleBitness; \
    DDS_SAMPLE_PATTERN samplePattern; \
    char*              name;

//! DDS ROM configuration
typedef struct
{
    DDS_COMMON_VARIABLE
} DDS_CONFIG;

//! DDS RAM handle
typedef struct
{
    DDS_COMMON_VARIABLE
    //! Node state
    DDS_STATE state;
    //! play Off Time Stamp Ms
    U64       playOffTimeStampMs;
    //! play duration in ms
    U64       durationMs;
    //! sample cnt
    U32       sampleCnt;
    //! init done flag
    U8        initDone;
    //! proc on flag
    U8        procOn;
} DDS_HANDLE;

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// None



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

// None



#endif /*DDS_TYPES_H*/

//****************************************** end of file *******************************************
