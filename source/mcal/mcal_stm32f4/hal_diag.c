#include "hal_diag.h"

#include "log.h"

const char* HalStatusToStr(const HAL_StatusTypeDef code) {
    const char* name = "?";
    switch(code) {
        case HAL_OK:         name = "Ok!";         break;
        case HAL_ERROR:      name = "Err";         break;
        case HAL_BUSY:       name = "Busy";         break;
        case HAL_TIMEOUT:    name = "TimeOut";         break;
        default:   name = "?";      break;
    }
    return name;
}
