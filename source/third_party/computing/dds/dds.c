//**************************************************************************************************
// @Module  DDS
//! \file   dds.c
//! \par    Platform
//!             This code can work on any platform with I2S, DAC or WAV files.
//! \par    Compatible
//!             This code can work on any platform with I2S, DAC or WAV files.
//! \brief  This is a code for generating complex waveforms (sine, saw, fence, pwm, chirp e.g.).
//!
//! \par    Abbreviations
//!             DDS - Direct digital synthesis
//!             I2S - Inter-Integrated Circuit Sound
//!             DAC - Digital-to-analog converter
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 15.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************


//! \defgroup   DDS Name of Module
//! \brief      Implementation of the DDS functionality.
//! \addtogroup DDS
//! @{
//! \file dds.c
//! \file dds.h
//! \file dds_cfg.h
//! @}
//**************************************************************************************************


//**************************************************************************************************
// Project Includes
//**************************************************************************************************


#include "dds.h"

#include "bit_utils.h"
#include "byte_utils.h"
#include "time_mcal.h"
#include "dds_configuration.h"

#ifdef I2S_IN_USE
#include "i2s_drv.h"
#endif // I2S_IN_USE


//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

// None



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

// None



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

//! \brief DDS_Calc One Sample Low Level
static DDS_SAMPLE_TYPE DDS_CalcOneSampleLowLevel(DDS_HANDLE* const Node,
                                                 const U32 curTimeNs);

//! \brief DDS On Off To State
static DDS_STATE  DDS_OnOffToState(const U8 onOff);

//! \brief DDS is valid player
static STD_RESULT DDS_IsValidPlayer(const DDS_PLAYER player);

//! \brief DDS Proc One
static STD_RESULT DDS_ProcOne(const U8 num);

//! \brief DDS Is Valid Signal
static STD_RESULT DDS_IsValidSignal(const DDS_SIGNAL ddsSignal);

//! \brief DDS_Is Valid Frame Pattern
static STD_RESULT DDS_IsValidFramePattern(const DDS_SAMPLE_PATTERN samplePattern);

//! \brief DDS Is Valid Config
static STD_RESULT DDS_IsValidConfig(const DDS_CONFIG* const Config);

//! \brief DDS Is Valid Sample Bitness
static STD_RESULT DDS_IsValidSampleBitness(const U8 sampleBitness);

//! \brief DDS Calc Max Time Ns
static U32 DDS_CalcMaxTimeNs(DDS_HANDLE* const Node,
                             const U32 periods);

//! \brief DDS Calc Store One Sample Low Level
static STD_RESULT DDS_CalcStoreOneSampleLowLevel(DDS_HANDLE* const Node,
                                                 const U32 curTimeNs,
                                                 const U32 sampleN);

//! \brief Dds Player To I2s Num
static S16 DDS_PlayerToI2sNum(const DDS_PLAYER player);

//! \brief DDS Set Valid Freq
static FLOAT32    DDS_SetValidFreq(const FLOAT32 frequencyHz);

//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! DDS Get RAM Node
//!
//! \note       DDS Get RAM Node
//!
//! \param[in]  num - DDS instance natural number
//!
//! \return     DDS RAM Node
//**************************************************************************************************
DDS_HANDLE* DDS_GetNode(const U8 num)
{
    DDS_HANDLE* Node = NULL_PTR;
    U32         i = 0;
    for (i = 0; i < DDS_GetCnt(); i++)
    {
        if (num == DDS_Instance[i].num)
        {
            if (DDS_Instance[i].valid)
            {
                Node = &DDS_Instance[i];
                break;
            }
        }
    }
    return Node;
} // end of DDS_GetNode()



