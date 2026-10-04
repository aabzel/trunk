#include "pc_commands.h"

#include <stdlib.h>

#include "convert.h"
#include "log.h"
#include "win_utils.h"

bool exit_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_WIN
    res = true;
    exit(1);
#endif
    return res;
}

bool plot_graph_command(int32_t argc, char* argv[]) {
    bool res = false;
    char CsvFileName[120] = {0};
    uint8_t y_col = 0;
    uint8_t x_col = 0;

    if(1 <= argc) {
        res = strcpy(CsvFileName, argv[0]);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &x_col);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &y_col);
    }

    if(res) {
        res = csv_plot_line(CsvFileName, x_col, y_col);
        log_info_res(SYS, res, "PlotLine");
    } else {
        LOG_ERROR(SYS, "Usage: pg CsvFileName X Y");
    }
    return res;
}
