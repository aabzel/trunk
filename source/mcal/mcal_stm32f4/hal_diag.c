#include "hal_diag.h"

#include "log.h"

const char* HalStatus2Str(HAL_StatusTypeDef code) {
    const char* name = "?";
    switch(code) {
    case HAL_OK:
        name = "Ok!";
        break;
    case HAL_ERROR:
        name = "Err";
        break;
    case HAL_BUSY:
        name = "Busy";
        break;
    case HAL_TIMEOUT:
        name = "TimeOut";
        break;
    default:
        break;
    }
    return name;
}
