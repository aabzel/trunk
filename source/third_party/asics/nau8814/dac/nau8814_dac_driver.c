//**************************************************************************************************
// @Module  NAU8814 DAC Driver
//! \file   nau8814_dac_driver.c
//! \par    Platform
//!             Any with NAU8814
//! \par    Compatible
//!              Any with NAU8814
//! \brief  Implementation of the MODULE functionality.
//!
//! \par    Abbreviations
//!             MCU - Microcontroller
//!             I2C - Inter-Integrated Circuit
//!             I2S - Inter-Integrated Circuit Sound
//!             DAC - digital to analog converter
//!             PCM - Pulse-code modulation
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   NAU8814 DAC
//! \brief      NAU8814 DAC driver
//! \addtogroup NAU8814 DAC
//! @{
//! \file nau8814_dac_driver.c
//! \file nau8814_dac_driver.h
//! @}
//**************************************************************************************************


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_dac_driver.h"


#include "i2c_drv.h"
#ifdef I2S_IN_USE
#include "i2s_drv.h"
#endif
#include "mcu_drv.h"
#include "nau8814_driver.h"


//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

// None.



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of local (private) data types
//**********************************************************************************************

// None.



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************

// None.



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

//! NAU8814 DAC Set Dac Gain Low Level
static STD_RESULT NAU8814_DAC_SetDacGainLowLevel(NAU8814_HANDLE* const  Node,
                                                 const NAU8814_FRACTIONAL_GAIN dacGain);

//! NAU8814 DAC Set Spk Gain Low Level
static STD_RESULT NAU8814_DAC_SetSpkGainLowLevel(NAU8814_HANDLE* const Node,
                                                 const NAU8814_GAIN speakerGain);

//! NAU8814 DAC Spk Gain To Code
static U16 NAU8814_DAC_SpkGainToCode(const NAU8814_GAIN spkGain);

//! \brief NAU8814 Spk Gain Code To Gain
static NAU8814_GAIN NAU8814_DAC_SpkGainCodeToGain(const U8 spkGainCode);

//! \brief NAU8814 Gain To Gain Code
static U8 NAU8814_DAC_GainToGainCode(const NAU8814_FRACTIONAL_GAIN dacGain);


//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! NAU8814 Ctrl Play
//!
//! \note       NAU8814 Ctrl Play
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  onOff - on off
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_CtrlPlay(const U8 num,
                                const U8 onOff)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        if (FALSE == Node->deInit)
        {
            // Here we can also mute speaker analog circuit
            ret = I2S_Ctrl(Node->i2sNum, onOff);
            if (RESULT_OK == ret)
            {
                Node->state = NAU8814_STATE_IDLE;
            }
        }
    }

    return ret;
} // end of NAU8814_DAC_CtrlPlay()


//**************************************************************************************************
//! NAU8814 De Init Dac
//!
//! \note       NAU8814 Init Dac
//!
//! \param[in]  num - NAU8814 number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_DeInit(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        ret = NAU8814_DAC_CtrlPlay(num, FALSE);
        ret = NAU8814_DAC_SetDacGain(num, -127.0);
        ret = NAU8814_DAC_SetSpkGain(num, -57.0);
    }
    return ret;
} // end of NAU8814_DAC_DeInit()


//**************************************************************************************************
//! NAU8814 Get Dac Gain
//!
//! \note       NAU8814 Get Dac Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  dacGain - dac Gain
//!
//! \return     Execution status. See STD_RESULT enumeration
//**************************************************************************************************
STD_RESULT NAU8814_DAC_GetDacGain(const U8 num,
                                  NAU8814_FRACTIONAL_GAIN* const dacGain)
{
    STD_RESULT                  ret = RESULT_NOT_OK;
    NAU8814_REGISTER_DAC_VOLUME Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_DAC_VOLUME, &Reg.word);
    if (RESULT_OK == ret)
    {
        *dacGain = NAU8814_DAC_DacGainCodeToGain(Reg.dacgain);
    }
    return ret;
} // end of NAU8814_DAC_GetDacGain()


//**************************************************************************************************
//! NAU8814 Get Spk Gain
//!
//! \note       NAU8814 Get Spk Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  spkGain - spk gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_GetSpkGain(const U8 num,
                                  NAU8814_GAIN* const spkGain)
{
    STD_RESULT                      ret = RESULT_NOT_OK;
    NAU8814_REGISTER_SPK_OUT_VOLUME Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_SPKOUT_VOLUME, &Reg.word);
    if (RESULT_OK == ret)
    {
        *spkGain = NAU8814_DAC_SpkGainCodeToGain(Reg.spkgain);
    }
    return ret;
} // end of NAU8814_DAC_GetSpkGain()


