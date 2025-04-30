#include "board_config.h"

#include "board_types.h"
#include "data_utils.h"
#include "log.h"

bool board_init(void) {
    bool res = true;
    LOG_INFO(SYS,"BoardInit");
    set_log_level(SYS,LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall: %u Hz",XTAL_FREQ_HZ);
#ifdef HAS_USB
    set_log_level(USB,LOG_LEVEL_ERROR);
    set_log_level(USB_HOST,LOG_LEVEL_ERROR);
    set_log_level(HID,LOG_LEVEL_ERROR);
#endif /*HAS_USB*/
    return res;
}

const Wire_t Wires[]= {
        {.pad={.port=PORT_D, .pin=2}, .wire_name="NC", },
        {.pad={.port=PORT_H, .pin=0}, .wire_name="OSC_IN", },
        {.pad={.port=PORT_H, .pin=1}, .wire_name="OSC_OUT", },

        {.pad={.port=PORT_C, .pin=0}, .conn={.designator="HD", .num=1, .pin=6,},},
        {.pad={.port=PORT_C, .pin=1}, .conn={.designator="HD", .num=1, .pin=8,},},
        {.pad={.port=PORT_C, .pin=2}, .conn={.designator="HD", .num=1, .pin=9,},},
        {.pad={.port=PORT_C, .pin=3}, .wire_name="NC", },
        {.pad={.port=PORT_C, .pin=4}, .conn={.designator="HD", .num=2, .pin=34,}, },
        {.pad={.port=PORT_C, .pin=5}, .conn={.designator="HD", .num=2, .pin=33,}, },
        {.pad={.port=PORT_C, .pin=6}, .wire_name="NC", },
        {.pad={.port=PORT_C, .pin=7}, .wire_name="NC", },
        {.pad={.port=PORT_C, .pin=8}, .wire_name="NC", },
        {.pad={.port=PORT_C, .pin=9}, .conn={.designator="HD", .num=1, .pin=15,},},
        {.pad={.port=PORT_C, .pin=10}, .conn={.designator="HD", .num=2, .pin=21,}, },
        {.pad={.port=PORT_C, .pin=11}, .conn={.designator="HD", .num=2, .pin=22,}, },
        {.pad={.port=PORT_C, .pin=12}, .wire_name="LD1Yellow", },
        {.pad={.port=PORT_C, .pin=13}, .wire_name="LD2Red", },
        {.pad={.port=PORT_C, .pin=14}, .wire_name="OSC32_IN", },
        {.pad={.port=PORT_C, .pin=15}, .wire_name="OSC32_OUT", },

        {.pad={.port=PORT_A, .pin=0}, .conn={.designator="HD", .num=1, .pin=2,}, },
        {.pad={.port=PORT_A, .pin=1}, .conn={.designator="HD", .num=1, .pin=3,}, },
        {.pad={.port=PORT_A, .pin=2}, .conn={.designator="HD", .num=1, .pin=4,}, },
        {.pad={.port=PORT_A, .pin=3}, .conn={.designator="HD", .num=1, .pin=5,}, },
        {.pad={.port=PORT_A, .pin=4}, .conn={.designator="HD", .num=2, .pin=37,}, },
        {.pad={.port=PORT_A, .pin=5}, .conn={.designator="HD", .num=2, .pin=38,}, },
        {.pad={.port=PORT_A, .pin=6}, .conn={.designator="HD", .num=2, .pin=40,}, },
        {.pad={.port=PORT_A, .pin=7}, .conn={.designator="HD", .num=2, .pin=39,}, },
        {.pad={.port=PORT_A, .pin=8}, .conn={.designator="HD", .num=1, .pin=10,}, },
        {.pad={.port=PORT_A, .pin=9}, .wire_name="USB-DET",.conn={.designator="CN", .num=1, .pin=1,}, },
        {.pad={.port=PORT_A, .pin=10}, .wire_name="USB-ID", .conn={.designator="CN", .num=1, .pin=4,}, },
        {.pad={.port=PORT_A, .pin=11}, .wire_name="USB-D_N",.conn={.designator="CN", .num=1, .pin=2,}, },
        {.pad={.port=PORT_A, .pin=12}, .wire_name="USB-D_P",.conn={.designator="CN", .num=1, .pin=3,}, },
        {.pad={.port=PORT_A, .pin=13}, .conn={.designator="HD", .num=2, .pin=35,}, },
        {.pad={.port=PORT_A, .pin=14}, .conn={.designator="HD", .num=2, .pin=36,}, },
        {.pad={.port=PORT_A, .pin=15}, .conn={.designator="HD", .num=2, .pin=30,}, },

        {.pad={.port=PORT_B, .pin=0}, .conn={.designator="HD", .num=1, .pin=19,}, },
        {.pad={.port=PORT_B, .pin=1}, .conn={.designator="HD", .num=1, .pin=20,}, },
        {.pad={.port=PORT_B, .pin=2}, .wire_name="NC", },
        {.pad={.port=PORT_B, .pin=3}, .conn={.designator="HD", .num=2, .pin=29,},  },
        {.pad={.port=PORT_B, .pin=4}, .conn={.designator="HD", .num=1, .pin=16,}, },
        {.pad={.port=PORT_B, .pin=5}, .conn={.designator="HD", .num=1, .pin=17,}, },
        {.pad={.port=PORT_B, .pin=6}, .conn={.designator="HD", .num=2, .pin=25,}, },
        {.pad={.port=PORT_B, .pin=7}, .conn={.designator="HD", .num=2, .pin=26,}, },
        {.pad={.port=PORT_B, .pin=8}, .conn={.designator="HD", .num=1, .pin=14,}, },
        {.pad={.port=PORT_B, .pin=9}, .conn={.designator="HD", .num=1, .pin=13,}, },
        {.pad={.port=PORT_B, .pin=10}, .conn={.designator="HD", .num=2, .pin=28,},  },
        {.pad={.port=PORT_B, .pin=11}, .conn={.designator="HD", .num=2, .pin=27,}, },
        {.pad={.port=PORT_B, .pin=12}, .conn={.designator="HD", .num=1, .pin=7,}, },
        {.pad={.port=PORT_B, .pin=13}, .conn={.designator="HD", .num=1, .pin=18,}, },
        {.pad={.port=PORT_B, .pin=14}, .conn={.designator="HD", .num=2, .pin=23,}, },
        {.pad={.port=PORT_B, .pin=15}, .conn={.designator="HD", .num=2, .pin=24,},  },
};

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);

    return cnt;
}

