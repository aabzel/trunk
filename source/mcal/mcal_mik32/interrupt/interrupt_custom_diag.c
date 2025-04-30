#include "interrupt_custom_diag.h"

#include <stdint.h>
#include <stdio.h>

#include "data_utils.h"
#include "debugger.h"
#include "interrupt_diag.h"
#include "interrupt_types.h"
#include "microcontroller_const.h"
#include "mik32_hal.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

static const Reg32_t InterruptControllerRegs[] = {
    {
        .num = 1,
        .access = ACCESS_READ_WRITE,
        .name = "MASK_EDGE_SET",
        .offset = 0x0,
        .valid = true,
    },
    {
        .num = 2,
        .access = ACCESS_READ_WRITE,
        .name = "MASK_EDGE_CLEAR",
        .offset = 0x4,
        .valid = true,
    },
    {
        .num = 3,
        .access = ACCESS_WRITE_ONLY,
        .name = "MASK_LEVEL_SET",
        .offset = 0x8,
        .valid = true,
    },
    {
        .num = 4,
        .access = ACCESS_WRITE_ONLY,
        .name = "MASK_LEVEL_CLEAR",
        .offset = 0xC,
        .valid = true,
    },
    {
        .num = 5,
        .access = ACCESS_WRITE_ONLY,
        .name = "CLEAR",
        .offset = 0x18,
        .valid = true,
    },
    {
        .num = 6,
        .access = ACCESS_READ_ONLY,
        .name = "STATUS",
        .offset = 0x1C,
        .valid = true,
    },
    {
        .num = 7,
        .access = ACCESS_READ_ONLY,
        .name = "RAW_STATUS",
        .offset = 0x20,
        .valid = true,
    },
};

bool interrupt_raw_reg(void) {
    bool res = false;
    uint32_t cnt = ARRAY_SIZE(InterruptControllerRegs);
    res = debug_raw_reg_diag(LG_INT, EPIC_BASE_ADDRESS, InterruptControllerRegs, cnt);
    return res;
}

#if 0
const char* InterruptNumToStr(int16_t int_n){
    const char* name = "?";
    uint32_t i = 0;
    for(i=0;i<ARRAY_SIZE(IntNameLut);i++){
        if(int_n==IntNameLut[i].int_n){
            name=IntNameLut[i].name;
            break;
        }
    }
    return name;
}
#endif

bool interrupt_custom_diag(char* key_word1, char* key_word2) {
    bool res = false;

    static const table_col_t cols[] = {
        {5, "No"},      {5, "irq"},    {3, "En"},     {12, "Base"},  {6, "Active"},
        {6, "pending"}, {6, "PrePri"}, {6, "SubPri"}, {9, "PrePri"}, {9, "SubPri"},
#ifdef HAS_INTERRUPT_DIAG
        {18, "name"},
#endif
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    int8_t irq_n = 0;
    char temp_str[120] = "";
    for(irq_n = 0; irq_n <= 31; irq_n++) {
        strcpy(temp_str, TSEP);
        snprintf(temp_str, sizeof(temp_str), "%s %3d " TSEP, temp_str, irq_n);
        if(is_contain(temp_str, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
