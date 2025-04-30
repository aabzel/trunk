#include "flash_config.h"

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#include "data_utils.h"

/* Memory map for STM32F407 */
/* mm_page 1        - 128k : [40000 ... 60000)  - sectors 6 */
/* mm_page 2        - 128k : [60000 ... 80000)  - sectors 7 */

const FlashConfig_t FlashConfig = {
    .boot_start= 0x08000000, 
    .app_start = 0x08020000,
    .file_sys_start = 0x08040000, 
    .file_sys_size =  2*128*1024,
    };




