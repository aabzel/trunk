//*****************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_adc_diagnostic.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!
//! \par    Abbreviations
//!             MCU - MicroController Unit
//!             ADC -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//*****************************************************************************
#include "nau8814_adc_diagnostic.h"

#include "nau8814_driver.h"

//*****************************************************************************
//! NAU8814 Adc Diag
//!
//! \note       NAU8814 Adc Diag
//!
//! \param[in]  num - asic num
//!
//! \return     [Description of return value]
//*****************************************************************************
STD_RESULT NAU8814_AdcDiag(const U8 num)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_ADC_GetPmicGain(num, &Node->pMicGain);
        ret = NAU8814_ADC_GetAuxGain(num, &Node->auxGain);
        ret = NAU8814_ADC_GetPgaGain(num, &Node->pgaGain);
        ret = NAU8814_ADC_GetAdc(num, &Node->adcOn);
    }
    return ret;
} // end of MODULE_FunctionThree()
//******************************* end of file *********************************
