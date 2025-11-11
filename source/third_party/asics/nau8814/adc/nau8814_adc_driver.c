//**************************************************************************************************
// @Module  NAU8814 ADC Driver
//! \file   nau8814_adc_driver.c
//! \par    Platform
//!             Any PCB with NAU8814
//! \par    Compatible
//!             Any PCB with NAU8814
//! \brief  Implementation of the NAU8814 ADC functionality.
//!
//! \par    Abbreviations
//!             I2S - Inter-Integrated Circuit Sound
//!             ADC - Analog-to-digital converter
//!             PGA - programmable-gain amplifiers
//!             I2C - Inter-Integrated Circuit
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   NAU8814 ADC
//! \brief      NAU8814 ADC driver
//! \addtogroup NAU8814 ADC
//! @{
//! \file nau8814_adc_driver.c
//! \file nau8814_adc_driver.h
//! @}
//**************************************************************************************************


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_adc_driver.h"

#include "i2c_drv.h"
#ifdef I2S_IN_USE
#include "i2s_drv.h"
#endif
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
//**************************************************************************************************

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


//! \brief NAU8814 Pga Gain Code to physical value
static FLOAT32 NAU8814_PgaGainCodeToValue(const U8 pgaGainCode);

//! \brief NAU8814 Bst Gain Code to physical value
static NAU8814_GAIN NAU8814_BstGainCodeToValue(const NAU8814_BOOST_GAIN_CODE BoostGainCode);

//! \brief NAU8814 Gain To Boost Gain Code
static NAU8814_BOOST_GAIN_CODE NAU8814_GainToBoostGainCode(const NAU8814_GAIN pMicGain);

//! \brief NAU8814 Gain To Pga Gain Code
static U8 NAU8814_GainToPgaGainCode(const FLOAT32 gain);


//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! NAU8814 Ctrl Adc
//!
//! \note       NAU8814 Ctrl Adc
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  adcOn - On or Off
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_Ctrl(const U8 num,
                            const U8 adcOn)
{
    STD_RESULT                         ret = RESULT_NOT_OK;
    NAU8814_REGISTER_POWER_MANAGEMENT2 Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_POWER_MANAGEMENT_2, &Reg.word);
    if (RESULT_OK == ret)
    {
        Reg.adcen = adcOn;
        ret = NAU8814_WriteReg(num, NAU8814_REGIS_POWER_MANAGEMENT_2, Reg.word);
    }
    return ret;
} // end of NAU8814_ADC_Ctrl()


//**************************************************************************************************
//! NAU8814 Ctrl Record
//!
//! \note       NAU8814 Ctrl Record
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  onOff - on off
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_CtrlRecord(const U8 num,
                                  const U8 onOff)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        if (FALSE == Node->deInit)
        {
            // Here we can also mute microphone analog circuit
            ret = I2S_Ctrl(Node->i2sNum, onOff);
            if (RESULT_OK == ret)
            {
                Node->state = NAU8814_STATE_IDLE;
            }
        }
    }
    return ret;
} // end of NAU8814_ADC_CtrlRecord()


//**************************************************************************************************
//! NAU8814 De Init Adc
//!
//! \note       NAU8814 De Init Adc
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_DeInit(const U8 num)
{
    STD_RESULT            ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        ret = NAU8814_ADC_CtrlRecord(num, FALSE);
        ret = NAU8814_ADC_Ctrl(num, OFF);
        ret = NAU8814_ADC_SetPmicGain(num, -12.0);
        ret = NAU8814_ADC_SetAuxGain(num, -12);
        ret = NAU8814_ADC_SetPgaGain(num, -12.0);
    }
    return ret;
} // end of NAU8814_ADC_DeInit()

//**************************************************************************************************
//! NAU8814 Get Adc
//!
//! \note       NAU8814 Get Adc
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[out] adcOn - on off
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_GetAdc(const U8  num,
                              U8* const adcOn)
{
    STD_RESULT                         ret = RESULT_NOT_OK;
    NAU8814_REGISTER_POWER_MANAGEMENT2 Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_POWER_MANAGEMENT_2, &Reg.word);
    if (RESULT_OK == ret)
    {
        *adcOn = Reg.adcen;
    }
    return ret;
} // end of NAU8814_GetAdc()


