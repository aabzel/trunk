#include "nrf_core_commands.h"

#include "log.h"
#include "convert.h"
#include "nrf_core_types.h"
#include "nrf_core_diag.h"
#include "nrf_core_drv.h"

bool nrf_core_net_set_command(int32_t argc, char* argv[]) {
    bool res = false;
 
    bool status = false;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &status);
        if(false == res) {
            LOG_ERROR(GPIO, "ParseErr status %s", argv[0]);
        }
    }
    
    if(res) {
        res = nrf_core_network_set_state(status);
        if(false == res) {
            LOG_ERROR(GPIO, "SetErr");
        } else {
            LOG_INFO(GPIO, "SetState %s", OnOff2Str(status));
        }
    } {
        LOG_ERROR(GPIO, "Usage: cns status");
        res = false;
    }
    return res;
}
