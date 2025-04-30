#ifndef FLASH_STM_CONST_H
#define FLASH_STM_CONST_H

#include "macro_utils.h"
//#include "sys_config.h"
//#include "flash_config.h"

#define QWORD_LEN 4

#ifndef HAS_STM32
#error "+HAS_STM32"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

/*Hardware related code start*/
//#define NOR_FLASH_SIZE ROM_SIZE
//#define NOR_FLASH_END (NOR_FLASH_BASE + NOR_FLASH_SIZE)
/*Hardware related code end*/

#define FLASH_WR_TIME_MS 20
#define MAX_SINGLE_WRITE_SIZE 256
//#define FLASH_SECTOR_SIZE (128UL*K_BYTES)

//#define FLASH_PAGE_CNT (NOR_FLASH_SIZE / FLASH_SECTOR_SIZE)


#endif /* FLASH_STM_CONST_H  */
