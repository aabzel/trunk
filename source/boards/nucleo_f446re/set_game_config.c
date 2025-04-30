#include "set_game_config.h"

#include "data_utils.h"

const SetGameConfig_t SetGameConfig[] = {
    {
    .num = 1,
    .scanner_num = 1,
    .ssd1306_num = 1,
    .valid = true,
    },
};

SetGameHandle_t SetGameInstance[]={
    {.num=1, .valid=true, },
};

uint32_t set_game_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SetGameInstance);
    cnt2 = ARRAY_SIZE(SetGameConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
