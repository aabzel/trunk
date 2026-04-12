#include "storage_routines.h"

#include "mcal_to_ehal.h"

#ifdef HAS_MEMORY_MANAGER_EHAL_PROC
#include "memory_manager.h"
#endif


#ifdef HAS_MEMORY_MANAGER_EHAL_PROC
bool MEMORY_MANAGER_EHAL_Process(void)
{
    bool res = false;
    STD_RESULT ret = MEMORY_MANAGER_Process();
    res = EHAL_RetToRes(ret);
    return res;
}


#endif
