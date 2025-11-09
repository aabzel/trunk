#include "sensitivity_initialize.h"

#include "mcal_to_ehal.h"

#ifdef HAS_ACCEL
#include "accelerometer.h"
#endif


#ifdef HAS_ACCEL
bool ACCELEROMETER_init(void)
{
    bool res = false ;
    STD_RESULT ret = ACCEL_Init();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif
