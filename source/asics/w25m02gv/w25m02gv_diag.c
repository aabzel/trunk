#include "w25m02gv_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "interfaces_diag.h"
#include "num_to_str.h"
#include "convert.h"
#include "gpio_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "w25m02gv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"


const char* W25m02gvJedecInfoToStr(const JedecInfo_t* const JedecInfo) {
    static char name[80]="";
    if(JedecInfo){
        strcpy(name,"");
        snprintf(name,sizeof(name),"%sMfrID:0x%02x,",name,JedecInfo->mfr_id);
        snprintf(name,sizeof(name),"%sDevID:0x%04x",name,JedecInfo->device_id);
    }
    return name;
}

const char* W25m02gvConfigToStr(const W25m02gvConfig_t* const Config){
    static char name[80]="";
    if(Config){
        strcpy(name,"");
        snprintf(name,sizeof(name),"%sN:%u,",name,Config->num);
        snprintf(name,sizeof(name),"%sSPI%u,",name,Config->spi_num);
        snprintf(name,sizeof(name),"%sCS:%s,",name,GpioPadToStr(Config->ChipSelect));
        snprintf(name,sizeof(name),"%sWP:%s,",name,GpioPadToStr(Config->WriteProtect));
        snprintf(name,sizeof(name),"%sHold:%s",name,GpioPadToStr(Config->Hold));
    }
    return name;
}

const char* W25m02gvNodeToStr(const W25m02gvHandle_t* const Node){
    static char name[150]="";
    if(Node){
        strcpy(name,"");
        snprintf(name,sizeof(name),"%sN:%u,",name,Node->num);
        snprintf(name,sizeof(name),"%sSPI%u,",name,Node->spi_num);
    }
    return name;
}

//7.1 Protection Register / Status Register-1 (Volatile Writable, OTP lockable)
static bool W25m02gvDiagReg_protect(const w25m02gvRegProtection_t* const Reg) {
    bool res = false;
    if(Reg) {
       LOG_WARNING(W25M02GV,"Byte:0x%02x", Reg->byte);
       w25m02gvStatusRegisterProtect_t SRP;
       SRP.byte=0;
       SRP.srp0=Reg->srp0;
       SRP.srp1=Reg->srp1;
       LOG_INFO(W25M02GV,"BP:%u", Reg->block_prot);
       LOG_INFO(W25M02GV,"TB:%u", Reg->top_buttom_prot_bit);
       LOG_INFO(W25M02GV,"WPE-E:%u", Reg->write_enable_bit);
       LOG_INFO(W25M02GV,"SRP:%u", SRP.byte);
       res = true;
    }
    return res;
}

//Configuration Register / Status Register-2 (Volatile Writable)
static bool W25m02gvDiagReg_configure(const w25m02gvRegConfiguration_t* const  Reg) {
    bool res = false;
    if(Reg) {
       LOG_WARNING(W25M02GV,"Byte:0x%02x", Reg->byte);
       LOG_INFO(W25M02GV,"BUF:%u", Reg->buffer_mode);
       LOG_INFO(W25M02GV,"ECC-E:%u", Reg->enable_ecc);
       LOG_INFO(W25M02GV,"SR1-L:%u", Reg->status_reg1_lock);
       LOG_INFO(W25M02GV,"OTP-E:%u", Reg->enter_otp_mode);
       LOG_INFO(W25M02GV,"OTP-L:%u", Reg->otp_data_pages_lock);
       res = true;
    }
    return res;
}

//Status Register-3 (Status Only)
static bool W25m02gvDiagReg_status(const w25m02gvRegStatus_t* const Reg) {
    bool res = false;
    if(Reg) {
    	LOG_WARNING(W25M02GV,"Byte:0x%02x", Reg->byte);
        LOG_INFO(W25M02GV,"Busy:%u", Reg->busy);
        LOG_INFO(W25M02GV,"WriteEnableLatch:%u", Reg->write_enable_latch);
        LOG_INFO(W25M02GV,"EraseFail:%u", Reg->erase_failure);
        LOG_INFO(W25M02GV,"ProgFail:%u", Reg->program_failire);
        LOG_INFO(W25M02GV,"ECC:%u", Reg->ecc_status);
        LOG_INFO(W25M02GV,"BBM_LUT_FULL:%u", Reg->bbm_lut_full);
        res = true;
    }
    return res;
}

