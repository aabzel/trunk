#ifndef ASICS_TASKS_H
#define ASICS_TASKS_H

#ifdef HAS_AT24CXX_PROC
#include "at24cxx_drv.h"
#define AT24CXX_TASK   {.name="AT24CXX", .period_us=AT24CXX_PERIOD_US, .limiter.function=at24cxx_proc,},
#else
#define AT24CXX_TASK
#endif

#ifdef HAS_BQ24079_PROC
#include "bq24079_drv.h"
#define BQ24079_TASK   {.name="BQ24079", .period_us=BQ24079_PERIOD_US, .limiter.function=bq24079_proc,},
#else
#define BQ24079_TASK
#endif

#ifdef HAS_SX1262_PROC
#include "sx1262_drv.h"
#define SX1262_TASK  {.name="SX1262", .period_us=SX1262_PERIOD_US, .limiter.function=sx1262_proc,},
#else
#define SX1262_TASK
#endif

#ifdef HAS_BC127_PROC
#include "bc127_drv.h"
#define BC127_TASKS {.name="BC127", .period_us=BC127_PERIOD_US, .limiter.function=bc127_proc,},
#else
#define BC127_TASKS
#endif

#ifdef HAS_BT1026_PROC
#include "bt1026_drv.h"

#define BT1026_TASKS                                                                                            \
    {.name="BT1026", .period_us=BT1026_PERIOD_US, .limiter.function=bt1026_proc,},                    \
    {.name="BT1026Link", .period_us=BT1026_LINK_CHECK_PERIOD_US, .limiter.function=bt1026_check_link,},   \
    {.name="BT1026Diag", .period_us=BT1026_DIAG_PERIOD_US, .limiter.function=bt1026_diag,},
#else
#define BT1026_TASKS
#endif

#ifdef HAS_DW1000_PROC
#include "dw1000_drv.h"
#define DW1000_TASKS  {.name="DW1000", .period_us=DW1000_PERIOD_US, .limiter.function=dw1000_process,},
#else
#define DW1000_TASKS
#endif

#ifdef HAS_DW3000_PROC
#include "dw3000_drv.h"
#define DW3000_TASKS  {.name="DW3000", .period_us=DW3000_PERIOD_US, .limiter.function=dwm3000_process,},
#else
#define DW3000_TASKS
#endif

#ifdef HAS_DECADRIVER_PROC
#include "decadriver.h"
#define DECADRIVER_TASK  {.name="DECADRIVER", .period_us=DECADRIVER_PERIOD_US, .limiter.function=decadriver_proc,},
#else
#define DECADRIVER_TASK
#endif

#ifdef HAS_GM67_PROC
#include "gm67_drv.h"
#define GM67_TASK {.name="GM67", .period_us=GM67_PERIOD_US, .limiter.function=gm67_proc,},
#else
#define GM67_TASK
#endif

#ifdef HAS_FDA801_PROC
#include "fda801_drv.h"
#define FDA801_TASKS {.name="FDA801", .period_us=FDA801_PERIOD_US, .limiter.function=fda801_proc,},
#else
#define FDA801_TASKS
#endif

#ifdef HAS_LTR390_PROC
#include "ltr390_drv.h"
#define LTR390_TASK {.name="Ltr390", .period_us=LTR390_PERIOD_US, .limiter.function=ltr390_proc,},
#else
#define LTR390_TASK
#endif

#ifdef HAS_MAX9860_PROC
#include "max9860_drv.h"
#define MAX9860_TASK  {.name="MAX9860", .period_us=MAX9860_PERIOD_US, .limiter.function=max9860_proc,},
#else
#define MAX9860_TASK
#endif

#ifdef HAS_NAU8814_PROC
#include "nau8814_drv.h"
#define NAU8814_TASK  {.name="Nau8814", .period_us=NAU8814_PERIOD_US, .limiter.function=nau8814_proc,},
#else
#define NAU8814_TASK
#endif

