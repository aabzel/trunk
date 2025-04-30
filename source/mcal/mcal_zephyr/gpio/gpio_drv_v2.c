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
#include "gpio_zephyr_types.h"

#include <hal/nrf_gpio.h>
#include <hal/nrf_spu.h>

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

bool gpio_set_state(uint8_t pad_num, GpioLogicLevel_t logic_level) {
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "Set Pad:%s LogicLev: %s", GpioPad2Str(pad_num), GpioLevel2Str(logic_level));
#endif
    bool res = false;
    Pad_t Pad = {.byte = 0};
    Pad.byte = pad_num;
    struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
    if(PortNode) {
    	if(GPIO_LVL_UNDEF != logic_level)
		{
			int ret = gpio_pin_set_raw(PortNode, (gpio_pin_t)Pad.pin, (int)logic_level);
			if(0 == ret)
				res = true;
		}
    }
    return res;
}

static gpio_flags_t GeneralPull2ZephyrPull(BSPGpioPullMode_t pull_code){
	gpio_flags_t gpio_flags = 0;
	switch(pull_code){
		case BSP_GPIO_PULL_DOWN:
			gpio_flags = ZEPHYR_PULL_DOWN;
			break;
		case BSP_GPIO_PULL_UP:
			gpio_flags = ZEPHYR_PULL_UP;
			break;
		case BSP_GPIO_PULL_AIR:
			gpio_flags = ZEPHYR_PULL_AIR;
			break;
		case BSP_GPIO_PULL_UNDEF:
			gpio_flags = ZEPHYR_PULL_AIR;
			break;
		case BSP_GPIO_PULL_UP_DOWN:
			gpio_flags = ZEPHYR_PULL_AIR;
			break;
	}
	return gpio_flags;
}

bool gpio_set_pull(uint8_t pad_num, GpioPullMode_t pull_code) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "SetPull Pad:%s Pull: %u", GpioPad2Str(pad_num), pull_code);
#endif
    Pad_t Pad = {.byte = 0};
	Pad.byte = pad_num;
	struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
	if(PortNode) {
		gpio_flags_t gpio_flags = GeneralPull2ZephyrPull(pull_code);
		int ret = gpio_pin_configure(PortNode, (gpio_pin_t)Pad.pin, gpio_flags);
//		LOG_INFO(CLI, "gpio_set_pull gpio_pin_configure PortNode %u, Pad.pin %u, gpio_flags %u ret 0x%X", PortNode, Pad.pin, gpio_flags, ret);
		if(0 == ret) {
			res = true;
		}
	}
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
//            *logic_level = gpio_pin_get_raw(PortNode, (gpio_pin_t)Pad.pin);
//            LOG_INFO(CLI, "gpio_get_state PortNode %u Pad.pin %u logic_level %u ", PortNode, Pad.pin, *logic_level);
			if(logic_level) {
				uint32_t pin_val = 0;
				uint32_t pin_out_val = 0;
				GpioDir_t dir = gpio_get_dir(pad_num);
				switch((uint8_t)dir) {
					case GPIO_DIR_INOUT:
					case GPIO_DIR_INOUT_OD:
					case GPIO_DIR_IN:
						pin_val = nrf_gpio_pin_read((uint32_t)pad_num);
						*logic_level = (GpioLogicLevel_t)pin_val;
						res = true;
						break;
					case GPIO_DIR_OUT_PUSH_PULL:
					case GPIO_DIR_OUT_OPEN_DRAIN:
					case GPIO_DIR_OUT:
						pin_out_val = nrf_gpio_pin_out_read((uint32_t)pad_num);
						*logic_level = (GpioLogicLevel_t)pin_out_val;
						res = true;
						break;
				}
			}
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
    switch((uint8_t)mcu_sel) {
    case GPIO_CORE_MUX_APP:
        mcu_sel = NRF_GPIO_PIN_MCUSEL_APP;
        res = true;
        break;
    case GPIO_CORE_MUX_NET:
        mcu_sel = NRF_GPIO_PIN_MCUSEL_NETWORK;
        res = true;
        break;
    }
    if(res) {
        nrf_gpio_pin_mcu_select(Pad.byte, mcu_sel);
    }
    return res;
}

