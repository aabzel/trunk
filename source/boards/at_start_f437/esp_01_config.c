#include "esp_01_config.h"

#include "data_utils.h"

static uint8_t RxArray[ESP_01_RX_HEAP_SIZE] = {0};
static uint8_t TxArray[ESP_01_TX_HEAP_SIZE] = {0};

const Esp01Config_t Esp01Config[] = {
    {
     .num = 1,
     .rx_array_size = ARRAY_SIZE(RxArray),
     .RxArray = RxArray,
     .tx_array_size = ARRAY_SIZE(TxArray),
     .TxArray = TxArray,
     .name = "ESP_01",
     .uart_num = 2,
     .valid = true,
    },
};

Esp01Handle_t Esp01Instance[] = {
    {
        .num = 1,
        .valid = true,
    }
};

uint32_t esp_01_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(Esp01Config);
    return cnt;
}

