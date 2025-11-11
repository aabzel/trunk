//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_driver.c
//! \par    Platform
//!             Any PCB with NAU8814 ASIC
//! \par    Compatible
//!             Any with NAU8814 ASIC
//! \brief  See NAU8814YG AudioCodec Review on https://habr.com/ru/articles/808499
//!
//! \par    Abbreviations
//!             ADC - Analog-to-digital converter
//!             ASIC - Application-specific integrated circuit
//!             DAC - digital to analog converter
//!             I2S - Inter-IC Sound Bus
//!             I2C - Inter-Integrated Circuit
//!             PCM - Pulse-code modulation
//!             PLL - Phase-locked loop
//!             PCM - Pulse-code modulation
//!             RAM - Random-access memory
//!             ROM - Read-only memory
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   NAU8814
//! \brief      NAU8814 ASIC driver
//! \addtogroup NAU8814
//! @{
//! \file nau8814_driver.c
//! \file nau8814_driver.h
//! \file nau8814_configuration.c
//! \file nau8814_configuration.h
//! \file nau8814_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_driver.h"

#include "bit_const.h"
#include "bit_utils.h"
#include "byte_utils.h"
#include "i2c_drv.h"
#ifdef I2S_IN_USE
#include "i2s_drv.h"
#endif


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

//! Nau8814 One Register Info
#define NAU8814_REGISTER_INFO_ONE(REGISTER_NAME, ACCESS)                       \
    {                                                                          \
        .valid = TRUE,                                                         \
        .addr = NAU8814_REGIS_##REGISTER_NAME,                                 \
        .name = #REGISTER_NAME,                                                \
        .access = NAU8814_ACCESS_##ACCESS,                                     \
    },

