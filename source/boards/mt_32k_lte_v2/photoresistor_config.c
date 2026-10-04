#include "photoresistor_config.h"

#ifndef HAS_PHOTORESISTOR
#error "Add HAS_PHOTORESISTOR"
#endif /*HAS_PHOTORESISTOR*/

#include "data_utils.h"
#include "photoresistor_types.h"

const PhotoResistorConfig_t SECTION_CFG_DATA PhotoResistorConfig[] = {
		{
		.num=1,
		.valid=true,
	    .u_in_v=3.3,
	    .r_vcc_om=1000000.0,
	    .r_gnd_om=0.0,
	    .pad={.port=PORT_A, .pin=0,},
		.name="Lignt",
		.vd_position = VOL_DIV_GND,
		.scale=1000000.0,
	},
};

PhotoResistorHandle_t PhotoResistorInstance[] = {
    {.num=1, .valid=true},
};

COMPONENT_GET_CNT(PhotoResistor, photo_resistor)

