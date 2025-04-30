#include "cross_detect_drv.h"

#include <stdint.h>
#include <string.h>

#include "cross_detect_diag.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "gpio_drv.h"
#include "log.h"
#include "time_mcal.h"

uint64_t cross_detect_period_us = MSEC_2_USEC(20);

static bool CrossDetectIsLeftHi(CrossDetectGpioRead_t read) {
    bool res = false;
    switch((uint8_t)read) {
    case READ_L1_R0:
        res = true;
        break;
    case READ_L1_R1:
        res = true;
        break;
    case READ_L0_R0:
        res = false;
        break;
    case READ_L0_R1:
        res = false;
        break;
    }
    return res;
}

static bool CrossDetectIsRightHi(CrossDetectGpioRead_t read) {
    bool res = false;
    switch((uint8_t)read) {
    case READ_L0_R1:
        res = true;
        break;
    case READ_L1_R1:
        res = true;
        break;
    case READ_L0_R0:
        res = false;
        break;
    case READ_L1_R0:
        res = false;
        break;
    }
    return res;
}

static bool CrossDetectIsRightLow(CrossDetectGpioRead_t read) {
    bool res = false;
    switch((uint8_t)read) {
    case READ_L0_R0:
        res = true;
        break;
    case READ_L1_R0:
        res = true;
        break;
    case READ_L0_R1:
        res = false;
        break;
    case READ_L1_R1:
        res = false;
        break;
    }
    return res;
}

static bool CrossDetectIsLeftLow(CrossDetectGpioRead_t read) {
    bool res = false;
    switch((uint8_t)read) {
    case READ_L0_R0:
        res = true;
        break;
    case READ_L0_R1:
        res = true;
        break;
    case READ_L1_R0:
        res = false;
        break;
    case READ_L1_R1:
        res = false;
        break;
    }
    return res;
}

static bool cross_detect_is_left_gnd(CrossDetectPairInfo_t* pair) {
    bool res = false;
    res = CrossDetectIsLeftLow(pair->measurements[CROSS_DETECT_STATE_LU_RA].read);
    if(res) {
        res = CrossDetectIsLeftLow(pair->measurements[CROSS_DETECT_STATE_LU_RU].read);
        if(res) {
            res = CrossDetectIsLeftLow(pair->measurements[CROSS_DETECT_STATE_LU_RD].read);
        }
    }

    return res;
}

static bool cross_detect_is_left_vcc(CrossDetectPairInfo_t* pair) {
    bool res = false;
    res = CrossDetectIsLeftHi(pair->measurements[CROSS_DETECT_STATE_LD_RA].read);
    if(res) {
        res = CrossDetectIsLeftHi(pair->measurements[CROSS_DETECT_STATE_LD_RD].read);
        if(res) {
            res = CrossDetectIsLeftHi(pair->measurements[CROSS_DETECT_STATE_LD_RU].read);
        }
    }

    return res;
}

static bool cross_detect_is_right_gnd(CrossDetectPairInfo_t* pair) {
    bool res = false;

    res = CrossDetectIsRightLow(pair->measurements[CROSS_DETECT_STATE_LD_RU].read);
    if(res) {
        res = CrossDetectIsRightLow(pair->measurements[CROSS_DETECT_STATE_LA_RU].read);
        if(res) {
            res = CrossDetectIsRightLow(pair->measurements[CROSS_DETECT_STATE_LU_RU].read);
        }
    }
    return res;
}

static bool cross_detect_is_right_vcc(CrossDetectPairInfo_t* pair) {
    bool res = false;

    res = CrossDetectIsRightHi(pair->measurements[CROSS_DETECT_STATE_LU_RD].read);
    if(res) {
        res = CrossDetectIsRightHi(pair->measurements[CROSS_DETECT_STATE_LD_RD].read);
        if(res) {
            res = CrossDetectIsRightHi(pair->measurements[CROSS_DETECT_STATE_LA_RD].read);
        }
    }
    return res;
}

