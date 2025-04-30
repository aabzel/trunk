#include "hal_nrfx_diag.h"

#include "nrfx_errors.h"

const char* HalStatus2Str(nrfx_err_t code){
    const char* name="?";
    switch((uint32_t)code) {
        case NRFX_ERROR_INTERNAL: name="ErrInternal";break;
        case NRFX_ERROR_DRV_TWI_ERR_ANACK: name="NoAck";break;
        case NRFX_ERROR_NO_MEM: name="NoMem";break;
        case NRFX_ERROR_INVALID_PARAM: name="InvParam";break;
        case NRFX_ERROR_INVALID_STATE: name="InvalState";break;
        case NRFX_ERROR_TIMEOUT: name="TimeOut";break;
        case NRFX_ERROR_NULL: name="Null";break;
        case NRFX_ERROR_FORBIDDEN: name="Forb";break;
        case NRFX_ERROR_INVALID_ADDR: name="InvalAdr";break;
        case NRFX_ERROR_BUSY: name="Busy";break;
        case NRFX_ERROR_ALREADY_INITIALIZED: name="ReInit";break;
        case NRFX_ERROR_DRV_TWI_ERR_OVERRUN: name="OverRun";break;
        case NRFX_ERROR_DRV_TWI_ERR_DNACK: name="DnAck";break;
        case NRFX_SUCCESS: name="Ok!";break;
        default : break;
    }
    return name;
}


