#include "interrupt_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "microcontroller_drv.h"
#include "shared_array.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_NVIC_DIAG
#include "nvic_diag.h"
#endif

const char* InterruptNumToStr(const int16_t int_n) {
    const char* name = "?";
    uint32_t i = 0;
    uint32_t cnt = interrupt_info_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(int_n == IntNumInfo[i].int_n) {
            name = IntNumInfo[i].name;
            break;
        }
    }
    return name;
}

bool interrupt_diag(char* key_word1, char* key_word2) {
    bool res = false;

    static const table_col_t cols[] = {
        {5, "No"},    {5, "irq"},     {17, "name"},  {5, "En"},     {12, "Base"},
        {6, "prior"}, {6, "pending"}, {9, "SubPri"}, {9, "PrePri"}, {9, "SubPri"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    // uint32_t PriorityGroup=NVIC_GetPriorityGrouping();
    int16_t irq_n = 0;
    for(irq_n = 0; irq_n <= MAX_IRQ_NUM; irq_n++) {
        uint8_t preempt_priority = 0;
        uint8_t sub_priority = 0;
        uint32_t handler_addr = 0;
        bool on_off = interrupt_is_active(irq_n);
        handler_addr = interrupt_get_isr_handler(irq_n);
        uint32_t priority1 = interrupt_get_priority1(irq_n);
        res = interrupt_get_priority(irq_n, &preempt_priority, &sub_priority);
        //  NVIC_GetPriority((IRQn_Type) irq_n, PriorityGroup, &preempt_priority, &sub_priority);
        char lText[120] = "";
        strcpy(lText, TSEP);
        snprintf(lText, sizeof(lText), "%s %3d " TSEP, lText, irq_n);
        snprintf(lText, sizeof(lText), "%s %15s " TSEP, lText, InterruptNumToStr(irq_n));
        snprintf(lText, sizeof(lText), "%s %3s " TSEP, lText, OnOffToStr(on_off));
        snprintf(lText, sizeof(lText), "%s 0x%08x " TSEP, lText, (unsigned int)handler_addr);
        snprintf(lText, sizeof(lText), "%s %4u " TSEP, lText, (unsigned int)priority1);
        snprintf(lText, sizeof(lText), "%s %2up  " TSEP, lText, (unsigned int)preempt_priority);
        snprintf(lText, sizeof(lText), "%s %5us  " TSEP, lText, (unsigned int)sub_priority);
#ifdef HAS_NVIC
        snprintf(lText, sizeof(lText), "%s %7s " TSEP, lText, IntPriToStr(preempt_priority));
        snprintf(lText, sizeof(lText), "%s %7s " TSEP, lText, IntPriToStr(sub_priority));
#endif
        res = is_contain(lText, key_word1, key_word2);
        if(res) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, lText);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    if(num) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

const char* InterruptConfigToStr(const InterruptConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sIRQ:%d,", text, Config->irq_n);
        snprintf(text, sizeof(text), "%sName:%s,", text, InterruptNumToStr(Config->irq_n));
        snprintf(text, sizeof(text), "%s%s,", text, OnOffToStr(Config->on_off));
        if(Config->on_off) {
            snprintf(text, sizeof(text), "%s,Pri:%d,", text, Config->priority);
        }
    }
    return text;
}
