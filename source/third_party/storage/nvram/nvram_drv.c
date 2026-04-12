//**************************************************************************************************
// @Module  NVRAM
//! \file   nvram_drv.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_NVRAM
//! \brief  Implementation of the NVRAM functionality.
//!             [text]
//! \par    Abbreviations
//!             NVRAM -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.2025 |  1.1.0  |   AAB   | Last  release.
//! | XX.XX.2025 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

//**************************************************************************************************
//! \defgroup   NVRAM Name of Module
//! \brief      Short description of Module
//! \addtogroup NVRAM
//! @{
//! \file nvram_drv.c
//! \file nvram_drv.h
//! \file module_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************


#include "nvram_drv.h"

//#include <inttypes.h>
#include <string.h>

#include "convert.h"
#include "log.h"
#include "interval.h"
#include "nvram_set_drv.h"
#include "nvram_configuration.h"
#include "nvram_diagnostic.h"
#include "storage_diagnostic.h"
#include "eeprom_emulation_ext.h"
#include "eeprom_emulation.h"

//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************


//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************


//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

static STD_RESULT NVRAM_IsEepromAddrUniq(const NVRAM_INFO* const  Info);

static STD_RESULT NVRAM_IsIdUniq(const NVRAM_DATA_ID id);

static STD_RESULT NVRAM_SetDefaultValue(const NVRAM_INFO* const  Info);

//**************************************************************************************************
//! Get NVRAM variable info
//!
//! \note       None
//!
//! \param[in]  nvramId - NVRAM ID
//!
//! \return     NVRAM variable info
//**************************************************************************************************
const NVRAM_INFO* NVRAM_GetVariableInfo(const U32 nvramId) {
    const NVRAM_INFO *Info = NULL_PTR;
    U32 cnt = NVRAM_GetCnt();
    U16 i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (nvramId == ((U32)NvramArray[i].id))
        {
            Info = &NvramArray[i];
            break;
        }
    }
    return Info;
} // end of MODULE_FunctionTwo()

//**************************************************************************************************
//! [Description of NVRAM_FunctionZero]
//!
//! \note       None
//!
//! \param[in]  typeId - [description of parameterZero]
//!
//! \return     [Description of return value]
//**************************************************************************************************
U16 NVRAM_GetTypeLen(STORAGE_TYPE typeId) {
    U16 len = 0;
    STORAGE_INFO *Info = STORAGE_GetInfo(typeId);
    if (Info) {
        len = Info->typeSize;
    } else {
        LOG_ERROR(NVRAM, "UndefTypeID:%u=%s", typeId, STORAGE_TypeToStr(typeId));
    }

    return len;
}

//**************************************************************************************************
//! [Description of NVRAM_FunctionZero]
//!
//! \note       None
//!
//! \param[in]  nvramId - NVRAM ID
//!
//! \return     [Description of return value]
//**************************************************************************************************
U32 NVRAM_GetLen(NVRAM_DATA_ID nvramId) {
    U16 len = 0;
    const NVRAM_INFO *Info = NVRAM_GetVariableInfo(nvramId);
    if (Info) {
        len = Info->len;
    } else {
        LOG_ERROR(NVRAM, "UndefID %u", nvramId);
    }
    return len;
} // end of MODULE_FunctionTwo()

//**************************************************************************************************
//! [Description of NVRAM_FunctionZero]
//!
//! \note       None
//!
//! \param[in]  nvramId - NVRAM ID
//!
//! \return     [Description of return value]
//**************************************************************************************************
STORAGE_TYPE NVRAM_GetType(NVRAM_DATA_ID nvramId) {
    STORAGE_TYPE nvramType = TYPE_UNDEF;
    const NVRAM_INFO *Info = NVRAM_GetVariableInfo(nvramId);
    if (Info) {
        nvramType = Info->type;
    } else {
        LOG_ERROR(NVRAM, "UndefLenForParID %u", nvramId);
    }

    return nvramType;
} // end of MODULE_FunctionTwo()

//**************************************************************************************************
//! Read NVRAM variable by ID
//!
//! \note       None
//!
//! \param[in]  nvramId - NVRAM ID
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT NVRAM_Get(const NVRAM_DATA_ID nvramId,
                     void* const outData) {
    STD_RESULT ret = RESULT_NOT_OK;
    const NVRAM_INFO* Info = NVRAM_GetVariableInfo(nvramId);
    if (Info)
    {
        if (Info->len)
        {
            if (outData)
            {
                ret = EMEEP_Load(Info->eepromAddress, (U8*) outData, Info->len);
            }
        }
        else
        {
#ifdef HAS_NVRAM_DIAG
        LOG_ERROR(NVRAM, "LackId:%s", NVRAM_IdToStr(nvramId));
#endif
        }
    }
    return ret;
}


