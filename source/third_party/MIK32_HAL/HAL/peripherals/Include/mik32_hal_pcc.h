#ifndef MIK32_HAL_PCC
#define MIK32_HAL_PCC

#include <stdint.h>

#include "wakeup.h"
#include "power_manager.h"
#include "mik32_hal_def.h"
//#include "mik32_memory_map.h"
#include "mcu32_memory_map.h"
#include "mik32_hal.h"

#define CLOCKSWITCH_TIMEOUT_VALUE 500000 /**< РЎС‚Р°РЅРґР°СЂС‚РЅР°СЏ Р·Р°РґРµСЂР¶РєР° РґР»СЏ РѕР¶РёРґР°РЅРёСЏ РґРµС‚РµРєС‚РёСЂРѕРІР°РЅРёСЏ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ, РЅР° РєРѕС‚РѕСЂС‹Р№ РїСЂРѕРёСЃС…РѕРґРёС‚ РїРµСЂРµРєР»СЋС‡РµРЅРёРµ */

/**
 * @brief Р�СЃС‚РѕС‡РЅРёРєРё С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ.
 *
 * Р�СЃРїРѕР»СЊР·СѓРµС‚СЃСЏ РєР°Рє РјР°СЃРєР° РґР»СЏ РІРєР»СЋС‡РµРЅРёСЏ РёСЃС‚РѕС‡РЅРёРєРѕРІ С‡Р°СЃС‚РѕС‚С‹ Рё
 * РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹ РІ РјРѕРЅРёС‚РѕСЂРµ С‡Р°СЃС‚РѕС‚С‹.
 */
typedef enum __HAL_PCC_OscillatorTypeTypeDef
{
    PCC_OSCILLATORTYPE_HSI32M   = 0b0001,       /**< Р’РЅСѓС‚СЂРµРЅРЅРёР№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ 32РњР“С† */
    PCC_OSCILLATORTYPE_OSC32M   = 0b0010,       /**< Р’РЅРµС€РЅРёР№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ 32РњР“С† */
    PCC_OSCILLATORTYPE_LSI32K   = 0b0100,       /**< Р’РЅСѓС‚СЂРµРЅРЅРёР№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ 32РљР“С† */
    PCC_OSCILLATORTYPE_OSC32K   = 0b1000,       /**< Р’РЅРµС€РЅРёР№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ 32РљР“С† */
    PCC_OSCILLATORTYPE_ALL      = 0b1111        /**< Р’СЃРµ РёСЃС‚РѕС‡РЅРёРєРё */
} HAL_PCC_OscillatorTypeTypeDef;

/**
 * @brief РџСЂРёРЅСѓРґРёС‚РµР»СЊРЅС‹Р№ РІС‹Р±РѕСЂ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹.
 * 
 * Р�СЃРїРѕР»СЊР·СѓРµС‚СЃСЏ РґР»СЏ РІРєР»СЋС‡РµРЅРёСЏ РёР»Рё РѕС‚РєР»СЋС‡РµРЅРёСЏ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРѕРіРѕ РїРµСЂРµРєР»СЋС‡РµРЅРёСЏ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹.
 */
typedef enum __HAL_PCC_ForceOscSysTypeDef
{
	PCC_FORCE_OSC_SYS_UNFIXED = 0,   /**< Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹ РЅРµ РІС‹Р±РёСЂР°РµС‚СЃСЏ РїСЂРёРЅСѓРґРёС‚РµР»СЊРЅРѕ */
	PCC_FORCE_OSC_SYS_FIXED = 1      /**< Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹ РІС‹Р±РёСЂР°РµС‚СЃСЏ РїСЂРёРЅСѓРґРёС‚РµР»СЊРЅРѕ */
} HAL_PCC_ForceOscSysTypeDef;

/**
 * @brief РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹.
 * 
 * Р�СЃРїРѕР»СЊР·СѓРµС‚СЃСЏ РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РѕРїРѕСЂРЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹.
 */
