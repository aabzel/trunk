#ifndef ASICS_COMMANDS_H
#define ASICS_COMMANDS_H

#ifdef HAS_AXP192_COMMANDS
#include "axp192_commands.h"
#else
#define AXP192_COMMANDS
#endif

#ifdef HAS_LTR390_COMMANDS
#include "ltr390_commands.h"
#else
#define LTR390_COMMANDS
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

#define ASICS_SENSITIVITY_COMMANDS    \
    GM67_COMMANDS         \
    LTR390_COMMANDS

#define ASICS_COMMANDS    \
    AD9833_COMMANDS       \
    ASICS_SENSITIVITY_COMMANDS       \
    AXP192_COMMANDS       \
    BC127_COMMANDS        \
    BQ24079_COMMANDS      \
    BT1026_COMMANDS       \
    FDA801_COMMANDS       \
    W25Q32JV_COMMANDS     \
    MAX9860_COMMANDS      \
    MAX98357_COMMANDS     \
    NAU8814_COMMANDS      \
    RS2058_COMMANDS       \
    BQ25171_Q1_COMMANDS   \
    TPA2013D1_COMMANDS    \
    SA51034_COMMANDS      \
    SI4703_COMMANDS       \
    SI4737_COMMANDS       \
    SSD1306_COMMANDS      \
    MIC2026_COMMANDS      \
    UBLOX_NEO_6M_COMMANDS \
    WM8731_COMMANDS

#endif /* ASICS_COMMANDS_H */