//**************************************************************************************************
//! DDS calculate one sin sample
//!
//! \note       calculate one sin sample
//!
//! \param[in]  upTimeUs - up Time Us
//! \param[in]  frequencyHz - frequency Hz
//! \param[in]  phaseMs - phase Ms
//! \param[in]  amplitudePcm - amplitude Pcm
//! \param[in]  offSet - off Set
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
FLOAT32 DDS_CalcSinSample(const U64 upTimeUs,
                          const FLOAT32 frequencyHz,
                          const FLOAT32 phaseMs,
                          const FLOAT32 amplitudePcm,
                          const FLOAT32 offSet) {
    FLOAT32 lineVal = 0.0;
    FLOAT32 radians = 0.0;
    FLOAT32 amplitude = 0.0;
    FLOAT32 amplitudeScaled = 0.0;
    FLOAT32 curTimeMs = ((FLOAT32)upTimeUs) / 1000.0;
    lineVal = ((curTimeMs + phaseMs) / 1000.0) * frequencyHz;
    radians = 2.0 * M_PI * lineVal;
    amplitude = (FLOAT32)sinf((FLOAT32)radians);
    amplitudeScaled = (amplitudePcm * amplitude) + offSet;
    return amplitudeScaled;
}
//**************************************************************************************************
//! DDS Ctrl
//!
//! \note       DDS Control
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  onOff - ON OFF
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_Ctrl(const U8 num,
                    const U8 onOff)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
#ifdef I2S_IN_USE
        S16 i2sNum = DDS_PlayerToI2sNum(Node->player);
        if (0 < i2sNum)
        {
            ret = I2S_Ctrl((const U8)i2sNum, onOff);
            if (RESULT_OK == ret)
            {
                Node->state = DDS_OnOffToState(onOff);
            }
        }
#endif
    }
    return ret;
} // end of DDS_Ctrl()
//**************************************************************************************************
//! DDS Init
//!
//! \note       DDS Init
//!
//! \param[in]  None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_Init(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32        okCnt = 0;
    U32        cnt = DDS_GetCnt();
    U32        num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = DDS_InitOne(num);
        if (RESULT_OK == ret)
        {
            okCnt++;
        }
        else
        {
        }
    }

    if (okCnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of DDS_Init()
//**************************************************************************************************
//! DDS init one instance
//!
//! \note       DDS init one instance
//!
//! \param[in]  num - DDS instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_InitOne(const U8 num)
{
    STD_RESULT        ret = RESULT_NOT_OK;
    const DDS_CONFIG* Config = DDS_GetConfig(num);
    if (Config)
    {
        DDS_HANDLE* Node = DDS_GetNode(num);
        ret = DDS_IsValidConfig(Config);
        if (RESULT_OK == ret)
        {
            if (Node)
            {
                Node->amplitude = Config->amplitude;
                Node->arraySize = Config->arraySize;
                Node->ddsSignal = Config->ddsSignal;
                Node->dutyCycle = Config->dutyCycle;
                Node->frequency = Config->frequency;
                Node->frequency2 = Config->frequency2;
                Node->framePerSec = Config->framePerSec;
                Node->name = Config->name;
                Node->offset = Config->offset;
                Node->player = Config->player;
                Node->phaseMs = Config->phaseMs;
                Node->sampleBitness = Config->sampleBitness;
                Node->samplePattern = Config->samplePattern;
                Node->txSampleArray = Config->txSampleArray;

                Node->valid = TRUE;
                Node->initDone = TRUE;
                Node->sampleCnt = 0;
                ret = RESULT_OK;
            }
        }
    }
    return ret;
} // end of DDS_InitOne()

//**************************************************************************************************
//! DDS play
//!
//! \note       DDS play
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  durationMs - duration Ms
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_Play(const U8 num,
                    const U64 durationMs)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        Node->durationMs = durationMs;
        Node->procOn = TRUE;
        ret = DDS_SetArray(num, 1, 0);
        if (RESULT_OK == ret)
        {
            ret = RESULT_NOT_OK;
#ifdef I2S_IN_USE
            S16 i2sNum = DDS_PlayerToI2sNum(Node->player);
            if (0 < i2sNum)
            {
                ret = I2S_Write((const U8)i2sNum,
                                (DDS_SAMPLE_TYPE*)Node->txSampleArray,
                                Node->sampleCnt);
            }
#endif
            if (RESULT_OK == ret)
            {
                U32 upTimeMs = MCU_GetUpTimeMs();
                Node->playOffTimeStampMs = (U64)upTimeMs + durationMs;
                Node->state = DDS_MODE_PLAY;
                ret = RESULT_OK;
            }
        }
    }
    return ret;
} // end of DDS_Play()

