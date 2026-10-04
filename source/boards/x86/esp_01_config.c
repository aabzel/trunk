#include "esp_01_config.h"

#include "data_utils.h"

static uint8_t temp[500]={0};

const Esp01Config_t Esp01Config[] = {
    {
     .num = 1,
 	 .rx_array_size = ARRAY_SIZE(temp),
     .RxArray = temp,
     .name = "ESP_01",
     .uart_num = 2,
	 .valid = true,
    },
};

Esp01Handle_t Esp01Instance[] = {
    {.num=1, .valid=true, }
};

uint32_t esp_01_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(Esp01Config);
    return cnt;
}

