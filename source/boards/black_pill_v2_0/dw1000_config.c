#include "dw1000_config.h"

const Dw1000Config_t Dw1000Config = {
    .spi_num = 1,
    .chip_select =
        {
            .port = PORT_A,
            .pin = 2,
        },
    .irq =
        {
            .port = PORT_A,
            .pin = 1,
        },
    .reset =
        {
            .port = PORT_A,
            .pin = 4,
        },
    .wakeup =
        {
            .port =PORT_A,
            .pin = 3,
        },
    .valid = true,
    .rx_ant_delay_tim = 0,
    .ant_delay_tim = 0,
    .ant_delay_m =
        {
            .min = 147.5058,
            .cur = 151.8968081,
            .max = 154.019,
        },
    .channel = CHANNEL_5,
    .fcs = true,
    .irq_active_level_dflt = GPIO_LVL_HI,
    .bit_rate_bit_p_sec = 110000,
    .preamble_length = 128,
    .sdf_timeout_symbols = 32000,
    .sfd_conf = SFD_CFG_STANDARD,
    .pulse_rep_rate = PULSE_REP_RATE_REP_16MHZ,
};

Dw1000Handle_t Dw1000Instance = {
    .valid = true,
};
