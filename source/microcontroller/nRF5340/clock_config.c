#include "clock_config.h"

//#include "clock_types.h"
//#include "data_utils.h"

ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .hf_source = CLK_HI_FREQ_32MHZ,  //  CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .valid = true,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};
