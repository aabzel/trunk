#include "interrupt_commands.h"

#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include "log.h"
#include "str_utils.h"
#include "data_utils.h"
#include "convert.h"
#include "common_diag.h"
#include "table_utils.h"
#include "nvic_diag.h"
#include "interrupt_diag.h"
#include "writer_config.h"
#include "nvic_diag.h"
#include "sys_config.h"
#include "at32f435_437.h"

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t PreemptPriority=0;
    uint32_t SubPriority=0;
    int8_t irq_n=0;
    if(1==argc){
        res = try_str2int8(argv[0], &irq_n);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
    }
    uint32_t PriorityGroup = NVIC_GetPriorityGrouping();
    LOG_INFO(SYS, "PriorityGroup %u",PriorityGroup);
    if(res){
       // NVIC_GetPriority((IRQn_Type) irq_n, PriorityGroup, &PreemptPriority, &SubPriority);
        LOG_INFO(SYS, "irq_n: %d  PreemptPriority:%u SubPriority:%u",irq_n,PreemptPriority,SubPriority);        
    }else{
        LOG_ERROR(LG_NVIC, "Usage: ig IrqN");
    }
    return res;
}

bool interrupt_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t PreemptPriority=0;
    int8_t irq_n=0;
    if(3==argc){
        res = try_str2int8(argv[0], &irq_n);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
        res = try_str2uint32(argv[0], &PreemptPriority);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse PreemptPriority");
        }
        

    }
        
    if(res){
        NVIC_SetPriority((IRQn_Type) irq_n,   PreemptPriority);
    }else{
        LOG_ERROR(LG_NVIC, "Usage: is irq_n PreemptPriority SubPriority");
    }
  return res;
}

bool interrupt_enable_irq_command(int32_t argc, char* argv[]) {
    bool res = false;
    int8_t irq_n=0;
    bool on_off = false;
    if(1<=argc){
        res = try_str2int8(argv[0], &irq_n);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
    }
    if(2<=argc){
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse IrqN");
        }
    }

    if(res && (2==argc)){
        if(on_off){
            LOG_INFO(LG_NVIC, "Ok %d %u Enable",irq_n,on_off);
            NVIC_EnableIRQ((IRQn_Type) irq_n);
        }else{
            LOG_INFO(LG_NVIC, "Ok %d %u Disable",irq_n,on_off);
            NVIC_DisableIRQ((IRQn_Type)irq_n);
        }
    }else{
        LOG_ERROR(LG_NVIC, "Usage: ien IrqN on_off");
    }
  return res;
}


static bool interrupt_diag(char* key_word1, char* key_word2) {
    bool res = false;

    uint32_t handler_addr=0;
    static const table_col_t cols[] = {
        {5, "No"},  
        {5, "irq"},
        {3, "En"},
        {12, "Base"},
        {6, "Active"},   
        {6, "pending"},  
        {6, "PrePri"},    
        {6, "SubPri"},  
        {9, "PrePri"},    
        {9, "SubPri"},  
#ifdef HAS_INTERRUPT_DIAG
        {18, "name"},
#endif
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    int8_t irq_n = 0;
    char temp_str[120]="";
    //uint32_t PriorityGroup=NVIC_GetPriorityGrouping();
    uint32_t PreemptPriority = 0;
    uint32_t SubPriority = 0;
    for(irq_n = NonMaskableInt_IRQn; irq_n <= MAX_IRQ_NUM; irq_n++) {
          //  NVIC_GetPriority((IRQn_Type) irq_n, PriorityGroup, &PreemptPriority, &SubPriority);
            strcpy(temp_str, TSEP);
            uint32_t status=NVIC_GetEnableIRQ((IRQn_Type)irq_n);
            handler_addr = NVIC_GetVector((IRQn_Type) irq_n);
            snprintf(temp_str, sizeof(temp_str), "%s %3d " TSEP, temp_str,  irq_n);
            snprintf(temp_str, sizeof(temp_str), "%s %1s " TSEP, temp_str,  Bit2Str(status));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, (unsigned int) handler_addr);
            snprintf(temp_str, sizeof(temp_str), "%s %1ua   " TSEP, temp_str, (unsigned int)NVIC_GetActive((IRQn_Type) irq_n));
            snprintf(temp_str, sizeof(temp_str), "%s %1ud   " TSEP, temp_str, (unsigned int)NVIC_GetPendingIRQ((IRQn_Type) irq_n));
            snprintf(temp_str, sizeof(temp_str), "%s %2up  " TSEP, temp_str, (unsigned int)PreemptPriority);
            snprintf(temp_str, sizeof(temp_str), "%s %2us  " TSEP, temp_str, (unsigned int) SubPriority);
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str,IntPri2Str(PreemptPriority));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str,IntPri2Str(SubPriority));
#ifdef HAS_INTERRUPT_DIAG
            snprintf(temp_str, sizeof(temp_str), "%s %15s " TSEP, temp_str,interrupt2Str(irq_n));
#endif
            if(is_contain(temp_str, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s"CRLF, temp_str);
                num++;
                res = true;
            } 
        
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

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
        res = interrupt_diag(keyWord1, keyWord2);
    }
    return res;
}

bool interrupt_enable_command(int32_t argc, char* argv[]) {
    bool status = false;
    bool res = false;
    if(1==argc){
        res = try_str2bool(argv[0], &status);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse status");
        }
    }
    if(res){
        if(false==status){
            __disable_irq();
            
        }else{
            __enable_irq();
        }
    }else{
        LOG_ERROR(SYS, "Usage: ie");
    }
    return res;
}