//**************************************************************************************************
//! DDS play endless test tone at frequency 1kHz
//!
//! \note       play endless test tone at frequency 1kHz
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  amplitude - amplitude
//! \param[in]  offset - offset
//! \param[in]  phaseMs - phase
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_Play1kHz(const U8 num,
                        const DDS_SAMPLE_TYPE amplitude,
                        const DDS_SAMPLE_TYPE offset,
                        const FLOAT32 phaseMs)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = DDS_SetSin(num, 1000.0, amplitude, phaseMs, offset);
    if (RESULT_OK == ret)
    {
        ret = DDS_Play(num, 0xFFFFFFFF);
    }
    return ret;
} // end of DDS_Play1kHz()

//**************************************************************************************************
//! DDS Proc
//!
//! \note       DDS Proc
//!
//! \param[in]  Node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_Proc(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32        okCnt = 0;
    U32        cnt = DDS_GetCnt();
    U32        num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = DDS_ProcOne(num);
        if (RESULT_OK == ret)
        {
            okCnt++;
        }
    }
    if (okCnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of DDS_Proc()


//**************************************************************************************************
//! DDS calculate array of samples
//!
//! \note       DDS calculate array of samples
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  periods - number of periods to be calculated
//! \param[in]  minAbsPeriodNs - audio track duration in Ns
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetArray(const U8 num,
                        const U32 periods,
                        const U32 minAbsPeriodNs)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    U32         samplePeriodNs = 0;
    U32         maxTimeNs = 0;
    U32         curTimeNs = 0;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (0 < Node->framePerSec)
    {
        samplePeriodNs = 1000000000 / Node->framePerSec;
        if (Node)
        {
            if (0 == minAbsPeriodNs)
            {
                maxTimeNs = DDS_CalcMaxTimeNs(Node, periods);
            }
            else
            {
                maxTimeNs = minAbsPeriodNs;
            }

            Node->sampleCnt = maxTimeNs / samplePeriodNs;
            ret = RESULT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        // U8 sample_size = Node->sampleBitness/8;
        U32 i = 0;
        U32 s = 0;
        for (curTimeNs = 0, i = 0, s = 0;
             s < Node->sampleCnt;
             curTimeNs += samplePeriodNs, i += 2, s++)
        {
            ret = DDS_CalcStoreOneSampleLowLevel(Node, curTimeNs, i);
        } // end of  for
        ret = RESULT_OK;
    } // end of  if(RESULT_OK == ret)
    return ret;
} // end of DDS_SetArray()
//**************************************************************************************************
//! DDS Set Fence signal
//!
//! \note        Set Fence signal
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  frequency - frequency
//! \param[in]  amplitude - amplitude
//! \param[in]  phaseMs - phaseMs
//! \param[in]  offset - offset
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetFence(const U8 num,
                        const FLOAT32 frequency,
                        const DDS_SAMPLE_TYPE amplitude,
                        const FLOAT32 phaseMs,
                        const DDS_SAMPLE_TYPE offset)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        Node->frequency = frequency;
        Node->amplitude = (DDS_SAMPLE_TYPE)amplitude;
        Node->phaseMs = phaseMs;
        Node->offset = (DDS_SAMPLE_TYPE)offset;
        Node->ddsSignal = DDS_SIGNAL_FENCE;
        ret = RESULT_OK;
    }
    return ret;
} // end of DDS_SetFence()

//**************************************************************************************************
//! DDS set frame per sec FPS
//!
//! \note       DDS set frame per sec FPS
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  framePerSec - frames Per Second (Fs)
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetFramePerSec(const U8 num,
                              const U32 framePerSec)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        if(8000 < framePerSec)
        {
            Node->framePerSec = framePerSec;
            ret = RESULT_OK;
        }
    }
    return ret;
} // end of DDS_SetFramePerSec()