static GpioPullMode_t ZephyrPull2GeneralPull(ZephyrPull_t Zephyr_pull_code) {
    GpioPullMode_t general_pull_code = GPIO_PULL_UNDEF;
    switch((uint8_t)Zephyr_pull_code) {
    case ZEPHYR_PULL_AIR:
        general_pull_code = BSP_GPIO_PULL_AIR;
        break;
    case ZEPHYR_PULL_UP:
        general_pull_code = BSP_GPIO_PULL_UP;
        break;
    case ZEPHYR_PULL_DOWN:
        general_pull_code = BSP_GPIO_PULL_DOWN;
        break;
    }
//	LOG_INFO(CLI, "ZephyrPull2GeneralPull Zephyr_pull_code %u, general_pull_code %u", Zephyr_pull_code, general_pull_code);
    return general_pull_code;
}

static GpioPullMode_t NrfPull2Pull(nrf_gpio_pin_pull_t pull) {
    GpioPullMode_t PullMode = GPIO_PULL_UNDEF;
    switch(pull) {
    case NRF_GPIO_PIN_NOPULL:
        PullMode = GPIO_PULL_AIR;
        break;
    case NRF_GPIO_PIN_PULLDOWN:
        PullMode = GPIO_PULL_DOWN;
        break;
    case NRF_GPIO_PIN_PULLUP:
        PullMode = GPIO_PULL_UP;
        break;
    }
    return PullMode;
}

GpioPullMode_t gpio_get_pull(uint8_t pad_num) {
    GpioPullMode_t PullMode = GPIO_PULL_UNDEF;
    Pad_t Pad = {.byte = 0};
	Pad.byte = pad_num;
	struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
	gpio_flags_t flags = 0;
	if(PortNode) {
//		int ret = gpio_pin_get_config(PortNode, (gpio_pin_t)Pad.pin, &flags);
//		PullMode = ZephyrPull2GeneralPull(flags);
//		LOG_INFO(CLI, "gpio_get_pull PortNode %u Pad.pin %u flags %u ret 0x%X", PortNode, Pad.pin,  flags, ret);
		nrf_gpio_pin_pull_t pull = nrf_gpio_pin_pull_get((uint32_t)pad_num);
		PullMode = NrfPull2Pull(pull);
//		LOG_INFO(CLI, "gpio_get_pull PortNode %u Pad.pin %u PullMode 0x%X", PortNode, Pad.pin,  PullMode);
	}
    return PullMode;
}

static GpioDir_t ZephyrDir2GeneralDir(gpio_flags_t gpio_flags){
	GpioDir_t GpioDir=GPIO_DIR_UNDEF;
	switch((uint32_t) gpio_flags){
		case GPIO_INPUT:
			GpioDir = GPIO_DIR_IN;
			break;
		case GPIO_OUTPUT:
			GpioDir = GPIO_DIR_OUT;
			break;
		case GPIO_DISCONNECTED:
			GpioDir = GPIO_DIR_NONE;
			break;
	}
//	LOG_INFO(CLI, "ZephyrDir2GeneralDir gpio_flags %u GpioDir %u", gpio_flags, GpioDir);
	return GpioDir;
}

static GpioDir_t NrfDir2Dir(nrf_gpio_pin_dir_t gpio_pin_dir) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    switch(gpio_pin_dir) {
    case NRF_GPIO_PIN_DIR_INPUT:
        dir = GPIO_DIR_IN;
        break;
    case NRF_GPIO_PIN_DIR_OUTPUT:
        dir = GPIO_DIR_OUT;
        break;
    }
    return dir;
}

GpioDir_t gpio_get_dir(uint8_t pad_num) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
	Pad_t Pad = {.byte = 0};
	Pad.byte = pad_num;
	struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
	gpio_flags_t gpio_flags=0;
//	int ret = gpio_pin_get_config(PortNode, (gpio_pin_t)Pad.pin, &gpio_flags);
//	LOG_INFO(CLI, "gpio_get_dir PortNode %u Pad.pin %u gpio_flags %u ret 0x%X", PortNode, Pad.pin, gpio_flags, ret);

	nrf_gpio_pin_dir_t gpio_pin_dir = NRF_GPIO_PIN_DIR_INPUT;
	gpio_pin_dir = nrf_gpio_pin_dir_get((uint32_t)pad_num);
	dir = NrfDir2Dir(gpio_pin_dir);
//	LOG_INFO(CLI, "gpio_pin_dir PortNode %u Pad.pin %u PullMode 0x%X", PortNode, Pad.pin,  dir);
//	dir = ZephyrDir2GeneralDir(gpio_flags);
	return dir;
}

