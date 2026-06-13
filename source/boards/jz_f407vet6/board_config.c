#include "board_config.h"

#include "gpio_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

bool board_indicate_init_error(void) {
    bool res = true;
    return res;
}

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    log_level_set(SYS,LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall:%u Hz",XTAL_FREQ_HZ);
#endif

#ifdef HAS_ISO_TP
    log_level_set(ISO_TP,LOG_LEVEL_DEBUG);
#endif

#ifdef HAS_USB
    log_level_set(USB, LOG_LEVEL_INFO);
#endif

#ifdef HAS_USB_HOST
    log_level_set(USB_HOST, LOG_LEVEL_INFO);
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
    { .pad = { .port=PORT_B,  .pin=10,}, .conn={.designator="P", .num=3,  .pin=5,}, .wire_name="SPI2_SCK",  .silk="",   } ,
    { .pad = { .port=PORT_C,  .pin=3,},  .conn={.designator="P", .num=3,  .pin=6,}, .wire_name="SPI2_MOSI", .silk="",   } ,
    { .pad = { .port=PORT_C,  .pin=2,},  .conn={.designator="P", .num=3,  .pin=7,}, .wire_name="SPI2_MISO", .silk="",   } ,
    { .pad = { .port=PORT_E,  .pin=9,},  .conn={.designator="P", .num=3,  .pin=8,}, .wire_name="",          .silk="",   } ,
    { .pad = { .port=PORT_E,  .pin=8,},  .conn={.designator="P", .num=3,  .pin=4,}, .wire_name="",          .silk="",   } ,
    { .pad = { .port=PORT_E,  .pin=7,},  .conn={.designator="P", .num=3,  .pin=3,}, .wire_name="",          .silk="",   } ,
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