static bool cross_detect_is_cross(CrossDetectPairInfo_t* pair) {
    bool res = false;
    if(READ_L1_R1 == pair->measurements[CROSS_DETECT_STATE_LU_RA].read) {
        if(CROSS_DETECT_STATE_LU_RA == pair->measurements[CROSS_DETECT_STATE_LU_RA].state) {
            if(READ_L1_R1 == pair->measurements[CROSS_DETECT_STATE_LA_RU].read) {
                if(CROSS_DETECT_STATE_LA_RU == pair->measurements[CROSS_DETECT_STATE_LA_RU].state) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
        if(READ_L0_R0 == pair->measurements[CROSS_DETECT_STATE_LA_RD].read) {
            if(READ_L0_R0 == pair->measurements[CROSS_DETECT_STATE_LD_RA].read) {
                res = true;
            }
        }
    }
    return res;
}

static bool cross_detect_run_analitic(CrossDetectHandle_t* const Node) {
    bool res = false;
    LOG_PARN(CROSS_DETECT, "RunAnalytics");
    if(Node) {
        // CrossDetectState_t state = 0;
        Node->pair.fault_cnt = 0;

        Node->pair.Fault.fault_code = 0;
        res = cross_detect_is_cross(&Node->pair);
        if(res) {
            Node->pair.Fault.cross = 1;
        } else {
            Node->pair.Fault.cross = 0;
        }

        res = cross_detect_is_left_gnd(&Node->pair);
        if(res) {
            Node->pair.Fault.left_short_gnd = 1;
        } else {
            Node->pair.Fault.left_short_gnd = 0;
        }

        res = cross_detect_is_right_gnd(&Node->pair);
        if(res) {
            Node->pair.Fault.right_short_gnd = 1;
        } else {
            Node->pair.Fault.right_short_gnd = 0;
        }

        res = cross_detect_is_left_vcc(&Node->pair);
        if(res) {
            Node->pair.Fault.left_short_vcc = 1;
        } else {
            Node->pair.Fault.left_short_vcc = 0;
        }

        res = cross_detect_is_right_vcc(&Node->pair);
        if(res) {
            Node->pair.Fault.right_short_vcc = 1;
        } else {
            Node->pair.Fault.right_short_vcc = 0;
        }

        if(Node->pair.Fault.fault_code != CrossDetectResult[Node->left_num][Node->right_num].FaultPrev.fault_code) {
            if(Node->pair.Fault.fault_code) {
                res = CrossDetectDiagFault(Node);
            }
        }
        CrossDetectResult[Node->left_num][Node->right_num].Fault.fault_code = Node->pair.Fault.fault_code;
        CrossDetectResult[Node->left_num][Node->right_num].FaultPrev.fault_code = Node->pair.Fault.fault_code;
        CrossDetectResult[Node->left_num][Node->right_num].update_cnt++;
        res = true;
    }
    return res;
}

/*  a  b  m     a  b  m
 * (0, 4, 5) ->(1, 0, 5)*/
U16Pair_t calc_next_uniq_u16pair(U16Pair_t pair) {
    U16Pair_t out;
    out = pair;

    if(out.a < out.max) {
        if(out.b < out.max) {
            out.b++;
            if(out.max == out.b) {
                out.a++;
                out.b = 0;
            }
        } else {
            out.a++;
            out.b = 0;
        }
    } else {
        out.a = 0;
        out.b = 1;
    }

    if(out.max == out.a) {
        out.a = 0;
    }

    if(out.a == out.b) {
        if(out.b < (out.max - 1)) {
            out.b++;
        } else {
            out.b = 0;
            if(out.a < (out.max - 1)) {
                out.a++;
            } else {
                out.a = 0;
            }
        }
    }
    return out;
}

static bool cross_detect_set_next_pair(CrossDetectHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->pair.spin_cnt = 0;

        uint32_t cnt = cross_detect_get_pin_cnt();
        res = cross_detect_reset_pair(&Node->pair);

        U16Pair_t in_pair = {
            .a = Node->left_num,
            .b = Node->right_num,
            .max = cnt,
        };
        U16Pair_t out = calc_next_uniq_u16pair(in_pair);
        Node->left_num = out.a;
        Node->right_num = out.b;
        LOG_DEBUG(CROSS_DETECT, "%u,%u", Node->left_num, Node->right_num);

        if((cnt * cnt - cnt) < Node->pair_cnt) {
            if(0 == (Node->pair_cnt % (cnt * cnt - cnt))) {
                uint32_t diratin_ms = time_get_ms32() - Node->start_ms;
                LOG_WARNING(CROSS_DETECT, "All %u PairsSolved!, %u ms", cnt * cnt - cnt, diratin_ms);
                Node->start_ms = time_get_ms32();
            }
        }
        Node->pair_cnt++;
        if(Node->left_num != Node->right_num) {
            res = cross_detect_init_pair(&Node->pair, CrossDetectPinConfig[Node->left_num].pad,
                                         CrossDetectPinConfig[Node->right_num].pad);
        }
    }

    return res;
}

static bool cross_detect_cycle_complete(CrossDetectHandle_t* const Node) {
    bool res = false;
    LOG_PARN(CROSS_DETECT, "CycleComplete");
    if(Node) {
        Node->pair.spin_cnt++;
        res = cross_detect_run_analitic(Node);
        if(CROSS_DETECT_TRY_PER_PAIR < Node->pair.spin_cnt) {
            res = cross_detect_set_next_pair(Node);
        }
    }
    return res;
}

static bool cross_detect_next_state(CrossDetectHandle_t* const Node) {
    bool res = true;
    LOG_PARN(CROSS_DETECT, "NextState");
    return res;
}

static bool cross_detect_start(CrossDetectHandle_t* const Node) {
    bool res = true;
    LOG_PARN(CROSS_DETECT, "Start");

    return res;
}

static const CrossDetectStateInfo_t StateTableLookUpTable[] = {
    [CROSS_DETECT_STATE_LA_RA] =
        {
            .pull_left = GPIO__PULL_AIR,
            .pull_right = GPIO__PULL_AIR,
            .action = cross_detect_start,
            .state_new = CROSS_DETECT_STATE_LU_RA,
        }, /*Left Pull air,Right pull air*/
    [CROSS_DETECT_STATE_LU_RA] =
        {
            .pull_left = GPIO__PULL_UP,
            .pull_right = GPIO__PULL_AIR,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LD_RA,
        }, /*Left pull up,Right pull air*/
    [CROSS_DETECT_STATE_LD_RA] =
        {
            .pull_left = GPIO__PULL_DOWN,
            .pull_right = GPIO__PULL_AIR,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LD_RD,
        }, /*Left pull down,Right pull air*/
    [CROSS_DETECT_STATE_LD_RD] =
        {
            .pull_left = GPIO__PULL_DOWN,
            .pull_right = GPIO__PULL_DOWN,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LD_RU,
        }, /*Left pull down,Right pull down*/
    [CROSS_DETECT_STATE_LD_RU] =
        {
            .pull_left = GPIO__PULL_DOWN,
            .pull_right = GPIO__PULL_UP,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LA_RU,
        }, /*Left pull down,Right pull up*/
    [CROSS_DETECT_STATE_LA_RU] =
        {
            .pull_left = GPIO__PULL_AIR,
            .pull_right = GPIO__PULL_UP,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LU_RU,
        }, /*Left pull air,Right pull up*/
    [CROSS_DETECT_STATE_LU_RU] =
        {
            .pull_left = GPIO__PULL_UP,
            .pull_right = GPIO__PULL_UP,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LU_RD,
        }, /*Left pull up,Right pull up*/
    [CROSS_DETECT_STATE_LU_RD] =
        {
            .pull_left = GPIO__PULL_UP,
            .pull_right = GPIO__PULL_DOWN,
            .action = cross_detect_next_state,
            .state_new = CROSS_DETECT_STATE_LA_RD,
        }, /*Left pull up,Right pull down*/
    [CROSS_DETECT_STATE_LA_RD] =
        {
            .pull_left = GPIO__PULL_AIR,
            .pull_right = GPIO__PULL_DOWN,
            .action = cross_detect_cycle_complete,
            .state_new = CROSS_DETECT_STATE_LA_RA,
        }, /*Left pull air,Right pull down*/
};

static bool cross_detect_state_set(CrossDetectPairInfo_t* const pair, CrossDetectState_t new_state) {
    bool res = false;
    if(pair) {
        uint8_t ok = 0;
        res = gpio_set_pull(pair->left.byte, StateTableLookUpTable[new_state].pull_left);
        if(res) {
            ok++;
        }

        res = gpio_set_pull(pair->right.byte, StateTableLookUpTable[new_state].pull_right);
        if(res) {
            ok++;
        }

        if(2 == ok) {
            pair->state = new_state;
            res = true;
        } else {
            LOG_ERROR(CROSS_DETECT, "SetStateErr %u=%s", new_state, CrossDetectState2Str(new_state));
            res = false;
        }
    }
    return res;
}

const CrossDetectSolutionInfo_t CrossDetectSolutionInfo[36] = {
    {
        /*1*/ .state = CROSS_DETECT_STATE_LA_RA,
        .read = READ_L0_R0,
        .left_short_gnd = CONF_NO,
        .right_short_gnd = CONF_NO,
        .left_short_vcc = CONF_NO,
        .right_short_vcc = CONF_NO,
        .cross = CONF_NO,
        .open = CONF_NO,
        .error = CONF_NO,
        .ok = CONF_YES,
    },

    {
        /*2*/ .state = CROSS_DETECT_STATE_LU_RA,
        .read = READ_L0_R0,
        .left_short_gnd = CONF_YES,
        .left_short_vcc = CONF_NO,
        .right_short_gnd = CONF_NO,
        .right_short_vcc = CONF_NO,
        .cross = CONF_MAYBE,
        .open = CONF_MAYBE,
        .error = CONF_YES,
        .ok = CONF_NO,
    },

    {
        /*3*/ .state = CROSS_DETECT_STATE_LD_RA,
        .read = READ_L0_R0,
        .left_short_gnd = CONF_MAYBE,
        .left_short_vcc = CONF_NO,
        .right_short_gnd = CONF_MAYBE,
        .right_short_vcc = CONF_NO,
        .cross = CONF_MAYBE,
        .open = CONF_MAYBE,
        .error = CONF_NO,
        .ok = CONF_YES,
    },

    {
        /*4*/ .state = CROSS_DETECT_STATE_LD_RD,
        .read = READ_L0_R0,
        .left_short_gnd = CONF_MAYBE,
        .left_short_vcc = CONF_NO,
        .right_short_gnd = CONF_MAYBE,
        .right_short_vcc = CONF_NO,
        .cross = CONF_MAYBE,
        .open = CONF_MAYBE,
        .error = CONF_NO,
        .ok = CONF_YES,
    },

    {
        /*5*/ .state = CROSS_DETECT_STATE_LD_RU,
        .read = READ_L0_R0,
        .left_short_gnd = CONF_MAYBE,
        .left_short_vcc = CONF_NO,
        .right_short_gnd = CONF_YES,
        .right_short_vcc = CONF_NO,
        .cross = CONF_MAYBE,
        .open = CONF_MAYBE,
        .error = CONF_YES,
        .ok = CONF_NO,
    },

    {
        /*6*/ .state = CROSS_DETECT_STATE_LA_RU,
        .read = READ_L0_R0,
        .left_short_gnd = CONF_MAYBE,
        .left_short_vcc = CONF_NO,
        .right_short_gnd = CONF_YES,
        .right_short_vcc = CONF_NO,
        .cross = CONF_MAYBE,
        .open = CONF_MAYBE,
        .error = CONF_YES,
        .ok = CONF_NO,
    },

    {/*7*/ .state = CROSS_DETECT_STATE_LU_RU,
     .read = READ_L0_R0,
     .left_short_gnd = CONF_YES,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_YES,
     .right_short_vcc = CONF_NO,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*8*/ .state = CROSS_DETECT_STATE_LU_RD,
     .read = READ_L0_R0,
     .left_short_gnd = CONF_YES,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*9*/ .state = CROSS_DETECT_STATE_LA_RD,
     .read = READ_L0_R0,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_NO,
     .ok = CONF_YES},

    {/*10*/ .state = CROSS_DETECT_STATE_LA_RA,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*11*/ .state = CROSS_DETECT_STATE_LU_RA,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_YES,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*12*/ .state = CROSS_DETECT_STATE_LD_RA,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*13*/ .state = CROSS_DETECT_STATE_LD_RD,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_YES,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*14*/ .state = CROSS_DETECT_STATE_LD_RU,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_NO,
     .ok = CONF_YES},

    {/*15*/ .state = CROSS_DETECT_STATE_LA_RU,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_NO,
     .ok = CONF_YES},

    {/*16*/ .state = CROSS_DETECT_STATE_LU_RU,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_YES,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*17*/ .state = CROSS_DETECT_STATE_LU_RD,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_YES,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_YES,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*18*/ .state = CROSS_DETECT_STATE_LA_RD,
     .read = READ_L0_R1,
     .left_short_gnd = CONF_MAYBE,
     .left_short_vcc = CONF_NO,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_YES,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*19*/ .state = CROSS_DETECT_STATE_LA_RA,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*20*/ .state = CROSS_DETECT_STATE_LU_RA,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_NO,
     .ok = CONF_YES},

    {/*21*/ .state = CROSS_DETECT_STATE_LD_RA,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_YES,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*22*/ .state = CROSS_DETECT_STATE_LD_RD,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_YES,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*23*/ .state = CROSS_DETECT_STATE_LD_RU,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_YES,
     .right_short_gnd = CONF_YES,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*24*/ .state = CROSS_DETECT_STATE_LA_RU,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_YES,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*25*/ .state = CROSS_DETECT_STATE_LU_RU,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_YES,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*26*/ .state = CROSS_DETECT_STATE_LU_RD,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_NO,
     .ok = CONF_YES},

    {/*27*/ .state = CROSS_DETECT_STATE_LA_RD,
     .read = READ_L1_R0,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_NO,
     .cross = CONF_NO,
     .open = CONF_YES,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*28*/ .state = CROSS_DETECT_STATE_LA_RA,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*29*/ .state = CROSS_DETECT_STATE_LU_RA,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_YES,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*30*/ .state = CROSS_DETECT_STATE_LD_RA,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_YES,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*31*/ .state = CROSS_DETECT_STATE_LD_RD,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_YES,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_YES,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*32*/ .state = CROSS_DETECT_STATE_LD_RU,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_YES,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*33*/ .state = CROSS_DETECT_STATE_LA_RU,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_YES,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*34*/ .state = CROSS_DETECT_STATE_LU_RU,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_MAYBE,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_NO,
     .ok = CONF_YES},

    {/*35*/ .state = CROSS_DETECT_STATE_LU_RD,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_NO,
     .right_short_vcc = CONF_YES,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},

    {/*36*/ .state = CROSS_DETECT_STATE_LA_RD,
     .read = READ_L1_R1,
     .left_short_gnd = CONF_NO,
     .left_short_vcc = CONF_MAYBE,
     .right_short_gnd = CONF_MAYBE,
     .right_short_vcc = CONF_YES,
     .cross = CONF_MAYBE,
     .open = CONF_MAYBE,
     .error = CONF_YES,
     .ok = CONF_NO},
};

uint32_t cross_detect_get_lut_size(void) {
    uint32_t cnt = ARRAY_SIZE(CrossDetectSolutionInfo);
    return cnt;
}

#if 0
static const CrossDetectSolutionInfo_t* GetSolNode(const CrossDetectStateMeasure_t* const measure_node) {
    const CrossDetectSolutionInfo_t* LutNode = NULL;
    uint32_t cnt = cross_detect_get_lut_size();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(CrossDetectSolutionInfo[i].state == measure_node->state) {
            if(CrossDetectSolutionInfo[i].read == measure_node->read) {
                LutNode = &CrossDetectSolutionInfo[i];
                break;
            }
        }
    }
    return LutNode;
}
#endif

