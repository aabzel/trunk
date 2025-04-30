#include "gpio_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "gpio_config.h"
#ifdef HAS_DIAG
#include "zephyr_diag.h"
#endif
#include "gpio_custom_types.h"

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifdef HAS_GPIO_DIAG
#include "gpio_general_diag.h"
#endif

static const PortInfo_t PortInfo[] = {{.port_num = PORT_0, .port = DEVICE_DT_GET(DT_NODELABEL(gpio0))},
                                      {.port_num = PORT_1, .port = DEVICE_DT_GET(DT_NODELABEL(gpio1))}};

static struct device* PortNum2PortPtr(Port_t port_num) {
    struct device* Node = NULL;
    uint32_t cnt = ARRAY_SIZE(PortInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(PortInfo[i].port_num == port_num) {
            Node = PortInfo[i].port;
            break;
        }
    }
    return Node;
}

static struct device* GpioPad2PortDev(uint8_t pad_num) {
    struct device* PortNode = NULL;
    Pad_t Pad = {.byte = 0};
    Pad.byte = pad_num;
    PortNode = PortNum2PortPtr((Port_t)Pad.port);
    return PortNode;
}

bool gpio_clock_init(void) { return false; }

bool gpio_set_state(uint8_t pad_num, uint8_t logic_level) {
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "Set Pad:%s LogicLev: %s", GpioPad2Str(pad_num), GpioLevel2Str(logic_level));
#endif
    bool res = false;
    Pad_t Pad = {.byte = 0};
    Pad.byte = pad_num;
    struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
    if(PortNode) {
        int ret = gpio_pin_set_raw(PortNode, (gpio_pin_t)Pad.pin, (int)logic_level);
        if(0 == ret) {
            res = true;
        }
    }
    return res;
}

bool gpio_set_pull(uint8_t pad_num, GpioPullMode_t pull_code) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "SetPull Pad:%s Pull: %u", GpioPad2Str(pad_num), pull_code);
#endif
    return res;
}

bool gpio_toggle(uint8_t pad_num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "Toggle Pad:%s", GpioPad2Str(pad_num));
#endif
    Pad_t Pad = {.byte = 0};
    Pad.byte = pad_num;
    struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
    if(PortNode) {
        int ret = gpio_pin_toggle(PortNode, (gpio_pin_t)Pad.pin);
        if(0 == ret) {
            res = true;
        }
    }
    return res;
}

bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* logic_level) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "Get Pad:%s", GpioPad2Str(pad_num));
#endif
    if(logic_level) {
        Pad_t Pad = {.byte = 0};
        Pad.byte = pad_num;
        struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
        if(PortNode) {
            *logic_level = gpio_pin_get_raw(PortNode, (gpio_pin_t)Pad.pin);
#ifdef HAS_LOG
            LOG_DEBUG(GPIO, "Get Pad:%s LogicLev: %s", GpioPad2Str(pad_num), GpioLevel2Str(*logic_level));
#endif
            res = true;
        }
    }

    return res;
}

bool gpio_set_pin_mcu(Pad_t Pad, GpioCoreMux_t mcu_sel) {
    bool res = false;
    return res;
}

GpioPullMode_t gpio_get_pull(uint8_t pad_num) {
    GpioPullMode_t PullMode = GPIO__PULL_UNDEF;
    LOG_DEBUG(GPIO, "GetPull %s", GpioPad2Str(pad_num));

#ifdef CONFIG_GPIO_GET_CONFIG
    Pad_t Pad = {.byte = 0};
    Pad.byte = pad_num;
    struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
    gpio_flags_t flags = 0;
    int ret = gpio_pin_get_config(PortNode, (gpio_pin_t)Pad.pin, &flags);
    if(0 == ret) {
        LOG_DEBUG(GPIO, "Pad %s Flags 0x%x", GpioPad2Str(pad_num), flags);
        if(GPIO__PULL_UP == (GPIO__PULL_UP & flags)) {
            PullMode = GPIO__PULL_UP;
        } else if(GPIO__PULL_DOWN == (GPIO__PULL_DOWN & flags)) {
            PullMode = GPIO__PULL_DOWN;
        }
    } else {
        LOG_ERROR(GPIO, "GetPullErr %s Ret %d=%s", GpioPad2Str(pad_num), ret, ErrNo2Str(ret));
    }
#endif
    return PullMode;
}