//**************************************************************************************************
//! DDS set sample pattern
//!
//! \note       DDS set sample pattern
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  samplePattern - sample Pattern
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetPattern(const U8 num,
                          const DDS_SAMPLE_PATTERN samplePattern)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        Node->samplePattern = samplePattern;
        ret = RESULT_OK;
    }
    return ret;
} // end of DDS_SetPattern()

//**************************************************************************************************
//! DDS set PWM signal
//!
//! \note       DDS set PWM signal
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  frequency - frequency in Hz
//! \param[in]  amplitude - amplitude in PCM
//! \param[in]  dutyCycle - duty Cycle (0;100)
//! \param[in]  phaseMs - phase Ms
//! \param[in]  offset - offset in PCM
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetPwm(const U8              num,
                      const FLOAT32         frequency,
                      const DDS_SAMPLE_TYPE amplitude,
                      const FLOAT32         dutyCycle,
                      const FLOAT32         phaseMs,
                      const DDS_SAMPLE_TYPE offset)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        Node->frequency = DDS_SetValidFreq(frequency);
        Node->amplitude = amplitude;
        Node->dutyCycle = dutyCycle;
        Node->phaseMs = phaseMs;
        Node->offset = (DDS_SAMPLE_TYPE)offset;
        Node->ddsSignal = DDS_SIGNAL_PWM;
        ret = RESULT_OK;
    }

    return ret;
} // end of DDS_SetPwm()

//**************************************************************************************************
//! DDS Set Saw
//!
//! \note       DDS Set Saw
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  frequency - frequency
//! \param[in]  amplitude - amplitude
//! \param[in]  phaseMs - phase Ms
//! \param[in]  offset - offset
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetSaw(const U8 num,
                      const FLOAT32 frequency,
                      const DDS_SAMPLE_TYPE amplitude,
                      const FLOAT32 phaseMs,
                      const DDS_SAMPLE_TYPE offset)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        Node->frequency = DDS_SetValidFreq(frequency);
        Node->amplitude = (DDS_SAMPLE_TYPE)amplitude;
        Node->phaseMs = phaseMs;
        Node->offset = (DDS_SAMPLE_TYPE)offset;
        Node->ddsSignal = DDS_SIGNAL_SAW;
        ret = RESULT_OK;
    }
    return ret;
} // end of DDS_SetSaw()

//**************************************************************************************************
//! DDS set sine signal
//!
//! \note       DDS set sine signal
//!
//! \param[in]  num - DDS instance natural number
//! \param[in]  frequency - frequency
//! \param[in]  amplitude - amplitude
//! \param[in]  phaseMs - phaseMs
//! \param[in]  offset - offset
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_SetSin(const U8              num,
                      const FLOAT32         frequency,
                      const DDS_SAMPLE_TYPE amplitude,
                      const FLOAT32         phaseMs,
                      const DDS_SAMPLE_TYPE offset)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (0 < amplitude)
    {
        DDS_HANDLE* Node = DDS_GetNode(num);
        if (Node)
        {
            Node->frequency = frequency;
            Node->amplitude = amplitude;
            Node->phaseMs = phaseMs;
            Node->offset = offset;
            Node->ddsSignal = DDS_SIGNAL_SIN;
            ret = RESULT_OK;
        }
    }
    return ret;
} // end of DDS_SetSin()







//**************************************************************************************************
//! DDS Stop
//!
//! \note       DDS stop
//!
//! \param[in]  num - DDS instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT DDS_Stop(const U8 num)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
#ifdef I2S_IN_USE
        S16 i2sNum = DDS_PlayerToI2sNum(Node->player);
        if (0 < i2sNum)
        {
            ret = I2S_Stop((const U8)i2sNum);
            if (RESULT_OK == ret)
            {
                Node->state = DDS_MODE_IDLE;
            }
        }
#endif
    }
    return ret;
} // end of DDS_FunctionThree()





//**************************************************************************************************

