#include "dwm1000_config.h"

#include "data_utils.h"
#include "gpio_types.h"
#include "common_const.h"

#include "deca_device_api.h"
#include "deca_regs.h"

const Dwm1000Config_t Dwm1000Config={
	.num = DWM1000_MAIN,
	.spi_num = DWM1000_SPI_NUM,
	.chip_select={.port=1, .pin=12,},
	.irq={.port=1, .pin=10,},
	.reset={.port=1, .pin=9,},
	.wakeup={.port=1, .pin=11,},
	.slow_speed_hz = 2000000,
	.fast_speed_hz = 16000000,
	.valid = true,

	.dwm1000_cfg = {
		.chan = 5,               			/* Channel number. */
		.prf = DWT_PRF_64M,     			/* Pulse repetition frequency. */
		.txPreambLength = DWT_PLEN_128,    	/* Preamble length. Used in TX only. */
		.rxPAC = DWT_PAC8,        			/* Preamble acquisition chunk size. Used in RX only. */
		.txCode = 9,               			/* TX preamble code. Used in TX only. */
		.rxCode = 9,               			/* RX preamble code. Used in RX only. */
		.nsSFD = 0,               			/* 0 to use standard SFD, 1 to use non-standard SFD. */
		.dataRate = DWT_BR_6M8,      		/* Data rate. */
		.phrMode = DWT_PHRMODE_EXT, //DWT_PHRMODE_STD,	// /* PHY header mode. */
		.sfdTO = (128 + 1 + 8 - 8)    		/* SFD timeout (preamble length + 1 + SFD length - PAC size). Used in RX only. */
    }
};

Dwm1000Handle_t Dwm1000Instance={
    .num=  DWM1000_MAIN,
	.valid = true,

};

/* Default communication configuration. We use here EVK1000's mode 4. See NOTE 1 below. */


