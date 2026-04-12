#include "gpio_config.h"
/*
  Do not auto format that file with clang-format on GNU-indent!
 */
#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "microcontroller_const.h"

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

//#include "c_defines_generated.h"

const GpioConfig_t GpioConfig[] = {
};

uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
