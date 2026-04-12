#include "nvram_set_drv.h"

#include <string.h>

#include "nvram_drv.h"
#include "nvram_diagnostic.h"
#include "general_types.h"
#include "eeprom_emulation.h"
#include "eeprom_emulation_ext.h"
#include "log.h"

STD_RESULT NVRAM_Set(const NVRAM_DATA_ID id,
		             const void *const wrData) {
    STD_RESULT ret = RESULT_NOT_OK;
    const NVRAM_INFO *Info = NVRAM_GetVariableInfo(id);
    if (Info) {
        if (Info->len) {
            if (wrData) {
                ret = EMEEP_Store((U32) Info->eepromAddress, (U8*) wrData, (U32) Info->len);
            }
        }
    }
    return ret;
}


STD_RESULT NVRAM_Invalidate(NVRAM_DATA_ID id) {
    STD_RESULT ret = RESULT_NOT_OK;
    const NVRAM_INFO *Info = NVRAM_GetVariableInfo(id);
    if (Info) {
        LOG_WARNING(NVRAM, "InValidate:%s", NVRAM_IdToStr(id));
        ret = EMEEP_Erase(Info->eepromAddress, Info->len);
    }
    return ret;
}

STD_RESULT NVRAM_SetLazy(NVRAM_DATA_ID id, const void *const rwData) {
    STD_RESULT ret = RESULT_NOT_OK;
    const NVRAM_INFO *Info = NVRAM_GetVariableInfo(id);
    if (Info) {
        U8 readData[128] = { 0 };
        ret = NVRAM_Get(id, readData);
        if (Info->len < sizeof(readData)) {
            int mret = memcmp(rwData, readData, Info->len);
            if (0 == mret) {
                LOG_INFO(NVRAM, "ID%u AlreadyTheSame", id);
                ret = RESULT_OK;
            } else {
                ret = RESULT_NOT_OK;
            }
        } else {
            LOG_ERROR(NVRAM, "TooBigNvram");
        }
        if (false == ret) {
            ret = NVRAM_Set(id, rwData);
        }
    }

    return ret;
}
