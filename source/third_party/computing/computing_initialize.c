#include "computing_initialize.h"

#include "mcal_to_ehal.h"

#ifdef HAS_DDS
bool DDS_init(void)
{
    bool res = false ;
    STD_RESULT ret = DDS_Init();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif



#ifdef HAS_PYRAMID_ACCEL_CALIBRATION
bool PYRAMID_ACCEL_CALIBRATION_init(void)
{
    bool res = false ;
    STD_RESULT ret = PYRAMID_ACCEL_CALIB_Init();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif

