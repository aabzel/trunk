#include "dwm3000_config.h"

#include "data_utils.h"
#include "gpio_types.h"
#include "common_const.h"
#include "dwm3000_const.h"

const Dwm3000Config_t Dwm3000Config = {
    .num = DWM3000_MAIN,
    .spi_num = DWM3000_SPI_NUM,
    .chip_select={.port=1, .pin=12,},
    .irq={.port=1, .pin=10,},
    .gpio5={.port=1, .pin=1,},
    .gpio6={.port=1, .pin=0,},
    .reset={.port=1, .pin=9,},
    .wakeup={.port=1, .pin=11,},
	.bit_rate=TX_BIT_RATE_850_K_BIT_PER_S,
    .preamble_length = 128,
	.rf_channel = RF_CHAN_5,
	.preamble_code = 10,
	.sfd_type = SFD_TYPE_0,
    .valid = true,

};

Dwm3000Handle_t Dwm3000Instance={
    .num=DWM3000_MAIN, .valid = true, .irq_active_level=GPIO_LVL_LOW,
};


