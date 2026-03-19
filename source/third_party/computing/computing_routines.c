#include "computing_routines.h"

#ifdef DDS_PROC_IN_USE
#include "dds.h"

bool DDS_proc(void) {
    bool res = false ;
    STD_RESULT ret = DDS_Proc();
    if (RESULT_OK==ret) {
        res = true;
    }
    return res;
}
#endif
