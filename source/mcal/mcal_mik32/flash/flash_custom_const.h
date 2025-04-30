#ifndef FLASH_MIK_CONST_H
#define FLASH_MIK_CONST_H

//#include "macro_utils.h"

#define QWORD_LEN 4

#ifndef HAS_MIK32
#error "+HAS_MIK32"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#define FLASH_WR_TIME_MS 20
#define MAX_SINGLE_WRITE_SIZE 256

#endif /* FLASH_MIK_CONST_H  */
