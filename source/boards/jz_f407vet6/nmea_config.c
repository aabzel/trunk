#include "nmea_config.h"

#include "data_utils.h"
#include "nmea_types.h"

static uint8_t NmeaRxArray[2*1024]={0};

const NmeaConfig_t NmeaConfig[]={
    {
    .num = 1,
    .baud_rate = 9600,
    .rx_buff_size = sizeof(NmeaRxArray),
    .RxFifoArray = NmeaRxArray,
    .uart_num = 6,
    .valid = true,
    },
};

NmeaHandle_t NmeaInstance[]={
    {.num=1, .valid=true, }
};


COMPONENT_GET_CNT(Nmea, nmea)