//**************************************************************************************************
//! DDS get ROM configuration
//!
//! \note       DDS get ROM config
//!
//! \param[in]  num - DDS instance natural number
//!
//! \return     DDS ROM Configuration
//**************************************************************************************************
const DDS_CONFIG* DDS_GetConfig(const U8 num)
{
    const DDS_CONFIG* Config = NULL_PTR;
    U32               i = 0;
    U32               cnt = DDS_GetCnt();
    for (i = 0; i < cnt; i++)
    {
        if (num == DDS_Configuration[i].num)
        {
            if (DDS_Configuration[i].valid)
            {
                Config = &DDS_Configuration[i];
                break;
            }
        }
    }
    return Config;
} // end of DDS_GetConfig()


//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! DDS calc one sample low level
//!
//! \note       calc one sample low level
//!
//! \param[in]  Node - Node
//! \param[in]  curTimeNs - upTime
//!
//! \return     sample to tx
//**************************************************************************************************
static DDS_SAMPLE_TYPE DDS_CalcOneSampleLowLevel(DDS_HANDLE* const Node,
                                                 const U32 curTimeNs)
{
    DDS_SAMPLE_TYPE txSample = 0;
    FLOAT32         txSampleReal = 0.0;
    U64             timeUs = curTimeNs / 1000;
    switch ((U8)Node->ddsSignal)
    {
    case DDS_SIGNAL_SIN:
    {
        txSampleReal = DDS_CalcSinSample(timeUs,
                                         Node->frequency,
                                         Node->phaseMs,
                                         (FLOAT32)Node->amplitude,
                                         (FLOAT32)Node->offset);
    }
    break;
#ifdef DDS_DTMF_IN_USE
    case DDS_SIGNAL_DTMF:
    {
        txSampleReal = calc_dtmf_sample(timeUs,
                                       Node->frequency,
                                       Node->frequency2,
                                       Node->phaseMs,
                                       ((FLOAT32)Node->amplitude),
                                       ((FLOAT32)Node->offset));
    }
    break;
#endif

    } // end of  switch
    txSample = (DDS_SAMPLE_TYPE) txSampleReal;
    return txSample;
} // end of DDS_CalcOneSampleLowLevel()

//**************************************************************************************************
//! DDS on off to state
//!
//! \note       DDS on off to state
//!
//! \param[in]  onOff - ON OFF
//!
//! \return     DDS state (DDS_MODE_PLAY, DDS_MODE_IDLE)
//**************************************************************************************************
static DDS_STATE DDS_OnOffToState(const U8 onOff)
{
    DDS_STATE state = DDS_SIGNAL_UNDEF;
    switch (onOff)
    {
    case ON:
        state = DDS_MODE_PLAY;
        break;
    case OFF:
        state = DDS_MODE_IDLE;
        break;
    default:
        state = DDS_MODE_IDLE;
        break;
    }// end of switch (onOff)
    return state;
} // end of DDS_OnOffToState()

//**************************************************************************************************
//! DDS is valid player
//!
//! \note       DDS is valid player
//!
//! \param[in]  player - player
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_IsValidPlayer(const DDS_PLAYER player)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch ((U32)player)
    {
    case DDS_PLAY_ON_I2S0:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_I2S1:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_I2S2:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_I2S3:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_I2S4:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_I2S5:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_I2S6:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_HW_DAC1:
        ret = RESULT_OK;
        break;
    case DDS_PLAY_ON_HW_DAC2:
        ret = RESULT_OK;
        break;
    default:
        ret = RESULT_NOT_OK;
        break;
    }
    return ret;
} // end of DDS_IsValidPlayer()


