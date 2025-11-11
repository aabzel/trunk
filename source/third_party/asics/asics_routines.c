#include "asics_routines.h"

#include "mcal_to_ehal.h"

#ifdef HAS_LIS3DH_EHAL_PROC
#include "lis3dh_driver.h"
#endif

#ifdef HAS_NAU8814_EHAL_PROC
#include "nau8814_driver.h"
#endif

#ifdef HAS_LIS3DH_EHAL_PROC
bool LIS3DH_EHAL_Process(void)
{
    bool res = false;
    STD_RESULT ret = LIS3DH_Process();
    res = EHAL_RetToRes(ret);
    return res;
}

bool LIS3DH_EHAL_ProcessLink(void)
{
    bool res = false;
    STD_RESULT ret = LIS3DH_ProcessLink();
    res = EHAL_RetToRes(ret);
    return res;
}


#endif

#ifdef HAS_NAU8814_EHAL_PROC
bool NAU8814_EHAL_Process(void)
{
    bool res = false ;
    STD_RESULT ret =  NAU8814_Proc();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif
