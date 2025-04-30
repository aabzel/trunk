#ifndef GPS_1BIT_DRV_H
#define GPS_1BIT_DRV_H

/*GPS receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "gps_1bit_config.h"
#include "gps_1bit_diag.h"
#include "gps_1bit_types.h"

const Gps1BitConfig_t* Gps1BitGetConfig(uint8_t num);
Gps1BitHandle_t* Gps1BitGetNode(uint8_t num);

bool gps_1bit_stream_to_i8( const  char* const file_name);
bool gps_1bit_init_custom(void);
bool gps_1bit_proc_one(uint8_t num);
bool gps_1bit_init_one(uint8_t num);
bool gps_1bit_init(void);

bool gps_1bit_seek_phase(char * data_path,  int prn, int16_t  given_freq_offset_hz);
bool gps_unpack_u16( const  char* const file_name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GPS_1BIT_DRV_H*/
