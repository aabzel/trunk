#include "mik32_hal_scr1_timer.h"

struct __HAL_Time_SCR1TIM_Handler
{
    uint32_t presc;     // AHB prescaler
    uint32_t pt;        // Timer divider
    uint32_t clock_freq; // Clock frequency
} HAL_Time_SCR1TIM_Handler;

/**
 * @brief Р�РЅРёС†РёР°Р»РёР·Р°С†РёСЏ С‚Р°Р№РјРµСЂР° SCR1 РґР»СЏ СЂР°Р±РѕС‚С‹ РІ РєР°С‡РµСЃС‚РІРµ СЃРёСЃС‚РµРјРЅС‹С… С‡Р°СЃРѕРІ.
 * РџРѕСЃР»Рµ РёРЅРёС†РёР°Р»РёР·Р°С†РёРё СЃРёСЃС‚РµРјРЅРѕРіРѕ С‚Р°Р№РјРµСЂР° РЅРµ СЂРµРєРѕРјРµРЅРґСѓРµС‚СЃСЏ РёР·РјРµРЅСЏС‚СЊ РґРµР»РёС‚РµР»СЊ С‚Р°РєС‚РѕРІРѕР№ С‡Р°СЃС‚РѕС‚С‹ AHB.
 * Р•СЃР»Рё РґРµР»РёС‚РµР»СЊ С‚Р°РєС‚Р° Р±С‹Р» РёР·РјРµРЅРµРЅ РёР»Рё РјРёРєСЂРѕРєРѕРЅС‚СЂРѕР»Р»РµСЂ РїРµСЂРµРєР»СЋС‡РёР»СЃСЏ РЅР° РґСЂСѓРіРѕР№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ, РЅРµРѕР±С…РѕРґРёРјРѕ
 * РїРµСЂРµРёРЅРёС†РёР°Р»РёР·Р°СЂРѕРІР°С‚СЊ С‚Р°Р№РјРµСЂ. РџСЂРё СЌС‚РѕРј РїСЂРµР¶РЅРµРµ Р·РЅР°С‡РµРЅРёРµ СЃРёСЃС‚РµРјРЅРѕРіРѕ РІСЂРµРјРµРЅРё РїРѕС‚РµСЂСЏРµС‚СЃСЏ
 * 
 * Р’СЂРµРјСЏ РїРµСЂРµРїРѕР»РЅРµРЅРёСЏ СЃРёСЃС‚РµРјРЅС‹С… С‡Р°СЃРѕРІ Р·Р°РІРёСЃРёС‚ РѕС‚ С‡Р°СЃС‚РѕС‚С‹ С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ. РњРёРЅРёРјР°Р»СЊРЅРѕРµ РІСЂРµРјСЏ РїРµСЂРµРїРѕР»РЅРµРЅРёСЏ - 4295c.
*/
void HAL_Time_SCR1TIM_Init(void)
{
    /* Setting dividers */
    HAL_Time_SCR1TIM_Handler.presc = (PM->DIV_AHB+1);
    HAL_Time_SCR1TIM_Handler.clock_freq = HAL_PCC_GetSysClockFreq();
    if (HAL_Time_SCR1TIM_Handler.clock_freq % (HAL_Time_SCR1TIM_Handler.presc * 1000000UL) != 0)
        HAL_Time_SCR1TIM_Handler.pt = 1;
    else
    {
        uint32_t pt_raw = HAL_Time_SCR1TIM_Handler.clock_freq / (HAL_Time_SCR1TIM_Handler.presc * 1000000UL);
        if (pt_raw < 2) HAL_Time_SCR1TIM_Handler.pt = 1;
        else HAL_Time_SCR1TIM_Handler.pt = pt_raw;
    }
    __HAL_SCR1_TIMER_SET_DIVIDER(HAL_Time_SCR1TIM_Handler.pt-1);
    /* Timer enable */
    __HAL_SCR1_TIMER_ENABLE();
    /* Clear the timer */
    __HAL_SCR1_TIMER_SET_TIME(0);
}

/**
 * @brief РЎРёСЃС‚РµРјРЅРѕРµ РІСЂРµРјСЏ РІ РјРёРєСЂРѕСЃРµРєСѓРЅРґР°С…, РёСЃРїРѕР»СЊР·СѓРµС‚СЃСЏ С‚Р°Р№РјРµСЂ SCR1 РІ РєР°С‡РµСЃС‚РІРµ СЃРёСЃС‚РµРјРЅС‹С… С‡Р°СЃРѕРІ
*/
uint32_t HAL_Time_SCR1TIM_Micros(void)
{
    return (uint32_t)(__HAL_SCR1_TIMER_GET_TIME() * (1000000UL * HAL_Time_SCR1TIM_Handler.presc *
        HAL_Time_SCR1TIM_Handler.pt) / HAL_Time_SCR1TIM_Handler.clock_freq);
}

/**
 * @brief РЎРёСЃС‚РµРјРЅРѕРµ РІСЂРµРјСЏ РІ РјРёР»Р»РёСЃРµРєСѓРЅРґР°С…, РёСЃРїРѕР»СЊР·СѓРµС‚СЃСЏ С‚Р°Р№РјРµСЂ SCR1 РІ РєР°С‡РµСЃС‚РІРµ СЃРёСЃС‚РµРјРЅС‹С… С‡Р°СЃРѕРІ
*/
uint32_t HAL_Time_SCR1TIM_Millis(void)
{
    return (uint32_t)(__HAL_SCR1_TIMER_GET_TIME() * (1000UL * HAL_Time_SCR1TIM_Handler.presc *
        HAL_Time_SCR1TIM_Handler.pt) / HAL_Time_SCR1TIM_Handler.clock_freq);
}

/**
 * @brief Р¤СѓРЅРєС†РёСЏ Р·Р°РґРµСЂР¶РєРё РІ РјРёРєСЂРѕСЃРµРєСѓРЅРґР°С…, РёСЃРїРѕР»СЊР·СѓРµС‚СЃСЏ С‚Р°Р№РјРµСЂ SCR1 РІ РєР°С‡РµСЃС‚РІРµ СЃРёСЃС‚РµРјРЅС‹С… С‡Р°СЃРѕРІ
*/
void HAL_Time_SCR1TIM_DelayUs(uint32_t time_us)
{
    uint32_t time_metka = HAL_Time_SCR1TIM_Micros();
    while (HAL_Time_SCR1TIM_Micros() - time_metka < time_us);
}

/**
 * @brief Р¤СѓРЅРєС†РёСЏ Р·Р°РґРµСЂР¶РєРё РІ РјРёР»Р»РёСЃРµРєСѓРЅРґР°С…, РёСЃРїРѕР»СЊР·СѓРµС‚СЃСЏ С‚Р°Р№РјРµСЂ SCR1 РІ РєР°С‡РµСЃС‚РІРµ СЃРёСЃС‚РµРјРЅС‹С… С‡Р°СЃРѕРІ
*/
void HAL_Time_SCR1TIM_DelayMs(uint32_t time_ms)
{
    uint32_t time_metka = HAL_Time_SCR1TIM_Millis();
    while (HAL_Time_SCR1TIM_Millis() - time_metka < time_ms);
}
