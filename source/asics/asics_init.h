#ifndef ASICS_INIT_H
#define ASICS_INIT_H

#include "std_includes.h"

#ifdef HAS_AT24CX
#include "at24cx_mcal.h"
#define AT24CX_INIT   {.init_function=at24cx_mcal_init, .name="AT24Cxx",},
#else
#define AT24CX_INIT
#endif

#ifdef HAS_MX25L6433F
#include "mx25l6433f_mcal.h"
#define MX25L6433F_INIT   {.init_function = mx25l6433f_mcal_init, .name = "MX25L6433F",},
#else
#define MX25L6433F_INIT
#endif

#ifdef HAS_GM67
#include "gm67_mcal.h"
#define GM67_INIT   {.init_function=gm67_mcal_init, .name="gm67",},
#else
#define GM67_INIT
#endif

#ifdef HAS_BC127
#include "bc127_mcal.h"
#define BC127_INIT   {.init_function=bc127_mcal_init, .name="BC127",},
#else
#define BC127_INIT
#endif /*HAS_BC127*/

#ifdef HAS_BT1026
#include "bt1026_mcal.h"
#define BT1026_INIT   {.init_function=bt1026_mcal_init, .name="BT1026",},
#else
#define BT1026_INIT
#endif /*HAS_BT1026*/


#ifdef HAS_ESP_01
#include "esp_01.h"
#define ESP_01_INIT   {.init_function=esp_01_mcal_init, .name="ESP_01",},
#else
#define ESP_01_INIT
#endif /*HAS_ESP_01*/



#ifdef HAS_FDA801
#include "fda801_mcal.h"
#define FDA801_INIT   {.init_function=fda801_mcal_init, .name="Fda801",},
#else
#define FDA801_INIT
#endif /*HAS_FDA801*/

#ifdef HAS_NAU8814
#include "nau8814_mcal.h"
#define NAU8814_INIT {.init_function=nau8814_mcal_init, .name="Nau8814",},
#else
#define NAU8814_INIT
#endif /*HAS_NAU8814*/

#ifdef HAS_LTR390
#include "ltr390_mcal.h"
#define LTR390_INIT   {.init_function=ltr390_mcal_init, .name="LTR390",},
#else
#define LTR390_INIT
#endif /*HAS_LTR390*/

#ifdef HAS_MAX98357
#include "max98357_mcal.h"
#define MAX98357_INIT   {.init_function=max98357_mcal_init, .name="max98357",},
#else
#define MAX98357_INIT
#endif

#ifdef HAS_SD_CARD
#include "sd_card_mcal.h"
#define SD_CARD_INIT   {.init_function=sd_card_mcal_init, .name="SdCard",},
#else
#define SD_CARD_INIT
#endif

#ifdef HAS_SI4703
#include "si4703_mcal.h"
#define SI4703_INIT   {.init_function=si4703_mcal_init, .name="Si4703",},
#else
#define SI4703_INIT
#endif

#ifdef HAS_SI4737
#include "si4737_mcal.h"
#define SI4737_INIT   {.init_function=si4737_mcal_init, .name="Si4737",},
#else
#define SI4737_INIT
#endif

#ifdef HAS_BQ24079
#include "bq24079_mcal.h"
#define BQ24079_INIT   {.init_function=bq24079_mcal_init, .name="bq24079",},
#else
#define BQ24079_INIT
#endif

#ifdef HAS_AD9833
#include "ad9833_mcal.h"
#define AD9833_INIT   {.init_function=ad9833_mcal_init, .name="Ad9833",},
#else
#define AD9833_INIT
#endif

#ifdef HAS_SSD1306
#include "ssd1306_mcal.h"
#define SSD1306_INIT {.init_function=ssd1306_mcal_init, .name="Ssd1306",},
#else
#define SSD1306_INIT
#endif

#ifdef HAS_DECADRIVER_INIT
#include "decadriver.h"
#define DECADRIVER_INIT {.init_function=decadriver_mcal_init, .name="DecaDriver",},
#else
#define DECADRIVER_INIT
#endif

#ifdef HAS_ILI9341
#include "ili9341_mcal.h"
#define ILI9341_INIT   {.init_function=ili9341_mcal_init, .name="ILI9341",},
#else
#define ILI9341_INIT
#endif

#ifdef HAS_SX1262
#include "sx1262_mcal.h"
#define SX1262_INIT   {.init_function=SX1262_mcal_init, .name="SX1262",},
#else
#define SX1262_INIT
#endif


#ifdef HAS_TPA2013D1
#include "tpa2013d1_mcal.h"
#define TPA2013D1_INIT   {.init_function=tpa2013d1_mcal_init, .name="Tpa2013d1",},
#else
#define TPA2013D1_INIT
#endif

