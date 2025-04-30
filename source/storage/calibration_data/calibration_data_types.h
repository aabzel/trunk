#ifndef CALIBRATION_DATA_TYPES_H
#define CALIBRATION_DATA_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "calibration_data_const.h"


/*must be 256 byte*/

typedef union{
    uint8_t buff[256];
    struct{
        uint8_t version;
        uint16_t decawave_address;
        double uwb_offset;
        uint8_t data[244];
    	uint8_t crc8;
    }__attribute__((packed)) ;
}__attribute__((packed)) CalibrationData_t;

#define CALIBRATION_DATA_COMMON_VARIABLES \
    uint8_t eeprom_num; \
    bool valid;

typedef struct{
	CALIBRATION_DATA_COMMON_VARIABLES
}CalibrationDataConfig_t;


typedef struct{
	CALIBRATION_DATA_COMMON_VARIABLES
	bool init;
}CalibrationDataHandle_t;


#endif /* CALIBRATION_DATA_TYPES_H */
