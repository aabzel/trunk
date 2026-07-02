#include "flash_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif /**/

#ifdef HAS_CRC32
#include "crc32.h"
#endif /**/
#include "data_utils.h"
#include "debug_info.h"
#include "flash_config.h"
#include "flash_custom_diag.h"
#include "flash_custom_types.h"
#include "flash_diag.h"
#include "flash_mcal.h"
#include "log.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"
#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif

#ifdef HAS_CRC32
#include "crc32.h"
#endif

bool flash_diag_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_parse_acr(FLASH->ACR);
        res = flash_parse_sr(FLASH->SR);
    }
    return res;
}
