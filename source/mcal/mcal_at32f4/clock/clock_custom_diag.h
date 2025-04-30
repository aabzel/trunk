#ifndef CLOCK_CUSTOM_DIAG_H
#define CLOCK_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#include "microcontroller_types.h"
#include "clock_custom_types.h"
#include "clock_const.h"

bool clock_custom_diag(void);
bool print_conditional(char *key_word1,char *key_word2, char* bus, char* module, bool on_off);
bool periph_clock_diag(char *keyWord1,char *keyWord2);
const char* Bus2Str(ClockBus_t bus_code) ;
//const char *Bus2Str(uint8_t code);
const char *At32Clock2Str(crm_clocks_freq_type* Node);
const char *At32ClockSrc2Str(crm_sclk_type crm_sclk);
#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_DIAG_H
