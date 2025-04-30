#include "clock_config.h"

#include "clock.h"
#include "log.h"
#include "sys_config.h"

ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .hf_source = XTALL_FREQ_HZ,      // CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .valid = true,
    .core_clock_mhz = 140000000,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};

#ifdef HAS_CPU_CLOCK_168MHZ
static bool clock_init_168mhz(void) {
    bool res = true;
    return res;
}
#endif

#ifdef HAS_AT32F413_FIRMWARE_LIB
/**
 * @brief  system clock config program
 * @note   the system clock is configured as follow:
 *         system clock (sclk)   = hext / 2 * pll_mult
 *         system clock source   = HEXT_VALUE
 *         - hext                = 16000000
 *         - sclk                = 96000000
 *         - ahbdiv              = 1
 *         - ahbclk              = 96000000
 *         - apb1div             = 2
 *         - apb1clk             = 48000000
 *         - apb2div             = 2
 *         - apb2clk             = 48000000
 *         - pll_mult            = 12
 *         - pll_range           = GT72MHZ (greater than 72 mhz)
 * @param  none
 * @retval none
 */
void system_clock_config_96(void) {
    /* reset crm */
    crm_reset();

    /* enable hext */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

    /* wait till hext is ready */
    while(crm_hext_stable_wait() == ERROR) {
    }

    /* config pll clock resource */
    crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_12, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

    /* enable pll */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

    /* wait till pll is ready */
    while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET) {
    }

    /* config ahbclk */
    crm_ahb_div_set(CRM_AHB_DIV_1);

    /* config apb2clk */
    crm_apb2_div_set(CRM_APB2_DIV_2);

    /* config apb1clk */
    crm_apb1_div_set(CRM_APB1_DIV_2);

    /* select pll as system clock source */
    crm_sysclk_switch(CRM_SCLK_PLL);

    /* wait till pll is used as system clock source */
    while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL) {
    }

    /* update system_core_clock global variable */
    system_core_clock_update();
}
#endif

#if 0
/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = hext / 2 * pll_mult
  *         system clock source   = HEXT_VALUE
  *         - hext                = 16000000
  *         - sclk                = 104000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 104000000
  *         - apb1div             = 2
  *         - apb1clk             = 52000000
  *         - apb2div             = 2
  *         - apb2clk             = 52000000
  *         - pll_mult            = 13
  *         - pll_range           = GT72MHZ (greater than 72 mhz)
  * @param  none
  * @retval none
  */
void system_clock_config_104(void)
{
  /* reset crm */
  crm_reset();

  /* enable hext */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

   /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_13, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* update system_core_clock global variable */
  system_core_clock_update();
}

/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = hext / 2 * pll_mult
  *         system clock source   = pll (hext)
  *         - hext                = HEXT_VALUE
  *         - sclk                = 192000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 192000000
  *         - apb2div             = 2
  *         - apb2clk             = 96000000
  *         - apb1div             = 2
  *         - apb1clk             = 96000000
  *         - pll_mult            = 48
  *         - pll_range           = GT72MHZ (greater than 72 mhz)
  * @param  none
  * @retval none
  */
static void system_clock_config_192MHz(void)
{
  /* reset crm */
  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

   /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_48, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk, the maximum frequency of APB1/APB2 clock is 100 MHz  */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk, the maximum frequency of APB1/APB2 clock is 100 MHz  */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE); //ee

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}
#endif

#ifdef HAS_MCAL_AT32
bool system_clock_config(void) {
    system_clock_config_96();
    return true;
}
#endif
