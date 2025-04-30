#include "i2c_config.h"

#include "data_utils.h"

#ifdef HAS_MCAL_NRF5340
#include "nrf_gpio.h"
#endif

#ifdef NRFX_TWIM_ENABLED
#include "nrfx_config_standalone.h"
#endif /*NRFX_TWIM_ENABLED*/

/*constant compile-time known settings*/
const I2cConfig_t I2cConfigLuT[] = {
    { .num=1,
      .clock_speed=1000,
      .name = "I2C1",
      .valid=true,
      .PadScl.port=1,      .PadScl.pin=3,
      .PadSda.port=1,      .PadSda.pin=2,
    },
};


I2cHandle_t I2cInstance[]={
    {.num=1,
     .valid=true,
#ifdef HAS_NRFX_I2C
     .i2c_h={
                                 .p_twim=NRF_TWIM1,       ///< Pointer to a structure with TWIM registers.
                                 .drv_inst_idx=NRFX_TWIM1_INST_IDX, ///< Index of the driver instance. For internal use only.
                                  },
      .twim_config={
                    .scl=NRF_GPIO_PIN_MAP(1,3),
                    .sda=NRF_GPIO_PIN_MAP(1,2),
                    .frequency=NRF_TWIM_FREQ_100K,
                    .interrupt_priority=4,
                    .hold_bus_uninit=true,
      },
#endif /*HAS_NRFX_I2C*/
    },
};


uint32_t i2c_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(I2cConfigLuT);
    uint32_t cnt_ints = ARRAY_SIZE(I2cInstance);
    if(cnt_conf == cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

