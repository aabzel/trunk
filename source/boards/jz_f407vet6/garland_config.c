#include "garland_config.h"

#include "data_utils.h"
#include "pwm_config.h"

#define GARLAND_AMP 20.0

const GarLandConfig_t SECTION_CFG_DATA GarLandConfig[] = {
    { .num = 1, .valid = true, .name = "RX1", .pwm_num = PWM_NUM_RX1_LED, .pwm_frequency_hz = 500.0,
      .signal_amplitude = GARLAND_AMP, .signal_offset = GARLAND_AMP, .signal_phase_ms = 0, .signal_frequency = 1.0,    },

    { .num = 2, .valid = true, .name = "TX1", .pwm_num = PWM_NUM_TX1_LED, .pwm_frequency_hz = 500.0,
      .signal_amplitude = GARLAND_AMP, .signal_offset = GARLAND_AMP, .signal_phase_ms = 2500, .signal_frequency = 0.5,    },

    { .num = 3, .valid = true, .name = "RX2", .pwm_num = PWM_NUM_RX2_LED, .pwm_frequency_hz = 500.0,
      .signal_amplitude = GARLAND_AMP, .signal_offset = GARLAND_AMP, .signal_phase_ms = 5000, .signal_frequency = 1.0/3.0,    },

    { .num = 4, .valid = true, .name = "TX2", .pwm_num = PWM_NUM_TX2_LED, .pwm_frequency_hz = 500.0,
      .signal_amplitude = GARLAND_AMP, .signal_offset = GARLAND_AMP, .signal_phase_ms = 0, .signal_frequency = 1.0/4.0,    },

    { .num = 5, .valid = true, .name = "STATUS_LED", .pwm_num = PWM_NUM_STATUS_LED, .pwm_frequency_hz = 500.0,
        .signal_amplitude = GARLAND_AMP, .signal_offset = GARLAND_AMP, .signal_phase_ms = 0, .signal_frequency = 2,    },

};




GarLandHandle_t GarLandInstance[] = {
    { .num = 1, .valid = true,    },
    { .num = 2, .valid = true,    },
    { .num = 3, .valid = true,    },
    { .num = 4, .valid = true,    },
    { .num = 5, .valid = true,    },
};


COMPONENT_GET_CNT(GarLand, garland)


