#include "proc_control.h"

#include "common_functions.h"
#include "log.h"


#ifdef HAS_LC3
#include "lc3_drv.h"
#endif

#ifdef HAS_TASK
#include "task_config.h"
#include "task_info.h"
#endif

#if 0
bool control_init(void) {
    bool res = true;
    LOG_INFO(SYS,"InitControl");
     res= asics_init();
#ifdef HAS_LC3
    res = try_init(lc3_init(), "LC3") && res;
#endif

    return res;
}
#endif
