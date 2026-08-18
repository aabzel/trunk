#include "tpa2013d1_drv.h"

#include <string.h>

#include "log.h"
#include "gpio_mcal.h"

bool tpa2013d1_proc(void){
    bool res = true;
    LOG_DEBUG(TPA2013D1, "Proc");
    return res;
}

bool tpa2013d1_init(void) {
    bool res = true;
    LOG_WARNING(TPA2013D1, "Init");

	Tpa2013Item.enable.byte = Tpa2013Config.enable.byte;
	Tpa2013Item.boost.byte = Tpa2013Config.boost.byte;

	gpio_set_logic_level(  Tpa2013Item.enable.byte,   	Tpa2013Config.def_enable);
	gpio_set_logic_level(  Tpa2013Item.boost.byte,   Tpa2013Config.def_boost);

    log_level_set(TPA2013D1, LOG_LEVEL_INFO);
    return res;
}



