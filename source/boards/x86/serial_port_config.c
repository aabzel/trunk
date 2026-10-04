#include "serial_port_config.h"

#include "data_utils.h"

const SerialPortConfig_t SerialPortConfig[] = {
    { .num = 1, .com_port_num = 1, .bit_rate = 115200, .byte_tx_pause_ms = 0, .valid = true,  .name = "USB2CANFD_V1",},
  //  {.num=2, .com_port_num=3, .bit_rate = 56000, .byte_tx_pause_ms=40, .valid = true, },
  //  {.num=3, .com_port_num=5, .bit_rate = 56000, .byte_tx_pause_ms=40, .valid = true, },
};

SerialPortHandle_t SerialPortInstance[]={
    {.num = 1, .valid = true,},
  //  {.num=2, .valid=true,},
  //  {.num=3, .valid=true,},
};


COMPONENT_GET_CNT(SerialPort, serial_port)