static gpio_flags_t GpioDir2ZephyrDir(GpioDir_t dir) {
    gpio_flags_t gpio_flags = 0;
    switch((uint32_t)dir) {
    case GPIO_DIR_IN:
        gpio_flags = GPIO_INPUT;
        break;
    case GPIO_DIR_OUT:
        gpio_flags = GPIO_OUTPUT;	//GPIO_OUTPUT_INACTIVE;//
        break;
    case GPIO_DIR_OUT_PUSH_PULL:
        gpio_flags = GPIO_OUTPUT;
        break;
    case GPIO_DIR_OUT_OPEN_DRAIN:
        gpio_flags = GPIO_OUTPUT;
        break;
    case GPIO_DIR_INOUT:
        gpio_flags = GPIO_OUTPUT | GPIO_INPUT;
        break;
    case GPIO_DIR_NONE:
        gpio_flags = 0;
        break;
    case GPIO_DIR_INOUT_OD:
        gpio_flags = GPIO_OUTPUT | GPIO_INPUT;
        break;
    }
//    LOG_INFO(CLI, "GpioDir2ZephyrGpioFlag dir %u, gpio_flags %u, GPIO_OUTPUT %u, GPIO_INPUT %u", dir, gpio_flags, GPIO_OUTPUT, GPIO_INPUT);
    return gpio_flags;
}

bool gpio_set_dir(uint8_t pad_num, GpioDir_t dir) {
    bool res = false;
    Pad_t Pad = {.byte = 0};
	Pad.byte = pad_num;
	struct device* PortNode = PortNum2PortPtr((Port_t)Pad.port);
    gpio_flags_t gpio_flags = GpioDir2ZephyrDir(dir);
	int ret = gpio_pin_configure(PortNode, (gpio_pin_t)Pad.pin, gpio_flags);
//    LOG_INFO(CLI, "gpio_set_dir PortNode %u, gpio_pin %u, gpio_flags %u ret 0x%X", PortNode, Pad.pin, gpio_flags, ret);
    if(0 == ret) {
        res = true;
    }
    return res;
}

static bool gpio_init_one(const GpioConfig_t* item) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(GPIO, "InitOne Dir:%u", item->dir);
#endif
    res = gpio_is_pin_single(item->pad.byte);
//    nrf_spu_gpio_config_set(NRF_SPU, 0, 0x00000000, false);
//    nrf_spu_gpio_config_set(NRF_SPU, 1, 0xFFFFFFFF, false);

//    LOG_INFO(CLI, "gpio_init_one pad.byte %u, item->dir %u, item->gpio_pull %u, item->logic_level %u, item->mcu_sel %u",
//    		item->pad.byte, item->dir, item->gpio_pull, item->logic_level, item->mcu_sel);

    if(res) {
        if(item) {
//            if(GPIO_DIR_UNDEF != item->dir) {
//                res = gpio_set_dir(item->pad.byte, item->dir);
//                if(false == res) {
//#ifdef HAS_GPIO_DIAG
//                    LOG_ERROR(GPIO, "SetDirErr Pad:%s", GpioPad2Str(item->pad.byte));
//#endif /*HAS_GPIO_DIAG*/
//                } else {
//                    LOG_INFO(GPIO, "SetDirOk Pad:%s %s", GpioPad2Str(item->pad.byte), GpioDir2Str(item->dir));
//                }
//
//            } else {

        	gpio_set_pull(item->pad.byte, item->dir);
        	gpio_set_dir(item->pad.byte, item->dir);
        	gpio_set_state(item->pad.byte, (uint8_t)item->logic_level);
			if(GPIO_CORE_MUX_UNDEF != item->mcu_sel) {
				gpio_set_pin_mcu(item->pad, item->mcu_sel);
			}
        }
    } else {
#ifdef HAS_GPIO_DIAG
        LOG_ERROR(GPIO, "ReDefine Pad:%s", GpioPad2Str(item->pad.byte));
#endif /*HAS_GPIO_DIAG*/
    }
    return res;
}

bool gpio_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(GPIO, "Init");
#endif

#ifdef HAS_PINS
    gpio_clock_init();
    uint32_t i = 0;
    uint32_t cnt_ok = 0;
    uint32_t pin_cnt = gpio_get_cnt();
    LOG_INFO(GPIO, "TotalPins: %u", pin_cnt);
    for(i = 0; i < pin_cnt; i++) {
        res = gpio_init_one(&GpioConfigLut[i]);
        if(res) {
            cnt_ok++;
        }
    }
    if(pin_cnt == cnt_ok) {
        res = true;
    } else {
        LOG_ERROR(GPIO, "InitPartialErr: %u/%u", cnt_ok / pin_cnt);
    }
#endif /*HAS_PINS*/
    return res;
}
