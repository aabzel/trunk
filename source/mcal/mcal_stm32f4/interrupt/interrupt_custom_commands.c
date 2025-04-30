#include "interrupt_custom_commands.h"

#include <string.h>
#include <inttypes.h>
#include <stdio.h>

#include "log.h"
#include "str_utils.h"
#include "data_utils.h"
#include "convert.h"
#include "common_diag.h"
#include "interrupt_diag.h"
#include "table_utils.h"
#include "writer_config.h"
//#include "nvic_diag.h"
//#include "nvic_diag.h"
#include "sys_config.h"
#include "stm32f4xx_hal.h"

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_custom_get_command(int32_t argc, char* argv[]) {
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
    uint32_t PriorityGroup = HAL_NVIC_GetPriorityGrouping();
    LOG_INFO(SYS, "PriorityGroup %u",PriorityGroup);
    if(res){
        HAL_NVIC_GetPriority((IRQn_Type) irq_n, PriorityGroup, &PreemptPriority, &SubPriority);
        LOG_INFO(SYS, "irq_n: %d  PreemptPriority:%u SubPriority:%u",irq_n,PreemptPriority,SubPriority);        
    }else{
        LOG_ERROR(LG_NVIC, "Usage: ig IrqN");
    }
    return res;
}

bool interrupt_custom_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t PreemptPriority=0;
    uint32_t SubPriority=0;
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
        
        res = try_str2uint32(argv[1], &SubPriority);
        if(false == res) {
            LOG_ERROR(LG_NVIC, "Unable to parse SubPriority");
        }
    }
        
    if(res){
        HAL_NVIC_SetPriority((IRQn_Type) irq_n,   PreemptPriority,   SubPriority);
    }else{
        LOG_ERROR(LG_NVIC, "Usage: is irq_n PreemptPriority SubPriority");
    }
  return res;
}

bool interrupt_custom_enable_irq_command(int32_t argc, char* argv[]) {
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
            HAL_NVIC_EnableIRQ((IRQn_Type) irq_n);
        }else{
            LOG_INFO(LG_NVIC, "Ok %d %u Disable",irq_n,on_off);
            HAL_NVIC_DisableIRQ((IRQn_Type)irq_n);
        }
    }else{
        LOG_ERROR(LG_NVIC, "Usage: ien IrqN on_off");
    }
  return res;
}


bool interrupt_custom_diag_command(int32_t argc, char* argv[]) {
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
    if(res) {
        res = interrupt_diag(keyWord1, keyWord2);
    }
    return res;
}

bool interrupt_custom_enable_command(int32_t argc, char* argv[]) {
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
