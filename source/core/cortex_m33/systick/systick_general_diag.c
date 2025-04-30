#include "systick_general_diag.h"
#include "systick_const.h"

char* SysTickClockSource2Str(uint8_t code){
    char* name="?";
    switch(code){
        case CLK_SRC_EXT :name="External"; break;
        case CLK_SRC_PROC :name="Processor"; break;
    }
    return name;
}
