//**************************************************************************************************
// @Module  DDS
//! \file   dds.h
//! \brief  Interface of the direct digital synthesis
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef DIRECT_DIGITAL_SYNTHESIS_H
#define DIRECT_DIGITAL_SYNTHESIS_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "platform.h"
#include "general_types.h"
#include "dds_cfg.h"
#include "dds_types.h"
#ifdef DDS_IN_USE_DIAG
#include "dds_diagnostic.h"
#endif



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

// None



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

//! \brief DDS Get RAM Node
extern DDS_HANDLE* DDS_GetNode(const U8 num);

//! \brief DDS calc one sin sample
extern FLOAT32 DDS_CalcSinSample(const U64 upTimeUs,
                                 const FLOAT32 frequencyHz,
                                 const FLOAT32 phaseMs,
                                 const FLOAT32 amplitudePcm,
                                 const FLOAT32 offSet);

//! \brief DDS Ctrl
extern STD_RESULT DDS_Ctrl(const U8 num,
                           const U8 onOff);

//! \brief DDS Init
extern STD_RESULT DDS_Init(void);

//! \brief DDS init one
extern STD_RESULT DDS_InitOne(const U8 num);

//! \brief DDS play by number
extern STD_RESULT DDS_Play(const U8 num,
                           const U64 durationMs);

//! \brief DDS play 1kHz
extern STD_RESULT DDS_Play1kHz(const U8 num,
                               const DDS_SAMPLE_TYPE amplitude,
                               const DDS_SAMPLE_TYPE offset,
                               const FLOAT32 phaseMs);

//! \brief DDS proc
extern STD_RESULT DDS_Proc(void);

//! \brief DDS set array
extern STD_RESULT DDS_SetArray(const U8 num,
                               const U32 periods,
                               const U32 minAbsPeriodNs);

//! \brief DDS set fence signal
extern STD_RESULT DDS_SetFence(const U8 num,
                               const FLOAT32 frequency,
                               const DDS_SAMPLE_TYPE amplitude,
                               const FLOAT32 phaseMs,
                               const DDS_SAMPLE_TYPE offset);

//! \brief DDS set frame per sec
extern STD_RESULT DDS_SetFramePerSec(const U8 num,
                                     const U32 framePerSec);

//! \brief DDS set pattern
extern STD_RESULT DDS_SetPattern(const U8 num,
                                 const DDS_SAMPLE_PATTERN samplePattern);

//! \brief DDS set pwm signal
extern STD_RESULT DDS_SetPwm(const U8 num,
                             const FLOAT32         frequency,
                             const DDS_SAMPLE_TYPE amplitude,
                             const FLOAT32         dutyCycle,
                             const FLOAT32         phaseMs,
                             const DDS_SAMPLE_TYPE         offset);

//! \brief DDS set saw signal
extern STD_RESULT DDS_SetSaw(const U8 num,
                             const FLOAT32 frequency,
                             const DDS_SAMPLE_TYPE amplitude,
                             const FLOAT32 phaseMs,
                             const DDS_SAMPLE_TYPE offset);

//! \brief DDS set sin signal
extern STD_RESULT DDS_SetSin(const U8 num,
                             const FLOAT32         frequency,
                             const DDS_SAMPLE_TYPE amplitude,
                             const FLOAT32         phaseMs,
                             const DDS_SAMPLE_TYPE offset);

//! \brief DDS stop signal
extern STD_RESULT DDS_Stop(const U8 num);

//! \brief DDS get rom config
extern const DDS_CONFIG* DDS_GetConfig(const U8 num);

#endif // #ifndef DIRECT_DIGITAL_SYNTHESIS_H

//****************************************** end of file *******************************************