CrossDetectHandle_t* CrossDetectGetNode(uint8_t num) {
    CrossDetectHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = cross_detect_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == CrossDetectInstance[i].num) {
            if(CrossDetectInstance[i].valid) {
                Node = &CrossDetectInstance[i];
                break;
            }
        }
    }
    return Node;
}

const CrossDetectConfig_t* CrossDetectGetConfNode(uint8_t num) {
    const CrossDetectConfig_t* Config = NULL;
    uint32_t i = 0;
    uint32_t cnt = cross_detect_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == CrossDetectConfig[i].num) {
            if(CrossDetectConfig[i].valid) {
                Config = &CrossDetectConfig[i];
                break;
            }
        }
    }
    return Config;
}

bool cross_detect_init_pair(CrossDetectPairInfo_t* const pair, Pad_t left, Pad_t right) {
    bool res = false;
    if(pair) {
        if(left.byte != right.byte) {
            pair->left = left;
            pair->right = right;
            pair->solution = CROSS_DETECT_SOL_UNDEF;
            // pair->prev_solution = CROSS_DETECT_SOL_UNDEF;
            pair->state = CROSS_DETECT_STATE_LA_RA;
            pair->spin_cnt = 0;
            pair->err_cnt = 0;
            pair->time_start = 0;
            pair->pause_ms = 0;
            pair->init = true;
            CrossDetectDiagPair(pair);
            res = cross_detect_state_set(pair, CROSS_DETECT_STATE_LA_RA);
        }
    }
    return res;
}

