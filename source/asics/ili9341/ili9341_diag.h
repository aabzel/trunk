#ifndef ILI9341_DIAG_H
#define ILI9341_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ili9341_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_ILI9341
#error "+HAS_ILI9341"
#endif

#ifndef HAS_ILI9341_DIAG
#error "+HAS_ILI9341_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif


bool ili9341_diag(void);
bool ili9341_diag_one(uint8_t num);
bool ili9341_raw_reg_diag(uint8_t num);
const char* Ili9341IdToStr( const Ili9341Id_t * const pID);
const char* Ili9341ConfigToStr(const Ili9341Config_t* const Config);
const char* Ili9341NodeToStr(const Ili9341Handle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* ILI9341_DIAG_H  */
