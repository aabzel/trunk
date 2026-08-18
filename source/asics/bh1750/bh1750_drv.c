#include "bh1750_drv.h"

#include "bh1750_config.h"
#include "bh1750_dep.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "i2c_mcal.h"
#include "log.h"
#include "utils_math.h"

static bool bh1750_init_custom(void) {
    bool res = true;
    return res;
}

COMPONENT_GET_NODE(Bh1750, bh1750)
COMPONENT_GET_CONFIG(Bh1750, bh1750)

#if 0
Bh1750Handle_t* Bh1750GetNode(uint8_t num) {
    Bh1750Handle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t bh1750_cnt = bh1750_get_cnt();
    for(i = 0; i < bh1750_cnt; i++) {
        if(num == Bh1750Instance[i].num) {
            if(Bh1750Instance[i].valid) {
                Node = &Bh1750Instance[i];
                break;
            }
        }
    }
    return Node;
}
#endif

#if 0
const Bh1750Config_t* Bh1750GetConfig(uint8_t num) {
    const Bh1750Config_t* Config = NULL;
    uint32_t i = 0;
    uint32_t bh1750_cnt = bh1750_get_cnt();
    for(i = 0; i < bh1750_cnt; i++) {
        if(num == Bh1750Config[i].num) {
            if(Bh1750Config[i].valid) {
                Config = &Bh1750Config[i];
                break;
            }
        }
    }
    return Config;
}
#endif

bool bh1750_send_opcode(uint8_t num, BhOpCode_t op_code) {
    bool res = false;
    LOG_WARNING(BH1750, "%u Send OpCode %u", num, op_code);
    Bh1750Handle_t* Node = Bh1750GetNode(num);
    if(Node) {
        uint8_t array = op_code;
        // uint8_t write_address=i2c_compose_write_address(  Node->chip_addr);
        res = i2c_write_wait(Node->i2c_num, Node->chip_addr, &array, 1);
        log_res(BH1750, res, "I2cWr");
    }
    return res;
}

bool bh1750_init_one(uint8_t num) {
    bool res = false;
    const Bh1750Config_t* Config = Bh1750GetConfig(num);
    if(Config) {
        Bh1750Handle_t* Node = Bh1750GetNode(num);
        if(Node) {
            res = true;
            LOG_WARNING(BH1750, "Init BH1750_%u", num);
            Node->chip_addr = Config->chip_addr;
            Node->i2c_num = Config->i2c_num;
            Node->num = Config->num;
            Node->valid = true;
            res = bh1750_send_opcode(num, BH1750_OP_CODE_POWER_DOWN) && res;
            res = bh1750_send_opcode(num, BH1750_OP_CODE_POWER_ON) && res;
            res = bh1750_send_opcode(num, BH1750_OP_CODE_CONTIN_H_RESOL_MODE) && res;
        }
    }
    return res;
}

bool bh1750_read_code(uint8_t num, uint16_t* const word) {
    bool res = false;
    Bh1750Handle_t* Node = Bh1750GetNode(num);
    if(Node) {
        LOG_DEBUG(BH1750, "ReadCode %u", num);
        // uint8_t read_address=i2c_compose_read_address(Node->chip_addr);
        U16_bit_t un16;
        un16.u16 = 0;
        res = i2c_mcal_read(Node->i2c_num, Node->chip_addr, (uint8_t*)un16.u8, 2);
        if(res) {
            LOG_DEBUG(BH1750, "ReadCode %u 0x%04x=%u Ok", num, un16.u16, un16.u16);
            (*word) = reverse_byte_order_uint16(un16.u16);
        } else {
            LOG_ERROR(BH1750, "ReadCode %u Err", num);
        }
    }
    return res;
}

double Bh1750Code2Lx(uint16_t word) {
    double lx = ((double)word) / 1.2;
    return lx;
}

bool bh1750_read_lx(uint8_t num, double* const lighting) {
    bool res = false;
    Bh1750Handle_t* Node = Bh1750GetNode(num);
    if(Node && lighting) {
        res = bh1750_read_code(num, &Node->word);
        if(res) {
            Node->lx.cur = Bh1750Code2Lx(Node->word);
            Node->lx.min = MIN(Node->lx.cur, Node->lx.min);
            Node->lx.max = MAX(Node->lx.cur, Node->lx.max);
            LOG_DEBUG(BH1750, "light %7.3f lx", num, Node->lx.cur);
            *lighting = Node->lx.cur;
        }
    }
    return res;
}

double bh1750_read_lx_short(uint8_t num) {
    double lighting = 0.0;
    bool res = bh1750_read_lx(num, &lighting);
    if(res) {
        LOG_INFO(BH1750, "%u light %7.3f lx", num, lighting);
    } else {
        LOG_ERROR(BH1750, "ReadLightErr %u", num);
    }
    return lighting;
}

bool bh1750_proc_one(uint8_t num) {
    bool res = false;
    Bh1750Handle_t* Node = Bh1750GetNode(num);
    if(Node) {
        LOG_DEBUG(BH1750, "Proc %u", num);
        double lighting = 0;
        res = bh1750_read_lx(num, &lighting);
    }
    return res;
}

#if 0
bool bh1750_mcal_init(void) {
    bool res = false;
    LOG_INFO(BH1750, "Version: %u", BH1750_DRIVER_VERSION);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    set_log_level(BH1750, LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint32_t cnt = bh1750_get_cnt();
    LOG_WARNING(BH1750, "Init %u LightSensor", cnt);
    for(i = 0; i <= cnt; i++) {
        res = bh1750_init_one(i);
        if(res) {
            ok_cnt++;
        }
    }

    if(ok_cnt) {
        LOG_INFO(BH1750, "InitOk %u", ok_cnt);
        res = true;
    } else {
        LOG_ERROR(BH1750, "InitErr ");
        res = false;
    }
    set_log_level(I2C, LOG_LEVEL_INFO);
    set_log_level(BH1750, LOG_LEVEL_INFO);
    return res;
}
#endif

#if 0
bool bh1750_proc(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = bh1750_get_cnt();
    LOG_DEBUG(BH1750, "Proc %u", cnt);
        for(i = 0; i <= cnt; i++) {
            res = bh1750_proc_one(i);
        }
        return res;
}
#endif

bool bh1750_reset(uint8_t num) {
    LOG_WARNING(BH1750, "Reset %u", num);
    bool res = bh1750_send_opcode(num, BH1750_OP_CODE_RESET);
    return res;
}

COMPONENT_INIT_PATTERT(BH1750, BH1750, bh1750)
COMPONENT_PROC_PATTERT(BH1750, BH1750, bh1750)
