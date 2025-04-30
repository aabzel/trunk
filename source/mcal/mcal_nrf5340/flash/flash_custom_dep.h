#ifndef FLASH_CUSTOM_DEP_H
#define FLASH_CUSTOM_DEP_H

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

#ifndef HAS_NRFX
#warning "+HAS_NRFX"
#endif

#ifndef NRFX_NVMC_ENABLED
#warning "+NRFX_NVMC_ENABLED"
#endif

#ifndef HAS_STORAGE
#error "+HAS_STORAGE"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#endif /* FLASH_CUSTOM_DEP_H  */
