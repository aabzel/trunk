#include "gpio_config.h"

#include "macro_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "sys_config.h"

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

const GpioConfig_t GpioConfig[] = {

#ifdef HAS_LED
    {.pad={.port=0, .pin=3}, .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="VD1",
#endif
    },
    {.pad={.port=1, .pin=3},
            .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_OUTPUT, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="VD2",
#endif
    },
#endif/*HAS_LED*/

#ifdef HAS_BUTTON
    {.pad={.port=0, .pin=8}, .name="USER_B", .dir=GPIO_DIR_IN, .connector1="PA.0", .connector2="pin34", .mode=GPIO_API_MODE_INPUT_EXINT_RISING, .pull=GPIO__PULL_AIR, .mux=0, .logic_level=GPIO_LVL_LOW},
#endif

#ifdef HAS_UART0
    {.pad={.port = 0, .pin = 6}, .dir = GPIO_DIR_OUT, .mode = GPIO_API_MODE_ALT1, .pull = GPIO__PULL_AIR, .mux = 1, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
            .name = "UART0_TX", .connector1 = "51",
#endif
    },
    {.pad={.port = 0, .pin = 5}, .dir = GPIO_DIR_IN, .mode = GPIO_API_MODE_ALT1, .pull = GPIO__PULL_UP, .mux = 1, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
            .name = "UART0_RX", .connector1 = "53",
#endif
    },
#if 0
    {.pad={.port = 0, .pin = 8}, .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=1, .logic_level=GPIO_LVL_HI,
#ifdef HAS_LOG
            .name="UART0_nrts", .connector1="49",
#endif
    },
#endif /*comment*/
#endif /*HAS_UART0*/

#ifdef HAS_UART1
    {.pad={.port = 1, .pin = 9}, .dir = GPIO_DIR_OUT, .mode = GPIO_API_MODE_ALT1, .mux = 1, .pull = GPIO__PULL_AIR, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
            .name = "UART1_TX", .connector1 = "XP1.10",
#endif
    },
    {.pad={.port = 1, .pin = 8}, .dir = GPIO_DIR_IN, .mode = GPIO_API_MODE_ALT1, .mux = 1, .pull = GPIO__PULL_UP, .logic_level = GPIO_LVL_HI,
#ifdef HAS_LOG
            .name="UART1_RX", .connector1="XP1.11",
#endif
    },
#if 0
    {.pad={.port = 1, .pin = 11}, .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1, .mux=1, .pull=GPIO__PULL_UP, .logic_level=GPIO_LVL_HI},
#ifdef HAS_LOG
            .name="UART1_nrts", .connector1="UEXT.4",
#endif
#endif /**/
#endif /*HAS_USART1*/

#ifdef HAS_SPIFI
    {.pad={.port=2, .pin=0}, .drive_select = GPIO_DRIVE_SELECT_8MA, .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=1, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="SPIFI_SCLK", .connector1="38", .connector2="pin34",
#endif
    },
    {.pad={.port=2, .pin=1},  .drive_select = GPIO_DRIVE_SELECT_8MA, .dir=GPIO_DIR_OUT, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_AIR, .mux=1, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="SPIFI_CS", .connector1="37", .connector2="pin34",
#endif
    },
    {.pad={.port=2, .pin=2},  .drive_select=GPIO_DRIVE_SELECT_8MA,.dir=GPIO_DIR_INOUT, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=1, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="SPIFI_DATA_0", .connector1="36", .connector2="pin34",
#endif
    },
    {.pad={.port=2, .pin=3},  .drive_select=GPIO_DRIVE_SELECT_8MA,.dir=GPIO_DIR_INOUT, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=1, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="SPIFI_DATA_1 ", .connector1="35", .connector2="pin34",
#endif
    },
    {.pad={.port=2, .pin=4}, .drive_select=GPIO_DRIVE_SELECT_8MA, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=1, .logic_level=GPIO_LVL_LOW, .dir=GPIO_DIR_INOUT,
#ifdef HAS_LOG
            .name="SPIFI_DATA_2 ", .connector1="34", .connector2="pin34",
#endif
    },
    {.pad={.port=2, .pin=5},  .drive_select=GPIO_DRIVE_SELECT_8MA, .dir=GPIO_DIR_INOUT, .mode=GPIO_API_MODE_ALT1, .pull=GPIO__PULL_UP, .mux=1, .logic_level=GPIO_LVL_LOW,
#ifdef HAS_LOG
            .name="SPIFI_DATA_3 ", .connector1="33", .connector2="pin34",
#endif
    },
#endif /*HAS_SPIFI*/

};



uint32_t gpio_get_cnt(void) {
    return ARRAY_SIZE(GpioConfig);
}
