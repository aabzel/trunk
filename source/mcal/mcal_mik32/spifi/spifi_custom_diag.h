#ifndef SPIFI_CUSTOM_DIAG_H
#define SPIFI_CUSTOM_DIAG_H

#include "std_includes.h"
#include "spifi_custom_types.h"
#include "spifi.h"

bool spifi_raw_reg(void);
bool spifi_custom_diag(void);
bool spifi_diag_low_level(void);

const char* SpiFiCacheEnToStr(const SpiFiCacheEn_t cache_en);

bool SpiFiDiagRegAddress(const SpiFiRegAddress_t *const Reg);
bool SpiFiDiagRegCmd(const SpiFiRegCmd_t *const Reg);
bool SpiFiDiagRegCtrl(const SpiFiRegCtrl_t *const Reg) ;
bool SpiFiDiagRegIdata(const SpiFiRegIdata_t *const Reg);
bool SpiFiDiagRegClimit(const SpiFiRegClimit_t *const Reg);
bool SpiFiDiagRegData(const SpiFiRegData_t *const Reg);
bool SpiFiDiagRegMcmd(const SpiFiRegMcmd_t *const Reg);
bool SpiFiDiagRegStat(const SpiFiRegStat_t *const Reg);

#endif /* SPIFI_CUSTOM_DIAG_H */