//**************************************************************************************************
//! DDS process one
//!
//! \note       DDS process one
//!
//! \param[in]  num - DDS instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_ProcOne(const U8 num)
{
    STD_RESULT  ret = RESULT_NOT_OK;
    DDS_HANDLE* Node = DDS_GetNode(num);
    if (Node)
    {
        if (Node->procOn)
        {
            U64 upTimeMs = MCU_GetUpTimeMs();
            switch ((U8)Node->state)
            {
                case DDS_MODE_PLAY:
                {
                    if (Node->playOffTimeStampMs < upTimeMs)
                    {
                        ret = DDS_Stop(num);
                    }
                }
                break;

                case DDS_MODE_IDLE:
                {
                    ret = RESULT_OK;
                }
                break;

                default:
                {
                    ret = RESULT_NOT_OK;
                }
                break;

            } // end of switch((U8)Node->state)
        } // end of if(Node->procOn)
    } // end of if(Node)
    return ret;
} // end of DDS_ProcOne()
//**************************************************************************************************
//! DDS is valid signal
//!
//! \note       DDS is valid signal
//!
//! \param[in]  ddsSignal - ddsSignal
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_IsValidSignal(const DDS_SIGNAL ddsSignal)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch ((U32)ddsSignal)
    {
    case DDS_SIGNAL_STATIC:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_PWM:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_SIN:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_SAW:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_FENCE:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_PULSE_TRAIN:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_CHIRP:
        ret = RESULT_OK;
        break;
    case DDS_SIGNAL_DTMF:
        ret = RESULT_OK;
        break;
    default:
        ret = RESULT_NOT_OK;
        break;
    }
    return ret;
} // end of DDS_IsValidSignal()

//**************************************************************************************************
//! DDS is valid frame pattern
//!
//! \note       DDS is valid frame pattern
//!
//! \param[in]  samplePattern - sample Pattern
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_IsValidFramePattern(const DDS_SAMPLE_PATTERN samplePattern)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch ((U32)samplePattern)
    {
    case DDS_CHANNEL_ONLY_RIGHT:
        ret = RESULT_OK;
        break;
    case DDS_CHANNEL_ONLY_LEFT:
        ret = RESULT_OK;
        break;
    case DDS_CHANNEL_BOTH:
        ret = RESULT_OK;
        break;
    case DDS_CHANNEL_MONO:
        ret = RESULT_OK;
        break;
    default:
        ret = RESULT_NOT_OK;
        break;
    }
    return ret;
} // end of DDS_IsValidFramePattern()



//**************************************************************************************************
//! Check that the ROM config is correct
//!
//! \note       Check that the ROM config is correct
//!
//! \param[in]  Config - ROM configuration
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_IsValidConfig(const DDS_CONFIG* const Config)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Config)
    {
        if (Config->valid)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        if (0 < Config->frequency)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        if (0 < Config->amplitude)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        if (Config->txSampleArray)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        if (96 <= Config->arraySize)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        ret = DDS_IsValidPlayer(Config->player);
    }

    if (RESULT_OK == ret)
    {
        ret = DDS_IsValidSignal(Config->ddsSignal);
    }

    if (RESULT_OK == ret)
    {
        if (8000 <= Config->framePerSec)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        ret = DDS_IsValidSampleBitness(Config->sampleBitness);
        if(sizeof(DDS_SAMPLE_TYPE) != (Config->sampleBitness/8))
        {
            ret = RESULT_NOT_OK;
        }
    }

    if (RESULT_OK == ret)
    {
        ret = DDS_IsValidFramePattern(Config->samplePattern);
    }

    return ret;
} // end of DDS_IsValidConfig()

//**************************************************************************************************
//! DDS is valid sample bitness
//!
//! \note       is valid sample bitness
//!
//! \param[in]  sampleBitness - number of bits in one sample
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_IsValidSampleBitness(const U8 sampleBitness)
{
    STD_RESULT ret = RESULT_NOT_OK;
    switch (sampleBitness)
    {
    case 8:
        ret = RESULT_OK;
        break;
    case 16:
        ret = RESULT_OK;
        break;
    case 24:
        ret = RESULT_OK;
        break;
    case 32:
        ret = RESULT_OK;
        break;
    case 64:
        ret = RESULT_OK;
        break;
    default:
        ret = RESULT_NOT_OK;
        break;
    }//switch (sampleBitness)
    return ret;
} // end of DDS_IsValidSampleBitness()

