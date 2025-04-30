#ifndef BOOTLOADER_DEP_H
#define BOOTLOADER_DEP_H

#ifndef HAS_CLI
#warning "+HAS_CLI"
#endif

#ifndef HAS_LED
#warning "+HAS_LED"
#endif

#ifndef HAS_LOG
#warning "+HAS_LOG"
#endif

#ifndef HAS_FLASH
#warning "+HAS_FLASH"
#endif

#ifndef HAS_FLASH_FS
#warning "+HAS_FLASH_FS"
#endif

#ifndef HAS_PARAM
#warning "+HAS_PARAM"
#endif

#endif /* BOOTLOADER_DEP_H */
