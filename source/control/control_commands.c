#include "action_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "table_utils.h"
#include "str_utils.h"

#ifdef HAS_I2S
#include "i2s_drv.h"
#endif /*HAS_I2S*/

#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif
#include "writer_config.h"

#if defined(HAS_WM8731) && defined(HAS_I2S)
bool cmd_action_bt1024_wm8731_fwd(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t words_num = 0;
    uint8_t i2s_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2s_num);
        if(false == res) {
#ifdef I2S_COUNT
            LOG_ERROR(I2S, "ParseErr I2sNum [1-%u]", I2S_COUNT);
#endif
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &words_num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr Words");
        }
    }

    if(res) {
        res= i2s_loopback(i2s_num, words_num);
        if(res) {
            LOG_INFO(I2S, "LoopBackOk");
            res = wm8731_set_volume(7, 7);
        }else {
            LOG_ERROR(I2S, "LoopBackErr");
        }
    }else{
        LOG_ERROR(I2S, "bwf I2sNum Words");
    }

    return res;
}
#endif /*HAS_WM8731 and HAS_I2S*/
