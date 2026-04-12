#include "iomux_custom_diag.h"

#include "artery_at32f4xx.h"
#include "data_utils.h"
#include "debugger.h"
#include "log.h"

// 11.5 I2C registers
static const Reg32_t IoMuxReg[] = {
    {
        .valid = true,
        .offset = 0x00,
        .name = "IOMUX_EVTOUT",
    },
    {
        .valid = true,
        .offset = 0x04,
        .name = "IOMUX_REMAP",
    },
    {
        .valid = true,
        .offset = 0x08,
        .name = "IOMUX_EXINTC1",
    },
    {
        .valid = true,
        .offset = 0x0C,
        .name = "IOMUX_EXINTC2",
    },
    {
        .valid = true,
        .offset = 0x10,
        .name = "IOMUX_EXINTC3",
    },
    {
        .valid = true,
        .offset = 0x14,
        .name = "IOMUX_EXINTC4",
    },
    {
        .valid = true,
        .offset = 0x1C,
        .name = "IOMUX_REMAP2",
    },
    {
        .valid = true,
        .offset = 0x20,
        .name = "IOMUX_REMAP3",
    },
    {
        .valid = true,
        .offset = 0x24,
        .name = "IOMUX_REMAP4",
    },
    {
        .valid = true,
        .offset = 0x28,
        .name = "IOMUX_REMAP5",
    },
    {
        .valid = true,
        .offset = 0x2C,
        .name = "IOMUX_REMAP6",
    },
    {
        .valid = true,
        .offset = 0x30,
        .name = "IOMUX_REMAP7",
    },
    {
        .valid = true,
        .offset = 0x34,
        .name = "IOMUX_REMAP8",
    },
};

bool iomux_diag_reg_map(void) {
    bool res = false;
    uint32_t cnt = ARRAY_SIZE(IoMuxReg);
    // 0x40010000 - 0x400103FF IOMUX Boundary address
    res = debug_raw_reg_diag(IO_MUX, (uint32_t)IOMUX_BASE, IoMuxReg, cnt);
    return res;
}
