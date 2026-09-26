#ifndef EXT_INT_MCAL_H
#define EXT_INT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ext_int_types.h"
#include "ext_int_config.h"
#include "ext_int_isr.h"

#ifdef HAS_EXT_INT_DIAG
#include "ext_int_diag.h"
#endif

/*API*/
ExtIntHandle_t* ExtIntGetNode(uint8_t num);
ExtIntHandle_t* ExtIntPadToNode(const Pad_t Pad);
const ExtIntConfig_t* ExtIntGetConfig(uint8_t num);
bool ExtIntIsValidConfig(const ExtIntConfig_t* Config);

uint32_t num_exint_line(uint8_t num) ;
bool ext_int_init_common(ExtIntHandle_t* Node, const ExtIntConfig_t* Config);
bool ext_int_init_one(uint8_t num);
bool ext_int_init_custom(void);
bool ext_int_mcal_init(void);

bool ext_int_proc_one(uint8_t num);
bool ext_int_proc(void);

/*getters*/
GpioPort_t ext_int_pin_to_port(const uint8_t gpio_pin_num);
uint8_t exti_get_pin(void);
PinIntEdge_t gpio_logic_level_to_edge(const GpioLogicLevel_t logic_level);

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_MCAL_H  */
