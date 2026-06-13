#include "ssd1306_config.h"

#include "data_utils.h"

#include "ssd1306_const.h"

const Ssd1306Config_t Ssd1306Config[] = {
      {.num=1, .i2c_num=2, .i2c_addr=0x3C, .valid=true, .mem_addressing_mode=SSD1306_MEM_ADDR_MODE_HORIZONTAL,},
};

Ssd1306Handle_t Ssd1306Instance[] = {
     {.num=1, .valid=true,},
};

COMPONENT_GET_CNT(Ssd1306, ssd1306)
