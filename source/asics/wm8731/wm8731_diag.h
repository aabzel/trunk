
#ifndef WM8731_DIAG_H
#define WM8731_DIAG_H

#include <stdint.h>

#include "wm8731_types.h"

const char* Wm8731I2sBusRole2Str(uint8_t bus_role);
const char* Wm8731ConfigToStr(const Wm8731Config_t* const Config) ;
const char* Wm8731NodeToStr(const Wm8731Handle_t* const Config) ;

#endif /* WM8731_DIAG_H */