typedef enum __HAL_PCC_FreqMonitorSourceTypeDef
{
	PCC_FREQ_MONITOR_SOURCE_AUTO    = 0b00,     /**< РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‡Р°СЃС‚РѕС‚С‹ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹ РІС‹Р±РёСЂР°РµС‚СЃСЏ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРё */
    PCC_FREQ_MONITOR_SOURCE_LSI32K  = 0b01,     /**< РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‡Р°СЃС‚РѕС‚С‹ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹ РїСЂРёРЅСѓРґРёС‚РµР»СЊРЅРѕ РІС‹Р±СЂР°РЅ РєР°Рє LSI32K */
	PCC_FREQ_MONITOR_SOURCE_OSC32K  = 0b10      /**< РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‡Р°СЃС‚РѕС‚С‹ РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹ РїСЂРёРЅСѓРґРёС‚РµР»СЊРЅРѕ РІС‹Р±СЂР°РЅ РєР°Рє OSC32K */
} HAL_PCC_FreqMonitorSourceTypeDef;

/**
 * @brief Р�СЃС‚РѕС‡РЅРёРєРё С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC.
 * 
 * Р�СЃРїРѕР»СЊР·СѓСЋС‚СЃСЏ РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РјРѕРґСѓР»СЏ RTC.
 */
typedef enum __HAL_PCC_RTCClockSourceTypeDef
{
	PCC_RTC_CLOCK_SOURCE_AUTO    = 0b00,    /**< Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІС‹Р±РёСЂР°РµС‚СЃСЏ Р°РІС‚РѕРјР°С‚РёС‡РµСЃРєРё. Р•СЃР»Рё РїСЂРёСЃСѓС‚СЃС‚РІСѓСЋС‚ РѕР±Р° С‚Р°РєС‚РѕРІС‹С… СЃРёРіРЅР°Р»Р° 32K, С‚Рѕ РІС‹Р±РёСЂР°РµС‚СЃСЏ LSI32K */
    PCC_RTC_CLOCK_SOURCE_LSI32K  = 0b01,    /**< РџСЂРёРѕСЂРёС‚РµС‚РЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC - LSI32K */
	PCC_RTC_CLOCK_SOURCE_OSC32K  = 0b10     /**< РџСЂРёРѕСЂРёС‚РµС‚РЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC - OSC32K */
} HAL_PCC_RTCClockSourceTypeDef;

/**
 * @brief Р�СЃС‚РѕС‡РЅРёРєРё С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°.
 * 
 * Р�СЃРїРѕР»СЊР·СѓСЋС‚СЃСЏ РґР»СЏ РЅР°Р·РЅР°С‡РµРЅРёСЏ РїСЂРёРѕСЂРёС‚РµС‚РЅРѕРіРѕ РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°.
 */
typedef enum __HAL_PCC_CPURTCClockSourceTypeDef
{
	PCC_CPU_RTC_CLOCK_SOURCE_OSC32K  = 0,    /**< Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР° - OSC32K */
	PCC_CPU_RTC_CLOCK_SOURCE_LSI32K  = 1     /**< Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР° - LSI32K */
} HAL_PCC_CPURTCClockSourceTypeDef;


/** 
 * @name РЁРёРЅР° AHB
 * @brief РњР°РєСЂРѕСЃС‹ РґР»СЏ РІРєР»СЋС‡РµРЅРёСЏ Рё РѕС‚РєР»СЋС‡РµРЅРёСЏ С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РїРµСЂРёС„РµСЂРёРё РЅР° С€РёРЅРµ AHB
    @{
*/

#define __HAL_PCC_CPU_CLK_ENABLE()      (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_CPU_M)       /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ CPU */
#define __HAL_PCC_CPU_CLK_DISABLE()     (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_CPU_M)       /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ CPU */

#define __HAL_PCC_EEPROM_CLK_ENABLE()   (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_EEPROM_M)    /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ EEPROM */
#define __HAL_PCC_EEPROM_CLK_DISABLE()  (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_EEPROM_M)    /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ EEPROM */

