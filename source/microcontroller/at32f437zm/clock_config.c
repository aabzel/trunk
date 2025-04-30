#include "clock_config.h"

#include "log.h"
#include "sys_config.h"
#include "clock.h"
//#include "clock_custom.h"

ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .hf_source = CLK_HI_FREQ_8MHZ,  //  CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .valid = true,
    .core_clock_mhz = 288000000,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};

#ifdef HAS_MCAL_AT32
/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = (hext * pll_ns)/(pll_ms * pll_fr)
  *         system clock source   = pll (hext)
  *         - hext                = HEXT_VALUE
  *         - sclk                = 288000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 288000000
  *         - apb2div             = 2
  *         - apb2clk             = 144000000
  *         - apb1div             = 2
  *         - apb1clk             = 144000000
  *         - pll_ns              = 144
  *         - pll_ms              = 1
  *         - pll_fr              = 4
  * @param  none
  * @retval none
  */
void system_clock_config(void)
{
  /* reset crm */
  crm_reset();

  /* enable pwc periph clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

  /* config ldo voltage */
  pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V3);

  /* set the flash clock divider */
  flash_clock_divider_set(FLASH_CLOCK_DIV_3);

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

  /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource
  common frequency config list: pll source selected  hick or hext(8mhz)
  _________________________________________________________________________________________________
  |        |         |         |         |         |         |         |         |        |        |
  |pll(mhz)|   288   |   252   |   216   |   192   |   180   |   144   |   108   |   72   |   36   |
  |________|_________|_________|_________|_________|_________|_________|_________|_________________|
  |        |         |         |         |         |         |         |         |        |        |
  |pll_ns  |   144   |   126   |   108   |   96    |   90    |   72    |   108   |   72   |   72   |
  |        |         |         |         |         |         |         |         |        |        |
  |pll_ms  |   1     |   1     |   1     |   1     |   1     |   1     |   1     |   1    |   1    |
  |        |         |         |         |         |         |         |         |        |        |
  |pll_fr  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_8  |   FR_8 |   FR_16|
  |________|_________|_________|_________|_________|_________|_________|_________|________|________|

  if pll clock source selects hext with other frequency values, or configure pll to other
  frequency values, please use the at32 new clock  configuration tool for configuration.  */
  crm_pll_config(CRM_PLL_SOURCE_HEXT, 144, 1, CRM_PLL_FR_4);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* config apb2clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk, the maximum frequency of APB1/APB2 clock is 144 MHz  */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

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

#ifdef HAS_CPU_CLOCK_168MHZ
static bool clock_init_168mhz(void) {
    bool res = true;
    return res;
}
#endif

#ifdef HAS_MCAL_AT32
/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = (hext * pll_ns)/(pll_ms * pll_fr)
  *         system clock source   = HEXT_VALUE
  *         - hext                = 8000000
  *         - sclk                = 100000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 100000000
  *         - apb1div             = 2
  *         - apb1clk             = 50000000
  *         - apb2div             = 2
  *         - apb2clk             = 50000000
  *         - pll_ns              = 400
  *         - pll_ms              = 4
  *         - pll_fr              = 8
  * @param  none
  * @retval none
  */
void system_clock_config_100mhz(void)
{
  /* reset crm */
  crm_reset();

  /* enable pwc periph clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

  /* config ldo voltage */
  pwc_ldo_output_voltage_set(PWC_LDO_OUTPUT_1V0);

  /* set the flash clock divider */
  flash_clock_divider_set(FLASH_CLOCK_DIV_2);

  /* enable hext */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

   /* wait till hext is ready */
  while(crm_hext_stable_wait() == ERROR)
  {
  }

  /* config pll clock resource
  common frequency config list: pll source selected  hick or hext(8mhz)
  _________________________________________________________________________________________________
  |        |         |         |         |         |         |         |         |        |        |
  |pll(mhz)|   288   |   252   |   216   |   192   |   180   |   144   |   108   |   72   |   36   |
  |________|_________|_________|_________|_________|_________|_________|_________|_________________|
  |        |         |         |         |         |         |         |         |        |        |
  |pll_ns  |   144   |   126   |   108   |   96    |   90    |   72    |   108   |   72   |   72   |
  |        |         |         |         |         |         |         |         |        |        |
  |pll_ms  |   1     |   1     |   1     |   1     |   1     |   1     |   1     |   1    |   1    |
  |        |         |         |         |         |         |         |         |        |        |
  |pll_fr  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_4  |   FR_8  |   FR_8 |   FR_16|
  |________|_________|_________|_________|_________|_________|_________|_________|________|________|

  if pll clock source selects hext with other frequency values, or configure pll to other
  frequency values, please use the at32 new clock  configuration tool for configuration.  */
  crm_pll_config(CRM_PLL_SOURCE_HEXT, 400, 4, CRM_PLL_FR_8);

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
#endif

__attribute__((weak)) bool clock_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(SYS, "ClockInit XTAL:%u Hz", XTALL_FREQ_HZ);
#endif
#ifdef HAS_MCAL_AT32
    system_clock_config_100mhz();
#endif

    return res;
}
