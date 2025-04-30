#include "gm67_config.h"

#include "data_utils.h"

static uint8_t Gm67RxArray1[16];

const Gm67Config_t Gm67Config[] = {
    {
      .num=1,
	  .uart_num=1,
	  .name = "Gm671",
      .rx_array_size=sizeof(Gm67RxArray1),
	  .RxArray=Gm67RxArray1,
      .valid=true,
    },
};

Gm67Handle_t Gm67Instance[] = {
    {.num=1, .valid=true, },
};

uint32_t gm67_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(Gm67Config);
    uint32_t cnt_ints = ARRAY_SIZE(Gm67Instance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

