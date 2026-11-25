/**
 * @file system_init.c
 * @author Flagchip
 * @brief interrupt configuration
 * @version 2.0.0
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2020-2025 Flagchip Semiconductors Co., Ltd.
 *
 */
 #include "device_header.h"

#define SCB_CPACR     0xE000ED88
/* #define DATA_IN_DTCM */

/* keil also contains macro __GNUC__, so elif must be used */
#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && __ARMCC_VERSION >= 6000000)

  #if defined __ARM_PCS_VFP
    #define __FPU_USED          1U
    #define __FPU_PRESENT       1U
  #else
    #define __FPU_USED          0U
  #endif
  
extern uint32 Load$$SRAM$$Base;
extern uint32 Image$$SRAM$$Base;
extern uint32 Load$$SRAM$$RW$$Base;
extern uint32 Image$$SRAM$$RW$$Base;
extern uint32 Image$$SRAM$$RW$$Limit;
extern uint32 Image$$SRAM$$ZI$$Base;
extern uint32 Image$$SRAM$$ZI$$Limit;

#elif defined(__GNUC__) || defined(__ghs__)
extern uint32 __data_start__[];
extern uint32 __data_end__[];
extern uint32 __data_init_start__[];
extern uint32 __bss_start__[];
extern uint32 __bss_end__[];
#elif defined(__ICCARM__)
#pragma section = ".data"
#pragma section = ".data_init"
#pragma section = ".bss"

uint32* const __data_start__ = (uint32*)(__section_begin(".data"));
uint32* const __data_end__ = (uint32*)(__section_end(".data"));
uint32* const __data_init_start__ = (uint32*)(__section_begin(".data_init"));
uint32* const __bss_start__ = (uint32*)(__section_begin(".bss"));
uint32* const __bss_end__ = (uint32*)(__section_end(".bss"));

#endif

extern void data_init(void);
extern void system_init(void);

static void data_clear(uint32 *pHead, uint32 *pTail)
{
    while (pHead < pTail)
    {
        *pHead = 0U;
        pHead++;
    }
}

static void data_copy(uint32 *pHead, uint32 *pTail, uint32 *pSrc)
{
    while (pHead < pTail)
    {
        *pHead = *pSrc;
        pHead++;
        pSrc++;
    }
}

void data_init(void)
{
#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && __ARMCC_VERSION >= 6000000)
    uint32* __bss_start__ = (uint32_t*)&Image$$SRAM$$ZI$$Base;
    uint32* __bss_end__ = (uint32_t*)&Image$$SRAM$$ZI$$Limit;
    uint32* __data_init_start__ = (uint32_t*)&Load$$SRAM$$RW$$Base;
    uint32* __data_start__ = (uint32_t*)&Image$$SRAM$$RW$$Base;
    uint32* __data_end__ = (uint32_t*)&Image$$SRAM$$RW$$Limit;
#endif

    /* core 0 */
    if (0U == Cpm_HWA_GetCoreId())
    {
        /* bss */
        data_clear(__bss_start__, __bss_end__);
        /* data */
        data_copy(__data_start__, __data_end__, __data_init_start__);

    }


}




#define REG_VAL(addr)                     (*(volatile uint32 *)(addr))
#define REG_VAL_OFF(addr,offset)          (*(volatile uint32 *)((addr)+(offset)))
#define WDOG0_BASE_ADDR                   0x40022000U
#define WDOG1_BASE_ADDR                   0x40433000U
#define WDOG2_BASE_ADDR                   0x40434000U
#define WDOG3_BASE_ADDR                   0x40435000U
#define SMC_STANDBY_CFG_ADDR              0x40045010U
#define SCM_BASE_ADDR                     0x40072000U
#define RGM_BASE_ADDR                     0x40046000U
#define PCC_STCU_ADDR                     0x400241FCU
#define STCU_BASE_ADDR                    0x4007F000U

#define DWT_CYCCNT_ADDR                   0xE0001004U
#define DEMCR_ADDR                        0xE000EDFCU

#define CPACR_ADDR                        0xE000ED88U

static void wdog_disable(uint32 wdog_base)
{
    uint32 u32ttt = 128;
    uint32 u32First = 1;
    /* if it is not first time configure wdog, unlock status only pending for 128 bus clock */
    do {
        /* check unlock active */
        if (0U == (0x800u & REG_VAL(wdog_base)))
        {
            /* if unlock statue turn to 0, means not first time configuring wdog */
            u32First = 0;
            break;
        }
    } while (u32ttt--);

    if (u32First == 0U)
    {
        /* only unlock=0, reconfig=1, can unlock wdog*/

        /* waiting reconfiguration successful */
        while (0U == (0x400u & REG_VAL(wdog_base)));

        /* unlock wdog */
        REG_VAL_OFF(wdog_base, 4) = 0x08181982;
        /* waiting unlock active */
        while (0U == (0x800u & REG_VAL(wdog_base)));

    }
    REG_VAL(wdog_base) = 0x2920;
    REG_VAL_OFF(wdog_base, 8) = 0xF000;
    /* waiting reconfiguration successful */
    while (0U == (0x400u & REG_VAL(wdog_base)));
}


