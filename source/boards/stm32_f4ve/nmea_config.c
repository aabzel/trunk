#include "nmea_config.h"

#include "data_utils.h"
#include "nmea_types.h"

static uint8_t NmeaRxArray[2*1024]={0};

const NmeaConfig_t NmeaConfig[]={
    {
    .baud_rate = 9600,
    .num = 1,
    .rx_buff_size = sizeof(NmeaRxArray),
    .RxFifoArray = NmeaRxArray,
    .uart_num = 6,
    .valid = true,
    },
};

NmeaHandle_t NmeaInstance[]={
    {
    .num=1, .valid=true, }
};


uint32_t nmea_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(NmeaConfig);
    return cnt;
}

