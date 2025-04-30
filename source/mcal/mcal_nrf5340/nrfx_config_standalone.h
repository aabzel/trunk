#ifndef NRFX_CONFIG_H
#define NRFX_CONFIG_H

#include "core_select.h"

#ifdef	HAS_CORE_APP

#define NRF_COMP         NRF_COMP_S
#define NRF_CLOCK        NRF_CLOCK_S
#define NRF_DCNF         NRF_DCNF_S
#define NRF_DPPIC        NRF_DPPIC_S
#define NRF_EGU0         NRF_EGU0_S
#define NRF_EGU1         NRF_EGU1_S
#define NRF_EGU2         NRF_EGU2_S
#define NRF_EGU3         NRF_EGU3_S
#define NRF_EGU4         NRF_EGU4_S
#define NRF_EGU5         NRF_EGU5_S
#define NRF_FPU          NRF_FPU_S
#define NRF_I2S          NRF_I2S0_S
#define NRF_IPC          NRF_IPC_S
#define NRF_KMU          NRF_KMU_S
#define NRF_LPCOMP       NRF_LPCOMP_S
#define NRF_MUTEX        NRF_MUTEX_S
#define NRF_NFCT         NRF_NFCT_S
#define NRF_NVMC         NRF_NVMC_S
#define NRF_OSCILLATORS  NRF_OSCILLATORS_S
#define NRF_P0           NRF_P0_S
#define NRF_P1           NRF_P1_S
#define NRF_PDM0         NRF_PDM0_S
#define NRF_POWER        NRF_POWER_S
#define NRF_PWM0         NRF_PWM0_S
#define NRF_PWM1         NRF_PWM1_S
#define NRF_PWM2         NRF_PWM2_S
#define NRF_PWM3         NRF_PWM3_S
#define NRF_QDEC0        NRF_QDEC0_S
#define NRF_QDEC1        NRF_QDEC1_S
#define NRF_QSPI         NRF_QSPI_S
#define NRF_REGULATORS   NRF_REGULATORS_S
#define NRF_RESET        NRF_RESET_S
#define NRF_RTC0         NRF_RTC0_S
#define NRF_RTC1         NRF_RTC1_S
#define NRF_SAADC        NRF_SAADC_S
#define NRF_SPIM0        NRF_SPIM0_S
#define NRF_SPIM1        NRF_SPIM1_S
#define NRF_SPIM2        NRF_SPIM2_S
#define NRF_SPIM3        NRF_SPIM3_S
#define NRF_SPIM4        NRF_SPIM4_S
#define NRF_SPIS0        NRF_SPIS0_S
#define NRF_SPIS1        NRF_SPIS1_S
#define NRF_SPIS2        NRF_SPIS2_S
#define NRF_SPIS3        NRF_SPIS3_S
#define NRF_TIMER0       NRF_TIMER0_S
#define NRF_TIMER1       NRF_TIMER1_S
#define NRF_TIMER2       NRF_TIMER2_S
#define NRF_TWIM0        NRF_TWIM0_S
#define NRF_TWIM1        NRF_TWIM1_S
#define NRF_TWIM2        NRF_TWIM2_S
#define NRF_TWIM3        NRF_TWIM3_S
#define NRF_TWIS0        NRF_TWIS0_S
#define NRF_TWIS1        NRF_TWIS1_S
#define NRF_TWIS2        NRF_TWIS2_S
#define NRF_TWIS3        NRF_TWIS3_S
#define NRF_UARTE0       NRF_UARTE0_S
#define NRF_UARTE1       NRF_UARTE1_S
#define NRF_UARTE2       NRF_UARTE2_S
#define NRF_UARTE3       NRF_UARTE3_S
#define NRF_USBD         NRF_USBD_S
#define NRF_USBREGULATOR NRF_USBREGULATOR_S
#define NRF_VMC          NRF_VMC_S
#define NRF_WDT0         NRF_WDT0_S
#define NRF_WDT1         NRF_WDT1_S

#endif /*HAS_CORE_APP*/



