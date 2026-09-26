#ifndef GPIO_CUSTOM_DRV_H
#define GPIO_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio_mcal.h"
#include "gpio_custom_const.h"
#include "gpio_custom_types.h"
#include "gpio_types.h"
#include "std_includes.h"
#include "x86x.h"

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif


PORT_InstanceType GpioPortTo_eInstance(const GpioPort_t port);
const GpioPortInfo_t* GpioGetPortInfo(GpioPort_t port);
uint32_t* Port2PortPtr(GpioPort_t port);
GpioOutType_t gpio_get_out_type(Pad_t Pad);
#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin);
#endif
bool ext_int_reset_mask(uint32_t mask);
bool ext_int_set_mask(uint32_t mask);
bool gpio_config_one(Pad_t pad, uint32_t Mode, uint32_t Pull, uint32_t Speed, uint32_t Alternate, GpioLogicLevel_t PinState);
bool gpio_set_state(Pad_t Pad, GpioLogicLevel_t logic_level);
bool gpios_init(void);
bool is_edge_irq_en(Pad_t Pad);
uint32_t gpio_read(Pad_t Pad);
uint8_t get_aux_num(Pad_t Pad);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_DRV_H  */
