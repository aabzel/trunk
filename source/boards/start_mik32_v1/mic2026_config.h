#ifndef MIC2026_CONFIG_H
#define MIC2026_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "mic2026_types.h"

#ifndef HAS_MIC2026
#error "Add HAS_MIC2026"
#endif /*HAS_MIC2026*/

extern const Mic2026Config_t Mic2026Config;
extern Mic2026Handle_t Mic2026Item;

#endif /* MIC2026_CONFIG_H  */