bool cross_detect_reset_pair(const CrossDetectPairInfo_t* const pair) {
    bool res = false;
    res = gpio_set_pull(pair->left.byte, GPIO__PULL_AIR);
    res = gpio_set_pull(pair->right.byte, GPIO__PULL_AIR);
    return res;
}

bool cross_detect_enable(uint8_t num, bool on_off) {
    bool res = false;
    CrossDetectHandle_t* Node = CrossDetectGetNode(num);
    if(Node) {
        Node->on = on_off;
        res = true;
    }
    return res;
}

static bool cross_detect_init_pin(const CrossDetectPinConfig_t* const PinConfig) {
    bool res = false;
    if(PinConfig) {
        uint8_t ok = 0;
        LOG_WARNING(CROSS_DETECT, "InitPad: %s In PullAir", GpioPad2Str(PinConfig->pad.byte));

        res = gpio_set_dir(PinConfig->pad.byte, GPIO_DIR_IN);
        if(res) {
            ok++;
        } else {
            LOG_ERROR(CROSS_DETECT, "Pad: %s SetDirIn Err", GpioPad2Str(PinConfig->pad.byte));
        }

        res = gpio_set_pull(PinConfig->pad.byte, GPIO__PULL_AIR);
        if(res) {
            ok++;
        } else {
            LOG_ERROR(CROSS_DETECT, "Pad: %s SetPullAir Err", GpioPad2Str(PinConfig->pad.byte));
        }

#ifdef HAS_NRF5340
        res = gpio_set_pin_mcu(PinConfig->pad, NRF_GPIO_PIN_MUX_APP);
        if(res) {
            ok++;
        } else {
            LOG_ERROR(CROSS_DETECT, "Pad: %s SetAppCore Err", GpioPad2Str(PinConfig->pad.byte));
        }
#endif

        if(3 == ok) {
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}

bool cross_detect_init_pins(uint8_t num) {
    bool res = false;
    uint32_t pin_cnt = cross_detect_get_pin_cnt();
    LOG_WARNING(CROSS_DETECT, "LD%u Init %u Pins", num, pin_cnt);
    uint32_t i;
    uint32_t ok = 0;
    for(i = 0; i < pin_cnt; i++) {
        if(num == CrossDetectPinConfig[i].num) {
            res = cross_detect_init_pin(&CrossDetectPinConfig[i]);
            if(res) {
                ok++;
                LOG_DEBUG(CROSS_DETECT, "InitPin %s Ok", GpioPadToStr(CrossDetectPinConfig[i].pad));
            } else {
                LOG_ERROR(CROSS_DETECT, "InitPinErr %d", num);
            }
        }
    }
    if(0 < ok) {
        res = true;
    }
    return res;
}

bool cross_detect_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CROSS_DETECT, "Init %d", num);
    const CrossDetectConfig_t* Config = CrossDetectGetConfNode(num);
    if(Config) {
        CrossDetectHandle_t* Node = CrossDetectGetNode(num);
        if(Node) {
            Node->on = true;
            Node->init = true;
            Node->valid = true;
            Node->pair_cnt = 0;
            Node->left_num = 0;
            Node->right_num = 1;
            Node->start_ms = time_get_ms32();
            // size_t size = sizeof(CrossDetectResult_t) * CROSS_DETECT_PIN_CNT * CROSS_DETECT_PIN_CNT;
            // LOG_INFO(CROSS_DETECT, "ZeroSize %u byte of result array", size);
            uint32_t l, r;
            uint32_t cnt = cross_detect_get_pin_cnt();
            for(l = 0; l < cnt; l++) {
                for(r = 0; r < cnt; r++) {
                    CrossDetectResult[l][r].Fault.fault_code = 0;
                    CrossDetectResult[l][r].FaultPrev.fault_code = 0;
                }
            }

            res = cross_detect_init_pins(num);
            if(res) {
                LOG_INFO(CROSS_DETECT, "%u InitPinsOk", num);
            } else {
                LOG_ERROR(CROSS_DETECT, "%u InitPinsErr", num);
            }

            res = cross_detect_init_pair(&Node->pair, CrossDetectPinConfig[Node->left_num].pad,
                                         CrossDetectPinConfig[Node->right_num].pad);
            if(res) {

            } else {
                LOG_ERROR(CROSS_DETECT, "InitPair %u,%u Err", Node->left_num, Node->right_num);
            }
        } else {
            LOG_ERROR(CROSS_DETECT, "%u NodeErr", num);
        }
    } else {
        LOG_ERROR(CROSS_DETECT, "%u ConfErr", num);
    }
    return res;
}

