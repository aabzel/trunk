#include "decadriver_config.h"

#include "deca_device_api.h"

const DecaDriverConfig_t DecaDriverConfig = {
    .spi_num = 3,
    .valid = true,
    .init_arg = DWT_LOADUCODE,
    .log_level = LOG_LEVEL_NOTICE,
    .rx_delay_us = 0,
    .preamble_detect_timeout_pac = 0, /*A value of 0 disables the timer and timeout*/
    .rx_timeout_us = 0,               /*If this is 0, the timeout will be disabled.*/
    .chip_select =
        {
            .port = 1,
            .pin = 12,
        },
    .irq =
        {
            .port = 1,
            .pin = 10,
        },
    .reset =
        {
            .port = 1,
            .pin = 9,
        },
    .wakeup =
        {
            .port = 1,
            .pin = 11,
        },
    .config =
        {
            .chan = 2,                       /* Channel number. */
            .prf = DWT_PRF_64M,              /* Pulse repetition frequency. */
            .txPreambLength = DWT_PLEN_1024, /* Preamble length. Used in TX only. */
            .rxPAC = DWT_PAC32,              /* Preamble acquisition chunk size. Used in RX only. */
            .txCode = 9,                     /* TX preamble code. Used in TX only. */
            .rxCode = 9,                     /* RX preamble code. Used in RX only. */
            .nsSFD = 1,                      /* 0 to use standard SFD, 1 to use non-standard SFD. */
            .dataRate = DWT_BR_110K,         /* Data rate. */
            .phrMode = DWT_PHRMODE_STD,      /* PHY header mode. */
            //.sfdTO = (1025 + 64 - 32) /* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only.
            //*/
            .sfdTO = 0, /* If a 0 value is selected the default value of 4161 symbols (DWT_SFDTOC_DEF) will be used */
        },
};

DecaDriverInstance_t DecaDriverInstance = {
    .valid = true,
};
