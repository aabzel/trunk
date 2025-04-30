#ifndef GPIO_CUSTOM_DRV_H
#define GPIO_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gpio_mcal.h"
#include "gpio_custom_const.h"
#include "gpio_custom_types.h"
#include "gpio_types.h"
#include "artery_at32f4xx.h"

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

//AltFunc_t gpio_get_alt(uint8_t pad_num);
gpio_type* Port2PortPtr(Port_t port_num);
GpioAt32Mode_t gpio_get_mode(uint8_t pad_num);
gpio_pull_type GpioPull2At32Pull(GpioPullMode_t pull_code);
GpioAt32Speed_t gpio_get_speed(uint8_t pad_num);
OutType_t gpio_get_out_type(uint8_t pad_num);

#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin);
#endif
//PinInt_t* PinIntGetNode(uint16_t pad_num);
//Port_t PortLetter2PortNum(char port);
bool ext_int_reset_mask(uint32_t mask);
bool ext_int_set_mask(uint32_t mask);
//bool generate_sw_int(uint32_t mask);
bool gpio_config_one(Pad_t pad, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate, GpioLogicLevel_t PinState);
//bool gpio_init_one(const GpioConfig_t* pinInstance);
bool gpio_set_state(uint8_t pad_num, GpioLogicLevel_t logic_level);
bool gpios_init(void);
bool is_edge_irq_en(uint8_t pad_num);
//bool pin_get_int(uint8_t pin);
//bool pin_get_int_pend(uint8_t pin);
//uint32_t PinNum2PinMask(uint8_t pin_num);
uint32_t gpio_read(uint8_t pad_num);
//uint8_t LogicLevel2PinState(GpioLogicLevel_t logic_level);
uint8_t get_aux_num(uint8_t pad_num);
///uint8_t get_mcu_pin(uint8_t pad_num);
//uint8_t gpio_port_pin2pad(Port_t port, uint8_t pin);
GpioAt32Pull_t GpioPullToArteryPull(GpioPullMode_t pull_mode);
GpioPullMode_t GpioAt32Pull2GeneralPull(gpio_pull_type at32_pull_code);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_DRV_H  */
