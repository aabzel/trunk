#include "nmea_config.h"

#include "data_utils.h"
#include "nmea_types.h"

const NmeaConfig_t NmeaConfig[]={
    {.num=1,
    	     .baud_rate = 9600,
    		.uart_num=6,
			.valid=true, },
};

NmeaHandle_t NmeaInstance[]={
    {.num=1, .valid=true, }
};


uint32_t nmea_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(NmeaConfig);
    return cnt;
}

