
#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include "photoresistor_types.h"

const PhotoResistorConfig_t* PhotoResistorGetConfigNode(uint8_t num) ;
double photoresistor_read_om(uint8_t num);
double photoresistor_read_lighting(uint8_t num);
bool photoresistor_proc(void);
bool photoresistor_init(void);

#endif /* PHOTORESISTOR_H */



