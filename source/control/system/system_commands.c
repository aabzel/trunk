#include "system_commands.h"

#include "if_config.h"
#include "interface_drv.h"
#include "log.h"
#include "system.h"
#include "table_utils.h"
#include "writer_config.h"

bool sys_rate_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint32_t if_cnt = 0xFFFF;
    LOG_ERROR(SYS, "InterafaceCnt: %u", if_cnt);
    static const table_col_t cols[] = {{11, "interf"}, {7, "proto"}, {9, "rxMin"}, {9, "rx"},
                                       {9, "rxMax"},   {9, "txMin"}, {9, "tx"},    {9, "txMax"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool sys_available_interfaces_command(int32_t argc, char* argv[]) {
    bool res = false;
    // res = sys_available_interfaces();
    return res;
}

bool sys_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = system_diag();
    return res;
}

bool system_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = system_mcal_init();
    return res;
}
