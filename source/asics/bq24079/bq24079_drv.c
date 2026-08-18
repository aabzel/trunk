#include "bq24079_drv.h"

#include "bq24079_diag.h"
#include "gpio_mcal.h"
#include "log.h"

Bq24079Settings_t bq24079_settings_get(void){
	bool res = true;
    Bq24079Settings_t settings = BQ24079_UNDEF;
    uint8_t code=0;

    res= gpio_get_state(Bq24079Config.en1.byte, &Bq24079Item.en1_lev);
    res= gpio_get_state(Bq24079Config.en2.byte, &Bq24079Item.en2_lev)&&res;

    if(res){
        if (Bq24079Item.en1_lev) {
            code |=(1<<0);
        }

        if (Bq24079Item.en2_lev) {
            code |=(1<<1);
        }

        settings = (Bq24079Settings_t) code;
    }
    return settings;
}

bool bq24079_settings_set(Bq24079Settings_t settings){
	bool res = false;
#ifdef HAS_BQ24079_DIAG
    LOG_WARNING(BQ24079,"SetSetting %u=%s",settings, Bq24079SettingsToStr(settings));
#endif
    switch(settings) {
        case BQ24079_100_MA:{
            res= gpio_set_logic_level(Bq24079Config.en1.byte,   GPIO_LVL_LOW);
            res= gpio_set_logic_level(Bq24079Config.en2.byte,   GPIO_LVL_LOW);
        } break;
        case BQ24079_500_MA:{
            res= gpio_set_logic_level(Bq24079Config.en1.byte,GPIO_LVL_HI);
            res= gpio_set_logic_level(Bq24079Config.en2.byte,   GPIO_LVL_LOW);
        } break;
        case BQ24079_SET_ILIM:{
            res= gpio_set_logic_level(Bq24079Config.en1.byte,  GPIO_LVL_LOW);
            res= gpio_set_logic_level(Bq24079Config.en2.byte,  GPIO_LVL_HI);
        } break;
        case BQ24079_STANDBY:{
            res= gpio_set_logic_level(Bq24079Config.en1.byte,  GPIO_LVL_HI);
            res= gpio_set_logic_level(Bq24079Config.en2.byte, GPIO_LVL_HI);
        } break;
        default: break;
    }
    return res;
}



bool bq24079_init(void){
    bool res = false;
    LOG_WARNING(BQ24079,"Init");

    Bq24079Item.en1.byte = Bq24079Config.en1.byte;
    Bq24079Item.en2.byte = Bq24079Config.en2.byte;
    Bq24079Item.pgood.byte = Bq24079Config.pgood.byte;

    res= gpio_set_pull(Bq24079Item.pgood.byte, GPIO__PULL_UP);

    res = bq24079_settings_set(Bq24079Config.setting);

    return res;
}

bool bq24079_proc(void) {
    bool res = false;
    LOG_DEBUG(BQ24079,"Proc");

    Bq24079Item.setting = bq24079_settings_get();
    res = gpio_get_state(Bq24079Config.pgood.byte, &Bq24079Item.pgood_lev);
#ifdef HAS_BQ24079_DIAG
    LOG_DEBUG(BQ24079,"Pgood:%s", Bq24079PgoodToStr(Bq24079Item.pgood_lev) );
#endif

    if (Bq24079Item.pgood_lev) {
        Bq24079Item.err_cnt++;
    }
    return res;
}