bool cross_detect_init(void) {
    bool res = false;
    set_log_level(CROSS_DETECT, LOG_LEVEL_DEBUG);
    uint32_t cnt = cross_detect_get_cnt();
    uint32_t ok = 0;
    LOG_WARNING(CROSS_DETECT, "Init Cnt %d", cnt);

    uint32_t i = 0;
    for(i = 1; i <= cnt; i++) {
        res = cross_detect_init_one(i);
        if(res) {
            ok++;
            LOG_INFO(CROSS_DETECT, "LD%u InitOk", i);
        } else {
            LOG_ERROR(CROSS_DETECT, "LD%u InitErr", i);
        }
    }

    if(ok) {
        res = true;
        LOG_INFO(CROSS_DETECT, "Init %u Ok", ok);
    } else {
        res = false;
        LOG_ERROR(CROSS_DETECT, "InitErr");
    }

    set_log_level(CROSS_DETECT, LOG_LEVEL_INFO);
    return res;
}

#if 0
static bool cross_detect_calc_fault(CrossDetectPairInfo_t* const pair, CrossDetectState_t state) {
    bool res = false;
    uint32_t i = 0;
    /*Are any faults found in this state?*/
    for(i = 0; i < 9; i++) {
        if(pair->measurements[i].state == state) {
            const CrossDetectSolutionInfo_t* LutNode = GetSolNode(&pair->measurements[i]);
            if(LutNode) {
                // if(CONF_YES == LutNode->cross) {
                //    pair->Fault.cross = 1;
                //}
                if(CONF_YES == LutNode->left_short_gnd) {
                    pair->Fault.left_short_gnd = 1;
                }
                if(CONF_YES == LutNode->left_short_vcc) {
                    pair->Fault.left_short_vcc = 1;
                }
                if(CONF_YES == LutNode->right_short_gnd) {
                    pair->Fault.right_short_gnd = 1;
                }
                if(CONF_YES == LutNode->right_short_vcc) {
                    pair->Fault.right_short_vcc = 1;
                }
                res = true;
            } else {
                LOG_ERROR(CROSS_DETECT, "UndefCase State %u, Read %u", state, pair->measurements[i].read);
            }
            break;
        }
    }
    return res;
}
#endif

