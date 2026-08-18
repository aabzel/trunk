#include "rs2058_drv.h"

#include <string.h>

#include "gpio_mcal.h"
#include "log.h"

#ifdef HAS_RS2058_DIAG
#include "rs2058_diag.h"
#endif

Rs2058Item_t* Rs2058GetNode(uint8_t num) {
    Rs2058Item_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = rs2058_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == Rs2058Item[i].num) {
            if(Rs2058Item[i].valid) {
                Node = &Rs2058Item[i];
                break;
            }
        }
    }
    return Node;
}

const Rs2058Config_t* Rs2058GetConfig(uint8_t num) {
    const Rs2058Config_t* Config = NULL;
    uint32_t i = 0;
    uint32_t cnt = rs2058_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == Rs2058Config[i].num) {
            if(Rs2058Config[i].valid) {
                Config = &Rs2058Config[i];
                break;
            }
        }
    }
    return Config;
}

bool rs2058_proc(void) {
    bool res = true;
    LOG_DEBUG(RS2058, "Proc");
    return res;
}

/*see FUNCTION TABLE in spec*/
static GpioLogicLevel_t Rs2058State2LogLev(Rs2058State_t state) {
    GpioLogicLevel_t logic_lev = GPIO_LVL_UNDEF;
    switch((uint8_t)state) {
    case RS2058_SW_COM_NO:
        logic_lev = GPIO_LVL_HI;
        break;
    case RS2058_SW_COM_NC:
        logic_lev = GPIO_LVL_LOW;
        break;
    default:
        logic_lev = GPIO_LVL_UNDEF;
        break;
    }
    return logic_lev;
}

Rs2058State_t Rs20582LogLev2State(GpioLogicLevel_t logic_lev) {
    Rs2058State_t state = RS2058_SW_UNDEF;
    switch((uint8_t)logic_lev) {
    case GPIO_LVL_HI:
        state = RS2058_SW_COM_NO;
        break;
    case GPIO_LVL_LOW:
        state = RS2058_SW_COM_NC;
        break;
    default:
        state = GPIO_LVL_UNDEF;
        break;
    }
    return state;
}

bool rs2058_set(const Rs2058Sw_t* const Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_RS2058_DIAG
        LOG_WARNING(RS2058, "%u Set %s", Node->num, Rs2058SwStateToStr(Node->state));
#endif
        if(Node) {
            GpioLogicLevel_t logic_level = Rs2058State2LogLev(Node->state);
            res = gpio_set_logic_level(Node->in.byte, logic_level);
        }
    }
    return res;
}

bool rs2058_ctrl(uint8_t chip_num, uint8_t mux_num, uint8_t state) {
    bool res = false;
    LOG_WARNING(RS2058, "Ctrl");
    Rs2058Item_t* Node = Rs2058GetNode(chip_num);
    if(Node) {
        if(mux_num < 2) {
            res = gpio_set_logic_level(Node->sw[mux_num].in.byte, state);
        }
    }
    return res;
}

bool rs2058_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(RS2058, "Init");
    const Rs2058Config_t* Config = Rs2058GetConfig(num);
    if(Config) {
        Rs2058Item_t* Node = Rs2058GetNode(num);
        if(Node) {
            memcpy(&Node->sw[0], &Config->sw[0], 2 * sizeof(Rs2058Sw_t));
            res = rs2058_set(&Config->sw[0]);
            res = rs2058_set(&Config->sw[1]) && res;
        }
    }
    set_log_level(RS2058, LOG_LEVEL_INFO);
    return res;
}

bool rs2058_init(void) {
    bool res = true;
    LOG_WARNING(RS2058, "Init..");
    uint8_t num = 0;
    uint32_t ok = 0;
    uint32_t cnt = rs2058_get_cnt();
    for(num = 0; num <= cnt; num++) {
        res = rs2058_init_one(num);
        if(res) {
            LOG_INFO(RS2058, "RS2058%u InitOk", num);
            ok++;
        } else {
            LOG_DEBUG(RS2058, "RS2058%u InitErr", num);
        }
    }

    if(ok) {
        res = true;
        LOG_INFO(RS2058, "Init %u RS2058s", ok);
    } else {
        res = false;
    }
    return res;
}
