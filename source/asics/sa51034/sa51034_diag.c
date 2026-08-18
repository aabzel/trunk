#include "sa51034_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "interfaces_diag.h"
#include "num_to_str.h"
#include "convert.h"
#include "log.h"

#include "none_blocking_pause.h"
#include "sa51034_drv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"



const char* Sa51034ConfigToStr(const Sa51034Config_t* const Config){
    static char name[80]="";
    if(Config){
        strcpy(name,"");
        snprintf(name,sizeof(name),"%sN:%u,",name,Config->num);
        snprintf(name,sizeof(name),"%sI2C:%u,",name,Config->i2c_num);
        snprintf(name,sizeof(name),"%sAddr:0x%x",name,Config->chip_addr);
    }
    return name;
}

const char* Sa51034NodeToStr(const Sa51034Handle_t* const Node){
    static char name[150]="";
    if(Node){
        strcpy(name,"");
        snprintf(name,sizeof(name),"%sN:%u,",name,Node->num);
        snprintf(name,sizeof(name),"%sI2C:%u,",name,Node->i2c_num);
        snprintf(name,sizeof(name),"%sAddr:0x%x,",name,Node->chip_addr);
    }
    return name;
}


#if 0
static const char* Sa51RegDiagToStr(Sa51034RegAddr_t addr, uint8_t value) {
    static char name[150]="";
    bool res = false;
    switch(addr) {
        case SA51034_REG_LATCHED_FAULT: res=RegLatchedFaultToStr(value,name);break;
        case SA51034_REG_STATUS_AND_LOAD_DIAGNOSTIC: res=RegStatusAndLoadDiagnosticToStr(value,name); break;
        case SA51034_REG_CONTROL: res=RegControlToStr(value,name);break;
    }
    return name;
}
#endif


bool Sa51DiagRegLatchedFault(  uint8_t  value){
    bool res = true;
    Sa51034RegLatchedFault_t Reg;
    Reg.byte=value;
    LOG_INFO(SA51034,"LoadDetectFault:%u",Reg.ld_fault);
    LOG_INFO(SA51034,"OverCurrentShtdn:%u", Reg.over_current_shutdown);
    LOG_INFO(SA51034,"pvddUnderVoltage:%u", Reg.pvdd_under_voltage);
    LOG_INFO(SA51034,"pvddOverVoltage:%u", Reg.pvdd_over_voltage);
    LOG_INFO(SA51034,"dcOffsetProtection:%u", Reg.dc_offset_protection);
    LOG_INFO(SA51034,"OverTemperatureShutdown:%u", Reg.over_temperature_shutdown);
    return res;
}

bool Sa51DiagRegStatusAndLoadDiagnostic(  uint8_t  value){
    bool res = true;
    Sa51034RegStatusAndLoadDiagnostic_t Reg ;
    Reg.byte=value;

    LOG_INFO(SA51034,"short_pvdd:%u",Reg.short_pvdd);
    LOG_INFO(SA51034,"short_gnd:%u",Reg.short_gnd);
    LOG_INFO(SA51034,"open_load:%u",Reg.open_load);
    LOG_INFO(SA51034,"shorted_load:%u",Reg.shorted_load);
    LOG_INFO(SA51034,"fault_state:%u",Reg.fault_state);
    LOG_INFO(SA51034,"run_load_detect:%u",Reg.run_load_detect);
    LOG_INFO(SA51034,"mute:%u",Reg.mute);
    LOG_INFO(SA51034,"play:%u",Reg.play);

    return res;
}

bool Sa51DiagRegControl(uint8_t value) {
    bool res = false;
    Sa51034RegControlRegister_t Reg;
    Reg.byte = value;
    LOG_INFO(SA51034,"frequency:%u=%u Hz",Reg.frequency,Sa51FrequencyCodeToHz(Reg.frequency));
    LOG_INFO(SA51034,"PowerLimit:%u=%f V",Reg.power_limit,Sa51PowerLimitCodeToVolts(Reg.power_limit));
    LOG_INFO(SA51034,"gain:%u=%d dB",Reg.gain,Sa51GainCodeToGain(Reg.gain));

    return res;
}

bool Sa51RegDiag( Sa51034RegAddr_t addr, uint8_t  value) {
    bool res = false;
    LOG_WARNING(SA51034,"Addr 0x%x=%s,Value:0x%x=%s",addr,Sa51034RegAddrToName(addr),value,utoa_bin8(value));

    switch((uint8_t)addr) {
        case SA51034_REG_LATCHED_FAULT:
        	res = Sa51DiagRegLatchedFault(value);
            break;
        case SA51034_REG_STATUS_AND_LOAD_DIAGNOSTIC:
        	res = Sa51DiagRegStatusAndLoadDiagnostic(value);
        	break;
        case SA51034_REG_CONTROL:
        	res = Sa51DiagRegControl(value);
            break;
    }
    return res;
}

