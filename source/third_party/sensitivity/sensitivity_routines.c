#include "sensitivity_routines.h"

#include "mcal_to_ehal.h"

#ifdef HAS_ACCEL
#include "accelerometer.h"
#endif


#ifdef HAS_ACCEL_PROC
bool ACCELEROMETER_proc(void)
{
    bool res = false;
    STD_RESULT ret = ACCEL_Process();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif

