#include "can_registers_diag.h"

#include "can_custom_diag.h"
#include "can_mcal.h"
#include "can_misc.h"
#include "can_register_types.h"
#include "common_diag.h"
#include "data_utils.h"
#include "debugger.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

/*
 */
const Reg32_t CanReg[] = {
    {
        .offset = 0x00,
        .name = "CAN_MCR",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x04,
        .name = "CAN_MSR",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x08,
        .name = "CAN_TSR",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x0C,
        .name = "CAN_RF0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x10,
        .name = "CAN_RF1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x14,
        .name = "CAN_IER",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x18,
        .name = "CAN_ESR",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1C,
        .name = "CAN_BTR",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x180,
        .name = "CAN_TI0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x190,
        .name = "CAN_TI1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x194,
        .name = "CAN_TDT1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x198,
        .name = "CAN_TDL1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x19C,
        .name = "CAN_TDH1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1A0,
        .name = "CAN_TI2R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1A4,
        .name = "CAN_TDT2R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1A8,
        .name = "CAN_TDL2R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1AC,
        .name = "CAN_TDH2R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1B0,
        .name = "CAN_RI0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1B4,
        .name = "CAN_RDT0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1B8,
        .name = "CAN_RDL0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1BC,
        .name = "CAN_RDH0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1C0,
        .name = "CAN_RI1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1C4,
        .name = "CAN_RDT1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1C8,
        .name = "CAN_RDL1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x1CC,
        .name = "CAN_RDH1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x184,
        .name = "CAN_TDT0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x188,
        .name = "CAN_TDL0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x18C,
        .name = "CAN_TDH0R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x200,
        .name = "CAN_FMR",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x204,
        .name = "CAN_FM1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x20C,
        .name = "CAN_FS1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x214,
        .name = "CAN_FFA1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x21C,
        .name = "CAN_FA1R",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x240,
        .name = "CAN_F0R1",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x24C,
        .name = "CAN_F1R2",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x318,
        .name = "CAN_F27R1",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
    {
        .offset = 0x31C,
        .name = "CAN_F27R2",
        .num = 1,
        .size = 4,
        .valid = true,
        .access = ACCESS_READ_WRITE,
    },
};

uint32_t can_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(CanReg);
    return cnt;
}

bool can_raw_reg_diag(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        LOG_INFO(CAN, "CAN%u,Base:0x%p", num, Info->CANx);
        uint32_t reg_cnt = can_reg_cnt();
        res = debug_raw_reg_diag(CAN, (uint32_t)Info->CANx, CanReg, reg_cnt);
    }
    return res;
}
