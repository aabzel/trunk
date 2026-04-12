/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */


#include "device_registers.h"
#include "system_YTM32B1ME0.h"
#include "stdbool.h"

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

#ifndef EFM_CTRL_WE_MASK
/*FUNCTION**********************************************************************
 *
 * Function Name : EfmInitMpu
 * Description   : This function initializes the MPU to protect the 
 * all flash memory regions. Only internal use.
 *
 * Implements    : EfmInitMpu_Activity
 *END**************************************************************************/
static void EfmInitMpu(void)
{
    const uint32_t lastRnr = ((MPU->TYPE & MPU_TYPE_DREGION_Msk) >> MPU_TYPE_DREGION_Pos) - 1U;
    ARM_MPU_Region_t mpuTable[1] = {
#if defined(FEATURE_EFM_HAS_DATA_FLASH) && (FEATURE_EFM_HAS_DATA_FLASH == 1)
        //                     BASE          SH              RO   NP   XN                         LIMIT                               ATTR 
        { .RBAR = ARM_MPU_RBAR(0x00000000UL, ARM_MPU_SH_NON, 1UL, 1UL, 0UL), .RLAR = ARM_MPU_RLAR(FEATURE_EFM_DATA_ARRAY_END_ADDRESS, 7UL) },
#else
        //                     BASE          SH              RO   NP   XN                         LIMIT                               ATTR 
        { .RBAR = ARM_MPU_RBAR(0x00000000UL, ARM_MPU_SH_NON, 1UL, 1UL, 0UL), .RLAR = ARM_MPU_RLAR(FEATURE_EFM_MAIN_ARRAY_END_ADDRESS, 7UL) },
#endif
    };

    ARM_MPU_SetMemAttr(7UL, ARM_MPU_ATTR(           /* Normal memory */
        ARM_MPU_ATTR_MEMORY_(1UL, 0UL, 1UL, 0UL),   /* Outer Write-Through non-transient with read allocate and write not allocate */
        ARM_MPU_ATTR_MEMORY_(1UL, 0UL, 1UL, 0UL)    /* Inner Write-Through non-transient with read allocate and write not allocate */
    ));
    ARM_MPU_Load(lastRnr, mpuTable, 1);
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk);
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SystemInit
 * Description   : This function disables the watchdog, enables FPU
 * and the power mode protection if the corresponding feature macro
 * is enabled. SystemInit is called from startup_device file.
 *
 * Implements    : SystemInit_Activity
 *END**************************************************************************/
void SystemInit(void)
{
/**************************************************************************/
                      /* FPU ENABLE*/
/**************************************************************************/
#ifdef ENABLE_FPU
  /* Enable CP10 and CP11 coprocessors */
  SCB->CPACR |= (3UL << 20 | 3UL << 22);
#endif /* ENABLE_FPU */
/**************************************************************************/
/* EFM CONTRROL */
/**************************************************************************/
    EFM->CTRL |= EFM_CTRL_DPD_EN_MASK | EFM_CTRL_PREFETCH_EN_MASK;
#ifndef EFM_CTRL_WE_MASK
    EfmInitMpu();
#endif
/**************************************************************************/
/* RCU CONTROL */
/**************************************************************************/
    CIM->CTRL |= CIM_CTRL_LOCKUPEN_MASK;
/**************************************************************************/
/* WDOG DISABLE*/
/**************************************************************************/
#if (DISABLE_WDOG)
    WDG0->SVCR = 0xB631;
    WDG0->SVCR = 0xC278;
    WDG0->CR &= ~WDG_CR_EN_MASK;
#endif /* (DISABLE_WDOG) */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SystemCoreClockUpdate
 * Description   : This function must be called whenever the core clock is changed
 * during program execution. It evaluates the clock register settings and calculates
 * the current core clock.
 *
 * Implements    : SystemCoreClockUpdate_Activity
 *END**************************************************************************/
void SystemCoreClockUpdate(void)
{
    uint32_t refClkFreq;
    uint32_t feedbackDiv;
    uint32_t referenceDiv;
    switch ((SCU->STS & SCU_STS_CLKST_MASK) >> SCU_STS_CLKST_SHIFT)
    {
        case 0x0:
            /* FIRC */
            SystemCoreClock = FEATURE_SCU_FIRC_FREQ;
            break;
#if defined(FEATURE_SCU_SUPPORT_PLL) && (FEATURE_SCU_SUPPORT_PLL)
        case 0x1:
            /* PLL */
            if (SCU_PLL_CTRL_REFCLKSRCSEL_MASK == (SCU->PLL_CTRL & SCU_PLL_CTRL_REFCLKSRCSEL_MASK))
            {
                /* Select FIRC as PLL reference clock */
                refClkFreq = FEATURE_SCU_FIRC_FREQ;
            }
            else
            {
                /* Select FXOSC as PLL reference clock */
                refClkFreq = FEATURE_SCU_FXOSC_FREQ;
            }
            /* Fout = (Fref * Ndiv) / ( 2 * Npre) */
            feedbackDiv = ((SCU->PLL_CTRL & SCU_PLL_CTRL_FBDIV_MASK) >> SCU_PLL_CTRL_FBDIV_SHIFT) + 1;
            referenceDiv = ((SCU->PLL_CTRL & SCU_PLL_CTRL_REFDIV_MASK) >> SCU_PLL_CTRL_REFDIV_SHIFT) + 1;
            SystemCoreClock = ((refClkFreq * feedbackDiv) / referenceDiv) >> 1;
            break;
#endif /* FEATURE_SCU_SUPPORT_PLL */
        case 0x2:
            /* FXOSC */
            SystemCoreClock = FEATURE_SCU_FXOSC_FREQ;
            break;
        case 0x3:
            /* SIRC */
            SystemCoreClock = FEATURE_SCU_SIRC_FREQ;
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SystemSoftwareReset
 * Description   : This function is used to initiate a system reset
 *
 * Implements    : SystemSoftwareReset_Activity
 *END**************************************************************************/
void SystemSoftwareReset(void)
{
    NVIC_SystemReset();
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
