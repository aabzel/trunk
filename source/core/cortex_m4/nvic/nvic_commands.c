#include "nvic_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "compiler_mcal.h"
#include "log.h"
#include "nvic_diag.h"
#include "nvic_types.h"
#include "core_driver.h"
#include "str_utils.h"
#include "microcontroller_const.h"
//#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_NVIC_COMMANDS
#error "+HAS_NVIC_COMMANDS"
#endif /*HAS_NVIC_COMMANDS*/

bool nvic_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    int8_t irq_n = 0;
    if(1 == argc) {
        res = try_str2int8(argv[0], &irq_n);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
    }
#ifdef HAS_CMSIS
    uint32_t PriorityGroup = NVIC_GetPriorityGrouping();
    LOG_INFO(SYS, "PriorityGroup %u", PriorityGroup);
#endif
    if(res) {
#ifdef HAS_CMSIS
        uint32_t Priority = 0;
        Priority = NVIC_GetPriority((IRQn_Type)irq_n);
        uint32_t vector = NVIC_GetVector((IRQn_Type)irq_n);
        LOG_INFO(SYS, "irq_n: %d Priority:%u,Vector: 0x%08x", irq_n, Priority, vector);
#endif
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
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
        res = try_str2uint32(argv[0], &Priority);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse PreemptPriority");
        }
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
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
    }

    if(res && (2 == argc)) {
        if(on_off) {
            LOG_INFO(LG_NVIC, "Ok %d %u Enable", irq_n, on_off);
#ifdef HAS_CMSIS
            NVIC_EnableIRQ((IRQn_Type)irq_n);
#endif
        } else {
            LOG_INFO(LG_NVIC, "Ok %d %u Disable", irq_n, on_off);
#ifdef HAS_CMSIS
            NVIC_DisableIRQ((IRQn_Type)irq_n);
#endif
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
        {6, "pending"}, {6, "Pri"}, {9, "Pri"}, {18, "name"},
    };
    uint16_t num = 0;
#ifdef HAS_CMSIS
    uint32_t PriorityGroup = NVIC_GetPriorityGrouping();
    LOG_INFO(SYS, "PriorityGroup %u", PriorityGroup);
#endif
    int8_t irq_n = 0;
    uint32_t Priority = 0;

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(irq_n = NON_MASKABLE_INT_IRQ_N; irq_n <= MAX_IRQ_NUM; irq_n++) {
#ifdef HAS_CMSIS
        Priority = NVIC_GetPriority((IRQn_Type)irq_n);
#endif
        char temp_str[120] = {0};
        strcpy(temp_str, TSEP);
#ifdef HAS_CMSIS
        uint32_t status = NVIC_GetEnableIRQ((IRQn_Type)irq_n);
        handler_addr = NVIC_GetVector((IRQn_Type)irq_n);
#endif
        snprintf(temp_str, sizeof(temp_str), "%s %3d " TSEP, temp_str, irq_n);
#ifdef HAS_CMSIS
        snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str, Bit2Str(status));
#endif
        snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, (unsigned int)handler_addr);
#ifdef HAS_CMSIS
        snprintf(temp_str, sizeof(temp_str), "%s %1ua   " TSEP, temp_str,
                 (unsigned int)NVIC_GetActive((IRQn_Type)irq_n));
        snprintf(temp_str, sizeof(temp_str), "%s %1ud   " TSEP, temp_str,
                 (unsigned int)NVIC_GetPendingIRQ((IRQn_Type)irq_n));
#endif
        snprintf(temp_str, sizeof(temp_str), "%s %2up  " TSEP, temp_str, (unsigned int)Priority);
        snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, IntPri2Str(Priority));
        snprintf(temp_str, sizeof(temp_str), "%s %16s " TSEP, temp_str, NvicToStr(irq_n));
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
        LOG_ERROR(SYS, "Usage: id keyWord");
    }
    if(true == res) {
        res = nvic_diag(keyWord1, keyWord2);
    }
    return res;
}

bool nvic_enable_command(int32_t argc, char* argv[]) {
    bool status = false;
    bool res = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &status);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse status");
        }
    }
    if(res) {
        if(false == status) {
#ifdef HAS_CMSIS
            __disable_irq();
#endif
        } else {
#ifdef HAS_CMSIS
            __enable_irq();
#endif
        }
    } else {
        LOG_ERROR(LG_NVIC, "Usage: ie");
    }
    return res;
}
