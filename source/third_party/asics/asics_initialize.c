#include "asics_initialize.h"

#include "mcal_to_ehal.h"

#ifdef HAS_LIS3DH_EHAL
#include "lis3dh_driver.h"
#endif

#ifdef HAS_NAU8814_EHAL
#include "nau8814_driver.h"
#endif

#ifdef HAS_NAU8814_EHAL

bool nau8814_init(void) {
    bool res = false ;
    STD_RESULT ret = NAU8814_Init();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif


#ifdef HAS_LIS3DH_EHAL

bool lis3dh_init(void) {
    bool res = false ;
    STD_RESULT ret = LIS3DH_Init();
    res = EHAL_RetToRes(ret);
    return res;
}
#endif
