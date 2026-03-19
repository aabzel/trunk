#ifndef EXT_INT_MCAL_H
#define EXT_INT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ext_int_config.h"
#include "ext_int_isr.h"
#include "ext_int_types.h"

#ifdef HAS_EXT_INT_DIAG
#include "ext_int_diag.h"
#endif

/*API*/
const ExtIntConfig_t* ExtIntGetConfig(uint8_t num);
ExtIntHandle_t* ExtIntGetNode(uint8_t num);

uint32_t num_exint_line(uint8_t num) ;
bool ext_int_init_one(uint8_t num);
bool ext_int_init_custom(void);
bool ext_int_mcal_init(void);
bool ext_int_proc_one(uint8_t num);
bool ext_int_proc(void);


PinIntEdge_t gpio_logic_level_to_edge(const GpioLogicLevel_t logic_level);

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_MCAL_H  */