#define __HAL_PCC_RAM_CLK_ENABLE()      (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_RAM_M)       /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ RAM */
#define __HAL_PCC_RAM_CLK_DISABLE()     (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_RAM_M)       /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPIFI */

#define __HAL_PCC_SPIFI_CLK_ENABLE()    (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_SPIFI_M)     /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPIFI */
#define __HAL_PCC_SPIFI_CLK_DISABLE()   (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_SPIFI_M)     /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPIFI */

#define __HAL_PCC_TCB_CLK_ENABLE()      (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_TCB_M)       /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Р±Р»РѕРєР° TCB */
#define __HAL_PCC_TCB_CLK_DISABLE()     (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_TCB_M)       /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Р±Р»РѕРєР° TCB */

#define __HAL_PCC_DMA_CLK_ENABLE()      (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_DMA_M)       /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ DMA */
#define __HAL_PCC_DMA_CLK_DISABLE()     (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_DMA_M)       /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ DMA */

#define __HAL_PCC_CRYPTO_CLK_ENABLE()   (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_CRYPTO_M)    /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РєСЂРёРїС‚Рѕ-Р±Р»РѕРєР° */
#define __HAL_PCC_CRYPTO_CLK_DISABLE()  (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_CRYPTO_M)    /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РєСЂРёРїС‚Рѕ-Р±Р»РѕРєР° */

#define __HAL_PCC_CRC32_CLK_ENABLE()    (PM->CLK_AHB_SET.dword = PM_CLOCK_AHB_CRC32_M)      /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ CRC */
#define __HAL_PCC_CRC32_CLK_DISABLE()   (PM->CLK_AHB_CLEAR = PM_CLOCK_AHB_CRC32_M)      /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ CRC */

/** @} */ 

/** 
 * @name РЁРёРЅР° APB_M
 * @brief РњР°РєСЂРѕСЃС‹ РґР»СЏ РІРєР»СЋС‡РµРЅРёСЏ Рё РѕС‚РєР»СЋС‡РµРЅРёСЏ С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РїРµСЂРёС„РµСЂРёРё РЅР° С€РёРЅРµ APB_M
    @{
*/

#define __HAL_PCC_PM_CLK_ENABLE()                   (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_PM_M)                   /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Power manager */
#define __HAL_PCC_PM_CLK_DISABLE()                  (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_PM_M)                 /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Power manager */

#define __HAL_PCC_EPIC_CLK_ENABLE()                 (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_EPIC_M)                 /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РєРѕРЅС‚СЂРѕР»Р»РµСЂР° РїСЂРµСЂС‹РІР°РЅРёР№ */
#define __HAL_PCC_EPIC_CLK_DISABLE()                (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_EPIC_M)               /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РєРѕРЅС‚СЂРѕР»Р»РµСЂР° РїСЂРµСЂС‹РІР°РЅРёР№ */

#define __HAL_PCC_TIMER32_0_CLK_ENABLE()            (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_TIMER32_0_M)            /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ TIMER32_0 */
#define __HAL_PCC_TIMER32_0_CLK_DISABLE()           (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_TIMER32_0_M)          /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ TIMER32_0 */

#define __HAL_PCC_PAD_CONFIG_CLK_ENABLE()           (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_PAD_CONFIG_M)           /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РєРѕРЅС‚СЂРѕР»Р»РµСЂР° РІС‹РІРѕРґРѕРІ */
#define __HAL_PCC_PAD_CONFIG_CLK_DISABLE()          (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_PAD_CONFIG_M)         /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РєРѕРЅС‚СЂРѕР»Р»РµСЂР° РІС‹РІРѕРґРѕРІ */

#define __HAL_PCC_WDT_BUS_CLK_ENABLE()              (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_WDT_BUS_M)              /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ СЃС‚РѕСЂРѕР¶РµРІРѕРіРѕ С‚Р°Р№РјРµСЂР° С€РёРЅС‹ */
#define __HAL_PCC_WDT_BUS_CLK_DISABLE()             (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_WDT_BUS_M)            /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ СЃС‚РѕСЂРѕР¶РµРІРѕРіРѕ С‚Р°Р№РјРµСЂР° С€РёРЅС‹ */