static bool cross_detect_measure(CrossDetectPairInfo_t* const pair) {
    bool res = false;
    if(pair) {
        LOG_PARN(CROSS_DETECT, "MeasureGPIOin %s", CrossDetectState2Str(pair->state));

        GpioLogicLevel_t logic_left = GPIO_LVL_UNDEF;
        GpioLogicLevel_t logic_right = GPIO_LVL_UNDEF;
        res = gpio_get_state(pair->left.byte, &logic_left);
        res = gpio_get_state(pair->right.byte, &logic_right);

        if(GPIO_LVL_HI == logic_left) {
            if(GPIO_LVL_HI == logic_right) {
                pair->measurements[pair->state].read = READ_L1_R1;
            } else {
                pair->measurements[pair->state].read = READ_L1_R0;
            }
        } else {
            if(GPIO_LVL_HI == logic_right) {
                pair->measurements[pair->state].read = READ_L0_R1;
            } else {
                pair->measurements[pair->state].read = READ_L0_R0;
            }
        }

        pair->measurements[pair->state].state = pair->state;
    }
    return res;
}

/*UP->AIR->Down->Up*/
bool cross_detect_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CROSS_DETECT, "Proc:%u", num);
    CrossDetectHandle_t* Node = CrossDetectGetNode(num);
    if(Node) {
        if(Node->on) {
            /*Measure GPIO logic levels */
            res = cross_detect_measure(&Node->pair);
            if(res) {
                LOG_PARN(CROSS_DETECT, "MeasureGPIOOk");
            } else {
                Node->pair.err_cnt++;
                LOG_ERROR(CROSS_DETECT, "MeaseireGPIOErr");
            }

            CrossDetectState_t new_state = StateTableLookUpTable[Node->pair.state].state_new;
            CrossDetectHandler_t action = StateTableLookUpTable[Node->pair.state].action;
            if(action) {
                res = action(Node);
            }

            res = cross_detect_state_set(&Node->pair, new_state);
            if(res) {
                LOG_PARN(CROSS_DETECT, "SetStateOk %u=%s", new_state, CrossDetectState2Str(new_state));
            } else {
                LOG_ERROR(CROSS_DETECT, "SetStateErr %u=%s", new_state, CrossDetectState2Str(new_state));
            }
        } else {
            LOG_DEBUG(CROSS_DETECT, "Off %u", num);
        }
    } else {
        LOG_ERROR(CROSS_DETECT, "NodeErr %u", num);
    }
    return res;
}

bool cross_detect_proc(void) {
    bool res = false;
    uint8_t ok = 0;
    uint8_t cnt = cross_detect_get_cnt();
    LOG_PARN(CROSS_DETECT, "Proc Cnt:%u", cnt);
    for(uint32_t i = 1; i <= cnt; i++) {
        res = cross_detect_proc_one(i);
        if(res) {
            ok++;
        }
    }

    if(ok) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
