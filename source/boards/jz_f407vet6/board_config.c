#include "board_config.h"

#include "gpio_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS,LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall:%u Hz",XTAL_FREQ_HZ);
#endif

#ifdef HAS_ISO_TP
    set_log_level(ISO_TP,LOG_LEVEL_DEBUG);
#endif

#ifdef HAS_USB
    set_log_level(USB, LOG_LEVEL_INFO);
#endif

#ifdef HAS_USB_HOST
    set_log_level(USB_HOST, LOG_LEVEL_INFO);
#endif
    return res;
}

bool keyboard_reboot(void){
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SYS,"RebootUSBHost");
#endif
    return res;
}

#ifdef HAS_BOARD_INFO
const Wire_t Wires[]= {

};


uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);

    return cnt;
}

#endif

bool board_proc(void) {
    bool res = true;
    Pad_t Pad={.port=PORT_C,.pin=0,};
    gpio_toggle(  Pad);
    return res;
}
