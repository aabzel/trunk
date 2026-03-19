//**************************************************************************************************
// @Module  DDS
//! \file   dds_constants.h
//! \brief  Constants of the DDS module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef DDS_CONSTANTS_H
#define DDS_CONSTANTS_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "dds_dependencies.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//None



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************


//! DDS STATIC CHANNEL CNT
#define DDS_STATIC_CHANNEL_CNT 100

//! DDS procces period us
#define DDS_POLL_PERIOD_US 1000

//! DDS_signal
typedef enum
{
    DDS_SIGNAL_STATIC = 0U,
    DDS_SIGNAL_PWM = 1U,
    DDS_SIGNAL_SIN = 2U,
    DDS_SIGNAL_SAW = 3U,
    DDS_SIGNAL_FENCE = 4U,
    DDS_SIGNAL_PULSE_TRAIN = 5U,
    DDS_SIGNAL_CHIRP = 6U,
    DDS_SIGNAL_DTMF = 7U,
    DDS_SIGNAL_UNDEF = 8U
} DDS_SIGNAL;

//! DDS state
typedef enum
{
    DDS_MODE_PLAY = 1,
    DDS_MODE_IDLE = 2,

    DDS_MODE_UNDEF = 0,
} DDS_STATE;

//! DDS PLAYER
typedef enum
{
    DDS_PLAY_ON_I2S0 = 0U,
    DDS_PLAY_ON_I2S1 = 1U,
    DDS_PLAY_ON_I2S2 = 2U,
    DDS_PLAY_ON_I2S3 = 3U,
    DDS_PLAY_ON_I2S4 = 4U,
    DDS_PLAY_ON_I2S5 = 5U,
    DDS_PLAY_ON_I2S6 = 6U,
    DDS_PLAY_ON_HW_DAC1 = 7U,
    DDS_PLAY_ON_HW_DAC2 = 8U,
    DDS_PLAY_ON_WAV_FILE = 9U,
    DDS_PLAY_ON_UNDEF = 8U
} DDS_PLAYER;

//! DDS FRAME PATTERN
typedef enum
{
    DDS_CHANNEL_ONLY_RIGHT = 1,
    DDS_CHANNEL_ONLY_LEFT = 2,
    DDS_CHANNEL_BOTH = 3,
    DDS_CHANNEL_MONO = 4,
    DDS_CHANNEL_UNDEF = 0,
} DDS_SAMPLE_PATTERN;

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//None



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//None



#endif // #ifndef  DDS_CONSTANTS_H


//****************************************** end of file *******************************************