//**************************************************************************************************
//! NAU8814 Get Aux Gain
//!
//! \note       NAU8814 Get Aux Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[out] auxGain - aux Gain
//!
//! \return     Execution status. See STD_RESULT enumeration
//**************************************************************************************************
STD_RESULT NAU8814_ADC_GetAuxGain(const U8 num,
                                  NAU8814_GAIN* const auxGain)
{
    STD_RESULT                 ret = RESULT_NOT_OK;
    NAU8814_REGISTER_ADC_BOOST Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_ADC_BOOST, &Reg.word);
    if (RESULT_OK == ret)
    {
        *auxGain = NAU8814_BstGainCodeToValue(Reg.auxbstgain);
    }
    return ret;
} // end of NAU8814_GetAuxGain()


//**************************************************************************************************
//! NAU8814 Get Pga Gain
//!
//! \note       NAU8814 Get Pga Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[out] pgaGain - pga Gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_GetPgaGain(const U8 num,
                                  FLOAT32* const pgaGain)
{
    STD_RESULT                ret = RESULT_NOT_OK;
    NAU8814_REGISTER_PGA_GAIN Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_PGA_GAIN, &Reg.word);
    if (RESULT_OK == ret)
    {
        *pgaGain = NAU8814_PgaGainCodeToValue(Reg.pgagain);
    }
    return ret;
} // end of NAU8814_GetPgaGain()


//**************************************************************************************************
//! NAU8814 Set Pga Gain
//!
//! \note       NAU8814 Set Pga Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  pgaGain - pga Gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_SetPgaGain(const U8 num,
                                  const FLOAT32 pgaGain)
{
    STD_RESULT                ret = RESULT_NOT_OK;
    NAU8814_REGISTER_PGA_GAIN Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_PGA_GAIN, &Reg.word);
    if (RESULT_OK == ret)
    {
        Reg.pgagain = NAU8814_GainToPgaGainCode(pgaGain);
        ret = NAU8814_WriteReg(num, NAU8814_REGIS_PGA_GAIN, Reg.word);
    }
    return ret;
} // end of NAU8814_SetPgaGain()

//**************************************************************************************************
//! NAU8814 Get Pmic Gain
//!
//! \note        NAU8814 Get Pmic Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[out] pMicGain - pMic Gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_GetPmicGain(const U8 num,
                                   NAU8814_GAIN* const pMicGain)
{
    STD_RESULT                 ret = RESULT_NOT_OK;
    NAU8814_REGISTER_ADC_BOOST Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_ADC_BOOST, &Reg.word);
    if (RESULT_OK == ret)
    {
        *pMicGain = NAU8814_BstGainCodeToValue(Reg.pmicbstgain);
    }
    return ret;
} // end of NAU8814_GetPmicGain()


//**************************************************************************************************
//! NAU8814 Init Adc
//!
//! \note       [text]
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_Init(const U8 num)
{
    STD_RESULT            ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        ret = NAU8814_ADC_Ctrl(num, Config->adcOn);
        ret = NAU8814_ADC_SetPmicGain(num, Config->pMicGain);
        ret = NAU8814_ADC_SetAuxGain(num, Config->auxGain);
        ret = NAU8814_ADC_SetPgaGain(num, Config->pgaGain);
    }
    return ret;
} // end of NAU8814_ADC_Init()


//**************************************************************************************************
//! NAU8814 Listen
//!
//! \note       NAU8814 Listen
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  desDurationMs - des Duration Ms
//! \param[out] none
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_Listen(const U8 num,
                              const U32 desDurationMs)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        if (FALSE == Node->deInit)
        {
            ret = I2S_Record(Node->i2sNum, desDurationMs);
            if (RESULT_OK == ret)
            {
                Node->state = NAU8814_STATE_RECORD;
                Node->playOffTimeStampMs = MCU_GetUpTimeMs() + desDurationMs;
            }
        }
    }
    return ret;
} // end of NAU8814_Listen()


//**************************************************************************************************
//! NAU8814 Set Aux Gain
//!
//! \note       NAU8814 Set Aux Gain
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  auxGain - aux Gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_SetAuxGain(const U8 num,
                                  const NAU8814_GAIN auxGain)
{
    STD_RESULT                 ret = RESULT_NOT_OK;
    NAU8814_REGISTER_ADC_BOOST Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_ADC_BOOST, &Reg.word);
    if (RESULT_OK == ret)
    {
        Reg.auxbstgain = NAU8814_GainToBoostGainCode(auxGain);
        ret = NAU8814_WriteReg(num, NAU8814_REGIS_ADC_BOOST, Reg.word);
    }
    return ret;
} // end of NAU8814_SetAuxGain()


