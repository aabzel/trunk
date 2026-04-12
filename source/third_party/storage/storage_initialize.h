#ifndef STORAGE_INITIALIZE_H
#define STORAGE_INITIALIZE_H

#include "std_includes.h"


#ifdef HAS_EEPROM_EMULATION

#include "eeprom_emulation.h"

bool eeprom_emulation_init(void);

#define EEPROM_EMULATION_INITIALIZE {.init_function = eeprom_emulation_init, .name="EepromEmulation",},
#else /*HAS_EEPROM_EMULATION*/
#define EEPROM_EMULATION_INITIALIZE
#endif /*HAS_EEPROM_EMULATION*/


#ifdef HAS_MEMORY_MANAGER

#include "memory_manager.h"

bool memory_manager_init(void);

#define MEMORY_MANAGER_INITIALIZE {.init_function = memory_manager_init, .name="MemMan",},
#else /*HAS_MEMORY_MANAGER*/
#define MEMORY_MANAGER_INITIALIZE
#endif /*HAS_MEMORY_MANAGER*/



#ifdef HAS_NVRAM

#include "nvram_drv.h"

bool nvram_ehal_init(void);

#define NVRAM_INITIALIZE {.init_function = nvram_ehal_init, .name="NVRAM",},
#else /* */
#define NVRAM_INITIALIZE
#endif /* */



#define STORAGE_INITIALIZE                \
    EEPROM_EMULATION_INITIALIZE           \
    MEMORY_MANAGER_INITIALIZE           \
    NVRAM_INITIALIZE

#endif /* STORAGE_INITIALIZE_H */
