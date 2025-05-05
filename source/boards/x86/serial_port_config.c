#include "serial_port_config.h"

#include "data_utils.h"

const SerialPortConfig_t SerialPortConfig[] = {
    {.num=1, .com_port_num=5, .bit_rate = 56000, .valid = true, },
};

SerialPortHandle_t SerialPortInstance[]={
    {.num=1, .valid=true,},
};

uint32_t serial_port_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SerialPortInstance);
    cnt2 = ARRAY_SIZE(SerialPortConfig);
    if(cnt1==cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
