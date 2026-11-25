#include "uart_custom_diag.h"

const char* FcUartErrorTypeToStr(const FCUART_ErrorTypeEnum code) {
    char* name = "?";
    switch(code) {
    case FCUART_ERROR_OK:
        name = "Ok";
        break;
    case FCUART_ERROR_INVALID_VERSION:
        name = "VerErr";
        break;
    case FCUART_ERROR_FAILED:
        name = "Fail";
        break;
    case FCUART_ERROR_INVALID_PARAM:
        name = "ParamErr";
        break;
    case FCUART_ERROR_INVALID_SIZE:
        name = "INVALID_SIZE";
        break;
    case FCUART_ERROR_INVALID_SEQUENCE:
        name = "INVALID_SEQUENCE";
        break;
    case FCUART_ERROR_TIMEOUT:
        name = "TIMEOUT";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}
