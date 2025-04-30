#ifndef BUTTON_DIAG_H
#define BUTTON_DIAG_H

//#include "button_const.h"
#include "button_types.h"

const char* ButtonState2Str(ButtonState_t state);
const char* ButtonPressType2Str(ButtonPressType_t press_type);
const char* ButtonInput2Str(ButtonInput_t input);
bool ButtonConfigDiag(const ButtonConfig_t* const Config);

#endif /* BUTTON_DIAG_H  */
