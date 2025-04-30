#include "core_driver.h"

#include <esp_mac.h>
#include <stdio.h>
#include <string.h>


#include "array.h"
#include "bit_utils.h"
#include "boot_cfg.h"
#include "data_utils.h"
#include "read_mem.h"
#include "sys.h"
#include "esp_system.h"


uint32_t cpu_get_id(void) {
    uint32_t value=0;

    return value;
}

uint64_t get_ble_mac(void) {
    Type64Union_t uValue;
    esp_err_t ret;
    uValue.u64 = 0;
    ret = esp_read_mac((uint8_t *)  &uValue.u8, ESP_MAC_BT);
    if(ESP_OK==ret){

    }
    return uValue.u64;
}

bool reboot(void) {
    bool res = false;
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
    return res;
}
