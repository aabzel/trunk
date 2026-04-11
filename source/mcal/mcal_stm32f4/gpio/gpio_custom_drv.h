#ifndef GPIO_CUSTOM_DRV_H
#define GPIO_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_mcal.h"
#include "gpio_custom_const.h"
#include "gpio_custom_types.h"
#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#endif
#include "gpio_types.h"
#include "stm32f4xx_hal.h"
#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

bool gpios_init(void);
bool generate_sw_int(uint32_t mask);
AltFunc_t gpio_get_alt(Pad_t Pad);
GPIO_TypeDef* GpioPortToPortPtr(const GpioPort_t port);
GpioStm32Mode_t gpio_get_mode(Pad_t Pad);
GpioStm32Speed_t gpio_get_speed(Pad_t Pad);
OutType_t gpio_get_out_type(Pad_t pad);
#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin);
#endif
bool ext_int_reset_mask(uint32_t mask);
bool ext_int_set_mask(uint32_t mask);
bool gpio_config_one(Pad_t pad, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate, GPIO_PinState PinState);
bool gpio_set_state(Pad_t Pad, GpioLogicLevel_t logic_level);
bool gpio_toggle_slow(Pad_t Pad);
bool is_edge_irq_en(Pad_t Pad);
uint32_t PinNum2PinMask(uint8_t pin_num);
uint32_t gpio_read(Pad_t Pad);
uint8_t get_aux_num(Pad_t Pad);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_DRV_H  */