#ifdef HAS_RS2058
#include "rs2058_mcal.h"
#define RS2058_INIT   {.init_function=rs2058_mcal_init, .name="Rs2058",},
#else
#define RS2058_INIT
#endif

#ifdef HAS_DRV8870
#include "drv8870_mcal.h"
#define DRV8870_INIT   {.init_function=drv8870_mcal_init, .name="DRV8870",},
#else
#define DRV8870_INIT
#endif

#ifdef HAS_W25Q16J
#include "w25q16j_mcal.h"
#ifdef HAS_LOG
#define W25Q16J_INIT_NAME .name = "W25Q16J",
#else
#define W25Q16J_INIT_NAME
#endif

#define W25Q16J_INIT   {.init_function=w25q16j_mcal_init, W25Q16J_INIT_NAME},
#else
#define W25Q16J_INIT
#endif

#ifdef HAS_W25Q32J
#include "w25q32jv_mcal.h"

#ifdef HAS_LOG
#define W25Q32J_INIT_NAME .name = "w25q32jv",
#else
#define W25Q32J_INIT_NAME
#endif

#define W25Q32J_INIT   {.init_function=w25q32jv_mcal_init, W25Q32J_INIT_NAME},
#else
#define W25Q32J_INIT
#endif

#ifdef HAS_MAX9860
#include "max9860_mcal.h"
#define MAX9860_INIT   {.init_function=max9860_mcal_init, .name="max9860",},
#else
#define MAX9860_INIT
#endif

#ifdef HAS_WM8731
#include "wm8731_mcal.h"
#define WM8731_INIT   {.init_function=wm8731_mcal_init, .name="WM8731",},
#else
#define WM8731_INIT
#endif

#ifdef HAS_WM8994
#include "wm8994_mcal.h"
#define WM8994_INIT   {.init_function = wm8994_mcal_init, .name = "WM8994",},
#else
#define WM8994_INIT
#endif

#ifdef HAS_NEO_6M
#define NEO_6M_INIT   {.init_function=neo_6m_mcal_init, .name="NEO_6M",},
#else
#define NEO_6M_INIT
#endif

#ifdef HAS_BH1750
#include "bh1750_mcal.h"
#define BH1750_INIT   {.init_function=bh1750_mcal_init, .name="bh1750",},
#else
#define BH1750_INIT
#endif

#ifdef HAS_DS3231
#include "ds3231_mcal.h"
#define DS3231_INIT   {.init_function=ds3231_mcal_init, .name="ds3231",},
#else
#define DS3231_INIT
#endif

#ifdef HAS_UBLOX_NEO_6M
#include "ublox_neo_6m.h"
#define UBLOX_NEO_6M_INIT {.init_function=ublox_neo_6m_mcal_init, .name="uBloxNEO-6M",},
#else
#define UBLOX_NEO_6M_INIT
#endif

#ifdef HAS_SA51034
#include "SA51034_mcal.h"
#define SA51034_INIT   {.init_function=sa51034_mcal_init, .name="SA51034",},
#else
#define SA51034_INIT
#endif

#ifdef HAS_ZED_F9P
#include "zed_f9p_mcal.h"
#define ZED_F9P_INIT   {.init_function=zed_f9p_mcal_init, .name="ZED_F9P",},
#else
#define ZED_F9P_INIT
#endif

#define ASICS_SENSITIVITY_INIT    \
    SI4703_INIT                   \
    SI4737_INIT                   \
    GM67_INIT                     \
    BH1750_INIT                   \
    LTR390_INIT                   \
    DS3231_INIT                   \
    NEO_6M_INIT                   \
    UBLOX_NEO_6M_INIT             \
    DECADRIVER_INIT               \
    ZED_F9P_INIT

#define ASICS_CONNECTIVITY_INIT   \
    SX1262_INIT                   \
    BT1026_INIT                   \
    ESP_01_INIT                   \
    BC127_INIT

#define ASICS_STORAGE_INIT        \
    AT24CX_INIT                   \
    MX25L6433F_INIT               \
    W25Q16J_INIT                  \
    W25Q32J_INIT                  \
    SD_CARD_INIT

#define ASICS_CONTROL_INIT        \
    FDA801_INIT                   \
    ILI9341_INIT                  \
    RS2058_INIT                   \
    AD9833_INIT                   \
    WM8731_INIT                   \
    WM8994_INIT                   \
    MAX9860_INIT                  \
    MAX98357_INIT                 \
    DRV8870_INIT                  \
    SSD1306_INIT                  \
    BQ24079_INIT                  \
    TPA2013D1_INIT

#define ASICS_INIT                      \
    ASICS_SENSITIVITY_INIT              \
    ASICS_CONNECTIVITY_INIT             \
    ASICS_STORAGE_INIT                  \
    ASICS_CONTROL_INIT



#endif /* ASICS_INIT_H */
