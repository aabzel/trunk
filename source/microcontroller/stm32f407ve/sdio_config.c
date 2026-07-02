#include "sdio_config.h"

#include "clock_utils.h"
#include "data_utils.h"
#include "log_config.h"
#include "mcal_const.h"

/*48MHz - err*/
/*30MHz - err*/
/*28MHz - */
/*24MHz - OK*/
/*20MHz - Err*/
/*10MHz - Err*/
/*5MHz  - Err*/

/*constant compile-time known settings in Flash*/
const SdioConfig_t SECTION_CFG_DATA SdioConfig[] = {
    {
        .num = 1,
        .move_mode = MOVE_MODE_INTERRUPT,
        .interrupt_on = true,
        .bit_rate_hz =  MHZ_2_HZ(1),
        .name = "SdCard",
        .valid = true,
    },
};

SdioHandle_t SdioInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Sdio, sdio)

