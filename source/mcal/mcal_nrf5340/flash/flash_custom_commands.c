#include "flash_custom_commands.h"

#include "convert.h"
#include "flash_mcal.h"
#include "log.h"

bool flash_custom_diag_cmd(int32_t argc, char* argv[]) {
    bool res = false;
    FlashDiagNode(&FlashInstance);
    res= flash_diag_usage(ON_CHIP_NOR_FLASH_PAGE_SIZE);
    if(res) {
        LOG_INFO(LG_FLASH, "FlashDiagOk");
    }else{
        LOG_ERROR(LG_FLASH, "FlashDiagErr");
    }
    return res;
}