//! Nau8814 All Register Info
#define NAU8814_REGISTER_INFO_ALL                                       \
    NAU8814_REGISTER_INFO_ONE(SOFTWARE_RESET, READ_WRITE)               \
    NAU8814_REGISTER_INFO_ONE(POWER_MANAGEMENT_1, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(POWER_MANAGEMENT_2, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(POWER_MANAGEMENT_3, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(AUDIO_INTERFACE, READ_WRITE)              \
    NAU8814_REGISTER_INFO_ONE(COMPANDING, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(CLOCK_CONTROL_1, READ_WRITE)              \
    NAU8814_REGISTER_INFO_ONE(CLOCK_CONTROL_2, READ_WRITE)              \
    NAU8814_REGISTER_INFO_ONE(GPIO_CTRL, READ_WRITE)                    \
    NAU8814_REGISTER_INFO_ONE(DAC_CTRL, READ_WRITE)                     \
    NAU8814_REGISTER_INFO_ONE(DAC_VOLUME, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(ADC_CTRL, READ_WRITE)                     \
    NAU8814_REGISTER_INFO_ONE(ADC_VOLUME, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(EQ1_LOW_CUTOFF, READ_WRITE)               \
    NAU8814_REGISTER_INFO_ONE(EQ2_PEAK_1, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(EQ3_PEAK_2, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(EQ4_PEAK_3, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(EQ5_HIGH_CUTOFF, READ_WRITE)              \
    NAU8814_REGISTER_INFO_ONE(DAC_LIMITER_1, READ_WRITE)                \
    NAU8814_REGISTER_INFO_ONE(DAC_LIMITER_2, READ_WRITE)                \
    NAU8814_REGISTER_INFO_ONE(NOTCH_FILTER_0_HIGH, READ_WRITE)          \
    NAU8814_REGISTER_INFO_ONE(NOTCH_FILTER_0_LOW, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(NOTCH_FILTER_1_HIGH, READ_WRITE)          \
    NAU8814_REGISTER_INFO_ONE(NOTCH_FILTER_1_LOW, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(ALC_CTRL_1, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(ALC_CTRL_2, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(ALC_CTRL_3, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(NOISE_GATE, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(PLL_N_CTRL, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(PLL_K_1, READ_WRITE)                      \
    NAU8814_REGISTER_INFO_ONE(PLL_K_2, READ_WRITE)                      \
    NAU8814_REGISTER_INFO_ONE(PLL_K_3, READ_WRITE)                      \
    NAU8814_REGISTER_INFO_ONE(ATTENUATION_CTRL, READ_WRITE)             \
    NAU8814_REGISTER_INFO_ONE(INPUT_CTRL, READ_WRITE)                   \
    NAU8814_REGISTER_INFO_ONE(PGA_GAIN, READ_WRITE)                     \
    NAU8814_REGISTER_INFO_ONE(ADC_BOOST, READ_WRITE)                    \
    NAU8814_REGISTER_INFO_ONE(OUTPUT_CTRL, READ_WRITE)                  \
    NAU8814_REGISTER_INFO_ONE(SPEAKER_MIXER_CTRL, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(SPKOUT_VOLUME, READ_WRITE)                \
    NAU8814_REGISTER_INFO_ONE(MONO_MIXER_CONTROL, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(POWER_MANAGEMENT_4, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(TIME_SLOT, READ_WRITE)                    \
    NAU8814_REGISTER_INFO_ONE(ADCOUT_DRIVE, READ_WRITE)                 \
    NAU8814_REGISTER_INFO_ONE(SILICON_REVISION, READ_ONLY)              \
    NAU8814_REGISTER_INFO_ONE(2_WIRE_ID, READ_ONLY)                     \
    NAU8814_REGISTER_INFO_ONE(ADDITIONAL_ID, READ_ONLY)                 \
    NAU8814_REGISTER_INFO_ONE(HIGH_VOLTAGE_CTRL, READ_WRITE)            \
    NAU8814_REGISTER_INFO_ONE(ALC_ENHANCEMENTS_1, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(ALC_ENHANCEMENTS_2, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(ADDITIONAL_IF_CTRL, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(POWER_TIE_OFF_CTRL, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(AGC_P2P_DETECTOR, READ_ONLY)              \
    NAU8814_REGISTER_INFO_ONE(AGC_PEAK_DETECTOR, READ_ONLY)             \
    NAU8814_REGISTER_INFO_ONE(CONTROL_AND_STATUS, READ_WRITE)           \
    NAU8814_REGISTER_INFO_ONE(OUTPUT_TIE_OFF_CTRL, READ_WRITE)

//! Nau8814 All Register Info
static const NAU8814_REGISTER_INFO Nau8814RegisterInfo[] = {
    NAU8814_REGISTER_INFO_ALL
};


//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

//! \brief Convert nau8814 master clock selection code to physical value
static FLOAT32 NAU8814_MasterClockSelectionToValue(const NAU8814_M_CLK_SEL div_code);

//! \brief Convert Bus Role To Clk Io En bits
static NAU8814_CLK_IO_EN BusRoleToClkIoEn(const NAU8814_I2S_BUS_ROLE i2sRole);

//! \brief Convert Nau Clk Io En bits To Bus Role
static NAU8814_I2S_BUS_ROLE NauClkIoEnToBusRole(const NAU8814_CLK_IO_EN code);

//! \brief Check that the NAU8814 chip is connected by I2C
static STD_RESULT NAU8814_IsConnected_ll(NAU8814_HANDLE* const Node);

//! \brief Convert nau8814 pll physical n value to code
static NAU8814_PLL_N NAU8814_PllNToCode(const U8 pllN);

//! \brief NAU8814 configure registers
static STD_RESULT NAU8814_ConfigRegister(const U8 num,
                                         const NAU8814_REGISTER_VAL* const Reg,
                                         const U32 cnt);

//! \brief NAU8814 proc one codec instance
static STD_RESULT NAU8814_ProcOne(const U8 num);

//! \brief NAU8814 init common variables
static STD_RESULT NAU8814_InitCommon(const NAU8814_CONFIG* const Config,
                                     NAU8814_HANDLE* const Node);

//! \brief NAU8814 Init PLL
static STD_RESULT NAU8814_InitPll(const U8 num);

//! \brief Convert nau8814 pll n code to physical value
static U8 NAU8814_PllNcodeToValue(const NAU8814_PLL_N pllNcode);

//! \brief Convert nau8814 pll d code to physical value
static U8 NAU8814_PllDcodeToValue(const NAU8814_PLL_MCLK divCode);

//! \brief NAU8814 read register low level
static STD_RESULT NAU8814_ReadRegLowLevel(NAU8814_HANDLE* const Node,
                                          const NAU8814_REGISTER_ADDR registerAddr,
                                          U16* const word);

//! \brief NAU8814 Write Reg low level
static STD_RESULT NAU8814_WriteRegLowLevel(NAU8814_HANDLE* const Node,
                                           const NAU8814_REGISTER_ADDR addr,
                                           const U16 word);

//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************


//**************************************************************************************************
//! NAU8814 Get Node
//!
//! \note       NAU8814 Get Node
//!
//! \param[in]  num - Audio codec instance number (natural number)
//!
//! \return     NAU8814 RAM node
//**************************************************************************************************
NAU8814_HANDLE* NAU8814_GetNode(const U8 num)
{
    NAU8814_HANDLE* Node = NULL_PTR;
    U32             i = 0;
    for (i = 0; i < NAU8814_GetCnt(); i++)
    {
        if (num == NAU8814_instance[i].num)
        {
            if (NAU8814_instance[i].valid)
            {
                Node = &NAU8814_instance[i];
                break;
            }
        }
    }
    return Node;
} // end of NAU8814_GetNode()


//*****************************************************************************
//! NAU8814 De Init
//!
//! \note       Reset all audio codec instances
//!
//! \param[in]  None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//*****************************************************************************
STD_RESULT NAU8814_DeInit(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32        ok = 0;
    U32        cnt = NAU8814_GetCnt();
    U32        num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = NAU8814_DeInitOne(num);
        if (RESULT_OK == ret)
        {
            ok++;
        }
    }
    if (ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of NAU8814_DeInit()


//**************************************************************************************************
//! NAU8814 De Init One
//!
//! \note       NAU8814 DeInit One
//!
//! \param[in]  num - Audio codec instance number (natural number)
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_DeInitOne(const U8 num)
{
    STD_RESULT            ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
#if ON == NAU8814_ADC_IN_USE
            ret = NAU8814_ADC_DeInit(num);
#endif

#if ON == NAU8814_DAC_IN_USE
            ret = NAU8814_DAC_DeInit(num);
#endif

            Node->init = FALSE;
            Node->deInit = TRUE;
        }
    }
    return ret;
} // end of NAU8814_DeInitOne()


//**************************************************************************************************
//! NAU8814 Get I2S Role
//!
//! \note       Returns ASIC the I2S role on the I2S bus
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[out] i2sRole - [description of parameterTwo]
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_GetI2sRole(const U8 num,
                              NAU8814_I2S_BUS_ROLE* const i2sRole)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    if(i2sRole)
    {
        *i2sRole = NAU8814_BUS_ROLE_UNDEF;
        NAU8814_REGISTER_CLOCK_CONTROL1 Reg;
        Reg.word = 0;
        ret = NAU8814_ReadReg(num, NAU8814_REGIS_CLOCK_CONTROL_1, &Reg.word);
        if (RESULT_OK == ret)
        {
            *i2sRole = NauClkIoEnToBusRole(Reg.clkioen);
        }
    }

    return ret;
} // end of NAU8814_GetI2sRole()


//**************************************************************************************************
//! NAU8814 Get Master Clock Div
//!
//! \note       NAU8814 Get Master Clock Div
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[out] divider
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_GetMasterClockDiv(const U8 num,
                                     FLOAT32* const divider)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        NAU8814_REGISTER_CLOCK_CONTROL1 Reg = {0};
        Reg.word = 0;
        ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_CLOCK_CONTROL_1, &Reg.word);
        if (RESULT_OK == ret)
        {
            *divider = NAU8814_MasterClockSelectionToValue(Reg.mclksel);
        }
    }

    return ret;
} // end of NAU8814_GetMasterClockDiv()


//**************************************************************************************************
//! NAU8814 Get PLL D
//!
//! \note       NAU8814 Get PLL D
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[out] NAU8814 Get PLL D
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_GetPllD(const U8 num,
                           U8* const pllD)
{
    STD_RESULT                     ret = RESULT_NOT_OK;
    NAU8814_REGISTER_PLL_N_CONTROL Reg;
    Reg.word = 0;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_PLL_N_CTRL, &Reg.word);
        if (RESULT_OK == ret)
        {
            Node->pllD = NAU8814_PllDcodeToValue(Reg.pllmclk);
            *pllD = Node->pllD;
        }
    }

    return ret;
} // end of NAU8814_GetPllD()

//**************************************************************************************************
//! NAU8814 Get PLL K
//!
//! \note       NAU8814 Get PLL K
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[out] pllK- PLL K
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_GetPllK(const U8 num,
                           U32* const pllK)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (pllK)
    {
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
            NAU8814_PLL_K Pllk = {0};
            Pllk.pllK = 0;

            NAU8814_REGISTER_PLL_K_MSB Reg1;
            Reg1.word = 0;

            NAU8814_REGISTER_PLL_MID Reg2;
            Reg2.word = 0;

            NAU8814_REGISTER_LSB Reg3;
            Reg3.word = 0;

            ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_PLL_K_1, &Reg1.word);
            ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_PLL_K_2, &Reg2.word);
            ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_PLL_K_3, &Reg3.word);
            if (RESULT_OK == ret)
            {
                Pllk.pllK_8_0 = Reg3.pllk_8_0;
                Pllk.pllK_17_9 = Reg2.pllk_17_9;
                Pllk.pllK_23_18 = Reg1.pllk_23_18;
                Node->pllK = Pllk.pllK;
                *pllK = Pllk.pllK;
            }
        }
    }
    return ret;
} // end of NAU8814_GetPllK()

//**************************************************************************************************
//! NAU8814 Get PLL N
//!
//! \note       NAU8814 Get PLL N
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[out] pllN
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_GetPllN(const U8 num,
                           U8* const pllN)
{
    STD_RESULT ret = RESULT_NOT_OK;
    NAU8814_REGISTER_PLL_N_CONTROL Reg = {0};
    Reg.word = 0;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_PLL_N_CTRL, &Reg.word);
        if (RESULT_OK == ret)
        {
            Node->pllN = NAU8814_PllNcodeToValue(Reg.plln);
            if(pllN)
            {
                *pllN = Node->pllN;
            }
        }
    }

    return ret;
} // end of NAU8814_GetPllN()

//**************************************************************************************************
//! NAU8814 Init
//!
//! \note       configure all audio codec instances
//!
//! \param[in]  None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_Init(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32        ok = 0;
    U32        cnt = NAU8814_GetCnt();
    U32        num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = NAU8814_InitOne(num);
        if (RESULT_OK == ret)
        {
            ok++;
        }
    }
    if (ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of NAU8814_Init()

//**************************************************************************************************
//! NAU8814 Init One
//!
//! \note       NAU8814 Init One
//!
//! \param[in]  num - Audio codec instance number (natural number)
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_InitOne(const U8 num)
{
    STD_RESULT            ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
            U32 okCnt = 0 ;
            ret = NAU8814_InitCommon(Config, Node);
            if(RESULT_NOT_OK==ret)
            {
                okCnt++;
            }
            Node->valid = TRUE;
            Node->deInit = FALSE;

            ret = NAU8814_IsConnected_ll(Node);
            if (RESULT_OK == ret)
            {
                okCnt++;
                ret = NAU8814_ConfigRegister( num, Config->RegVals, Config->regValCnt);
                if(RESULT_NOT_OK==ret)
                {
                    okCnt++;
                }
                ret = NAU8814_InitPll(num);
                if(RESULT_NOT_OK==ret)
                {
                    okCnt++;
                }
                ret = NAU8814_SetI2sRole(num, Config->i2sRole);
                if(RESULT_NOT_OK==ret)
                {
                    okCnt++;
                }
            }

#ifdef NAU8814_ADC_IN_USE
            ret = NAU8814_ADC_Init(num);
            if(RESULT_NOT_OK==ret)
            {
                okCnt++;
            }
#endif

#ifdef NAU8814_DAC_IN_USE
            ret = NAU8814_DAC_Init(num);
            if(RESULT_NOT_OK==ret)
            {
                okCnt++;
            }
#endif

            if ( 5 <= okCnt)
            {
                Node->init = TRUE;
            }
        }
    }
    return ret;
} // end of NAU8814_InitOne()

//**************************************************************************************************
//! Check that NAU8814 chip is really connected to I2C
//!
//! \note       Check if the codec is connected
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  parameterOne - [description of parameterOne]
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_IsConnected(const U8 num)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_IsConnected_ll(Node);
    }
    return ret;
} // end of NAU8814_IsConnected()

//**************************************************************************************************
//! The function checks whether such a register exists.
//!
//! \note       The function checks whether such a register exists.
//!
//! \param[in]  registerAddress - I2S register address
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_IsValidI2cRegisterAddr(const U8 registerAddress)
{
    STD_RESULT                   ret = RESULT_NOT_OK;
    const NAU8814_REGISTER_INFO* Node = Nau8814_RegAddrToInfo(registerAddress);
    if (Node)
    {
        ret = RESULT_OK;
    }

    return ret;
} // end of NAU8814_IsValidI2cRegisterAddr()


//**************************************************************************************************
//! NAU8814 Proc all audio codec nodes
//!
//! \note       Perform audio codec
//!
//! \param[in]  Node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_Proc(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32        ok = 0;
    U32        cnt = NAU8814_GetCnt();
    U32        num = 0;
    for (num = 0; num <= cnt; num++)
    {
        ret = NAU8814_ProcOne(num);
        if (ret)
        {
            ok++;
        }
        else
        {
        }
    }
    if (ok)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of NAU8814_Proc()

//**************************************************************************************************
//! NAU8814 Read I2S Reg
//!
//! \note       NAU8814 Read I2S Reg
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  addr - register address
//! \param[out] word - pointer to register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_ReadReg(const U8 num,
                           const NAU8814_REGISTER_ADDR registerAddr,
                           U16* const regVal)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_ReadRegLowLevel(Node, registerAddr, regVal);
    }
    return ret;
} // end of NAU8814_ReadReg()


//**************************************************************************************************
//! NAU8814 Reset ASIC
//!
//! \note       Reset audio codec
//!             see 13.1. SOFTWARE RESET in spec
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[out] None
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_Reset(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = NAU8814_WriteReg(num, NAU8814_REGIS_SOFTWARE_RESET, 0x0000);
    return ret;
} // end of NAU8814_Reset()

//**************************************************************************************************
//! NAU8814 Set I2s Role
//!
//! \note       Assign an audio codec a role on the bus
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  i2sRole - role on bus
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_SetI2sRole(const U8 num,
                              const NAU8814_I2S_BUS_ROLE i2sRole)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        NAU8814_REGISTER_CLOCK_CONTROL1 Reg;
        Reg.word = 0;
        ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_CLOCK_CONTROL_1, &Reg.word);
        if (RESULT_OK == ret)
        {
            Reg.clkioen = BusRoleToClkIoEn(i2sRole);
            ret = NAU8814_WriteRegLowLevel(
                Node, NAU8814_REGIS_CLOCK_CONTROL_1, Reg.word);
        }
    }
    return ret;
} // end of NAU8814_SetI2sRole()