#ifdef HAS_MIC2026_PROC
#include "mic2026_drv.h"
#define MIC2026_TASK {.name="MIC2026", .period_us=MIC2026_PERIOD_US, .limiter.function=mic2026_proc,},
#else
#define MIC2026_TASK
#endif

#ifdef HAS_SA51034_PROC
#include "sa51034_drv.h"
#define SA51034_TASK {.name="SA51034", .period_us=SA51034_PERIOD_US, .limiter.function=sa51034_proc,},
#else
#define SA51034_TASK
#endif

#ifdef HAS_SI4703_PROC
#include "si4703_drv.h"
#define SI4703_TASKS {.name="SI4703", .period_us=SI4703_PERIOD_US, .limiter.function=si4703_proc,},
#else
#define SI4703_TASKS
#endif

#ifdef HAS_SI4737_PROC
#include "si4737_drv.h"
#define SI4737_TASKS {.name="SI4737", .period_us=SI4737_PERIOD_US, .limiter.function=si4737_proc,},
#else
#define SI4737_TASKS
#endif

#ifdef HAS_SSD1306_PROC
#include "ssd1306_drv.h"
#define SSD1306_TASK  {.name="SSD1306", .period_us=SSD1306_PERIOD_US, .limiter.function=ssd1306_proc,},
#else
#define SSD1306_TASK
#endif


#ifdef HAS_SX1262_PROC
#include "sx1262_drv.h"
#define SX1262_TASKS  {.name="SX1262", .period_us=SX1262_PERIOD_US, .limiter.function=sx1262_process,},
#else
#define SX1262_TASKS
#endif

#ifdef HAS_UBLOX_NEO_6M_PROC
#include "ublox_neo_6m.h"
#define UBLOX_NEO_6M_TASK {.name="uBloxNEO-6M", .period_us=UBLOX_NEO_6M_PERIOD_US, .limiter.function=ublox_neo_6m_proc,},
#else
#define UBLOX_NEO_6M_TASK
#endif


#ifdef HAS_TCAN4550_PROC
#include "tcan4550_drv.h"
#define TCAN4550_TASKS  {.name="TCAN4550", .period_us=TCAN4550_PERIOD_US, .limiter.function=tcan4550_proc,},
#else
#define TCAN4550_TASKS
#endif

#ifdef HAS_ZED_F9P_PROC
#include "zed_f9p_drv.h"
#define ZED_F9P_TASK {.name="ZED_F9P", .period_us=ZED_F9P_PERIOD_US, .limiter.function=zed_f9p_proc,},
#else
#define ZED_F9P_TASK
#endif


#ifdef HAS_W25Q32JV_PROC
#include "w25q32jv_drv.h"
#define W25Q32JV_TASK  {.name="W25Q32JV", .period_us=W25Q32JV_PERIOD_US, .limiter.function=w25q32jv_proc,},
#else
#define W25Q32JV_TASK
#endif


#define ASICS_STORAGE_TASK   \
    AT24CXX_TASK             \
    W25Q32JV_TASK

#define ASICS_CONNECTIVITY_TASK   \
    BC127_TASKS         \
    TCAN4550_TASKS      \
    SX1262_TASKS        \
    BT1026_TASKS        \
    DECADRIVER_TASK


#define ASICS_SENSITIVITY_TASK   \
    UBLOX_NEO_6M_TASK \
    SI4703_TASKS      \
    SI4737_TASKS      \
    GM67_TASK         \
    LTR390_TASK       \
    ZED_F9P_TASK


#define ASICS_MULTIMEDIA_TASK   \
    MAX9860_TASK      \
    NAU8814_TASK      \
    FDA801_TASKS

#define ASICS_CONTROL_TASK   \
    SA51034_TASK      \
    MIC2026_TASK      \
    BQ24079_TASK      \
    SSD1306_TASK

#define ASICS_TASK             \
    ASICS_SENSITIVITY_TASK         \
    ASICS_CONTROL_TASK         \
    ASICS_STORAGE_TASK         \
    ASICS_CONNECTIVITY_TASK    \
    ASICS_MULTIMEDIA_TASK


#endif /* ASICS_TASKS_H */
