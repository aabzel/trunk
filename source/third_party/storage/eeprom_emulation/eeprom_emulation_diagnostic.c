#include "eeprom_emulation_diagnostic.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "flash_mcal.h"
#include "mcal_to_ehal.h"
#include "array_diag.h"
#include "flash_diag.h"
#include "log.h"
#include "bit_utils.h"
#include "memory_types.h"
#include "eeprom_emulation_ext.h"
#include "eeprom_emulation.h"

const char* MemJobResToStr(U8 code) {
    char* name = "?";
    switch(code) {
        case MEM_JOB_RESULT_OK: name = "Ok"; break;
        case MEM_JOB_RESULT_NOT_OK: name = "Err"; break;
        case MEM_JOB_RESULT_PENDING: name = "Pending";break;
        default: break;
    }
    return name;
}

const char* MemoryStatusToStr(U32 code) {
    static char text[80]={};
    strcpy(text,"");
    if(  CHECK_MASK(code, MEM_STATUS_READ_ERR_MASK) ){
        snprintf(text,sizeof(text),"%sReadErr,",text);
    }
    if(  CHECK_MASK(code, MEM_STATUS_WRITE_ERR_MASK) ){
        snprintf(text,sizeof(text),"%sWriteErr,",text);
    }
    if(  CHECK_MASK(code, MEM_STATUS_ERASE_ERR_MASK) ){
        snprintf(text,sizeof(text),"%sEraseErr,",text);
    }
    if(  CHECK_MASK(code, MEM_STATUS_RECOVER_WARN_MASK) ){
        snprintf(text,sizeof(text),"%sRecoverWarn,",text);
    }
    if(  CHECK_MASK(code, MEM_STATUS_WEAR_THRS_1_WARN_MASK) ){
        snprintf(text,sizeof(text),"%sWearTres1Warn,",text);
    }
    if(  CHECK_MASK(code, MEM_STATUS_WEAR_THRS_2_ERR_MASK) ){
        snprintf(text,sizeof(text),"%sWearTres1Err,",text);
    }
    return text;
}



STD_RESULT EEPROM_EMULATION_Diag(void) {
    STD_RESULT ret = RESULT_NOT_OK;

    // Returns the last emulated EEPROM job result
    U8 JobResult = EMEEP_GetJobResult();
    LOG_INFO(EEPROM_EMULATION,"JobResult:%u=[%s]",JobResult,MemJobResToStr(JobResult));

    // Returns memory status mask
    U32 MemoryStatus = EMEEP_GetMemoryStatus();
    LOG_INFO(EEPROM_EMULATION,"MemoryStatus:%u=[%s]",MemoryStatus,MemoryStatusToStr(MemoryStatus));

    bool res = true;
    res= flash_scan_diag(  EMEEP_BANK_0_START_ADDRESS,   EMEEP_BANK_0_SIZE);
    res= flash_scan_diag(  EMEEP_BANK_1_START_ADDRESS,   EMEEP_BANK_1_SIZE) && res;
    ret = MCAL_ResToEHALRet(res);
    return ret;
}

STD_RESULT EEPROM_EMULATION_Dump(U8 bankNum) {
    STD_RESULT ret = RESULT_NOT_OK;
    bool res = true;
    switch(bankNum) {
        case 0: {
            res = print_mem((uint8_t*) EMEEP_BANK_0_START_ADDRESS, EMEEP_BANK_0_SIZE, true, true, true, true);
        }break;
        case 1: {
            res = print_mem((uint8_t*) EMEEP_BANK_1_START_ADDRESS, EMEEP_BANK_1_SIZE, true, true, true, true);
        }break;
       default: break;
    }
    ret = MCAL_ResToEHALRet(res);
    return ret;
}