//**************************************************************************************************
//! NAU8814 Set PLL K value
//!
//! \note       NAU8814 Set PLL K value
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  setPllK - set PLL K
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_SetPllK(const U8 num,
                           const U32 setPllK)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32        getPllK = 0;
    ret = NAU8814_GetPllK(num, &getPllK);
    if (RESULT_OK == ret)
    {
        if (getPllK == setPllK)
        {
        }
        else
        {
            NAU8814_PLL_K Pllk = {0};
            Pllk.pllK = setPllK;

            NAU8814_REGISTER_PLL_K_MSB Reg1;
            Reg1.word = 0;
            Reg1.pllk_23_18 = Pllk.pllK_23_18;

            NAU8814_REGISTER_PLL_MID Reg2;
            Reg2.word = 0;
            Reg2.pllk_17_9 = Pllk.pllK_17_9;

            NAU8814_REGISTER_LSB Reg3;
            Reg3.word = 0;
            Pllk.pllK_8_0 = Reg3.pllk_8_0;

            NAU8814_HANDLE* Node = NAU8814_GetNode(num);
            if (Node)
            {
                ret = NAU8814_WriteRegLowLevel(Node, NAU8814_REGIS_PLL_K_1, Reg1.word);
                ret = NAU8814_WriteRegLowLevel(Node, NAU8814_REGIS_PLL_K_2, Reg2.word);
                ret = NAU8814_WriteRegLowLevel(Node, NAU8814_REGIS_PLL_K_3, Reg3.word);
            }
        }
    }
    return ret;
} // end of NAU8814_SetPllK()