void system_init(void)
{
    uint32 u32CoreId;
    /* only errata in debug mode */
    /* if (0 != (0x01 & REG_VAL(0xE000EDF0))) */
    {
        /* --------------- Errata MCU debug Issue 1 lockstep lost start -------------- */
        /* clear dwt counter to handle cpu0 lockstep error under debug */
        REG_VAL(DEMCR_ADDR) = 0x01000000u; /* open TRCENA */
        REG_VAL(DWT_CYCCNT_ADDR) = 0x0u;  /* Clear DWT_CYCCNT */
        /* ----------------- Errata MCU debug Issue 1 lockstep lost end -------------- */
    }

    u32CoreId = Cpm_HWA_GetCoreId();
    if (0U == u32CoreId)
    {
        uint32 u32ResetType = (REG_VAL_OFF(RGM_BASE_ADDR, 8));
        /* only power on reset or low power reset need to clear all ram */
        if (0U != (u32ResetType & 0x83))
        {
            /* --------- Errata MCU debug Issue 2 for ITCM error hardfault start --------- */
            /* ------------------ NVR must set ITCM initial auto enable ------------------ */
            /* disable AXBS/CPU0/1/2/ ECC */
            REG_VAL_OFF(SCM_BASE_ADDR, 0x20) = 0x0AAAAAAA;
            REG_VAL_OFF(SCM_BASE_ADDR, 0x24) = 0x000003AA;
            REG_VAL_OFF(SCM_BASE_ADDR, 0x28) = 0x00000AAA;
            REG_VAL_OFF(SCM_BASE_ADDR, 0x30) = 0x00000AAA;
            REG_VAL_OFF(SCM_BASE_ADDR, 0x38) = 0x00000AAA;

            /* STCU PCC Enable*/
            REG_VAL(PCC_STCU_ADDR) = 0x00800000;
            /* clear all itcm dtcm sram*/
            REG_VAL_OFF(STCU_BASE_ADDR, 0x50) = 0xFFFFFFFF; /* reserved bit write non-effect */
            if (0x01U == (u32ResetType & 0x01U)) /* only skip ram for standby wakeup */
            {
                /* Get SMC standby mode */
                uint32 standbymode = REG_VAL(SMC_STANDBY_CFG_ADDR) & 0x03U;
                /* config skip ram for special standby */
                REG_VAL_OFF(STCU_BASE_ADDR, 0x48) = 1u | (standbymode << 16);
            }
            else
            {
                REG_VAL_OFF(STCU_BASE_ADDR, 0x48) = 1u;
            }

            while (0 == ((REG_VAL_OFF(STCU_BASE_ADDR, 0x4C)) & 2u)); /* wait busy */
            while (0 == ((REG_VAL_OFF(STCU_BASE_ADDR, 0x4C)) & 1u)); /* wait done */

        }

        /* enable AXBS/CPU0/1/2/ ECC after every reset */
        REG_VAL_OFF(SCM_BASE_ADDR, 0x20) = 0x0FFFFFFF;
        REG_VAL_OFF(SCM_BASE_ADDR, 0x24) = 0x000003FF;
        REG_VAL_OFF(SCM_BASE_ADDR, 0x28) = 0x00000FFF;
        REG_VAL_OFF(SCM_BASE_ADDR, 0x30) = 0x00000FFF;
        REG_VAL_OFF(SCM_BASE_ADDR, 0x38) = 0x00000FFF;

        /* force store lr to stack after ram clearing */
        __asm volatile("push {lr}");

        __asm volatile("dsb");

        /* disable wdog 0 */
        wdog_disable(WDOG0_BASE_ADDR);


#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
        REG_VAL(CPACR_ADDR) = 0x00F00000u;    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

        /* force pop lr after operation finished, due to stack is destroyed via stcu  */
        __asm volatile("pop {pc}");
        /* Core 0 End */
    }
    else /* other cores do not need special stack operation */
    {
        if (1U == u32CoreId)
        {
            /* disable wdog 1 */
            wdog_disable(WDOG1_BASE_ADDR);
        }
        else if (2U == u32CoreId)
        {
            /* disable wdog 2 */
            wdog_disable(WDOG2_BASE_ADDR);
        }
        else if (3U == u32CoreId) /* only FC7300F8MDQ */
        {
            /* disable wdog 3 */
            wdog_disable(WDOG3_BASE_ADDR);
        }
        else
        {
        }


#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
        REG_VAL(CPACR_ADDR) = 0x00F00000u;    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

    }
}