#define __HAL_PCC_OTP_CONTROLLER_CLK_ENABLE()       (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_OTP_CONTROLLER_M)       /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ OTP */
#define __HAL_PCC_OTP_CONTROLLER_CLK_DISABLE()      (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_OTP_CONTROLLER_M)     /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ OTP */

#define __HAL_PCC_PVD_CONTROL_CLK_ENABLE()          (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_PVD_CONTROL_M)          /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РњРѕРЅРёС‚РѕСЂР° РЅР°РїСЂСЏР¶РµРЅРёСЏ */
#define __HAL_PCC_PVD_CONTROL_CLK_DISABLE()         (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_PVD_CONTROL_M)        /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ РњРѕРЅРёС‚РѕСЂР° РЅР°РїСЂСЏР¶РµРЅРёСЏ */

#define __HAL_PCC_WU_CLK_ENABLE()                   (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_WU_M)                   /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Wake up */
#define __HAL_PCC_WU_CLK_DISABLE()                  (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_WU_M)                 /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Wake up */

#define __HAL_PCC_RTC_CLK_ENABLE()                  (PM->CLK_APB_M_SET = PM_CLOCK_APB_M_RTC_M)                  /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ RTC */
#define __HAL_PCC_RTC_CLK_DISABLE()                 (PM->CLK_APB_M_CLEAR = PM_CLOCK_APB_M_RTC_M)                /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ RTC */

/** @} */ 


/** 
 * @name РЁРёРЅР° APB_P
 * @brief РњР°РєСЂРѕСЃС‹ РґР»СЏ РІРєР»СЋС‡РµРЅРёСЏ Рё РѕС‚РєР»СЋС‡РµРЅРёСЏ С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ РїРµСЂРёС„РµСЂРёРё РЅР° С€РёРЅРµ APB_P
    @{
*/

#define __HAL_PCC_WDT_CLK_ENABLE()              (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_WDT_M)              /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ СЃС‚РѕСЂРѕР¶РµРІРѕРіРѕ С‚Р°Р№РјРµСЂР° */
#define __HAL_PCC_WDT_CLK_DISABLE()             (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_WDT_M)            /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ СЃС‚РѕСЂРѕР¶РµРІРѕРіРѕ С‚Р°Р№РјРµСЂР° */

#define __HAL_PCC_UART_0_CLK_ENABLE()           (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_UART_0_M)           /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ UART_0 */
#define __HAL_PCC_UART_0_CLK_DISABLE()          (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_UART_0_M)         /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ UART_0 */

#define __HAL_PCC_UART_1_CLK_ENABLE()           (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_UART_1_M)           /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ UART_1 */
#define __HAL_PCC_UART_1_CLK_DISABLE()          (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_UART_1_M)         /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ UART_1 */

#define __HAL_PCC_TIMER16_0_CLK_ENABLE()        (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_TIMER16_0_M)        /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer16_0 */
#define __HAL_PCC_TIMER16_0_CLK_DISABLE()       (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_TIMER16_0_M)      /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer16_0 */

#define __HAL_PCC_TIMER16_1_CLK_ENABLE()        (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_TIMER16_1_M)        /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer16_1 */
#define __HAL_PCC_TIMER16_1_CLK_DISABLE()       (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_TIMER16_1_M)      /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer16_1 */

#define __HAL_PCC_TIMER16_2_CLK_ENABLE()        (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_TIMER16_2_M)        /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer16_2 */
#define __HAL_PCC_TIMER16_2_CLK_DISABLE()       (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_TIMER16_2_M)      /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer16_2 */

#define __HAL_PCC_TIMER32_1_CLK_ENABLE()        (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_TIMER32_1_M)        /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer32_1 */
#define __HAL_PCC_TIMER32_1_CLK_DISABLE()       (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_TIMER32_1_M)      /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer32_1 */

