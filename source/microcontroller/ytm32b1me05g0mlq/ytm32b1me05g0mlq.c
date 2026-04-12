#include "microcontroller.h"

#include "log.h"

const PinData_t PinConfig[]={0};

bool mcu_init(void) {
    bool res = false;
    LOG_WARNING(SYS,"Init,MCU:%s",MCU_NAME);
    res = true;
    return res;
}

uint16_t pin_get_cnt(void) {
    return 0xFFFF;
}