bool w25m02gv_diag_low_level(uint8_t num, const char* const key_word) {
    bool res = false;
    uint32_t cnt = 0;
    LOG_INFO(W25M02GV, "LowLevelDiag KeyWord [%s]", key_word);
    W25m02gvRegUniversal_t Reg = {0};

    Reg.byte=0;
    res = w25m02gv_register_read(num, W25M02GV_REG_PROTECTION, &Reg);
    if(res) {
        cnt++;
        res=W25m02gvDiagReg_protect(&Reg.Protect);
    }

    Reg.byte = 0;
    res = w25m02gv_register_read(num, W25M02GV_REG_CONFIGURATION, &Reg);
    if(res) {
        cnt++;
        res=W25m02gvDiagReg_configure(&Reg.Configuration);
    }

    Reg.byte = 0;
    res = w25m02gv_register_read(num, W25M02GV_REG_STATUS, &Reg);
    if(res) {
        cnt++;
        res=W25m02gvDiagReg_status(&Reg.Status);
    }

    if (3 == cnt) {
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


bool w25m02gv_reg_hazy(uint8_t num) {
    bool res = false;
    LOG_INFO(W25M02GV,"HazyRegs");
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
        res = w25m02gv_is_valid_addr(some_addr);
        if(false == res) {
            W25m02gvRegUniversal_t Reg ={ 0};
            res = w25m02gv_register_read(num, some_addr, &Reg);
            if(res) {
                if(Reg.byte){
                    strcpy(text, TSEP);
                    snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, Reg.byte);
                    snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(Reg.byte));
                    snprintf(text, sizeof(text), "%s %4s " TSEP, text, ValU8ToStar(Reg.byte));
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


bool w25m02gv_reg_map_diag(uint8_t num, char* key_word, char* key_word2) {
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
        const W25m02gvRegInfo_t*  Info=W25m02gvRegAddrToInfo(addr);
        if(Info){
            W25m02gvRegUniversal_t value= {0};
            res= w25m02gv_register_read(num, addr, &value);
            if(res){
                strcpy(text, TSEP);
                cli_printf(TSEP " %3u ", cnt);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value.byte);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value.byte));
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

bool w25m02gv_reg_map_hidden_diag(uint8_t num) {
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
        res = w25m02gv_is_valid_addr(some_addr);
        if(false == res) {
            W25m02gvRegUniversal_t Reg = {0};
            res = w25m02gv_register_read(num, some_addr, &Reg);
            if(res) {
                strcpy(text, TSEP);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, Reg.byte);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(Reg.byte));
                cli_printf(TSEP " %3u ", cnt);
                cli_printf("%s" CRLF, text);
                cnt++;

            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool w25m02gv_diag_high_level(uint8_t num ) {
    bool res = false;
    LOG_INFO(W25M02GV, "DiagHighLevel");
    res = w25m02gv_is_connected(num);
    if(res) {
        LOG_INFO(W25M02GV, "Connected %s", OnOffToStr(res));
           const W25m02gvConfig_t* Config=W25m02gvGetConfig(num);
           if(Config){
               LOG_INFO(W25M02GV, "%s", W25m02gvConfigToStr(Config));
           }
        W25m02gvHandle_t* Node=W25m02gvGetNode(num);
        if(Node){
            LOG_INFO(W25M02GV, "%s",W25m02gvNodeToStr(Node));
        }

    }

    return res;
}

const char* W25m02gvRegAddrToName(W25m02gvRegAddr_t addr) {
    const char* name = "?";
    const W25m02gvRegInfo_t* Info = W25m02gvRegAddrToInfo(addr);
    if(Info) {
        name = Info->name;
    }
    return name;
}

bool W25m02gvDiagReg(W25m02gvRegAddr_t reg_addr, const W25m02gvRegUniversal_t* const Reg) {
    bool res = false;
    switch(reg_addr) {
        case W25M02GV_REG_PROTECTION: res = W25m02gvDiagReg_protect(&Reg->Protect); break;
        case W25M02GV_REG_CONFIGURATION: res = W25m02gvDiagReg_configure(&Reg->Configuration); break;
        case W25M02GV_REG_STATUS: res = W25m02gvDiagReg_status(&Reg->Status); break;
        default: break;
    }
    return res;
}