//**************************************************************************************************
//! NAU8814 Set DAC Gain Low Level
//!
//! \note       NAU8814 Set Dac Gain Low Level
//!
//! \param[in]  Node - Node
//! \param[in]  dacGain : DAC Gain -127.0......0
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_DAC_SetDacGainLowLevel(NAU8814_HANDLE* const  Node,
                                                 const NAU8814_FRACTIONAL_GAIN dacGain)
{
    STD_RESULT                  ret = RESULT_NOT_OK;
    NAU8814_REGISTER_DAC_VOLUME Reg;
    Reg.word = 0;
    Reg.dacgain = NAU8814_DAC_GainToGainCode(dacGain);
    ret = NAU8814_WriteReg(Node->num, NAU8814_REGIS_DAC_VOLUME, Reg.word);
    return ret;
} // end of NAU8814_DAC_SetDacGainLowLevel()


//**************************************************************************************************
//! NAU8814 Init Dac
//!
//! \note       NAU8814 Init Dac
//!
//! \param[in]  num - NAU8814 number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_Init(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;

    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        ret = NAU8814_DAC_SetDacGain(num, Config->dacGain);
        ret = NAU8814_DAC_SetSpkGain(num, Config->spkGain);
    }


    return ret;
} // end of NAU8814_DAC_Init()


//**************************************************************************************************
//! NAU8814 Mute
//!
//! \note       NAU8814 Mute
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_Mute(const U8 num)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_DAC_SetDacGainLowLevel(Node, -128.0);
    }
    return ret;
} // end of NAU8814_DAC_Mute()


//**************************************************************************************************
//! NAU8814 play 1kHz sine wave
//!
//! \note       NAU8814 play 1 kHz
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  amplitude - amplitude in PCM
//! \param[in]  duratinMs - duratin in Ms
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_Play1kHz(const U8 num,
                                const NAU8814_SAMPLE_TYPE amplitude,
                                const U32 duratinMs)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (duratinMs)
    {
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
            ret = NAU8814_DAC_Play1kHzContinuous(num, amplitude);
            if (RESULT_OK == ret)
            {
                ret = RESULT_NOT_OK;
                Node->state = NAU8814_STATE_PLAY;
                Node->playOffTimeStampMs = MCU_GetUpTimeMs() + duratinMs;
            }
        }
    }

    return ret;
} // end of NAU8814_DAC_Play1kHz()


//**************************************************************************************************
//! NAU8814 Play 1kHz sine wave Continuous
//!
//! \note       NAU8814 Play 1kHz Continuous
//!
//! \param[in]  num - NAU8814 audio codec instance (natural number)
//! \param[in]  amplitude - amplitude in PCMs
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_Play1kHzContinuous(const U8 num,
                                          const NAU8814_SAMPLE_TYPE amplitude)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        if (FALSE == Node->deInit)
        {
            ret = I2S_Play1kHz(Node->i2sNum, Node->ddsNum, amplitude, 0);
        }
    }
    return ret;
} // end of NAU8814_DAC_Play1kHzContinuous()


//**************************************************************************************************
//! NAU8814 Play Indefinite
//!
//! \note       NAU8814 Play Indefinite
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  frequencyHz - frequency Hz
//! \param[in]  amplitude - amplitude PCM
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_PlayIndefinite(const U8 num,
                                      const U32 frequencyHz,
                                      const NAU8814_SAMPLE_TYPE amplitude)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (0 < frequencyHz)
    {
        if (0 < amplitude)
        {
            NAU8814_HANDLE* Node = NAU8814_GetNode(num);
            if (Node)
            {
                if (FALSE == Node->deInit)
                {
                    ret = I2S_PlayTone(Node->i2sNum, Node->ddsNum, amplitude, frequencyHz);
                    if (RESULT_OK == ret)
                    {
                        Node->playOffTimeStampMs = 0xFFFFFFFFFFFFFFFF;
                        Node->state = NAU8814_STATE_PLAY;
                    }
                }
            }
        }
    }
    return ret;
} // end of NAU8814_DAC_PlayIndefinite()


//**************************************************************************************************
//! NAU8814 Play sine wave Tone
//!
//! \note       NAU8814 Play sine wave Tone
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  frequencyHz - tone frequency Hz
//! \param[in]  amplitude - tone amplitude
//! \param[in]  durationMs - tone duration Ms
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_PlayTone(const U8 num,
                                const U32 frequencyHz,
                                const NAU8814_SAMPLE_TYPE amplitude,
                                const U64 durationMs)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (0 < frequencyHz)
    {
        if (0 < amplitude)
        {
            NAU8814_HANDLE* Node = NAU8814_GetNode(num);
            if (Node)
            {
                if (FALSE == Node->deInit)
                {
                    ret = I2S_PlayTone(Node->i2sNum, Node->ddsNum, amplitude, frequencyHz);
                    if (RESULT_OK == ret)
                    {
                        U64 upTimeMs = (U64)MCU_GetUpTimeMs();
                        Node->playOffTimeStampMs = upTimeMs + durationMs;
                        Node->state = NAU8814_STATE_PLAY;
                    }
                }
            }
        }
    }
    return ret;
} // end of NAU8814_DAC_PlayTone()


