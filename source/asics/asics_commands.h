#ifndef ASICS_COMMANDS_H
#define ASICS_COMMANDS_H

#ifdef HAS_AXP192_COMMANDS
#include "axp192_commands.h"
#else
#define AXP192_COMMANDS
#endif

#ifdef HAS_BTS724G_COMMANDS
#include "bts724g_commands.h"
#else
#define BTS724G_COMMANDS
#endif

#ifdef HAS_BH1750_COMMANDS
#include "bh1750_commands.h"
#else
#define BH1750_COMMANDS
#endif

#ifdef HAS_DS3231_COMMANDS
#include "ds3231_commands.h"
#else
#define DS3231_COMMANDS
#endif

#ifdef HAS_DRV8870_COMMANDS
#include "drv8870_commands.h"
#else
#define DRV8870_COMMANDS
#endif

#ifdef HAS_LTR390_COMMANDS
#include "ltr390_commands.h"
#else
#define LTR390_COMMANDS
#endif

#ifdef HAS_LIS3DH_COMMANDS
#include "lis3dh_commands.h"
#else
#define LIS3DH_COMMANDS
#endif

#ifdef HAS_AD9833_COMMANDS
#include "ad9833_commands.h"
#else
#define AD9833_COMMANDS
#endif

#ifdef HAS_BQ24079_COMMANDS
#include "bq24079_commands.h"
#else
#define BQ24079_COMMANDS
#endif

#ifdef HAS_BQ25171_Q1_COMMANDS
#include "bq25171_q1_commands.h"
#else
#define BQ25171_Q1_COMMANDS
#endif /*HAS_BQ25171_Q1*/

#ifdef HAS_MIC2026_COMMANDS
#include "mic2026_commands.h"
#else
#define MIC2026_COMMANDS
#endif

#ifdef HAS_MAX98357_COMMANDS
#include "max98357_commands.h"
#else
#define MAX98357_COMMANDS
#endif

#ifdef HAS_RS2058_COMMANDS
#include "rs2058_commands.h"
#else
#define RS2058_COMMANDS
#endif

#ifdef HAS_GD5F1GQ5_COMMANDS
#include "gd5f1gq5_commands.h"
#else
#define GD5F1GQ5_COMMANDS
#endif

#ifdef HAS_BC127_COMMANDS
#include "bc127_commands.h"
#else
#define BC127_COMMANDS
#endif

#ifdef HAS_BT1026_COMMANDS
#include "bt1026_commands.h"
#else
#define BT1026_COMMANDS
#endif

#ifdef HAS_ESP_01_COMMANDS
#include "esp_01_commands.h"
#else
#define ESP_01_COMMANDS
#endif

#ifdef HAS_FDA801_COMMANDS
#include "fda801_commands.h"
#else
#define FDA801_COMMANDS
#endif

#ifdef HAS_GM67_COMMANDS
#include "gm67_commands.h"
#else
#define GM67_COMMANDS
#endif

#ifdef HAS_MX25L6433F_COMMANDS
#include "mx25l6433f_commands.h"
#else
#define MX25L6433F_COMMANDS
#endif


#ifdef HAS_MAX9860_COMMANDS
#include "max9860_commands.h"
#else
#define MAX9860_COMMANDS
#endif

#ifdef HAS_NAU8814_COMMANDS
#include "nau8814_commands.h"
#else
#define NAU8814_COMMANDS
#endif

#ifdef HAS_SA51034_COMMANDS
#include "sa51034_commands.h"
#else
#define SA51034_COMMANDS
#endif

#ifdef HAS_SI4703_COMMANDS
#include "si4703_commands.h"
#else
#define SI4703_COMMANDS
#endif

#ifdef HAS_SI4737_COMMANDS
#include "si4737_commands.h"
#else
#define SI4737_COMMANDS
#endif

#ifdef HAS_SSD1306_COMMANDS
#include "ssd1306_commands.h"
#else
#define SSD1306_COMMANDS
#endif

#ifdef HAS_TPA2013D1_COMMANDS
#include "tpa2013d1_commands.h"
#else
#define TPA2013D1_COMMANDS
#endif

#ifdef HAS_W25M02GV_COMMANDS
#include "w25m02gv_commands.h"
#else
#define W25M02GV_COMMANDS
#endif

#ifdef HAS_WM8731_COMMANDS
#include "wm8731_commands.h"
#else
#define WM8731_COMMANDS
#endif

#ifdef HAS_W25Q32JV_COMMANDS
#include "w25q32jv_commands.h"
#else
#define W25Q32JV_COMMANDS
#endif

#ifdef HAS_UBLOX_NEO_6M_COMMANDS
#include "ublox_neo_6m_commands.h"
#else
#define UBLOX_NEO_6M_COMMANDS
#endif

#ifdef HAS_WM8994_COMMANDS
#include "WM8994_commands.h"
#else
#define WM8994_COMMANDS
#endif

#define ASICS_SENSITIVITY_COMMANDS    \
    TPA2013D1_COMMANDS    \
    DS3231_COMMANDS       \
    BH1750_COMMANDS       \
    SI4703_COMMANDS       \
    SI4737_COMMANDS       \
    UBLOX_NEO_6M_COMMANDS \
    SA51034_COMMANDS      \
    GM67_COMMANDS         \
    LTR390_COMMANDS

#define ASICS_STORAGE_COMMANDS     \
    MX25L6433F_COMMANDS

#define ASICS_CONTROL_COMMANDS    \
            MAX9860_COMMANDS      \
            MIC2026_COMMANDS      \
            RS2058_COMMANDS       \
            AXP192_COMMANDS       \
            BQ24079_COMMANDS      \
            AD9833_COMMANDS       \
            SSD1306_COMMANDS      \
            MAX98357_COMMANDS     \
            WM8994_COMMANDS       \
            NAU8814_COMMANDS      \
            BQ25171_Q1_COMMANDS   \
            FDA801_COMMANDS       \
            DRV8870_COMMANDS      \
            WM8731_COMMANDS

#define ASICS_COMMANDS             \
    ASICS_CONTROL_COMMANDS         \
    ASICS_STORAGE_COMMANDS         \
    ASICS_SENSITIVITY_COMMANDS     \
    BC127_COMMANDS                 \
    BT1026_COMMANDS                \
    ESP_01_COMMANDS                \
    W25Q32JV_COMMANDS

#endif /* ASICS_COMMANDS_H */