//**************************************************************************************************
//! nau8814 set PLL n
//!
//! \note       nau8814 set pll n
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  pllN - PLL N value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_SetPllN(const U8 num,
                           const U8 pllN)
{
    STD_RESULT                     ret = RESULT_NOT_OK;
    NAU8814_REGISTER_PLL_N_CONTROL Reg = {0};
    Reg.word = 0;
    ret = NAU8814_ReadReg(num, NAU8814_REGIS_PLL_N_CTRL, &Reg.word);
    if (RESULT_OK == ret)
    {
        Reg.plln = NAU8814_PllNToCode(pllN);
        ret = NAU8814_WriteReg(num, NAU8814_REGIS_PLL_N_CTRL, Reg.word);
    }
    return ret;
} // end of NAU8814_SetPllN()


//**************************************************************************************************
//! Writing One Byte of Data to the NAU8814
//!
//! \note       Writing One Byte of Data to the NAU8814
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  addr - register address
//! \param[in]  word - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_WriteReg(const U8 num,
                            const NAU8814_REGISTER_ADDR registerAddr,
                            const U16 regVal)
{
    STD_RESULT      ret = RESULT_NOT_OK;
    NAU8814_HANDLE* Node = NAU8814_GetNode(num);
    if (Node)
    {
        ret = NAU8814_WriteRegLowLevel(Node, registerAddr, regVal);
    }
    return ret;
} // end of NAU8814_WriteReg()

