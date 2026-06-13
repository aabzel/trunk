#include "laser_sight_config.h"

#include "pwm_config.h"
#include "data_utils.h"

//static uint8_t TxData[]="Laser transmitted Data.";
/*0xF0 - 0xaa,0x55 in Manchester code */
static uint8_t TxData[] = {0xaa,0x55};

const LaserSightConfig_t LaserSightConfig[] = {
    {
        .num = 1,
        .valid = true,
        .TxData = TxData,
        .tx_data_size = sizeof(TxData),
        .carrier_pwm_num = 1,
        .PadTxData = {.port = PORT_E, .pin = 6,},
        .PadTxClk = {.port = PORT_D, .pin = 4,},
        .bit_rate_frequency_hz = 250.0f,
        .carrier_frequency_hz = 250.0f,
        .name = "TxByLaser",
    },
};


LaserSightHandle_t LaserSightInstance[] = {
    {        .num = 1,        .valid = true,    },
};

COMPONENT_GET_CNT(LaserSight, laser_sight)

