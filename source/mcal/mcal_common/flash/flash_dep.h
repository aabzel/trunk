#ifndef FLASH_DEP_H
#define FLASH_DEP_H


#ifndef HAS_ARRAY
#warning "+ HAS_ARRAY"
#endif

#ifndef HAS_CRC16
#warning "+ HAS_CRC16"
#endif

#ifndef HAS_STORAGE
#warning "+ HAS_STORAGE"
#endif

#ifndef HAS_FLASH
#error "+ HAS_FLASH"
#endif

#ifndef HAS_TIME
#warning "+ HAS_TIME"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+ HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#endif /* FLASH_DEP_H */
