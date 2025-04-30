#include "interrupt_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "writer_config.h"

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t preempt_priority = 0;
    uint8_t sub_priority = 0;
    int16_t irq_n = 0;
    if(1 == argc) {
        res = try_str2int16(argv[0], &irq_n);
        log_res(LG_INT, res, "GetNum");
        if(false == res) {
            LOG_ERROR(LG_INT, "Unable to parse IrqN");
        }
    }

    if(res) {
        interrupt_get_priority(irq_n, (uint8_t*)&preempt_priority, (uint8_t*)&sub_priority);
        LOG_INFO(SYS, "irq_n: %d  preempt_priority:%u sub_priority:%u", irq_n, preempt_priority, sub_priority);
    } else {
        LOG_ERROR(LG_INT, "Usage: ig IrqN");
    }
    return res;
}

bool interrupt_enable_command(int32_t argc, char* argv[]) {
    bool res = true;

    if(res) {
        res = interrupt_enable();
        log_res(LG_INT, res, "IntEnable");
    } else {
        LOG_ERROR(SYS, "Usage: ie");
    }
    return res;
}

bool interrupt_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t preempt_priority = 0;
    int16_t irq_n = 0;
    if(3 == argc) {
        res = try_str2int16(argv[0], &irq_n);
        if(false == res) {
            LOG_ERROR(LG_INT, "Unable to parse IrqN");
        }
        res = try_str2uint32(argv[0], &preempt_priority);
        if(false == res) {
            LOG_ERROR(LG_INT, "Unable to parse preempt_priority");
        }
    }

    if(res) {
        res = interrupt_set_priority(irq_n, preempt_priority);
        log_res(LG_INT, res, "SetPrio");
    } else {
        LOG_ERROR(LG_INT, "Usage: is irq_n preempt_priority sub_priority");
    }
    return res;
}

bool interrupt_enable_irq_command(int32_t argc, char* argv[]) {
    bool res = false;
    int8_t irq_n = 0;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &irq_n);
        if(false == res) {
            LOG_ERROR(LG_INT, "Unable to parse IrqN");
        }
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(LG_INT, "Unable to parse IrqN");
        }
    }

    if(res && (2 == argc)) {
        res = interrupt_control(irq_n, on_off);
        log_res(LG_INT, res, "Ctrl");
    } else {
        LOG_ERROR(LG_INT, "Usage: ien IrqN on_off");
    }
    return res;
}

bool interrupt_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = interrupt_mcal_init();
    log_res(LG_INT, res, "Init");
    return res;
}

bool interrupt_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(SYS, "Usage: id keyWord");
    }
    if(true == res) {
#ifdef HAS_INTERRUPT_DIAG
        res = interrupt_diag(keyWord1, keyWord2);
#endif
        log_res(LG_INT, res, "Diag");
    }
    return res;
}