//*****************************************************************************
//! nau8814 write reg and verify
//!
//! \note       nau8814 write reg and verify
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  registerAddr - reg Addr
//! \param[in]  setWord - Word to write
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT NAU8814_WriteRegVerify(const U8 num,
                                  const NAU8814_REGISTER_ADDR registerAddr,
                                  const U16 setWord)
{
    STD_RESULT ret = RESULT_NOT_OK;
    ret = NAU8814_WriteReg(num, registerAddr, setWord);
    if (RESULT_OK == ret)
    {
        U16 wordRead = 0;
        ret = NAU8814_ReadReg(num, registerAddr, &wordRead);
        if (wordRead == setWord)
        {
            ret = RESULT_OK;
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }

    return ret;
} // end of NAU8814_WriteRegVerify()


//**************************************************************************************************
//! NAU8814 get registers cnt
//!
//! \note       Return the number of specified registers inside the audio codec
//!
//! \param[in]  None
//!
//! \return     number of registers
//**************************************************************************************************
U32 NAU8814_GetRegCnt(void)
{
    U32 cnt = SIZE_OF_ARRAY(Nau8814RegisterInfo);
    return cnt;
} // end of NAU8814_GetRegCnt()


//**************************************************************************************************
//! NAU8814 Get ROM configuration
//!
//! \note       NAU8814 Get configuration
//!
//! \param[in]  num - Audio codec instance number (natural number)
//!
//! \return     NAU8814 ROM node
//**************************************************************************************************
const NAU8814_CONFIG* NAU8814_GetConfig(const U8 num)
{
    const NAU8814_CONFIG* Config = NULL_PTR;
    U32                   i = 0;
    for (i = 0; i < NAU8814_GetCnt(); i++)
    {
        if (num == Nau8814_configuration[i].num)
        {
            if (Nau8814_configuration[i].valid)
            {
                Config = &Nau8814_configuration[i];
                break;
            }
        }
    }
    return Config;
} // end of NAU8814_GetConfig()


//**************************************************************************************************
//! Nau8814 Reg Addr To Info
//!
//! \note       Nau8814 Reg Addr To Info
//!
//! \param[in]  addr - register addr
//!
//! \return     Information about register
//**************************************************************************************************
const NAU8814_REGISTER_INFO* Nau8814_RegAddrToInfo(const NAU8814_REGISTER_ADDR addr)
{
    NAU8814_REGISTER_INFO* RegInfo = NULL_PTR;
    U32                    cnt = SIZE_OF_ARRAY(Nau8814RegisterInfo);
    U32                    i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (Nau8814RegisterInfo[i].valid)
        {
            if (addr == Nau8814RegisterInfo[i].addr)
            {
                RegInfo = &Nau8814RegisterInfo[i];
            }
        }
    }
    return RegInfo;
} // end of Nau8814_RegAddrToInfo()