//**************************************************************************************************
//! NAU8814 Play sine wave tone 1kHz
//!
//! \note       Play Test tone
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  amplitude - amplitude
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_PlayTone1kHz(const U8 num,
                                    const NAU8814_SAMPLE_TYPE amplitude,
                                    const U32 durationMs)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = NAU8814_DAC_PlayTone(num, 1000, amplitude, durationMs);
    return ret;
} // end of NAU8814_DAC_PlayTone1kHz()

//**************************************************************************************************
//! NAU8814 Set Dac Gain
//!
//! \note       NAU8814 Set Dac Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  dacGain - dac Gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_SetDacGain(const U8 num,
                                  const NAU8814_FRACTIONAL_GAIN dacGain)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_DAC_SetDacGainLowLevel(Node, dacGain);
    }
    return ret;
} // end of NAU8814_DAC_SetDacGain()


//**************************************************************************************************
//! NAU8814 Set Spk Gain
//!
//! \note       Speaker Gain Control Register
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  speakerGain - gain -57.0  ..... +6.0
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DAC_SetSpkGain(const U8 num,
                                  const NAU8814_GAIN speakerGain)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_DAC_SetSpkGainLowLevel(Node, speakerGain);
    }
    return ret;
} // end of NAU8814_DAC_SetSpkGain()


//**************************************************************************************************
//! Convert NAU8814 Dac Gain Code To Gain
//!
//! \note       y=ax+b, y=(0.5)x+(-127.5) Y=(0.5)*X +(-127.5)
//!
//! \param[in]  code - gain code
//!
//! \return     Gain
//**************************************************************************************************
NAU8814_FRACTIONAL_GAIN NAU8814_DAC_DacGainCodeToGain(const U16 code)
{
    NAU8814_FRACTIONAL_GAIN dacGain = 0;
    if (code)
    {
        dacGain = (NAU8814_FRACTIONAL_GAIN) ( (0.5 * ( (FLOAT32)code) ) - 127.5 );
    }
    else
    {
        dacGain = -999.0;
    }

    return dacGain;
} // end of NAU8814_DAC_DacGainCodeToGain()


//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! NAU8814 Set Spk Gain Low Level
//!
//! \note       Set speaker gain control register
//!
//! \param[in]  Node - Codec RAM node
//! \param[in]  speakerGain - Speaker Gain  -57.0  ..... +6.0
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_DAC_SetSpkGainLowLevel(NAU8814_HANDLE* const Node,
                                                 const NAU8814_GAIN speakerGain)
{
    STD_RESULT                      ret = RESULT_NOT_OK;
    if (Node)
    {
        NAU8814_REGISTER_SPK_OUT_VOLUME Reg;
        Reg.word = 0;
        ret = NAU8814_ReadReg(Node->num, NAU8814_REGIS_SPKOUT_VOLUME, &Reg.word);
        if (RESULT_OK == ret)
        {
            Reg.spkgain = NAU8814_DAC_SpkGainToCode(speakerGain);
            ret = NAU8814_WriteReg(Node->num, NAU8814_REGIS_SPKOUT_VOLUME, Reg.word);
        }
    }
    return ret;
} // end of NAU8814_DAC_SetSpkGainLowLevel()


//**************************************************************************************************
//! Convert NAU8814 spk gain to spk gain code
//!
//! \note       NAU8814 Spk Gain To Code
//!
//! \param[in]  spkGain - spk gain
//!
//! \return     spk gain code
//**************************************************************************************************
static U16 NAU8814_DAC_SpkGainToCode(const NAU8814_GAIN spkGain)
{
    U16 spkGainCode = 0;
    spkGainCode = spkGain + 57U;
    return spkGainCode;
} // end of NAU8814_DAC_SpkGainToCode()

//**************************************************************************************************
//! Convert NAU8814 Speaker Gain Code To Gain
//!
//! \note       NAU8814 Speaker Gain Code To Gain
//!
//! \param[in]  spkGainCode - Speaker Gain Code
//!
//! \return     Speaker Gain
//**************************************************************************************************
static NAU8814_GAIN NAU8814_DAC_SpkGainCodeToGain(const U8 spkGainCode)
{
    NAU8814_GAIN spkGain = 0;
    spkGain = spkGainCode - 57;
    return spkGain;
} // end of NAU8814_DAC_SpkGainCodeToGain()

//**************************************************************************************************
//! Convert NAU8814 DAC Gain To Gain Code
//!
//! \note      y=ax+b, y=(2)x+(255)  Y=(2)*X +(255)
//!
//! \param[in]  dacGain - dac Gain
//!
//! \return     code - dac Gain code
//**************************************************************************************************
static U8 NAU8814_DAC_GainToGainCode(const NAU8814_FRACTIONAL_GAIN dacGain)
{
    U16 code = 0;
    if (-127.0 <= dacGain)
    {
        if (dacGain <= 0.0)
        {
            code = (2.0 * dacGain) + 255.0;
        }
        else
        {
            code = 0xFF;
        }
    }
    else
    {
        code = 0;
    }

    return (U8)code;
} // end of NAU8814_DAC_GainToGainCode()



//******************************* end of file ******************************************************