#define __HAL_PCC_TIMER32_2_CLK_ENABLE()        (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_TIMER32_2_M)        /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer32_2 */
#define __HAL_PCC_TIMER32_2_CLK_DISABLE()       (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_TIMER32_2_M)      /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Timer32_2 */

#define __HAL_PCC_SPI_0_CLK_ENABLE()            (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_SPI_0_M)            /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPI_0 */
#define __HAL_PCC_SPI_0_CLK_DISABLE()           (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_SPI_0_M)          /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPI_0 */

#define __HAL_PCC_SPI_1_CLK_ENABLE()            (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_SPI_1_M)            /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPI_1 */
#define __HAL_PCC_SPI_1_CLK_DISABLE()           (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_SPI_1_M)          /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ SPI_1 */

#define __HAL_PCC_I2C_0_CLK_ENABLE()            (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_I2C_0_M)            /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ I2C_0 */
#define __HAL_PCC_I2C_0_CLK_DISABLE()           (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_I2C_0_M)          /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ I2C_0 */

#define __HAL_PCC_I2C_1_CLK_ENABLE()            (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_I2C_1_M)            /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ I2C_1 */
#define __HAL_PCC_I2C_1_CLK_DISABLE()           (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_I2C_1_M)          /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ I2C_1 */

#define __HAL_PCC_GPIO_0_CLK_ENABLE()           (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_GPIO_0_M)           /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ GPIO_0 */
#define __HAL_PCC_GPIO_0_CLK_DISABLE()          (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_GPIO_0_M)         /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ GPIO_0 */

#define __HAL_PCC_GPIO_1_CLK_ENABLE()           (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_GPIO_1_M)           /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ GPIO_1 */
#define __HAL_PCC_GPIO_1_CLK_DISABLE()          (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_GPIO_1_M)         /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ GPIO_1 */

#define __HAL_PCC_GPIO_2_CLK_ENABLE()           (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_GPIO_2_M)           /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ GPIO_2 */
#define __HAL_PCC_GPIO_2_CLK_DISABLE()          (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_GPIO_2_M)         /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ GPIO_2 */

#define __HAL_PCC_ANALOG_REGS_CLK_ENABLE()      (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_ANALOG_REGS_M)      /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Р°РЅР°Р»РѕРіРѕРІС‹С… Р±Р»РѕРєРѕРІ */
#define __HAL_PCC_ANALOG_REGS_CLK_DISABLE()     (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_ANALOG_REGS_M)    /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ Р°РЅР°Р»РѕРіРѕРІС‹С… Р±Р»РѕРєРѕРІ */

#define __HAL_PCC_GPIO_IRQ_CLK_ENABLE()         (PM->CLK_APB_P_SET = PM_CLOCK_APB_P_GPIO_IRQ_M)         /**< Р’РєР»СЋС‡РёС‚СЊ  С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ СЃС…РµРјС‹ С„РѕСЂРјРёСЂРѕРІР°РЅРёСЏ РїСЂРµСЂС‹РІР°РЅРёР№ GPIO */
#define __HAL_PCC_GPIO_IRQ_CLK_DISABLE()        (PM->CLK_APB_P_CLEAR = PM_CLOCK_APB_P_GPIO_IRQ_M)       /**< Р’С‹РєР»СЋС‡РёС‚СЊ С‚Р°РєС‚РёСЂРѕРІР°РЅРёРµ СЃС…РµРјС‹ С„РѕСЂРјРёСЂРѕРІР°РЅРёСЏ РїСЂРµСЂС‹РІР°РЅРёР№ GPIO */

/** @} */

/**
 * @brief РЎС‚СЂСѓРєС‚СѓСЂР° СЃ СЃРѕСЃС‚РѕСЏРЅРёСЏРјРё РѕС€РёР±РѕРє.
 * 
 * Р�СЃРїРѕР»СЊР·СѓРµС‚СЃСЏ С‚РѕР»СЊРєРѕ РєР°Рє РІРѕР·РІСЂР°С‰Р°РµРјРѕРµ Р·РЅР°С‡РµРЅРёРµ С„СѓРЅРєС†РёРё HAL_PCC_Config(PCC_InitTypeDef *PCC_Init).
 */
