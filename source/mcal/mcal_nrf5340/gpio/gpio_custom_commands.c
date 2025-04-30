#include "gpio_custom_commands.h"

#include "convert.h"
#include "gpio_mcal.h"
#include "gpio_custom_diag.h"
#include "gpio_custom_drv.h"
#include "gpio_custom_types.h"
#include "log.h"

bool nrf_gpio_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t logic_level = 0xFF;
    Pad_t Pad = {.byte = 0};

    if(2 <= argc) {
        res = parse_pad(argv, &Pad);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr LogicLevel %s", argv[2]);
        }
    }

    if(argc < 3) {
        LOG_ERROR(GPIO, "Usage: ngs port pin level");
        LOG_INFO(GPIO, "port 0..1");
        LOG_INFO(GPIO, "pin 0....15 ");
        LOG_INFO(GPIO, "level 0..1 ");
        res = false;
    }
    if(res) {
    	res = false;
        LOG_WARNING(GPIO, "TrySetState Pad: %s LogicLev: %s", GpioPad2Str(Pad.byte), GpioLevel2Str(logic_level));
       // res = gpio_set_state(Pad.byte, logic_level);
        if(false == res) {
            LOG_ERROR(GPIO, "SetErr");
        } else {
            LOG_INFO(GPIO, "SetState %s %s", GpioPad2Str(Pad.byte), GpioLevel2Str(logic_level));
        }
    }
    return res;
}

bool nrf_gpio_set_core_command(int32_t argc, char* argv[]) {
    bool res = false;
    Pad_t Pad = {.byte = 0};
    uint8_t code = 0xFF;
    if(2 <= argc) {
        res = parse_pad(argv, &Pad);
    }

    if(3 == argc) {
        res = try_str2uint8(argv[2], &code);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr code %s", argv[2]);
        }
    }

    if(res) {
        nrf_gpio_pin_mcusel_t mcusel=0;
        if(2 == argc) {
            LOG_INFO(GPIO, "GetPinMux Pad: %s", GpioPad2Str(Pad.byte));
            mcusel = nrf_gpio_pin_mcu_select_get(Pad.byte);
        }

        if(3 == argc) {
            LOG_INFO(GPIO, "SetPinMux Pad: %s McuSel %s", GpioPad2Str(Pad.byte), McuSel2Str(mcusel));
            mcusel = (nrf_gpio_pin_mcusel_t)code;
            nrf_gpio_pin_mcu_select(Pad.byte, mcusel);
        }
        LOG_INFO(GPIO, "Pad: %s McuSel %s", GpioPad2Str(Pad.byte), McuSel2Str(mcusel));
    } else {
        LOG_ERROR(GPIO, "Usage: ngsm port pin sel");
        LOG_INFO(GPIO, "Sel %u=App", NRF_GPIO_PIN_MCUSEL_APP);
        LOG_INFO(GPIO, "Sel %u=Net", NRF_GPIO_PIN_MCUSEL_NETWORK);
        LOG_INFO(GPIO, "Sel %u=Trace", NRF_GPIO_PIN_MCUSEL_TND);
    }
    return res;
}


//ngc 2 1 0 0 3 0
//ngc 3 1 0 0 3 0
bool nrf_gpio_cfg_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t             pin_number =0;
    nrf_gpio_pin_dir_t   dir = NRF_GPIO_PIN_DIR_INPUT;
	nrf_gpio_pin_input_t input = NRF_GPIO_PIN_INPUT_CONNECT;
	nrf_gpio_pin_pull_t  pull = NRF_GPIO_PIN_NOPULL;
    nrf_gpio_pin_drive_t drive = NRF_GPIO_PIN_S0S1;
	nrf_gpio_pin_sense_t sense = NRF_GPIO_PIN_NOSENSE;

    if(1<=argc){
        res = try_str2uint32(argv[0], &pin_number);
    }

    if(2<=argc){
        res = try_str2uint8(argv[1], &dir);
    }
    if(3<=argc){
        res = try_str2uint8(argv[2], &input);
    }

    if(4<=argc){
        res = try_str2uint8(argv[3], &pull);
    }

    if(5<=argc){
        res = try_str2uint8(argv[4], &drive);
    }

    if(6<=argc){
        res = try_str2uint8(argv[5], &sense);
    }

     if(res){
         nrf_gpio_cfg(pin_number, dir, input, pull, drive, sense);
     }
     return res;
}
