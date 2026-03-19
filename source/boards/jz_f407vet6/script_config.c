#include "script_config.h"

#include "data_utils.h"
//#include "c_defines_generated.h"

/* instances inside CommandArray must be sorted by up time!
mcc 2 1; mcc 3 1
 */
static const ScriptCmd_t CommandArray[] = {
    {  .up_time_s=6,  .command="mcc 2 1", .valid=true,},
    {  .up_time_s=9,  .command="mcc 3 1", .valid=true,},
    {  .up_time_s=15, .command="vi",      .valid=true,},
};

/*constant compile-time known settings*/
const ScriptConfig_t ScriptConfig[] = {
    {
        .num = 1,
        .cli_num = 1,
        .name = "Script1",
        .Routine = (ScriptCmd_t*) CommandArray,
        .line_cnt = ARRAY_SIZE(CommandArray),
        .valid = true,
    },
};

ScriptHandle_t ScriptInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Script, script)

