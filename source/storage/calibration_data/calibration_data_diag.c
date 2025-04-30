#include "calibration_data_diag.h"

#include <stdio.h>
#include <string.h>

#include "calibration_data.h"
#include "calibration_data_config.h"
#include "log.h"


const char* CalibrationData2Str(const CalibrationData_t * const Node) {
    static char text[80]="";
    if(Node){
        snprintf(text,sizeof(text),"Ver:%u,DecaWaveID:%x,UwbOffset:%f m,CRC8:%x",
                Node->version,
                Node->decawave_address,
                Node->uwb_offset,
                Node->crc8 );
    }
    return text;
}

bool calibration_data_diag(void) {
    bool res = false;
	CalibrationData_t Data = {0};
    memset(Data.buff, 0, sizeof(CalibrationData_t));
	res = calibration_data_get(Data.buff);
	if (res){
		LOG_INFO(CALIBRATION_DATA, "%s", CalibrationData2Str(&Data));
	}
    return res;
}