static STD_RESULT NVRAM_InitOne(U32 nvramId) {
    STD_RESULT ret = RESULT_NOT_OK;

    const NVRAM_INFO* Info = NVRAM_GetVariableInfo((NVRAM_DATA_ID) nvramId);
    if(Info)
    {
        LOG_WARNING(NVRAM, "Init:%s", NVRAM_VariableInfoToStr(Info));
        ret = NVRAM_IsIdUniq(Info->id);
        if (RESULT_OK==ret)
        {
            ret = NVRAM_IsEepromAddrUniq(Info);
            if(RESULT_OK==ret)
            {
                U8 value[512]={0};
                ret = NVRAM_Get(Info->id, value);
                if (RESULT_NOT_OK==ret)
                {
                    LOG_WARNING(NVRAM, "NoNvram:%u=%s,NVRAM", Info->id, Info->name);
                    ret = NVRAM_SetDefaultValue(Info);
                }
            } else {
                LOG_ERROR(NVRAM, "Nvram %u isNotUniqEepromAddr", Info->id);
                ret = RESULT_NOT_OK;
            }
        } else {
            LOG_ERROR(NVRAM, "Nvram %u is not uniq", Info->id);
            ret = RESULT_NOT_OK;
        }
    }

    return ret;
} // end of MODULE_FunctionTwo()


//**************************************************************************************************
//! NVRAM Init
//!
//! \note       None
//!
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
STD_RESULT NVRAM_Init(void) {
    STD_RESULT ret = RESULT_OK;
    U32 ok = 0;
    U32 cnt = NVRAM_GetCnt();
    LOG_WARNING(NVRAM, "InitCnt:%u", cnt);
    U32 i = 0;
    for (i = 0; i < 0xFFFF; i++) {
    	ret = NVRAM_InitOne(i);
    	if (RESULT_OK==ret){
    		ok++;
    	}
    }

    if (cnt==ok) {
        LOG_INFO(NVRAM, "OkCnt:%u/%u", ok, cnt);
        ret = RESULT_OK;
    } else {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of MODULE_FunctionTwo()

//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! [Description of NVRAM_FunctionZero]
//!
//! \note       None
//!
//! \param[in]  Info - [description of parameterZero]
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static STD_RESULT NVRAM_IsEepromAddrUniq(const NVRAM_INFO* const  Info) {
    bool ret = RESULT_NOT_OK;
    U32 matchCnt = 0, i = 0;
    U32 cnt = NVRAM_GetCnt();
    for (i = 0; i < cnt; i++)
    {
        IntervalE_t IntervalCurr={0};
        IntervalCurr.start = Info->eepromAddress;
        IntervalCurr.end = Info->eepromAddress + Info->len;

        IntervalE_t IntervalRun={0};
        IntervalCurr.start = NvramArray[i].eepromAddress;
        IntervalCurr.end = NvramArray[i].eepromAddress + NvramArray[i].len;
        bool res = intervals_overlaps(&IntervalCurr, &IntervalRun);
        if (res) {
            matchCnt++;
        }
    }

    if (1 == matchCnt) {
        ret = RESULT_OK;
    } else {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of MODULE_FunctionTwo()

//**************************************************************************************************
//! Check that NVRAM ID is uniq
//!
//! \note       None
//!
//! \param[in]  parameterZero - [description of parameterZero]
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static STD_RESULT NVRAM_IsIdUniq(const NVRAM_DATA_ID id) {
	STD_RESULT ret = RESULT_NOT_OK;
    U32 matchCnt = 0;
    U32 cnt = NVRAM_GetCnt();
    U32 i = 0;
    for (i = 0; i < cnt; i++)
    {
        if (id == NvramArray[i].id)
        {
            matchCnt++;
        }
    }
    if (1 == matchCnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }

    return ret;
} // end of NVRAM_IsIdUniq()

//**************************************************************************************************
//! NVRAM Set Default value
//!
//! \note       None
//!
//! \param[in]  Info - NVRAM variable info
//!
//! \return     RESULT_OK     - function succeeded,
//!             RESULT_NOT_OK - function NOT succeeded.
//**************************************************************************************************
static STD_RESULT NVRAM_SetDefaultValue(const NVRAM_INFO* const  Info)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Info->defaultValue)
    {
        U8 data[100] = { 0 };
        ret = try_str2type(Info->defaultValue,
                           Info->type,
                           data,
                           sizeof(data));
        if (ret)
        {
            LOG_WARNING(NVRAM, "Set,%s", NVRAM_VariableInfoToStr(Info));
            ret = NVRAM_Set(Info->id, data);
            if (ret)
            {
                LOG_INFO(NVRAM, "SetDfltID:%uOk", Info->id);
            }
            else
            {
                LOG_ERROR(NVRAM, "SetDfltID:%uErr", Info->id);
            }
        } // end of if (ret)
    } // end of if (Info->defaultValue)
    else
    {
        LOG_ERROR(NVRAM, "NoDef,ID:%u", Info->id);
    }
    return ret;
} // end of NVRAM_SetDefaultValue()

//****************************************** end of file *******************************************

