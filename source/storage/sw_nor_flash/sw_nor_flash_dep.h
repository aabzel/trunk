#ifndef SW_NOR_FLASH_DEP_H
#define SW_NOR_FLASH_DEP_H

#ifndef HAS_PC
#error "SW_NOR_FLASH Needs HAS_PC"
#endif

#ifndef HAS_STORAGE
#error "SW_NOR_FLASH Needs HAS_STORAGE"
#endif

#ifndef HAS_SW_NOR_FLASH
#error "+HAS_SW_NOR_FLASH"
#endif

#ifndef HAS_NOR_FLASH
#error "+HAS_NOR_FLASH"
#endif

#endif /* SW_NOR_FLASH_DEP_H */
