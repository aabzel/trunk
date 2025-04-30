#ifndef NMEA_ISR_H
#define NMEA_ISR_H

#include "std_includes.h"
#include "nmea_types.h"

bool nmea_proc_byte_isr(NmeaHandle_t* const Node, uint8_t rx_byte);

#endif /* NMEA_ISR_H */
