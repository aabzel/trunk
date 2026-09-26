#include "board_config.h"

#include "gpio_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

const Wire_t Wires[] = {
};

bool board_indicate_init_error(void) {
    bool res = true;
    return res;
}


bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS,LOG_LEVEL_INFO);
#endif
    LOG_INFO(SYS,"XTall: %u Hz",XTAL_FREQ_HZ);
#ifdef HAS_PASTILDA
    set_log_level(PASTILDA,LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_KEEPASS
    set_log_level(KEEPASS,LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_USB
    set_log_level(USB,LOG_LEVEL_INFO);
#ifdef HAS_USB_HOST
    set_log_level(USB_HOST,LOG_LEVEL_INFO);
#endif /*HAS_USB_HOST*/
    set_log_level(HID,LOG_LEVEL_INFO);
#endif /*HAS_USB*/
    return res;
}


uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);
    return cnt;
}

bool board_proc(void) {
    bool res = true;
    //Pad_t Pad={.port=PORT_C,.pin=0,};
    //gpio_toggle(  Pad);
    return res;
}

