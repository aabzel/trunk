#include "flash_custom_commands.h"

//#include <inttypes.h>

#include <zephyr/drivers/flash.h>

#include "convert.h"
//#include "data_utils.h"
#include "log.h"
//#include "ostream.h"
//#include "table_utils.h"
#include "flash_drv.h"
//#include "flash_types.h"
//#include "writer_config.h"
//#include "string_reader.h"


bool flash_custom_diag_commands(int32_t argc, char* argv[]){
    bool res = false;
    res = flash_custom_diag();

    return res;
}
