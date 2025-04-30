#include "ssd1306_config.h"

#include "data_utils.h"

#include "ssd1306_const.h"

const Ssd1306Config_t Ssd1306Config[]={
      {.num = 1,
       .i2c_num = 1,
       //.i2c_addr=0xbc,
       .i2c_addr = 0x3c,
       .valid = true,
       .mem_addressing_mode = SSD1306_MEM_ADDR_MODE_HORIZONTAL,},
};

Ssd1306Handle_t Ssd1306Instance[]={
     {
      .num=1,
      .valid=true,
     },
};

uint32_t ssd1306_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(Ssd1306Instance);
    cnt2 = ARRAY_SIZE(Ssd1306Config);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
