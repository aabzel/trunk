#ifndef PIN_MCAL_API_H
#define PIN_MCAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "pin_config.h"
#include "pin_types.h"
#ifdef HAS_PIN_DIAG
#include "pin_diag.h"
#endif


#ifdef HAS_PIN_CUSTOM
#include "pin_custom_drv.h"
#endif

/*API*/
#ifdef HAS_PIN_CUSTOM
const PinInfo_t* PinGetInfo(Port_t port);
#endif
bool pin_clock_init(void);
bool pin_init_custom(void);
bool pin_mcal_init(void); //pin_init-busy name
bool pin_init_one(const PinConfig_t* const Config);
bool pin_proc(void);
bool pin_proc_one(const PinConfig_t* const Config);
bool pin_deinit_one(Pad_t Pad);

/*Set*/


/*Get*/
uint8_t get_mcu_pin(uint8_t pad);
bool mcu_get_prev_pin(PinData_t cur_pin, PinData_t* const prev_pin);
bool mcu_get_next_pin(PinData_t cur_pin, PinData_t* const next_pin);
bool mcu_get_up_pin(PinData_t cur_pin, PinData_t* const up_pin);
bool mcu_get_down_pin(PinData_t cur_pin, PinData_t* const down_pin);
bool mcu_get_right_pin(PinData_t cur_pin, PinData_t* const right_pin);
bool mcu_get_left_pin(PinData_t cur_pin, PinData_t* const left_pin);





#ifdef __cplusplus
}
#endif

#endif /* PIN_MCAL_API_H  */