//**************************************************************************************************
//! NAU8814 Set Pmic Gain
//!
//! \note       ADC Boost Control Registers
//!
//! \param[in]  num - NAU8814 audio codec instance natural number
//! \param[in]  pMicGain - -12....+6 Gain (dB)
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ADC_SetPmicGain(const U8 num,
                                   const NAU8814_GAIN pMicGain)
{
    STD_RESULT                 ret = RESULT_NOT_OK;
    NAU8814_REGISTER_ADC_BOOST Reg;
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_ADC_BOOST, &Reg.word);
    if (RESULT_OK == ret)
    {
        Reg.pmicbstgain = NAU8814_GainToBoostGainCode(pMicGain);
        ret = NAU8814_WriteReg(num, NAU8814_REGIS_ADC_BOOST, Reg.word);
    }
    return ret;
} // end of NAU8814_SetPmicGain()


//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! NAU8814 PGA gain code to value
//!
//! \note       NAU8814 PGA gain code to value
//!
//! \param[in]  pgaGainCode - PGA gain code
//!
//! \return     Pga gain physical value
//**************************************************************************************************
static FLOAT32 NAU8814_PgaGainCodeToValue(const U8 pgaGainCode)
{
    FLOAT32 pgaGainVal = 0.0;
    pgaGainVal = ( 0.75 * ((FLOAT32)pgaGainCode) ) - 12.0;
    return pgaGainVal;
} // end of NAU8814_PgaGainCodeToValue()


//**************************************************************************************************
//! NAU8814 boost gain code to physical value
//!
//! \note  NAU8814 boost Gain Code to physical value
//!
//! \param[in]  BoostGainCode - boost gain raw code
//!
//! \return     boost gain physical value
//**************************************************************************************************
static NAU8814_GAIN NAU8814_BstGainCodeToValue(const NAU8814_BOOST_GAIN_CODE BoostGainCode)
{
    NAU8814_GAIN gain = -99;
    switch ((U8)BoostGainCode)
    {
    case NAU8814_BOOST_GAIN_CODE_DISCONNECTED:
        gain = -99;
        break;
    case NAU8814_BOOST_GAIN_CODE_M12:
        gain = -12;
        break;
    case NAU8814_BOOST_GAIN_CODE_M9:
        gain = -9;
        break;
    case NAU8814_BOOST_GAIN_CODE_M6:
        gain = -6;
        break;
    case NAU8814_BOOST_GAIN_CODE_M3:
        gain = -3;
        break;
    case NAU8814_BOOST_GAIN_CODE_0:
        gain = 0;
        break;
    case NAU8814_BOOST_GAIN_CODE_3:
        gain = 3;
        break;
    case NAU8814_BOOST_GAIN_CODE_6:
        gain = 6;
        break;
    }
    return gain;
} // end of NAU8814_BstGainCodeToValue()

//**************************************************************************************************
//! Convert NAU8814 Gain To Boost Gain Code
//!
//! \note       NAU8814 Gain To Boost Gain Code
//!
//! \param[in]  pMicGain - + Mic Gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static NAU8814_BOOST_GAIN_CODE NAU8814_GainToBoostGainCode(const NAU8814_GAIN pMicGain)
{
    NAU8814_BOOST_GAIN_CODE code = NAU8814_BOOST_GAIN_CODE_DISCONNECTED;
    switch (pMicGain)
    {
    case -12:
        code = NAU8814_BOOST_GAIN_CODE_M12;
        break;
    case -9:
        code = NAU8814_BOOST_GAIN_CODE_M9;
        break;
    case -6:
        code = NAU8814_BOOST_GAIN_CODE_M6;
        break;
    case -3:
        code = NAU8814_BOOST_GAIN_CODE_M3;
        break;
    case 0:
        code = NAU8814_BOOST_GAIN_CODE_0;
        break;
    case 3:
        code = NAU8814_BOOST_GAIN_CODE_3;
        break;
    case 6:
        code = NAU8814_BOOST_GAIN_CODE_6;
        break;
    default:
        code = NAU8814_BOOST_GAIN_CODE_DISCONNECTED;
        break;
    }
    return code;
} // end of NAU8814_GainToBoostGainCode()


//**************************************************************************************************
//! Convert NAU8814 Gain To Pga Gain Code
//!
//! \note       NAU8814 Gain To Pga Gain Code
//!
//! \param[in]  gain - gain
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static U8 NAU8814_GainToPgaGainCode(const FLOAT32 gain)
{
    U8 code = 0;
    code = ((U8)((4.0 * gain) / 3.0)) + 16;
    return code;
} // end of NAU8814_GainToPgaGainCode()



//******************************* end of file ******************************************************
