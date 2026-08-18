#include "tpa2013d1_diag.h"

#include "tpa2013d1_config.h"
#include "tpa2013d1_types.h"
#include "log.h"
#include "tpa2013d1_drv.h"
#include "gpio_mcal.h"


const char* Tpa2013EnableToStr(GpioLogicLevel_t boost_ll){
	const char* name;
	if(boost_ll){
		name="EnableClassD";
	}else{
		name="ShutDownClassD";
	}
	return name;
}

const char* Tpa2013BoostToStr(GpioLogicLevel_t boost_ll){
	const char* name;
	if(boost_ll){
		name="EnableBoost";
	}else{
		name="ShutDownBoost";
	}
	return name;
}

bool tpa2013d1_diag(void) {
    bool res = false;

    res= gpio_get_state( Tpa2013Item.enable.byte, &Tpa2013Item.enable_ll);
    res= gpio_get_state( Tpa2013Item.boost.byte, &Tpa2013Item.boost_ll);
    LOG_INFO(TPA2013D1,"Enable %u=%s",Tpa2013Item.enable_ll,Tpa2013EnableToStr(Tpa2013Item.enable_ll));
    LOG_INFO(TPA2013D1,"Boost %u=%s",Tpa2013Item.boost_ll,Tpa2013BoostToStr(Tpa2013Item.boost_ll));

    return res;
}

