#include "ad9833_config.h"

#include "clock_utils.h"
#include "data_utils.h"

const Ad9833Config_t Ad9833Config[] = {
    {
        .num = 1,
        .spi_num = 4,
        .RegDefault.word = 0,
        .valid = true,
        .signal_form = SIGNAL_FORM_SINUSOIDAL,
        .freq_hz = 11000000.0,
        .phase = 0.0,
        .chip_select =
            {
                .port = 1,
                .pin = 8,
            },
    },
};

Ad9833Handle_t Ad9833Instance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t ad9833_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(Ad9833Instance);
    cnt2 = ARRAY_SIZE(Ad9833Config);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