typedef struct __PCC_ConfigErrorsTypeDef
{
    HAL_StatusTypeDef FreqMonRef;       /**< РћС€РёР±РєР°, РІРѕР·РІСЂР°С‰Р°РµРјР°СЏ С„СѓРЅРєС†РёРµР№ HAL_PCC_FreqMonRefSet(HAL_PCC_FreqMonitorSourceTypeDef Force32KClk) */

    HAL_StatusTypeDef SetOscSystem;     /**< РћС€РёР±РєР°, РІРѕР·РІСЂР°С‰Р°РµРјР°СЏ С„СѓРЅРєС†РёРµР№ HAL_PCC_SetOscSystem(uint32_t OscillatorSystem, HAL_PCC_ForceOscSysTypeDef ForceOscSys) */

    HAL_StatusTypeDef RTCClock;         /**< РћС€РёР±РєР°, РІРѕР·РІСЂР°С‰Р°РµРјР°СЏ С„СѓРЅРєС†РёРµР№ HAL_PCC_RTCClock(HAL_PCC_RTCClockSourceTypeDef Oscillator) */

    HAL_StatusTypeDef CPURTCClock;      /**< РћС€РёР±РєР°, РІРѕР·РІСЂР°С‰Р°РµРјР°СЏ С„СѓРЅРєС†РёРµР№ HAL_PCC_CPURTCClock(HAL_PCC_CPURTCClockSourceTypeDef Oscillator) */

} PCC_ConfigErrorsTypeDef;


/**
 * @brief РќР°СЃС‚СЂРѕР№РєРё РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹
 */
typedef struct __PCC_FreqMonTypeDef
{
    uint8_t OscillatorSystem;                       /**<  Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹. РњРѕР¶РµС‚ РїСЂРёРЅРёРјР°С‚СЊ РѕРґРЅРѕ РёР· Р·РЅР°С‡РµРЅРёР№ HAL_PCC_OscillatorTypeTypeDef. */

    HAL_PCC_ForceOscSysTypeDef ForceOscSys;         /**< Р Р°Р·СЂРµС€РµРЅРёРµ РїСЂРёРЅСѓРґРёС‚РµР»СЊРЅРѕРіРѕ РІС‹Р±РѕСЂР° РёСЃС‚РѕС‡РЅРёРєР° С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ СЃРёСЃС‚РµРјС‹. РњРѕР¶РµС‚ РїСЂРёРЅРёРјР°С‚СЊ РѕРґРЅРѕ РёР· Р·РЅР°С‡РµРЅРёР№ HAL_PCC_ForceOscSysTypeDef. */

    HAL_PCC_FreqMonitorSourceTypeDef Force32KClk;   /**< РћРїРѕСЂРЅС‹Р№ РёСЃС‚РѕС‡РЅРёРє РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹. РњРѕР¶РµС‚ РїСЂРёРЅРёРјР°С‚СЊ РѕРґРЅРѕ РёР· Р·РЅР°С‡РµРЅРёР№ HAL_PCC_FreqMonitorSourceTypeDef. */

} PCC_FreqMonTypeDef;

/**
 * @brief РќР°СЃС‚СЂРѕР№РєРё С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ Рё РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹
 */
