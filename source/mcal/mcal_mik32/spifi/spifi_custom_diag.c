#include "spifi_custom_diag.h"

#include "storage_const.h"
#include "mcu32_memory_map.h"
#include "debugger.h"
#include "mcal_types.h"
#include "array.h"


const char* SpiFiCacheEnToStr(const SpiFiCacheEn_t cache_en){
    const char* name = "?";
    switch(cache_en) {
    case SPIFI_CACHE_DISABLE:
        name = "Off";
        break;
    case SPIFI_CACHE_ENABLE:
        name = "On";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

/* see Table 103 – List of SPIFI controller registers */
static const Reg32_t SpiFiRegs[]={
    {.num=1, .access=ACCESS_READ_WRITE, .name="CTRL", .offset=0x0, .valid=true, },
    {.num=2, .access=ACCESS_READ_WRITE, .name="CMD", .offset=0x4, .valid=true, },
    {.num=3, .access=ACCESS_READ_WRITE, .name="ADDR", .offset=0x8, .valid=true, },
    {.num=4, .access=ACCESS_READ_WRITE, .name="IDATA", .offset=0xC, .valid=true, },
    {.num=5, .access=ACCESS_READ_WRITE, .name="CLIMIT", .offset=0x10, .valid=true, },
    {.num=7, .access=ACCESS_READ_WRITE, .name="MCMD", .offset=0x18, .valid=true, },
    {.num=8, .access=ACCESS_READ_WRITE, .name="STAT", .offset=0x1C, .valid=true, },
    {.num=6, .access=ACCESS_READ_WRITE, .name="DATA", .offset=0x14, .valid=true, }, /*Hang On wher read*/
};


bool SpiFiDiagRegCtrl(const SpiFiRegCtrl_t *const Reg) {
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "CTRL:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "cshigh:%u", Reg->cshigh);
        LOG_INFO(SPIFI, "cache_en:%u=%s", Reg->cache_en, SpiFiCacheEnToStr(Reg->cache_en));
        LOG_INFO(SPIFI, "d_cache_dis:%u", Reg->d_cache_dis);
        LOG_INFO(SPIFI, "inten:%u", Reg->inten);
        LOG_INFO(SPIFI, "mode3:%u", Reg->mode3);
        LOG_INFO(SPIFI, "sck_div:%u", Reg->sck_div);
        LOG_INFO(SPIFI, "prftch_dis:%u", Reg->prftch_dis);
        LOG_INFO(SPIFI, "cshigh:%u", Reg->cshigh);
        LOG_INFO(SPIFI, "dual:%u", Reg->dual);
        LOG_INFO(SPIFI, "dmaen:%u", Reg->dmaen);
        LOG_INFO(SPIFI, "fbclk:%u", Reg->fbclk);
        LOG_INFO(SPIFI, "rfclk:%u", Reg->rfclk);
        res = true;
    }
    return res;
}



bool SpiFiDiagRegCmd(const SpiFiRegCmd_t *const Reg) {
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "CMD:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "datalen:%u", Reg->datalen);
        LOG_INFO(SPIFI, "poll:%u", Reg->poll);
        LOG_INFO(SPIFI, "dout:%u", Reg->dout);
        LOG_INFO(SPIFI, "intlen:%u", Reg->intlen);
        LOG_INFO(SPIFI, "fieldform:%u", Reg->fieldform);
        LOG_INFO(SPIFI, "frameform:%u", Reg->frameform);
        LOG_INFO(SPIFI, "opcode:%u", Reg->opcode);
        res = true;
    }
    return res;
}

bool SpiFiDiagRegAddress(const SpiFiRegAddress_t *const Reg){
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "ADDRESS:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "address:%u", Reg->address);
        res = true;
    }
    return res;
}


bool SpiFiDiagRegIdata(const SpiFiRegIdata_t *const Reg){
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "IDATA:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "idata:%u", Reg->idata);
        res = true;
    }
    return res;
}

bool SpiFiDiagRegClimit(const SpiFiRegClimit_t *const Reg){
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "CLIMIT:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "climit:%u", Reg->climit);
        res = true;
    }
    return res;
}

bool SpiFiDiagRegData(const SpiFiRegData_t *const Reg) {
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "DATA:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "data32:%u", Reg->data32);
        res = true;
    }
    return res;
}



bool SpiFiDiagRegMcmd(const SpiFiRegMcmd_t *const Reg){
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "MCMD:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "poll:%u", Reg->poll);
        LOG_INFO(SPIFI, "dout:%u", Reg->dout);
        LOG_INFO(SPIFI, "intlen:%u", Reg->intlen);
        LOG_INFO(SPIFI, "fieldform:%u", Reg->fieldform);
        LOG_INFO(SPIFI, "frameform:%u", Reg->frameform);
        LOG_INFO(SPIFI, "opcode:%u", Reg->opcode);
        res = true;
    }
    return res;
}


bool SpiFiDiagRegStat(const SpiFiRegStat_t *const Reg){
    bool res = false;
    if (Reg) {
        LOG_WARNING(SPIFI, "STAT:0x%08x", Reg->dword);
        LOG_INFO(SPIFI, "mcinit:%u", Reg->mcinit);
        LOG_INFO(SPIFI, "cmd:%u", Reg->cmd);
        LOG_INFO(SPIFI, "reset:%u", Reg->reset);
        LOG_INFO(SPIFI, "intrq:%u", Reg->intrq);
        LOG_INFO(SPIFI, "version:%u", Reg->version);
        res = true;
    }
    return res;
}


bool spifi_diag_low_level(void) {
    bool res = false;
    SpiFiRegCtrl_t RegCtrl={0};
    RegCtrl.dword = SPIFI_CONFIG->CTRL.dword;
    SpiFiDiagRegCtrl(&RegCtrl);

    SpiFiRegCmd_t RegCmd={0};
    RegCmd.dword = SPIFI_CONFIG->CMD.dword;
    SpiFiDiagRegCmd(&RegCmd);

    SpiFiRegAddress_t RegAddress={0};
    RegAddress.dword = SPIFI_CONFIG->ADDR;
    res=SpiFiDiagRegAddress(&RegAddress);

    SpiFiRegIdata_t RegIdata = {0};
    RegIdata.dword = SPIFI_CONFIG->IDATA;
    res = SpiFiDiagRegIdata(&RegIdata);

    SpiFiRegClimit_t RegClimit = {0};
    RegClimit.dword = SPIFI_CONFIG->IDATA;
    res = SpiFiDiagRegClimit(&RegClimit);

    SpiFiRegMcmd_t RegMcmd={0};
    RegClimit.dword = SPIFI_CONFIG->MCMD;
    SpiFiDiagRegMcmd(&RegMcmd);

    SpiFiRegStat_t RegStat={0};
    RegClimit.dword = SPIFI_CONFIG->STAT.dword;
    SpiFiDiagRegStat(&RegStat);
#if 0
    SpiFiRegData_t RegData={0};
    RegClimit.dword = SPIFI_CONFIG->DATA;
    SpiFiDiagRegData(&RegData );
#endif

    return res;
}





bool spifi_custom_diag(void) {
    bool res = false ;
    res=spifi_diag_low_level();
    return res;
}

bool spifi_raw_reg(void) {
    bool res = false;
    uint32_t cnt  = ARRAY_SIZE(SpiFiRegs);
    res = debug_raw_reg_diag(LG_INT, SPIFI_CONFIG_BASE_ADDRESS, SpiFiRegs, cnt );
    return res;
}