//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************


//**************************************************************************************************
//! Convert NAU8814 Master Clock Selection to physical value
//!
//! \note Convert NAU8814 Master Clock Selection to physical value
//!
//! \param[in]  code - clock divider code
//!
//! \return     Execution status. See STD_RESULT enumeration
//**************************************************************************************************
static FLOAT32 NAU8814_MasterClockSelectionToValue(const NAU8814_M_CLK_SEL div_code)
{
    U8 divider = 0;
    switch ((U8)div_code)
    {
    case NAU8814_MCLKSEL_DIV1:
        divider = 1.0;
        break;
    case NAU8814_MCLKSEL_DIV1_5:
        divider = 1.5;
        break;
    case NAU8814_MCLKSEL_DIV2:
        divider = 2.0;
        break;
    case NAU8814_MCLKSEL_DIV3:
        divider = 3.0;
        break;
    case NAU8814_MCLKSEL_DIV4:
        divider = 4.0;
        break;
    case NAU8814_MCLKSEL_DIV6:
        divider = 6.0;
        break;
    case NAU8814_MCLKSEL_DIV8:
        divider = 8.0;
        break;
    case NAU8814_MCLKSEL_DIV12:
        divider = 12.0;
        break;
    }
    return divider;
} // end of NAU8814_MasterClockSelectionToValue()


//**************************************************************************************************
//! Bus Role To Clk Io En
//!
//! \note       Bus Role To Clk Io En
//!
//! \param[in]  i2sRole - i2s Role
//!
//! \return     NAU8814 CLK_IO_EN code
//**************************************************************************************************
static NAU8814_CLK_IO_EN BusRoleToClkIoEn(const NAU8814_I2S_BUS_ROLE i2sRole)
{
    NAU8814_CLK_IO_EN code = NAU8814_CLKIOEN_UNDEF;
    switch ((U8)i2sRole)
    {
    case NAU8814_BUS_ROLE_MASTER:
        code = NAU8814_CLKIOEN_MASTER_MODE;
        break;
    case NAU8814_BUS_ROLE_SLAVE:
        code = NAU8814_CLKIOEN_SLAVE_MODE;
        break;
    }
    return code;
} // end of BusRoleToClkIoEn()


//**************************************************************************************************
//! Nau Clk Io En To Bus Role
//!
//! \note       [text]
//!
//! \param[in]  code - [description of parameterZero]
//! \param[out] None
//!
//! \return     I2S Bus role
//**************************************************************************************************
static NAU8814_I2S_BUS_ROLE NauClkIoEnToBusRole(const NAU8814_CLK_IO_EN code)
{
    NAU8814_I2S_BUS_ROLE busRole = 0;
    switch ((U8)code)
    {
    case NAU8814_CLKIOEN_SLAVE_MODE:
        busRole = NAU8814_BUS_ROLE_SLAVE;
        break;
    case NAU8814_CLKIOEN_MASTER_MODE:
        busRole = NAU8814_BUS_ROLE_MASTER;
        break;
    }
    return busRole;
} // end of NauClkIoEnToBusRole()


//**************************************************************************************************
//! Check that the NAU8814 chip is connected to I2C
//!
//! \note       NAU8814 Is Connected low level
//!
//! \param[in]  Node - NAU8814 RAM Node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_IsConnected_ll(NAU8814_HANDLE* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Node)
    {
        U16 word = 0;
        ret = NAU8814_ReadRegLowLevel(Node, NAU8814_REGIS_2_WIRE_ID, &word);
        if (RESULT_OK == ret)
        {
            if (NAU8814_7BIT_ADDRESS == word)
            {
                ret = RESULT_OK;
            }
            else
            {
                ret = RESULT_NOT_OK;
            }
        }
        else
        {
            ret = RESULT_NOT_OK;
        }
    }
    return ret;
} // end of NAU8814_IsConnected_ll()

