#include "game_pad_ps2_config.h"

#include "data_utils.h"

const GamePadPs2Config_t GamePadPs2Config[] = {
    {
        .num = 1,
        .valid = true,
        .spi_num = 2,
        .ChipSelect = {.port=PORT_B, .pin=12,},
        .name = "GAME_PAD_PS21",
    },
};



GamePadPs2Handle_t GamePadPs2Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t game_pad_ps2_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(GamePadPs2Config);
    cnt2 = ARRAY_SIZE(GamePadPs2Instance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
