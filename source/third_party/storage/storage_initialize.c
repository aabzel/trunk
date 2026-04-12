#include "storage_initialize.h"

#ifdef HAS_EHAL
#include "mcal_to_ehal.h"
#endif
#include "log.h"


#ifdef HAS_EEPROM_EMULATION
#include "eeprom_emulation.h"
#endif

#ifdef HAS_EEPROM_EMULATION

bool eeprom_emulation_init(void)
{
    bool res = false ;
    EMEEP_Init();
    res = true;
    return res;
}
#endif



#ifdef HAS_MEMORY_MANAGER
#include "memory_manager.h"
#endif

#ifdef HAS_MEMORY_MANAGER

// End of memory job callback
static void MEMMAN_EndOfLoadCallBack(const U8 nEventID, const U8 nJobResult){
    LOG_INFO(MEMORY_MANAGER,"EndOfLoadID:%u,JobRes:%u",nEventID,nJobResult);
}

static void MEMMAN_EndOfStoreCallBack(const U8 nEventID, const U8 nJobResult){
    LOG_INFO(MEMORY_MANAGER,"EndOfStoreID:%u,JobRes:%u",nEventID,nJobResult);
}

bool memory_manager_init(void)
{
    bool res = false ;
    STD_RESULT ret = RESULT_NOT_OK;
    MEMMAN_Init();

    U8 eventID = 0;

    ret = MEMMAN_SetJobCallback( MEM_JOB_CALLBACK_LOAD, eventID,     MEMMAN_EndOfLoadCallBack);
    res = EHAL_RetToRes(ret);

    ret = MEMMAN_SetJobCallback( MEM_JOB_CALLBACK_STORE, eventID,     MEMMAN_EndOfStoreCallBack);
    res=EHAL_RetToRes(ret) && res;


    return res;
}
#endif




#ifdef HAS_NVRAM

bool nvram_ehal_init(void)
{
    STD_RESULT ret = NVRAM_Init();
    bool res = EHAL_RetToRes(ret);
    return res;
}
#endif

