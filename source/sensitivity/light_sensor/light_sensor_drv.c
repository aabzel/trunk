#include "light_sensor_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_LTR390
#include "ltr390_drv.h"
#endif

#ifdef HAS_BH1750
#include "bh1750_drv.h"
#endif

#ifdef HAS_PHOTORESISTOR
#include "photoresistor.h"
#endif
#include "log.h"

const LightSensorConfig_t* LightSensorGetConfig(uint8_t lx_num) {
    const LightSensorConfig_t* LightSensorNode = NULL;
    uint32_t i = 0;
    uint32_t cnt = light_sensor_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(lx_num == LightSensorConfig[i].num) {
            if(LightSensorConfig[i].valid) {
                LightSensorNode = &LightSensorConfig[i];
                break;
            }
        }
    }
    return LightSensorNode;
}

double light_sensor_read(uint32_t num){
	double lighting=0.0;
	bool res = false;
	const LightSensorConfig_t* Config=LightSensorGetConfig(num);
	if(Config){
        switch(Config->sen_type){
#ifdef HAS_PHOTORESISTOR
            case LI_SENS_PHOTORESISTOR: {
            	lighting= photoresistor_read_lighting( Config->sen_num);
            	res = true;
            } break;
#endif

#ifdef HAS_BH1750
            case LI_SENS_BH1750: {
            	lighting=bh1750_read_lx_short(Config->sen_num);
            	res = true;
            } break;
#endif

#ifdef HAS_LTR390
            case LI_SENS_LTR390_ALS: {
            	lighting=ltr390_read_lx_short(Config->sen_num);
            	res = true;
            } break;

            case LI_SENS_LTR390_UVS: {
            	lighting = ltr390_read_uv_short(Config->sen_num);
            	res = true;
            } break;
#endif
            default:
            	LOG_ERROR(LIGHT_SENSOR,"Error %u",num);
            	break;
        }
	}
	if(res){

    	LOG_INFO(LIGHT_SENSOR,"Read %u Light %f",num,lighting);
	}
	return lighting;
}



