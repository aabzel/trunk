#include "usb_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"

COMPONENT_GET_NODE(Usb, usb)
COMPONENT_GET_CONFIG(Usb, usb)


/*ISO-26262 require verify configuration*/

_WEAK_FUN_
bool UsbIsValidConfig(const UsbConfig_t* const Config) {
    bool res = false ;
    if(Config) {
        res = true;
        ifn(Config->speed) {
             res = false ;
             LOG_ERROR(USB, "speed,error");
        }
        ifn(Config->device_speed) {
            LOG_ERROR(USB, "device_speed,error");
            // res = false ;
        }

        ifn(Config->host_speed) {
            LOG_WARNING(USB, "host_speed,error");
            // res = false ;
        }

        ifn(Config->role) {
            LOG_ERROR(USB, "role,error");
             res = false ;
        }
        ifn(Config->name) {
            LOG_ERROR(USB, "name,error");
             res = false ;
        }
    }
    return res;
}

#if 0
void uds1_gpio_init(void){
    UsbConfig_t* Config = UsbGetConfig(1);
    if(Config ) {
        gpio_init_pad(Config->PadDP);
        gpio_init_pad(Config->PadDM);
    }
}

void uds2_gpio_init(void){
    UsbConfig_t* Config = UsbGetConfig(1);
    if(Config ) {
        gpio_init_pad(Config->PadDP);
        gpio_init_pad(Config->PadDM);
    }
}
#endif

/* This operation needed to reload USB driver on the side of PC */
bool usb_re_plug(const uint8_t num) {
    bool res = false;
    UsbConfig_t *Config = UsbGetConfig(num);
    if(Config) {
        gpio_deinit_pad(Config->PadDP);
        gpio_deinit_pad(Config->PadDM);

        wait_in_loop_ms(2000);

        gpio_init_pad(Config->PadDP);
        gpio_init_pad(Config->PadDM);
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool usb_init_custom(void) {
    bool res = false;
    LOG_INFO(USB, "Version:%s", USB_VERSION);
    return res;
}

_WEAK_FUN_
bool usb_proc_custom(void) {
    bool res = false;

    return res;
}



_WEAK_FUN_
bool usb_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(USB, "Proc %u", i);
    UsbHandle_t* Node = UsbGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool usb_init_common(const UsbConfig_t* const Config, UsbHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->interrupt_on = Config->interrupt_on;
            Node->PadDP = Config->PadDP;
            Node->PadDM = Config->PadDM;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool usb_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(USB, "USB%u", num);
    const UsbConfig_t* Config = UsbGetConfig(num);
    if(Config) {
        res = UsbIsValidConfig(Config);
        if(res) {
#ifdef HAS_USB_DIAG
            LOG_WARNING(USB, "%s", UsbConfigToStr(Config));
#endif
            UsbHandle_t* Node = UsbGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(USB, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(USB, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(USB, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(USB, USB, usb)
COMPONENT_PROC_PATTERT(USB, USB, usb)