//**************************************************************************************************
//! DDS calc play duration nanoseconds
//!
//! \note       DDS Calc play duration nanoseconds
//!
//! \param[in]  Node - RAM node
//! \param[in]  periods - the number of periods we will play
//!
//! \return     play duration in nanoseconds
//**************************************************************************************************
static U32 DDS_CalcMaxTimeNs(DDS_HANDLE* const Node,
                             const U32 periods)
{
    U32     maxTimeNs = 0;
    FLOAT32 minFreqHz = Node->frequency;
#ifdef DDS_DTMF_IN_USE
    if (DDS_SIGNAL_DTMF == Node->ddsSignal)
    {
        minFreqHz = MIN(Node->frequency, Node->frequency2);
    }
#endif
    maxTimeNs = (U32)((FLOAT32)periods) * (1000000000.0 / minFreqHz);
    return maxTimeNs;
} // end of DDS_CalcMaxTimeNs()

//**************************************************************************************************
//! DDS calc and store one sample low level
//!
//! \note       DDS calc and store one sample low level
//!
//! \param[in]  Node - Node
//! \param[in]  curTimeNs - up time in Ns
//! \param[in]  sampleN - sample number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT DDS_CalcStoreOneSampleLowLevel(DDS_HANDLE* const Node,
                                                 const U32 curTimeNs,
                                                 const U32 sampleN)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    DDS_SAMPLE_TYPE txSample = 0;
    txSample = DDS_CalcOneSampleLowLevel(Node, curTimeNs);

    if (sampleN < Node->arraySize)
    {
        switch ((U8)Node->samplePattern)
        {
        case DDS_CHANNEL_ONLY_RIGHT:
        {
            Node->txSampleArray[sampleN] = 0;
            Node->txSampleArray[sampleN + 1] = txSample;
        }
        break;
        case DDS_CHANNEL_ONLY_LEFT:
        {
            Node->txSampleArray[sampleN] = txSample;
            Node->txSampleArray[sampleN + 1] = 0;
        }
        break;
        case DDS_CHANNEL_BOTH:
        {
            Node->txSampleArray[sampleN] = txSample;
            Node->txSampleArray[sampleN + 1] = txSample;
        }
        break;
        }// end of switch ((U8)Node->samplePattern)
    }// end of if (i < Node->arraySize)
    return ret;
} // end of DDS_FunctionThree()

//**************************************************************************************************
//! Convert DDS player to I2S num
//!
//! \note       Convert DDS player to I2S num
//!
//! \param[in]  player - player
//!
//! \return     I2S num
//**************************************************************************************************
static S16 DDS_PlayerToI2sNum(const DDS_PLAYER player)
{
    S16 i2sNum = -1;
    switch ((U32)player)
    {
    case DDS_PLAY_ON_I2S0:
        i2sNum = 0;
        break;
    case DDS_PLAY_ON_I2S1:
        i2sNum = 1;
        break;
    case DDS_PLAY_ON_I2S2:
        i2sNum = 2;
        break;
    case DDS_PLAY_ON_I2S3:
        i2sNum = 3;
        break;
    case DDS_PLAY_ON_I2S4:
        i2sNum = 4;
        break;
    case DDS_PLAY_ON_I2S5:
        i2sNum = 5;
        break;
    case DDS_PLAY_ON_I2S6:
        i2sNum = 6;
        break;
    default:
        i2sNum = -1;
        break;
    } // end of switch ((U32)player)
    return i2sNum;
} // end of DDS_PlayerToI2sNum()

//**************************************************************************************************
//! DDS set valid frequency
//!
//! \note       DDS set valid frequency
//!
//! \param[in]  frequencyHz - frequency Hz
//!
//! \return     correct frequency
//**************************************************************************************************
static FLOAT32 DDS_SetValidFreq(const FLOAT32 frequencyHz)
{
    FLOAT32 out_freq = 0.0;
    if (0.0 < frequencyHz)
    {
        out_freq = frequencyHz;
    }
    else
    {
        out_freq = 1.0;
    }
    return out_freq;
} // end of DDS_SetValidFreq()

//****************************************** end of file *******************************************
