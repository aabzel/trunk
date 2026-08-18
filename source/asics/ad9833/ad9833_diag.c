#include "ad9833_diag.h"

#include <stdio.h>

#include "convert.h"
#include "ad9833_config.h"
#include "ad9833_const.h"
#include "ad9833_types.h"
#include "ad9833_drv.h"
#ifdef HAS_LOG
#include "log.h"
#endif

bool ad9833_diag(void) {
    bool res = false;
    return res;
}

const char* SignalFormToStr(SignalForm_t form){
     char* name = "?";
    switch(form) {
    case SIGNAL_FORM_SQUARE:
        name = "Square";
    break;

    case SIGNAL_FORM_SINUSOIDAL:
        name = "Sin";
    break;

    case SIGNAL_FORM_TRIANGULAR:
        name = "Triangular";
    break;

    case SIGNAL_FORM_CONST:
        name = "Const";
    break;

    default: name = "?";break;
    }
    return name;
}
