#include "clock_config.h"

#include <stddef.h>

#include "clock_mcal.h"
#include "board_config.h"

ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .core_clock_mhz = MHZ_2_HZ(210),
    .pll0 = MHZ_2_HZ(210),
    .pll1 = MHZ_2_HZ(200),
    .hf_source = XTALL_FREQ_HZ,      // CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .core_source = CLOCK_CORE_SRC_PLL0,
    .valid = true,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};