GpioDir_t gpio_get_dir(uint8_t pad_num) {
    LOG_DEBUG(GPIO, "GetDir %s", GpioPad2Str(pad_num));
    GpioDir_t dirr = GPIO_DIR_UNDEF;
#ifdef CONFIG_GPIO_GET_CONFIG
    Pad_t Pad = {.byte = 0};
    Pad.byte = pad_num;
    struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
    gpio_flags_t flags = 0;
    int ret = gpio_pin_get_config(PortNode, (gpio_pin_t)Pad.pin, &flags);
    if(0 == ret) {
        LOG_DEBUG(GPIO, "Pad %s Flags 0x%x", GpioPad2Str(pad_num), flags);
        if(GPIO_INPUT == (GPIO_INPUT & flags)) {
            dirr = GPIO_DIR_IN;
        } else if(GPIO_OUTPUT == (GPIO_OUTPUT & flags)) {
            dirr = GPIO_DIR_OUT;
        }
    } else {
        LOG_ERROR(GPIO, "GetDirErr %s Ret %d=%s", GpioPad2Str(pad_num), ret, ErrNo2Str(ret));
    }
#endif
    return dirr;
}

static gpio_flags_t GpioDir2ZephyrGpioFlag(GpioDir_t dir) {
    gpio_flags_t gpio_flag = 0;
    switch((uint32_t)dir) {
    case GPIO_DIR_IN:
        gpio_flag = GPIO_INPUT;
        break;
    case GPIO_DIR_OUT:
        gpio_flag = GPIO_OUTPUT;
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        gpio_flag = GPIO_OUTPUT;
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        gpio_flag = GPIO_OUTPUT;
        break;
    case GPIO_DIR_INOUT:
        gpio_flag = GPIO_OUTPUT | GPIO_INPUT;
        break;
    case GPIO_DIR_NONE:
        gpio_flag = 0;
        break;
    case GPIO_DIR_INOUT_OD:
        gpio_flag = GPIO_OUTPUT | GPIO_INPUT;
        break;
    }
    return gpio_flag;
}

bool gpio_set_dir(uint8_t pad_num, GpioDir_t dir) {
    bool res = false;
    struct device* PortDev = GpioPad2PortDev(pad_num);
    gpio_pin_t gpio_pin = gpio_padval_2pin(pad_num);
    gpio_flags_t gpio_flag = GpioDir2ZephyrGpioFlag(dir);
    int ret = gpio_pin_configure(PortDev, gpio_pin, gpio_flag);
    if(0 == ret) {
        res = true;
    }
    return res;
}

bool gpio_init_one(const GpioConfig_t* item) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "InitOne Dir:%u", item->dir);
#endif
    res = gpio_is_pin_single(item->pad.byte);
    if(res) {
        if(item) {
            if(GPIO_DIR_UNDEF != item->dir) {
                res = gpio_set_dir(item->pad.byte, item->dir);
                if(false == res) {
#ifdef HAS_GPIO_DIAG
                    LOG_ERROR(GPIO, "SetDirErr Pad:%s", GpioPad2Str(item->pad.byte));
#endif /*HAS_GPIO_DIAG*/
                } else {
                    LOG_INFO(GPIO, "SetDirOk Pad:%s %s", GpioPad2Str(item->pad.byte), GpioDir2Str(item->dir));
                }

            } else {
            }
        }
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "ReDefine Pad:%s", GpioPad2Str(item->pad.byte));
#endif /*HAS_GPIO_DIAG*/
    }
    return res;
}
