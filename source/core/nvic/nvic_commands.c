#include "nvic_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "nvic_drv.h"
#include "str_utils.h"

#include "table_utils.h"

#ifndef HAS_WRITER
//#include "writer.h"
#endif

#ifndef HAS_NVIC_COMMANDS
#error "+HAS_NVIC_COMMANDS"
#endif /**/

bool nvic_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t Priority = 0;
    int16_t irq_n = 0;
    if(1 == argc) {
        res = try_str2int16(argv[0], &irq_n);
    }
    uint32_t PriorityGroup = NVIC_GetPriorityGrouping();
    LOG_INFO(SYS, "PriorityGroup %u", PriorityGroup);
    if(res) {
        Priority = NVIC_GetPriority((IRQn_Type)irq_n);
        uint32_t vector = NVIC_GetVector((IRQn_Type)irq_n);
        LOG_INFO(SYS, "irq_n: %d Priority:%u,Vector: 0x%08x", irq_n, Priority, vector);
    } else {
        LOG_ERROR(LG_NVIC, "Usage: ig IrqN");
    }
    return res;
}

bool nvic_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t Priority = 0;

    int8_t irq_n = 0;
    if(2 == argc) {
        res = try_str2int8(argv[0], &irq_n);
        res = try_str2uint32(argv[0], &Priority);
    }

    if(res) {
#ifdef HAS_CMSIS
        NVIC_SetPriority((IRQn_Type)irq_n, Priority);
#endif
    } else {
        LOG_ERROR(LG_NVIC, "Usage: is irq_n Priority");
    }
    return res;
}

bool nvic_enable_irq_command(int32_t argc, char* argv[]) {
    bool res = false;
    int8_t irq_n = 0;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &irq_n);
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
    }

    if(res) {
        if(2 == argc) {
            res = nvic_irq_ctrl(irq_n, on_off);
        }
    } else {
        LOG_ERROR(LG_NVIC, "Usage: ien IrqN on_off");
    }
    return res;
}

static bool nvic_diag(char* key_word1, char* key_word2) {
    bool res = false;
    uint32_t handler_addr = 0;
    static const table_col_t cols[] = {
        {5, "No"},      {5, "irq"}, {3, "En"},   {12, "Base"}, {6, "Active"},
        {6, "pending"}, {6, "Pri"}, {10, "Pri"}, {18, "name"},
    };
    uint16_t num = 0;
    uint32_t PriorityGroup = NVIC_GetPriorityGrouping();
    LOG_INFO(SYS, "PriorityGroup %u", PriorityGroup);
    int16_t irq_n = 0;
    char temp_str[120];
    uint32_t Priority = 0;

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(irq_n = NonMaskableInt_IRQn; irq_n <= ((int16_t)MAX_IRQ_NUM); irq_n++) {
#ifdef HAS_CMSIS
        Priority = NVIC_GetPriority((IRQn_Type)irq_n);
        uint32_t status = NVIC_GetEnableIRQ((IRQn_Type)irq_n);
        handler_addr = NVIC_GetVector((IRQn_Type)irq_n);
#endif
        strcpy(temp_str, TSEP);
        snprintf(temp_str, sizeof(temp_str), "%s %3d " TSEP, temp_str, irq_n);
        snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str, BitToAsterisk(status));
        snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, (unsigned int)handler_addr);
#ifdef HAS_CMSIS
        snprintf(temp_str, sizeof(temp_str), "%s %1ua   " TSEP, temp_str,
                 (unsigned int)NVIC_GetActive((IRQn_Type)irq_n));
        snprintf(temp_str, sizeof(temp_str), "%s %1ud   " TSEP, temp_str,
                 (unsigned int)NVIC_GetPendingIRQ((IRQn_Type)irq_n));
#endif
        snprintf(temp_str, sizeof(temp_str), "%s %2up  " TSEP, temp_str, (unsigned int)Priority);
        snprintf(temp_str, sizeof(temp_str), "%s %10s " TSEP, temp_str, IntPriToStr(Priority));
        snprintf(temp_str, sizeof(temp_str), "%s %10s " TSEP, temp_str, NvicToStr(irq_n));
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

bool nvic_diag_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(LG_NVIC, "Usage: id keyWord");
    }
    if(true == res) {
        res = nvic_diag(keyWord1, keyWord2);
    }
    return res;
}

bool nvic_enable_command(int32_t argc, char* argv[]) {
    bool on_off = false;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
    }
    if(res) {
        res = nvic_ctrl(on_off);
    } else {
        LOG_ERROR(LG_NVIC, "Usage: ie");
    }
    return res;
}
