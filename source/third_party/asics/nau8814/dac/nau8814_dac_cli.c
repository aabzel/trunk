//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_dac_cli.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!             [text]
//! \par    Abbreviations
//!             ABBR0 -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#include "nau8814_dac_cli.h"

#include "convert.h"
#include "log.h"
#include "nau8814_driver.h"
#ifdef HAS_TEST_NAU8814
#include "test_nau8814.h"
#endif


bool NAU8814_DAC_GainCommand(int32_t argc, char* argv[])
{
    bool    res = false;
    NAU8814_FRACTIONAL_GAIN gain = 0.0;

    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2float(argv[0],(float*) &gain);
    }

    if (res)
    {
        switch (argc)
        {
        case 0:
            gain = NAU8814_DAC_GetDacGain(1, &gain);
            LOG_INFO(NAU8814, "GetDACGain %f Ok", gain);
            break;
        case 1:
            LOG_INFO(NAU8814, "SetDACGain %f Ok", gain);
            STD_RESULT ret;
            ret = NAU8814_DAC_SetDacGain(1, gain);
            if (RESULT_OK == ret)
            {
                LOG_INFO(NAU8814, "SetDACGain %f Ok", gain);
            }
            else
            {
                LOG_ERROR(NAU8814, "SetDACGain %f err", gain);
            }
            break;
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: ngc DacGain");
    }
    return res;
} // end of MODULE_FunctionThree()

//
bool NAU8814_PlayInfiniteCommand(int32_t argc, char* argv[])
{
    bool    res = false;
    U32     frequencyHz = 3000;
    int32_t amplitude = 5000;

    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2uint32(argv[0], &frequencyHz);
    }

    if (2 <= argc)
    {
        res = try_str2int32(argv[1], &amplitude);
    }

    if (res)
    {
        STD_RESULT ret;
        LOG_INFO(NAU8814, "Play,Freq:%u Hz,Amp:%u PCM", frequencyHz, amplitude);
        ret = NAU8814_DAC_PlayIndefinite(1, frequencyHz, (NAU8814_SAMPLE_TYPE)amplitude);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "PlayInfOk");
        }
        else
        {
            LOG_ERROR(NAU8814, "PlayInfErr");
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: npic FreqHz Amp");
    }

    return res;
} // end of NAU8814_PlayInfiniteCommand()

// noc 2000 999999
bool NAU8814_PlayTone1kHzCommand(int32_t argc, char* argv[])
{
    bool    res = false;
    int32_t amplitude = 3333;
    U32     duratinMs = 10000;

    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2int32(argv[0], &amplitude);
    }

    if (2 <= argc)
    {
        res = try_str2uint32(argv[1], &duratinMs);
    }

    if (res)
    {
        LOG_INFO(NAU8814, "TryPlay1kHz");
        STD_RESULT ret = NAU8814_DAC_Play1kHz(1, (NAU8814_SAMPLE_TYPE)amplitude, duratinMs);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "CmdPlay1kOk");
        }
        else
        {
            LOG_ERROR(NAU8814, "CmdPlay1kErr");
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: noc Amp DurationMs");
    }

    return res;
} // end of MODULE_FunctionThree()



//**************************************************************************************************
//! [Description of NAU8814_PlayToneCommand]
//!
//! \note       npc 2000 15000 100000
//!
//! \param[in]  parameterZero - [description of parameterZero]
//!
//! \return     [Description of return value]
//**************************************************************************************************
bool NAU8814_PlayToneCommand(int32_t argc, char* argv[])
{
    bool    res = false;
    U32     frequencyHz = 1000;
    int32_t amplitude = 100;
    U32     durationMs = 100.0;
    if (1 <= argc)
    {
        res = try_str2uint32(argv[0], &frequencyHz);
    }

    if (2 <= argc)
    {
        res = try_str2int32(argv[1], &amplitude);
    }

    if (3 <= argc)
    {
        res = try_str2uint32(argv[2], &durationMs);
    }

    if (res)
    {
        STD_RESULT ret;
        LOG_INFO(NAU8814,
                 "Play,Freq:%u Hz,Amp:%u PCM,Dur:%u ms",
                 frequencyHz,
                 amplitude,
                 durationMs);
        ret = NAU8814_DAC_PlayTone(
            1, frequencyHz, (NAU8814_SAMPLE_TYPE)amplitude, durationMs);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "PlayToneOk");
        }
        else
        {
            LOG_ERROR(NAU8814, "PlayToneErr");
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: np FreqHz Amp DurationMs");
    }

    return res;
} // end of NAU8814_PlayToneCommand()

//******************************* end of file ******************************************************
