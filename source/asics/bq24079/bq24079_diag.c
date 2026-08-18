#include "bq24079_diag.h"

#include <stdint.h>
#include <stdio.h>

#include "bq24079_drv.h"
#include "str_utils.h"
#include "bq24079_const.h"
#include "common_diag.h"
#include "log.h"
#include "convert.h"
#include "data_utils.h"
#include "log_utils.h"
#include "table_utils.h"
#include "writer_config.h"
#include "bq24079_config.h"

#ifndef HAS_BQ24079
#error "+HAS_BQ24079"
#endif

const char* Bq24079SettingsToStr(Bq24079Settings_t mode) {
    const char* name = "?";
    switch(mode) {
    case BQ24079_100_MA:
        name = "100mA";
        break;
    case BQ24079_500_MA:
        name = "500mA";
        break;
    case BQ24079_SET_ILIM:
        name = "SetByIlim";
        break;
    case BQ24079_STANDBY:
        name = "StandBy";
        break;
    default:
        break;
    }
    return name;
}

const char* Bq24079PgoodToStr(GpioLogicLevel_t pgood_lev) {
    const char* name = "?";
    switch(pgood_lev) {
    case GPIO_LVL_LOW:
        name = "ValidInSource";
        break;
    case GPIO_LVL_HI:
        name = "NoValidInSource";
        break;

    default:
        break;
    }
    return name;
}

bool bq24079_diag( void) {
    bool res = true;
    LOG_INFO(BQ24079,"ErrCnt:%u",Bq24079Item.err_cnt);
    LOG_INFO(BQ24079,"Setting:%u=%s",Bq24079Item.setting,Bq24079SettingsToStr(Bq24079Item.setting));
    LOG_INFO(BQ24079,"Pgood:%u=%s",Bq24079Item.pgood_lev,Bq24079PgoodToStr(Bq24079Item.pgood_lev));

    return res;
}
