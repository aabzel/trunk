#include "dma_channel_custom_commands.h"

#include "dma_mcal.h"
#include "dma_channel_custom_diag.h"
#include "log.h"
#include "sys_config.h"


bool dma_channel_diag_custom_command(int32_t argc, char* argv[]){
    bool res = false;
    res = dma_channel_diag_custom();
    return res;
}

bool dma_channel_diag_ll_command(int32_t argc, char* argv[]){
    bool res = dma_channel_diag_low_level("","");
    return res;
}