#ifdef	HAS_CORE_NET
#define NRF_ACL        NRF_ACL_NS
#define NRF_AAR        NRF_AAR_NS
#define NRF_CCM        NRF_CCM_NS
#define NRF_CLOCK      NRF_CLOCK_NS
#define NRF_DCNF       NRF_DCNF_NS
#define NRF_DPPIC      NRF_DPPIC_NS
#define NRF_ECB        NRF_ECB_NS
#define NRF_EGU0       NRF_EGU0_NS
#define NRF_FICR       NRF_FICR_NS
#define NRF_GPIOTE     NRF_GPIOTE_NS
#define NRF_IPC        NRF_IPC_NS
#define NRF_NVMC       NRF_NVMC_NS
#define NRF_P0         NRF_P0_NS
#define NRF_P1         NRF_P1_NS
#define NRF_POWER      NRF_POWER_NS
#define NRF_RADIO      NRF_RADIO_NS
#define NRF_RESET      NRF_RESET_NS
#define NRF_RNG        NRF_RNG_NS
#define NRF_RTC0       NRF_RTC0_NS
#define NRF_RTC1       NRF_RTC1_NS
#define NRF_SPIM0      NRF_SPIM0_NS
#define NRF_SPIS0      NRF_SPIS0_NS
#define NRF_SWI0       NRF_SWI0_NS
#define NRF_SWI1       NRF_SWI1_NS
#define NRF_SWI2       NRF_SWI2_NS
#define NRF_SWI3       NRF_SWI3_NS
#define NRF_TEMP       NRF_TEMP_NS
#define NRF_TIMER0     NRF_TIMER0_NS
#define NRF_TIMER1     NRF_TIMER1_NS
#define NRF_TIMER2     NRF_TIMER2_NS
#define NRF_TWIM0      NRF_TWIM0_NS
#define NRF_TWIS0      NRF_TWIS0_NS
#define NRF_UARTE0     NRF_UARTE0_NS
#define NRF_UICR       NRF_UICR_NS
#define NRF_VMC        NRF_VMC_NS
#define NRF_VREQCTRL   NRF_VREQCTRL_NS
#define NRF_WDT        NRF_WDT_NS
#endif /*HAS_CORE_NET*/


/*
 * The following section provides the name translation for peripherals with
 * only one type of access available. For these peripherals, you cannot choose
 * between secure and non-secure mapping.
 */
#ifdef	HAS_CORE_APP
#define NRF_CACHE      NRF_CACHE_S
#define NRF_CACHEINFO  NRF_CACHEINFO_S
#define NRF_CACHEDATA  NRF_CACHEDATA_S
#define NRF_CRYPTOCELL NRF_CRYPTOCELL_S
#define NRF_FICR       NRF_FICR_S
#define NRF_GPIOTE0    NRF_GPIOTE0_S
#define NRF_GPIOTE1    NRF_GPIOTE1_NS
#define NRF_SPU        NRF_SPU_S
#define NRF_UICR       NRF_UICR_S


/* Fixups for GPIOTE driver. */
#define NRF_GPIOTE        NRF_GPIOTE0_S
#define GPIOTE_IRQHandler GPIOTE0_IRQHandler

/* Fixups for QDEC driver. */
#define NRF_QDEC        NRF_QDEC0
#define QDEC_IRQHandler QDEC0_IRQHandler
#define NRFX_QSPI_ENABLED               1

#endif /*HAS_CORE_APP*/



#define NRFX_SYSTICK_ENABLED            1
#define NRFX_NVMC_ENABLED               1

#define NRFX_POWER_ENABLED              1
#define NRFX_POWER_DEFAULT_CONFIG_IRQ_PRIORITY  7
#define NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY  7
#define NRFX_CLOCK_CONFIG_LF_SRC NRF_CLOCK_LFCLK_Xtal
#define NRFX_CLOCK_CONFIG_HFCLK192M_SRC  NRF_CLOCK_HFCLK_HIGH_ACCURACY

#endif // NRFX_CONFIG_H
