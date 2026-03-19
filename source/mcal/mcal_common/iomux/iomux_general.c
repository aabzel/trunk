#include "iomux_mcal.h"

#include "log.h"

__attribute__((weak)) bool iomux_mcal_init(void) {
    bool res = false;
    LOG_ERROR(IO_MUX, "NotImpl,%s", __FUNCTION__);
    return res;
}
