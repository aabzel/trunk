#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include "std_includes.h"
#include "button_config.h"
#include "button_types.h"

#ifdef HAS_BUTTON_DIAG
#include "button_diag.h"
#endif

#ifdef HAS_FREE_RTOS
void button_thread(void* arg);
#endif /**/

/*API*/
ButtonHandle_t* ButtonGetNode(uint8_t num);
const ButtonConfig_t* ButtonGetConfig(uint8_t num);
bool button_mcal_init(void);
bool button_init_one(uint32_t num) ;

bool button_proc(void);

bool ButtonStateToOnOff( ButtonState_t state) ;
bool button_press(uint8_t num, ButtonPressType_t press_type);
ButtonState_t button_get(uint8_t num);

#endif /* BUTTON_DRIVER_H  */