typedef struct __PCC_InitTypeDef
{
    uint8_t OscillatorEnable;                               /**< РћСЃС†РёР»Р»СЏС‚РѕСЂ, РєРѕС‚РѕСЂС‹Р№ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ РІРєР»СЋС‡РµРЅ. Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РјРѕР¶РµС‚ Р±С‹С‚СЊ РјР°СЃРєРѕР№ РёР· Р·РЅР°С‡РµРЅРёР№ HAL_PCC_OscillatorTypeTypeDef. */

    PCC_FreqMonTypeDef FreqMon;                             /**< РќР°СЃС‚СЂРѕР№РєРё РјРѕРЅРёС‚РѕСЂР° С‡Р°СЃС‚РѕС‚С‹. */

    uint32_t AHBDivider;                                     /**< Р”РµР»РёС‚РµР»СЊ С‡Р°СЃС‚РѕС‚С‹ AHB. Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ С‡РёСЃР»РѕРј РјРµР¶РґСѓ Min = 0 Рё Max = 255 */

    uint32_t APBMDivider;                                    /**< Р”РµР»РёС‚РµР»СЊ С‡Р°СЃС‚РѕС‚С‹ APB_M. Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ С‡РёСЃР»РѕРј РјРµР¶РґСѓ Min = 0 Рё Max = 255 */

    uint32_t APBPDivider;                                    /**< Р”РµР»РёС‚РµР»СЊ С‡Р°СЃС‚РѕС‚С‹ APB_P. Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ С‡РёСЃР»РѕРј РјРµР¶РґСѓ Min = 0 Рё Max = 255 */
    
    uint8_t HSI32MCalibrationValue;                         /**< РџРѕРїСЂР°РІРѕС‡РЅС‹Р№ РєРѕСЌС„С„РёС†РёРµРЅС‚ HSI32M. Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ С‡РёСЃР»РѕРј РјРµР¶РґСѓ Min = 0 Рё Max = 255 */

    uint8_t LSI32KCalibrationValue;                         /**< РџРѕРїСЂР°РІРѕС‡РЅС‹Р№ РєРѕСЌС„С„РёС†РёРµРЅС‚ LSI32K. Р­С‚РѕС‚ РїР°СЂР°РјРµС‚СЂ РґРѕР»Р¶РµРЅ Р±С‹С‚СЊ С‡РёСЃР»РѕРј РјРµР¶РґСѓ Min = 0 Рё Max = 15 */

    HAL_PCC_RTCClockSourceTypeDef RTCClockSelection;        /**<  Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC. РњРѕР¶РµС‚ РїСЂРёРЅРёРјР°С‚СЊ РѕРґРЅРѕ РёР· Р·РЅР°С‡РµРЅРёР№ HAL_PCC_RTCClockSourceTypeDef. */

    HAL_PCC_CPURTCClockSourceTypeDef RTCClockCPUSelection;  /**<  Р�СЃС‚РѕС‡РЅРёРє С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ RTC РІ СЃРѕСЃС‚Р°РІРµ СЏРґСЂР°. РњРѕР¶РµС‚ РїСЂРёРЅРёРјР°С‚СЊ РѕРґРЅРѕ РёР· Р·РЅР°С‡РµРЅРёР№ HAL_PCC_CPURTCClockSourceTypeDef. */

} PCC_InitTypeDef;



void HAL_PCC_OscEnable(HAL_PCC_OscillatorTypeTypeDef Oscillator);
void HAL_PCC_OscDisable(uint32_t Oscillator);
HAL_StatusTypeDef HAL_PCC_FreqMonRefSet(HAL_PCC_FreqMonitorSourceTypeDef Force32KClk);
HAL_StatusTypeDef HAL_PCC_SetOscSystem(uint32_t OscillatorSystem, HAL_PCC_ForceOscSysTypeDef ForceOscSys);
HAL_StatusTypeDef HAL_PCC_RTCClock(HAL_PCC_RTCClockSourceTypeDef Oscillator);
HAL_StatusTypeDef HAL_PCC_CPURTCClock(HAL_PCC_CPURTCClockSourceTypeDef Oscillator);
void HAL_PCC_DividerAHB(uint32_t DividerAHB);
void HAL_PCC_DividerAPB_M(uint32_t DividerAPB_M);
void HAL_PCC_DividerAPB_P(uint32_t DividerAPB_P);
PCC_ConfigErrorsTypeDef HAL_PCC_Config(PCC_InitTypeDef *PCC_Init);
uint32_t HAL_PCC_GetSysClockFreq(void);


#endif
