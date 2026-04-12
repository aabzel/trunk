#include "mik32_hal_pcc.h"

/**
 * @brief Р’РєР»СЋС‡РёС‚СЊ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ.
 * @param Oscillator Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РґР»СЏ РІРєР»СЋС‡РµРЅРёСЏ.
 * @warning РђСЂРіСѓРјРµРЅС‚ С„СѓРЅРєС†РёРё РЅРµ СЏРІР»СЏРµС‚СЃСЏ РјР°СЃРєРѕР№.
 * 
 */
void HAL_PCC_OscEnable(HAL_PCC_OscillatorTypeTypeDef Oscillator)
{
    switch (Oscillator)
    {
    case PCC_OSCILLATORTYPE_HSI32M:
        WU->CLOCKS_SYS &= ~(1 << WU_CLOCKS_SYS_HSI32M_EN_S); // Р’РєР»СЋС‡РёС‚СЊ HSI32M
        break;
    case PCC_OSCILLATORTYPE_OSC32M:
        WU->CLOCKS_SYS &= ~(1 << WU_CLOCKS_SYS_OSC32M_EN_S); // Р’РєР»СЋС‡РёС‚СЊ OSC32M
        break;
    case PCC_OSCILLATORTYPE_LSI32K:
        WU->CLOCKS_BU &= ~(1 << WU_CLOCKS_BU_LSI32K_EN_S); // Р’РєР»СЋС‡РёС‚СЊ LSI32K
        break;
    case PCC_OSCILLATORTYPE_OSC32K:
        WU->CLOCKS_BU &= ~(1 << WU_CLOCKS_BU_OSC32K_EN_S); // Р’РєР»СЋС‡РёС‚СЊ OSC32K
        break;
    default:
        break;
    }
}

#ifdef HAS_PCC_EXT
/**
 * @brief Р’С‹РєР»СЋС‡РёС‚СЊ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ.
 * @param Oscillator Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РґР»СЏ РІС‹РєР»СЋС‡РµРЅРёСЏ.
 * @warning РђСЂРіСѓРјРµРЅС‚ С„СѓРЅРєС†РёРё РЅРµ СЏРІР»СЏРµС‚СЃСЏ РјР°СЃРєРѕР№.
 * 
 */