//**************************************************************************************************
//! Convert nau8814 plln to nau8814 interanl code
//!
//! \note        Convert nau8814 pll n to nau8814 internal code
//!
//! \param[in]  pllN - plln in dec
//!
//! \return     nau8814 internal code
//**************************************************************************************************
static NAU8814_PLL_N NAU8814_PllNToCode(const U8 pllN)
{
    NAU8814_PLL_N pllNcode = 1;
    switch (pllN)
    {
    case 5:
        pllNcode = NAU8814_PLLN_5;
        break;
    case 6:
        pllNcode = NAU8814_PLLN_6;
        break;
    case 7:
        pllNcode = NAU8814_PLLN_7;
        break;
    case 8:
        pllNcode = NAU8814_PLLN_8;
        break;
    case 9:
        pllNcode = NAU8814_PLLN_9;
        break;
    case 10:
        pllNcode = NAU8814_PLLN_10;
        break;
    case 11:
        pllNcode = NAU8814_PLLN_11;
        break;
    case 12:
        pllNcode = NAU8814_PLLN_12;
        break;
    case 13:
        pllNcode = NAU8814_PLLN_13;
        break;
    default:
        pllNcode = NAU8814_PLLN_NOT_VALID_0;
        break;
    }
    return pllNcode;
} // end of NAU8814_PllNToCode()


//**************************************************************************************************
//! NAU8814 configuration Register
//!
//! \note       Apply resister array  to NAU8814 ASIC
//!
//! \param[in]  num - Audio codec instance number (natural number)
//! \param[in]  Reg - resister array
//! \param[in]  cnt - resister array size
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_ConfigRegister(const U8 num,
                                         const NAU8814_REGISTER_VAL* const Reg,
                                         const U32 cnt)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Reg)
    {
        if (cnt)
        {
            U32 i = 0;
            U32 ok = 0;
            for (i = 0; i < cnt; i++)
            {
                ret = NAU8814_WriteReg(num, Reg[i].addr, Reg[i].Reg.word);
                if (RESULT_OK == ret)
                {
                    ok++;
                }
            }

            if (ok == cnt)
            {
                ret = RESULT_OK;
            }
            else
            {
                ret = RESULT_NOT_OK;
            }
        }
    }
    return ret;
} // end of NAU8814_ConfigRegister()


//**************************************************************************************************
//! NAU8814 Proc One
//!
//! \note       NAU8814 Proc One
//!
//! \param[in]  num - Audio codec instance number (natural number)
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//*****************************************************************************
static STD_RESULT NAU8814_ProcOne(const U8 num)
{
    STD_RESULT            ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
            if (Node->init)
            {
                U32 upTimeMs = MCU_GetUpTimeMs();
                switch (Node->state)
                {
                    case NAU8814_STATE_PLAY_AND_RECORD:
                    {
                    }
                    break;

                    case NAU8814_STATE_PLAY:
                    {
                        if (Node->playOffTimeStampMs < upTimeMs)
                        {
                            ret = NAU8814_DAC_CtrlPlay(num, FALSE);
                        }
                    }
                    break;

                    case NAU8814_STATE_RECORD:
                    {
                        if (Node->recOffTimeStampMs < upTimeMs)
                        {
                            ret = NAU8814_ADC_CtrlRecord(num, FALSE);
                        }
                    }
                    break;
                    default:
                        {

                        }
                        break;
                }// end of switch (Node->state)
            }// end of if (Node->init)
        }// end of if (Node)
    }// end of if (Config)
    return ret;
} // end of NAU8814_ProcOne()



//**************************************************************************************************
//! NAU8814 Init Common
//!
//! \note       NAU8814 Init Common
//!
//! \param[in]  configuration - configuration node if ROM
//! \param[out] Node - NAU8814 RAM Node
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_InitCommon(const NAU8814_CONFIG* const Config,
                                     NAU8814_HANDLE* const Node)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Config)
    {
        if (Node)
        {
            Node->adcOn = Config->adcOn;
            Node->auxGain = Config->auxGain;
            Node->chipAddr = Config->chipAddr;
            Node->dacGain = Config->dacGain;
            Node->ddsNum = Config->ddsNum;
            Node->i2cNum = Config->i2cNum;
            Node->i2sNum = Config->i2sNum;
            Node->i2sRole = Config->i2sRole;
            Node->pMicGain = Config->pMicGain;
            Node->pgaGain = Config->pgaGain;
            Node->pllK = Config->pllK;
            ret = RESULT_OK;
        }
    }
    return ret;
} // end of NAU8814_InitCommon()

//**************************************************************************************************
//! NAU8814 Init PLL
//!
//! \note       NAU8814 Init PLL
//!
//! \param[in]  num - Audio codec instance number (natural number)
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_InitPll(const U8 num)
{
    STD_RESULT            ret = RESULT_NOT_OK;
    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
            ret = NAU8814_SetPllN(num, Config->pllN);
            ret = NAU8814_GetPllK(num, &Node->pllK);
        }
    }
    return ret;
} // end of NAU8814_InitPll()

