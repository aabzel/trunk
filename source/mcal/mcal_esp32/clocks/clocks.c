#include "clocks.h"

#include <stdbool.h>
#include <stdint.h>

#include "driver/gptimer.h"
#include "esp_log.h"

gptimer_handle_t gptimer = NULL;

gptimer_config_t timer_config = {
    .clk_src = GPTIMER_CLK_SRC_APB,
    .direction = GPTIMER_COUNT_UP,
    .resolution_hz = 1000000, // 1MHz, 1 tick=1us
};

bool clock_init(void){
	bool res = true;
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));
    ESP_ERROR_CHECK(gptimer_start(gptimer));
    ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, 0));
	return res;
}

bool delay_ms(uint32_t delay_in_ms) {
    bool res = false;
    return res;
}

uint64_t get_time_us(void) {
    uint64_t cur_time_us = 0;
    gptimer_get_raw_count(gptimer, &cur_time_us);
    return cur_time_us;
}

uint32_t esp_get_time_ms32(void) {
	return (uint32_t) get_time_us()/1000;
}

#if 0
uint64_t get_time_ms64(void) {
	return (uint64_t)get_time_us()/1000;
}
#endif


void pause_1us(void ){

}

void pause_1ms(void){

}