void HAL_PCC_OscDisable(uint32_t Oscillator)
{
    switch (Oscillator)
    {
    case PCC_OSCILLATORTYPE_HSI32M:
        WU->CLOCKS_SYS |= (1 << WU_CLOCKS_SYS_HSI32M_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ HSI32M
        break;
    case PCC_OSCILLATORTYPE_OSC32M:
        WU->CLOCKS_SYS |= (1 << WU_CLOCKS_SYS_OSC32M_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ OSC32M
        break;
    case PCC_OSCILLATORTYPE_LSI32K:
        WU->CLOCKS_BU |= (1 << WU_CLOCKS_BU_LSI32K_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ LSI32K
        break;
    case PCC_OSCILLATORTYPE_OSC32K:
        WU->CLOCKS_BU |= (1 << WU_CLOCKS_BU_OSC32K_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ OSC32K
        break;
    }
}
#endif

#ifdef HAS_PCC_EXT
/**
 * @brief Р’С‹Р±СЂР°С‚СЊ РѕРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹.
 * 
 * Р¤СѓРЅРєС†РёСЏ РїСЂРµРґРЅР°Р·РЅР°С‡РµРЅР° РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РѕРїРѕСЂРЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹.
 * 
 * @param Force32KClk РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹.
 * @return РЎРѕСЃС‚РѕСЏРЅРёРµ РѕР± РѕС€РёР±РєР°С….
 * @warning Р•СЃР»Рё РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ РґРµС‚РµРєС‚РёСЂСѓРµС‚СЃСЏ РјРѕРЅРёС‚РѕСЂРѕРј С‡Р°СЃС‚РѕС‚С‹ РІ С‚РµС‡РµРЅРёРµ #CLOCKSWITCH_TIMEOUT_VALUE РёС‚РµСЂР°С†РёР№,
 * С‚Рѕ С„СѓРЅРєС†РёСЏ РІРµСЂРЅРµС‚ РѕС€РёР±РєСѓ HAL_TIMEOUT, Р° РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ Р±СѓРґРµС‚ РЅР°Р·РЅР°С‡РµРЅ.
 * 
 */
HAL_StatusTypeDef HAL_PCC_FreqMonRefSet(HAL_PCC_FreqMonitorSourceTypeDef Force32KClk)
{
    uint32_t clockswitch_timeout = 0;
    uint32_t ref_clk_m = 0;
    uint32_t ref_clk_flag_m = 0;

    switch (Force32KClk)
    {
    case PCC_FREQ_MONITOR_SOURCE_AUTO:
        WU->CLOCKS_SYS &= ~WU_CLOCKS_SYS_FORCE_32K_CLK_M;
        return HAL_OK;
    case PCC_FREQ_MONITOR_SOURCE_OSC32K:
        ref_clk_m = WU_CLOCKS_SYS_FORCE_32K_CLK_OSC32K_M;
        ref_clk_flag_m = PM_FREQ_STATUS_OSC32K_M;
        break;
    case PCC_FREQ_MONITOR_SOURCE_LSI32K:
        ref_clk_m = WU_CLOCKS_SYS_FORCE_32K_CLK_LSI32K_M;
        ref_clk_flag_m = PM_FREQ_STATUS_LSI32K_M;
        break;
    default:
        return HAL_ERROR;
    }

    while (!(PM->FREQ_STATUS & ref_clk_flag_m))
    {
        clockswitch_timeout++;
        if (clockswitch_timeout >= CLOCKSWITCH_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    WU->CLOCKS_SYS = (WU->CLOCKS_SYS & ~(WU_CLOCKS_SYS_FORCE_32K_CLK_M)) | ref_clk_m;
    for (volatile int i = 0; i < 100; i++)
        ;
    return HAL_OK;
}
#endif

#ifdef HAS_PCC_EXT
/**
 * @brief Р’С‹Р±СЂР°С‚СЊ РїСЂРёРѕСЂРёС‚РµС‚РЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹.
 * 
 * Р¤СѓРЅРєС†РёСЏ РїСЂРµРґРЅР°Р·РЅР°С‡РµРЅР° РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹. Р•СЃР»Рё ForceOscSys = #PCC_FORCE_OSC_SYS_FIXED, 
 * С‚Рѕ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹ РЅРµ Р±СѓРґРµС‚ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРё РїРµСЂРµРєР»СЋС‡Р°С‚СЊСЃСЏ, РїСЂРё РїСЂРѕРїР°РґР°РЅРёРё СЃРёРіРЅР°Р»Р°.
 * 
 * @param OscillatorSystem Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹.
 * @param ForceOscSys Р—Р°РїСЂРµС‚ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРѕРіРѕ РїРµСЂРµРєР»СЋС‡РµРЅРёСЏ СЃ РІС‹Р±СЂР°РЅРЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ.
 * @return РЎРѕСЃС‚РѕСЏРЅРёРµ РѕР± РѕС€РёР±РєР°С….
 * @warning Р•СЃР»Рё РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ РґРµС‚РµРєС‚РёСЂСѓРµС‚СЃСЏ РјРѕРЅРёС‚РѕСЂРѕРј С‡Р°СЃС‚РѕС‚С‹ РІ С‚РµС‡РµРЅРёРµ #CLOCKSWITCH_TIMEOUT_VALUE РёС‚РµСЂР°С†РёР№,
 * С‚Рѕ С„СѓРЅРєС†РёСЏ РІРµСЂРЅРµС‚ РѕС€РёР±РєСѓ HAL_TIMEOUT. РџСЂРё СЌС‚РѕРј РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє Р±СѓРґРµС‚ РЅР°Р·РЅР°С‡РµРЅ РїСЂРёРѕСЂРёС‚РµС‚РЅС‹Рј. Р Р°Р·СЂРµС€РµРЅРёРµ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРѕРіРѕ 
 * РїРµСЂРµРєР»СЋС‡РµРЅРёСЏ Р±СѓРґРµС‚ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РєР°Рє #PCC_FORCE_OSC_SYS_UNFIXED.
 * 
 */
HAL_StatusTypeDef HAL_PCC_SetOscSystem(uint32_t OscillatorSystem, HAL_PCC_ForceOscSysTypeDef ForceOscSys)
{
    uint32_t clockswitch_timeout = 0;
    uint32_t sys_clk_m = 0;
    uint32_t osc_clk_flag_m = 0;

    /* РќР°СЃС‚СЂРѕР№РєР° РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹ */
    switch (OscillatorSystem)
    {
    case PCC_OSCILLATORTYPE_HSI32M:
        sys_clk_m = PM_AHB_CLK_MUX_HSI32M_M;
        osc_clk_flag_m = PM_FREQ_STATUS_HSI32M_M;
        break;
    case PCC_OSCILLATORTYPE_OSC32M:
        sys_clk_m = PM_AHB_CLK_MUX_OSC32M_M;
        osc_clk_flag_m = PM_FREQ_STATUS_OSC32M_M;
        break;
    case PCC_OSCILLATORTYPE_LSI32K:
        sys_clk_m = PM_AHB_CLK_MUX_LSI32K_M;
        osc_clk_flag_m = PM_FREQ_STATUS_LSI32K_M;
        break;
    case PCC_OSCILLATORTYPE_OSC32K:
        sys_clk_m = PM_AHB_CLK_MUX_OSC32K_M;
        osc_clk_flag_m = PM_FREQ_STATUS_OSC32K_M;
        break;
    default:
        return HAL_ERROR;
    }

    while (!(PM->FREQ_STATUS & osc_clk_flag_m))
    {
        clockswitch_timeout++;
        if (clockswitch_timeout >= CLOCKSWITCH_TIMEOUT_VALUE)
        {
            PM->AHB_CLK_MUX = sys_clk_m | PM_AHB_FORCE_MUX_UNFIXED;
            return HAL_TIMEOUT;
        }
    }

    PM->AHB_CLK_MUX = sys_clk_m | (ForceOscSys << PM_AHB_FORCE_MUX_S);

    for (volatile int i = 0; i < 100; i++)
        ;

    return HAL_OK;
}
#endif

#ifdef HAS_PCC_EXT
/**
 * @brief Р’С‹Р±СЂР°С‚СЊ РїСЂРёРѕСЂРёС‚РµС‚РЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC.
 * 
 * Р¤СѓРЅРєС†РёСЏ РїСЂРµРґРЅР°Р·РЅР°С‡РµРЅР° РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° RTC.
 * 
 * @param Oscillator Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC.
 * @return РЎРѕСЃС‚РѕСЏРЅРёРµ РѕР± РѕС€РёР±РєР°С….
 * @warning Р•СЃР»Рё РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ РґРµС‚РµРєС‚РёСЂСѓРµС‚СЃСЏ РјРѕРЅРёС‚РѕСЂРѕРј С‡Р°СЃС‚РѕС‚С‹ РІ С‚РµС‡РµРЅРёРµ #CLOCKSWITCH_TIMEOUT_VALUE РёС‚РµСЂР°С†РёР№,
 * С‚Рѕ С„СѓРЅРєС†РёСЏ РІРµСЂРЅРµС‚ РѕС€РёР±РєСѓ HAL_TIMEOUT. РџСЂРё СЌС‚РѕРј РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ Р±СѓРґРµС‚ РЅР°Р·РЅР°С‡РµРЅ РїСЂРёРѕСЂРёС‚РµС‚РЅС‹Рј.
 * 
 */
HAL_StatusTypeDef HAL_PCC_RTCClock(HAL_PCC_RTCClockSourceTypeDef Oscillator)
{
    uint32_t clockswitch_timeout = 0;
    uint32_t rtc_clk_m = 0;
    uint32_t osc_clk_flag_m = 0;

    switch (Oscillator)
    {
    case PCC_RTC_CLOCK_SOURCE_AUTO:
        WU->CLOCKS_BU &= ~WU_CLOCKS_BU_RTC_CLK_MUX_M;
        return HAL_OK;
    case PCC_RTC_CLOCK_SOURCE_LSI32K:
        rtc_clk_m = WU_CLOCKS_BU_RTC_CLK_MUX_LSI32K_M;
        osc_clk_flag_m = PM_FREQ_STATUS_LSI32K_M;
        break;
    case PCC_RTC_CLOCK_SOURCE_OSC32K:
        rtc_clk_m = WU_CLOCKS_BU_RTC_CLK_MUX_OSC32K_M;
        osc_clk_flag_m = PM_FREQ_STATUS_OSC32K_M;
        break;
    default:
        return HAL_ERROR;
    }

    while (!(PM->FREQ_STATUS & osc_clk_flag_m))
    {
        clockswitch_timeout++;
        if (clockswitch_timeout >= CLOCKSWITCH_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }

    /* Р’С‹Р±РѕСЂ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC */
    WU->CLOCKS_BU = (WU->CLOCKS_BU & ~WU_CLOCKS_BU_RTC_CLK_MUX_M) | rtc_clk_m;

    WU->RTC_CONRTOL = WU_RTC_CONTROL_RESET_SET_M;
    WU->RTC_CONRTOL = WU_RTC_CONTROL_RESET_CLEAR_M;
    
    for (volatile int i = 0; i < 100; i++)
        ;


    return HAL_OK;
}
#endif

#ifdef HAS_PCC_EXT
/**
 * @brief Р’С‹Р±СЂР°С‚СЊ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°.
 * 
 * Р¤СѓРЅРєС†РёСЏ РїСЂРµРґРЅР°Р·РЅР°С‡РµРЅР° РґР»СЏ РІС‹Р±РѕСЂР° РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°.
 * 
 * @param Oscillator Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°.
 * @return РЎРѕСЃС‚РѕСЏРЅРёРµ РѕР± РѕС€РёР±РєР°С….
 * @warning Р•СЃР»Рё РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ РґРµС‚РµРєС‚РёСЂСѓРµС‚СЃСЏ РјРѕРЅРёС‚РѕСЂРѕРј С‡Р°СЃС‚РѕС‚С‹ РІ С‚РµС‡РµРЅРёРµ #CLOCKSWITCH_TIMEOUT_VALUE РёС‚РµСЂР°С†РёР№,
 * С‚Рѕ С„СѓРЅРєС†РёСЏ РІРµСЂРЅРµС‚ РѕС€РёР±РєСѓ HAL_TIMEOUT. РџСЂРё СЌС‚РѕРј РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ Р±СѓРґРµС‚ РІС‹Р±СЂР°РЅ.
 * 
 */
HAL_StatusTypeDef HAL_PCC_CPURTCClock(HAL_PCC_CPURTCClockSourceTypeDef Oscillator)
{
    uint32_t clockswitch_timeout = 0;
    uint32_t rtc_clk_m = 0;
    uint32_t osc_clk_flag_m = 0;

    switch (Oscillator)
    {
    case PCC_CPU_RTC_CLOCK_SOURCE_LSI32K:
        rtc_clk_m = PM_CPU_RTC_CLK_MUX_LSI32K_M;
        osc_clk_flag_m = PM_FREQ_STATUS_LSI32K_M;
        break;
    case PCC_CPU_RTC_CLOCK_SOURCE_OSC32K:
        rtc_clk_m = PM_CPU_RTC_CLK_MUX_OSC32K_M;
        osc_clk_flag_m = PM_FREQ_STATUS_OSC32K_M;
        break;
    default:
        return HAL_ERROR;
    }

    while (!(PM->FREQ_STATUS & osc_clk_flag_m))
    {
        clockswitch_timeout++;
        if (clockswitch_timeout >= CLOCKSWITCH_TIMEOUT_VALUE)
        {
            return HAL_TIMEOUT;
        }
    }
    
    PM->CPU_RTC_CLK_MUX = rtc_clk_m;

    for (volatile int i = 0; i < 100; i++)
        ;

    return HAL_OK;
}

/**
 * @brief Р—Р°РґР°С‚СЊ РґРµР»РёС‚РµР»СЊ С€РёРЅС‹ AHB.
 * @param DividerAHB Р”РµР»РёС‚РµР»СЊ.
 * 
 *  Р”РµР»РёС‚РµР»СЊ СЏРІР»СЏРµС‚СЃСЏ 32-С… Р±РёС‚РЅС‹Рј С‡РёСЃР»РѕРј. Р§Р°СЃС‚РѕС‚Р° С€РёРЅС‹ AHB РѕРїСЂРµРґРµР»СЏРµС‚СЃСЏ РїРѕ С„РѕСЂРјСѓР»Рµ: @f$ \frac{F_{sys\_clk}}{DividerAHB + 1} @f$.
 */
void HAL_PCC_DividerAHB(uint32_t DividerAHB)
{
    PM->DIV_AHB = DividerAHB;
}
#endif

#ifdef HAS_PCC_EXT
/**
 * @brief Р—Р°РґР°С‚СЊ РґРµР»РёС‚РµР»СЊ С€РёРЅС‹ APB_M.
 * @param DividerAPB_M Р”РµР»РёС‚РµР»СЊ.
 * 
 * Р”РµР»РёС‚РµР»СЊ СЏРІР»СЏРµС‚СЃСЏ 32-С… Р±РёС‚РЅС‹Рј С‡РёСЃР»РѕРј. Р§Р°СЃС‚РѕС‚Р° С€РёРЅС‹ APB_M РѕРїСЂРµРґРµР»СЏРµС‚СЃСЏ РїРѕ С„РѕСЂРјСѓР»Рµ: @f$ \frac{F_{AHB}}{DividerAPB\_M + 1} @f$.
 */
void HAL_PCC_DividerAPB_M(uint32_t DividerAPB_M)
{
    PM->DIV_APB_M = DividerAPB_M;
}

/**
 * @brief Р—Р°РґР°С‚СЊ РґРµР»РёС‚РµР»СЊ С€РёРЅС‹ APB_P.
 * @param DividerAPB_P Р”РµР»РёС‚РµР»СЊ.
 * 
 * Р”РµР»РёС‚РµР»СЊ СЏРІР»СЏРµС‚СЃСЏ 32-С… Р±РёС‚РЅС‹Рј С‡РёСЃР»РѕРј. Р§Р°СЃС‚РѕС‚Р° С€РёРЅС‹ APB_M РѕРїСЂРµРґРµР»СЏРµС‚СЃСЏ РїРѕ С„РѕСЂРјСѓР»Рµ: @f$ \frac{F_{AHB}}{DividerAPB\_P + 1} @f$.
 */
void HAL_PCC_DividerAPB_P(uint32_t DividerAPB_P)
{
    PM->DIV_APB_P = DividerAPB_P;
}
#endif

#ifdef HAS_PCC_EXT


/**
 * @brief РќР°СЃС‚СЂРѕРёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Рё РјРѕРЅРёС‚РѕСЂ С‡Р°СЃС‚РѕС‚С‹.
 * 
 * Р¤СѓРЅРєС†РёСЏ РґР»СЏ РЅР°СЃС‚СЂРѕР№РєРё С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ Рё РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹ РІ СЃРѕРѕС‚РІРµС‚СЃС‚РІРёРё СЃ Р·Р°РґР°РЅРЅС‹РјРё РЅР°СЃС‚СЂРѕР№РєР°РјРё РІ PCC_Init.
 * 
 * @param PCC_Init РЎС‚СЂСѓРєС‚СѓСЂР° СЃ РЅР°СЃС‚СЂРѕР№РєР°РјРё.
 * @return РЎС‚СЂСѓРєС‚СѓСЂР° СЃ СЃРѕСЃС‚РѕСЏРЅРёСЏРјРё РѕР± РѕС€РёР±РєР°С….
 * @warning Р•СЃР»Рё РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ РґРµС‚РµРєС‚РёСЂСѓРµС‚СЃСЏ РјРѕРЅРёС‚РѕСЂРѕРј С‡Р°СЃС‚РѕС‚С‹ РІ С‚РµС‡РµРЅРёРµ #CLOCKSWITCH_TIMEOUT_VALUE РёС‚РµСЂР°С†РёР№,
 * С‚Рѕ С„СѓРЅРєС†РёСЏ РІРµСЂРЅРµС‚ РѕС€РёР±РєСѓ HAL_TIMEOUT. РџСЂРё СЌС‚РѕРј РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РЅРµ Р±СѓРґРµС‚ РїСЂРёРјРµРЅРµРЅ. Р•СЃР»Рё С‚Р°РєР°СЏ РѕС€РёР±РєР° РІРѕР·РЅРёРєР»Р° РїСЂРё
 * РїСЂРё РІС‹Р±РѕСЂРµ СЃРёСЃС‚РµРјРЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР°, С‚Рѕ РІС‹Р±СЂР°РЅРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє Р±СѓРґРµС‚ РЅР°Р·РЅР°С‡РµРЅ РїСЂРёРѕСЂРёС‚РµС‚РЅС‹Рј. Р Р°Р·СЂРµС€РµРЅРёРµ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРѕРіРѕ 
 * РїРµСЂРµРєР»СЋС‡РµРЅРёСЏ Р±СѓРґРµС‚ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РєР°Рє #PCC_FORCE_OSC_SYS_UNFIXED.
 * 
 */
PCC_ConfigErrorsTypeDef HAL_PCC_Config(PCC_InitTypeDef *PCC_Init)
{
    PCC_ConfigErrorsTypeDef errors = {HAL_OK};

    /* Р’РєР»СЋС‡РёС‚СЊ РІСЃРµ РёСЃС‚РѕС‡РЅРёРєРё С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ */
    WU->CLOCKS_SYS &= ~(0b11 << WU_CLOCKS_SYS_OSC32M_EN_S); // Р’РєР»СЋС‡РёС‚СЊ OSC32M Рё HSI32M
    WU->CLOCKS_BU &= ~(0b11 << WU_CLOCKS_BU_OSC32K_EN_S);   // Р’РєР»СЋС‡РёС‚СЊ OSC32K Рё LSI32K

    WU->CLOCKS_SYS = (WU->CLOCKS_SYS & (~WU_CLOCKS_SYS_ADJ_HSI32M_M)) | WU_CLOCKS_SYS_ADJ_HSI32M(PCC_Init->HSI32MCalibrationValue); // РџРѕРїСЂР°РІРѕС‡РЅС‹Р№ РєРѕСЌС„С„РёС†РёРµРЅС‚ HSI32M
    WU->CLOCKS_BU = (WU->CLOCKS_BU & (~WU_CLOCKS_BU_ADJ_LSI32K_M)) | WU_CLOCKS_BU_ADJ_LSI32K(PCC_Init->LSI32KCalibrationValue); // РџРѕРїСЂР°РІРѕС‡РЅС‹Р№ РєРѕСЌС„С„РёС†РёРµРЅС‚ LSI32K

    /* РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РґР»СЏ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹ */
    errors.FreqMonRef = HAL_PCC_FreqMonRefSet(PCC_Init->FreqMon.Force32KClk);
    
    /* РќР°СЃС‚СЂРѕР№РєР° РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹ */
    errors.SetOscSystem = HAL_PCC_SetOscSystem(PCC_Init->FreqMon.OscillatorSystem, PCC_Init->FreqMon.ForceOscSys);

    /* Р”РµР»РёС‚РµР»Рё С‡Р°СЃС‚РѕС‚С‹ */
    HAL_PCC_DividerAHB(PCC_Init->AHBDivider);
    HAL_PCC_DividerAPB_M(PCC_Init->APBMDivider);
    HAL_PCC_DividerAPB_P(PCC_Init->APBPDivider);

    /* Р’С‹Р±РѕСЂ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC */
    errors.RTCClock = HAL_PCC_RTCClock(PCC_Init->RTCClockSelection);
    
    /* Р’С‹Р±РѕСЂ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°*/
    errors.CPURTCClock = HAL_PCC_CPURTCClock(PCC_Init->RTCClockCPUSelection);



    /* РћС‚РєР»СЋС‡РµРЅРёРµ РЅРµРёСЃРїРѕР»СЊР·СѓРµРјС‹С… РёСЃС‚РѕС‡РЅРёРєРѕРІ С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ */
    /* Р�СЃС‚РѕС‡РЅРёРєРё 32РњР“С† */
    /* Р’РЅСѓС‚СЂРµРЅРЅРёР№ */
    if (!(PCC_Init->OscillatorEnable & PCC_OSCILLATORTYPE_HSI32M))
    {
        WU->CLOCKS_SYS |= (1 << WU_CLOCKS_SYS_HSI32M_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ HSI32M
    }

    // /* Р’РЅРµС€РЅРёР№ */
    if (!(PCC_Init->OscillatorEnable & PCC_OSCILLATORTYPE_OSC32M))
    {
        WU->CLOCKS_SYS |= (1 << WU_CLOCKS_SYS_OSC32M_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ OSC32M
    }

    /* Р�СЃС‚РѕС‡РЅРёРєРё 32РєР“С† */
    /* Р’РЅСѓС‚СЂРµРЅРЅРёР№  */
    if (!(PCC_Init->OscillatorEnable & PCC_OSCILLATORTYPE_LSI32K))
    {
        WU->CLOCKS_BU |= (1 << WU_CLOCKS_BU_LSI32K_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ LSI32K
    }

    /* Р’РЅРµС€РЅРёР№ */
    if (!(PCC_Init->OscillatorEnable & PCC_OSCILLATORTYPE_OSC32K))
    {
        WU->CLOCKS_BU |= (1 << WU_CLOCKS_BU_OSC32K_EN_S); // Р’С‹РєР»СЋС‡РёС‚СЊ OSC32K
    }

    return errors;
}
#endif

/**
 * @brief РџРѕР»СѓС‡РёС‚СЊ С‡Р°СЃС‚РѕС‚Сѓ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ СЃРёСЃС‚РµРјРЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РІ Р“С†.
 * @return Р§Р°СЃС‚РѕС‚Р° РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ СЃРёСЃС‚РµРјРЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° РІ Р“С†.
 * @warning РЎРёСЃС‚РµРјР° РјРѕР¶РµС‚ С‚Р°РєС‚РёСЂРѕРІР°С‚СЊСЃСЏ РЅРµ РѕС‚ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР°. РќР°РїСЂРёРјРµСЂ, РµСЃР»Рё РёСЃС‚РѕС‡РЅРёРє РЅРµ Р±С‹Р» РЅР°Р·РЅР°С‡РµРЅ РїСЂРёРЅСѓРґРёС‚РµР»СЊРЅРѕ Рё СЃРёРіРЅР°Р» РѕС‚ РёСЃС‚РѕС‡РЅРёРєР° РѕС‚СЃСѓС‚СЃС‚РІСѓРµС‚.
 * Р’ С‚Р°РєРѕРј СЃР»СѓС‡Р°Рµ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРё РІС‹Р±РёСЂР°РµС‚СЃСЏ РёСЃС‚РѕС‡РЅРёРє РІ СЃРѕРѕС‚РІРµС‚СЃС‚РІРёРё СЃРѕ СЃР»РµРґСѓСЋС‰РёРј РїСЂРёРѕСЂРёС‚РµС‚РѕРј: OSC32M, HSI32M, OSC32K, LSI32K.
 */
uint32_t HAL_PCC_GetSysClockFreq(void)
{
    uint32_t system_clock = 0;

    switch (PM->AHB_CLK_MUX & PM_AHB_CLK_MUX_M)
    {
    case PM_AHB_CLK_MUX_OSC32M_M:
        system_clock = OSC_SYSTEM_VALUE;
        break;
    case PM_AHB_CLK_MUX_OSC32K_M:
        system_clock = OSC_CLOCK_VALUE;
        break;
    case PM_AHB_CLK_MUX_HSI32M_M:
        system_clock = HSI_VALUE;
        break;
    case PM_AHB_CLK_MUX_LSI32K_M:
        system_clock = LSI_VALUE;
        break;
    }

    return system_clock;
}
