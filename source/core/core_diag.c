#include "core_diag.h"

#include "array_diag.h"
#include "core_const.h"
#include "core_driver.h"
#include "debug_info.h"
#include "flash_config.h"
#include "float_diag.h"
#include "log.h"
#include "rational_num_diag.h"

extern int main(void);

const char* CortexFpuTypeToStr(const CortexFpu_t fpu_type) {
    char* name = "?";
    switch(fpu_type) {
    case ARM_CORTEX_FPU_NO:
        name = "NoFPU";
        break;
    case ARM_CORTEX_FPU_PRECISION_SINGLE:
        name = "FpuPrecSingle";
        break;
    case ARM_CORTEX_FPU_PRECISION_DOUBLE_SINGLE:
        name = "FpuPrecDoubleSingle";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

extern uint8_t __HeapBegin;
extern uint8_t __Core0_StackTop;
extern uint8_t __Core0_StackLimit;
extern uint8_t _end;

bool core_diag_stack_mem(void) {
    bool res = false;
    LOG_INFO(CORE, "__Core0_StackLimit:%08p", &__Core0_StackLimit);
    LOG_INFO(CORE, "  __Core0_StackTop:%08p", &__Core0_StackTop);
    uint32_t stack_size = &__Core0_StackLimit - &__Core0_StackTop;
    FloatFixPoint_t stack_used = core_stack_used((uint32_t)&__Core0_StackTop, stack_size);
    LOG_INFO(CORE, "StackUsed:%s", FloatFixToStr(&stack_used));
    if(stack_used.fractional < 100) {
        res = true;
    }
    return res;
}

bool core_diag(void) {
    bool res = false;
#if 0
    uint32_t offset_size = cortex_offset_size_get(RAM_START);
    LOG_INFO(CORE, "OffsetSize:%u", offset_size);
    print_sys_info();
    cli_printf("        _end:0x%08p" CRLF, &_end);
    uint32_t fpu_type = SCB_GetFPUType();
    LOG_INFO(CORE, "%s", CortexFpuTypeToStr(fpu_type));
    LOG_INFO(CORE, "Cnt:%u", cnt);
    cli_printf("        main: 0x%08p" CRLF, main);
#endif
    static const table_col_t cols[] = {
        {5, "Num"},  {7, "name"}, {12, "stack_top"},  {12, "stack_limit"},
        {7, "Size"}, {6, "init"}, {10, "stack_used"}, {6, "spin"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t cnt = core_get_cnt();
    uint8_t i = 0;
    for(i = 0; i <= cnt; i++) {
        CoreHandle_t* Node = CoreGetNode(i);
        if(Node) {
            uint32_t size = Node->stack_top - Node->stack_limit;
            char line_str[200] = {0};
            strcpy(line_str, TSEP);
            sprintf(line_str, "%s %3u " TSEP, line_str, Node->num);
            sprintf(line_str, "%s %5s " TSEP, line_str, Node->name);
            sprintf(line_str, "%s 0x%08X " TSEP, line_str, Node->stack_top);
            sprintf(line_str, "%s 0x%08X " TSEP, line_str, Node->stack_limit);
            sprintf(line_str, "%10s %5u " TSEP, line_str, size);
            sprintf(line_str, "%s %4u " TSEP, line_str, Node->init);
            sprintf(line_str, "%s %8s " TSEP, line_str, FloatFixToStr(&Node->stack_used));
            sprintf(line_str, "%s %4u " TSEP, line_str, Node->spin);

            cli_printf("%s" CRLF, line_str);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool core_diag_stack_usage(const uint8_t num, const FloatFixPoint_t* stack_used) {
    bool res = false;
    if(80 < stack_used->integer) {
        LOG_ERROR(CORE, "CORE%u,StackUsed80%%+:%s", num, FloatFixToStr(stack_used));
        res = false;
    } else {
        if(70 < stack_used->integer) {
            LOG_WARNING(CORE, "CORE%u,StackUsed,70%%+:%s", num, FloatFixToStr(stack_used));
            res = false;
        } else {
            res = true;
        }
    }
    return res;
}

const char* CoreConfigToStr(const CoreConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sStackTop:0x%x,", text, Config->stack_top);
        snprintf(text, sizeof(text), "%sStackLim:0x%x,", text, Config->stack_limit);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* CoreNodeToStr(const CoreHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sStackUsed:%f,", text, Node->stack_used);
        snprintf(text, sizeof(text), "%sStackUsed:%s,", text, FloatFixToStr(&Node->stack_used));
    }
    return text;
}

bool core_stack_print(const uint8_t num) {
    bool res = false;
    CoreHandle_t* Node = CoreGetNode(num);
    if(Node) {
        uint32_t stack_size_dword = (Node->stack_top - Node->stack_limit) / 4;
        LOG_INFO(CORE, "Core%u,StackLimit:0x%08x,Size:%u dWords", num, Node->stack_limit, stack_size_dword);
        uint32_t* array = (uint32_t*)Node->stack_limit;
        res = array_u32_print(array, stack_size_dword);
    }
    return res;
}

bool print_vector_table(const uint32_t vectors_table_base) {
    uint32_t* addres = 0;
    LOG_WARNING(SYS, "VectorsTableBase:0x%08x", vectors_table_base);
    uint32_t offset = 0, num = 0;
    for(offset = 0, num = 0; offset <= 4 * 53; offset += 4, num++) {
        addres = (uint32_t*)(vectors_table_base + offset);
        cli_printf("number:%2u,Addr:0x%08p,Handler:0x%08x" CRLF, num, addres, *(addres));
    }
    return true;
}
