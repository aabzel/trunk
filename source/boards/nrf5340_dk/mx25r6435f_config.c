#include "mx25r6435f_config.h"


#include "data_utils.h"
#include "mx25r6435f_types.h"

const Mx25r6435fConfig_t Mx25r6435fConfig = {
    .chip_select={.port=0, .pin=18,},
    .reset={.port=0, .pin=16,},
    .write_protection={.port=0, .pin=15,},
    .spi_num = 3,
};

Mx25r6435fItem_t Mx25r6435fItem={
	    .status.byte=0,
	    .electronic_signature=0,
};

uint32_t mx25r6435f_get_config_cnt(void) {
    uint8_t cnt = 1;
    return cnt;
}
