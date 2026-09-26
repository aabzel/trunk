#include "can_if_drv.h"

#include "log.h"
#include "std_includes.h"

bool can_if_send(uint8_t num, const uint8_t* const data, uint16_t len) {
    bool res = false;
    return res;
}

bool can_if_proc_payload(uint8_t* const rx_payload, uint32_t rx_size) {
    bool res = false;

    return res;
}

bool can_if_proc(void) {
    bool res = false;
    return res;
}

bool can_if_init(void) {
    bool out_res = true;
    (void)out_res;

    return out_res;
}
