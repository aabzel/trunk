#include "kalah_config.h"

#include "data_utils.h"

const KalahConfig_t KalahConfig[] = {
    {
    .num = 1,
    .valid = true,
    .first_turn = PLAYER_A,
    .init_val= 1,
    },
};





KalahHandle_t KalahInstance[]={
    {.num=1, .valid=true, },
};

uint32_t kalah_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(KalahInstance);
    cnt2 = ARRAY_SIZE(KalahConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
