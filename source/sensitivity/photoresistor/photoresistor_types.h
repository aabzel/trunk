
#ifndef PHOTORESISTOR_TYPES_H
#define PHOTORESISTOR_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "photoresistor_const.h"
#include "gpio_types.h"

typedef struct {
	uint8_t num;;
	bool valid;
    double u_in_v;
    double r_vcc_om;
    double r_gnd_om;
    Pad_t pad;
    char* name;
    double scale;
	VdPosition_t vd_position;
}PhotoResistorConfig_t;

typedef struct {
	uint8_t num;
	bool valid;
    double u_in_v;
    double r_vcc_om;
    double r_gnd_om;
    double resistance;
    double scale;
    double lighting;
    Pad_t pad;
	VdPosition_t vd_position;
}PhotoResistorHandle_t;

#endif /* PHOTORESISTOR_TYPES_H */