//**************************************************************************************************
//! Convert NAU8814 PLL N code to physical value
//!
//! \note       NAU8814 PLL N code to value
//!
//! \param[in]  pllNcode - pll n code
//!
//! \return     PLL N Value
//**************************************************************************************************
static U8 NAU8814_PllNcodeToValue(const NAU8814_PLL_N pllNcode)
{
    U8 pllNvalue = 0;
    switch ((U8)pllNcode)
    {
    case NAU8814_PLLN_NOT_VALID_0:
        pllNvalue = 0;
        break;
    case NAU8814_PLLN_NOT_VALID_1:
        pllNvalue = 0;
        break;
    case NAU8814_PLLN_NOT_VALID_2:
        pllNvalue = 0;
        break;
    case NAU8814_PLLN_NOT_VALID_3:
        pllNvalue = 0;
        break;
    case NAU8814_PLLN_NOT_VALID_4:
        pllNvalue = 0;
        break;
    case NAU8814_PLLN_5:
        pllNvalue = 5;
        break;
    case NAU8814_PLLN_6:
        pllNvalue = 6;
        break;
    case NAU8814_PLLN_7:
        pllNvalue = 7;
        break;
    case NAU8814_PLLN_8:
        pllNvalue = 8;
        break;
    case NAU8814_PLLN_9:
        pllNvalue = 9;
        break;
    case NAU8814_PLLN_10:
        pllNvalue = 10;
        break;
    case NAU8814_PLLN_11:
        pllNvalue = 11;
        break;
    case NAU8814_PLLN_12:
        pllNvalue = 12;
        break;
    case NAU8814_PLLN_13:
        pllNvalue = 13;
        break;
    case NAU8814_PLLN_NOT_VALID_14:
        pllNvalue = 0;
        break;
    case NAU8814_PLLN_NOT_VALID_15:
        pllNvalue = 0;
        break;
    }
    return pllNvalue;
} // end of NAU8814_PllNcodeToValue()


//**************************************************************************************************
//! Convert NAU8814 PLL D code to physical value
//!
//! \note       NAU8814 PLL D-code to physical value
//!
//! \param[in]  divCode - div Code
//!
//! \return     Execution status. See STD_RESULT enumeration
//**************************************************************************************************
static U8 NAU8814_PllDcodeToValue(const NAU8814_PLL_MCLK divCode)
{
    U8 pllD = 0;
    switch ((U8)divCode)
    {
    case NAU8814_PLLMCLK_MCLK_DIV1:
        pllD = 1;
        break;
    case NAU8814_PLLMCLK_MCLK_DIV2:
        pllD = 2;
        break;
    }
    return pllD;
} // end of NAU8814_PllDcodeToValue()

//**************************************************************************************************
//! NAU8814 read register low level
//!
//! \note       NAU8814 read i2c register
//!
//! \param[in]  Node - ASIC node pointer
//! \param[in]  registerAddr - register address
//! \param[out] word - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_ReadRegLowLevel(NAU8814_HANDLE* const Node,
                                          const NAU8814_REGISTER_ADDR registerAddr,
                                          U16* const word)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Node)
    {
        if (word)
        {
            if (FALSE == Node->deInit)
            {
                U16 reg_word = 0;
                U8 addr_val = registerAddr;
                addr_val = addr_val << 1;
                RESET_BIT_NUM(addr_val, 0);
                ret = I2C_ReadWord(Node->i2cNum, Node->chipAddr, addr_val, &reg_word);
                if (RESULT_OK == ret)
                {
                    *word = reg_word;
                }
            }
        }
    }
    return ret;
} // end of NAU8814_ReadRegLowLevel()

//**************************************************************************************************
//! NAU8814 Write Reg low level
//!
//! \note       NAU8814_WriteRegLowLevel
//!
//! \param[in]  Node - NAU8814 RAM Node
//! \param[in]  addr - nau8814 register addr
//! \param[out] word - reg value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
static STD_RESULT NAU8814_WriteRegLowLevel(NAU8814_HANDLE* const Node,
                                           const NAU8814_REGISTER_ADDR addr,
                                           const U16 word)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Node)
    {
        if (FALSE == Node->deInit)
        {
            ret = NAU8814_IsValidI2cRegisterAddr(addr);
            if (RESULT_OK == ret)
            {
                NAU8814_WRITE_FRAME Frame;
                Frame.word = 0;
                Frame.registerAddr = WORD_MASK_7BIT & addr;
                Frame.regValue = WORD_MASK_9BIT & word;

                Frame.word = reverse_byte_order_uint16(Frame.word);
                ret = I2C_WriteReg(Node->i2cNum, Node->chipAddr, Frame.buff, NAU8814_FRAME_SIZE);
            }
        }
    }
    return ret;
} // end of NAU8814_WriteRegLowLevel()



//******************************* end of file ******************************************************