bool sa51034_diag_low_level(uint8_t num,const char* const key_word) {
    bool res = false;
    uint32_t addr=0 ;
    uint32_t cnt =0;

    for(addr=0;addr<0xFF;addr++) {
        const Sa51034RegInfo_t*  Info=Sa51034RegAddrToInfo(addr);
        if(Info){
            uint8_t value= 0;
            res= sa51034_reg_read(num, addr, &value);
            if(res){
            	res= Sa51RegDiag(  addr,   value);
            	if(res){
            		cnt++;
            	}
            }
        }

    }


    if(0<cnt){
        res = true;
    }else{
        res = false ;
    }
    return res;
}

static const char* ValU8ToStar(uint8_t byte){
	const char* name="";
    if (0<byte) {
    	name = "*";
    }
    return name;
}


bool sa51034_reg_hazy(uint8_t num) {
    bool res = false;
    LOG_INFO(SA51034,"HazyRegs");
    static const table_col_t cols[] = {
        {5, "No"},
        {6, "addrD"},
        {6, "addrH"},
        {6, "val"},
        {11, "val [bin]"},
        {6, "mark"},
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0 ;
    uint32_t cnt = 0 ;
    for(i = 0; i <= 127; i++) {
        uint8_t some_addr = i;
        res = sa51034_is_valid_addr(some_addr);
        if(false == res) {
            uint8_t value = 0;
            res = sa51034_reg_read(num, some_addr, &value);
            if(res) {
            	if(value){
                    strcpy(text, TSEP);
                    snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
                    snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
                    snprintf(text, sizeof(text), "%s %4s " TSEP, text, ValU8ToStar(value));
                    cli_printf(TSEP " %3u ", cnt);
                    cli_printf("%s" CRLF, text);
                    wait_in_loop_ms(10);
                    cnt++;
            	}
            }
        }

    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));


    if(0<cnt){
        res = true;
    }else{
        res = false ;
    }
    return res;
}


bool sa51034_reg_map_diag(uint8_t num, char* key_word, char* key_word2) {
    bool res = false;
    uint32_t addr=0 ;
    uint32_t cnt =0;
    static const table_col_t cols[] = {
        {5, "No"},
        {6, "addrD"},
        {6, "addrH"},
        {6, "val"},
        {11, "val [bin]"},
        {25, "name"},
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(addr=0;addr<0xFF;addr++){
        const Sa51034RegInfo_t*  Info=Sa51034RegAddrToInfo(addr);
        if(Info){
            uint8_t value= 0;
            res= sa51034_reg_read(num, addr, &value);
            if(res){
                strcpy(text, TSEP);
                cli_printf(TSEP " %3u ", cnt);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
                snprintf(text, sizeof(text), "%s %23s " TSEP, text, Info->name);
                cli_printf("%s" CRLF, text);
                wait_in_loop_ms(10);
                cnt++;
            }
        }

    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));


    if(0<cnt){
        res = true;
    }else{
        res = false ;
    }
    return res;
}

bool sa51034_reg_map_hidden_diag(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},
        {6, "addr"},
        {6, "addr"},
        {6, "val"},
        {11, "val [bin]"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char text[120] = "";
    int32_t i = 0;
    int32_t cnt = 0;
    for(i = 0; i <= 127; i++) {
        uint8_t some_addr = i;
        res = sa51034_is_valid_addr(some_addr);
        if(false == res) {
            uint8_t value = 0;
            res = sa51034_reg_read(num, some_addr, &value);
            if(res) {
                strcpy(text, TSEP);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
                cli_printf(TSEP " %3u ", cnt);
                cli_printf("%s" CRLF, text);
                cnt++;

            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}



bool sa51034_diag_high_level(uint8_t num ) {
    bool res = false;
    LOG_INFO(SA51034, "DiagHighLevel");

    res = sa51034_is_connected(num);
    if(res) {
        LOG_INFO(SA51034, "Connected %s", OnOff2Str(res));
    	Sa51034Handle_t* Node=Sa51034GetNode(num);
    	if(Node){

    	}

    }

    return res;
}


const char* Sa51034RegAddrToName(Sa51034RegAddr_t addr){
    const char* name="?";
    const Sa51034RegInfo_t* Info = Sa51034RegAddrToInfo(addr);
    if(Info){
        name=Info->name;
    }
    return name;
}
