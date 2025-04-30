#include "statistics_commands.h"

#include <string.h>

#include "convert.h"
#include "log.h"
#include "statistics.h"
#include "statistics_diag.h"

bool statistics_load_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t column = 0;
    char file_name[150] = "";
    LOG_INFO(STATISTICS, "Argc:%d", argc);
    if(1 <= argc) {
        LOG_INFO(STATISTICS, "ArgLen: %u bytes", strlen(argv[0]));
        if(strlen(argv[0]) < sizeof(file_name)) {
            strncpy(file_name, argv[0], sizeof(file_name));
            res = true;
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &column);
        if(res) {
            LOG_INFO(STATISTICS, "column: %u", column);
        } else {
            LOG_ERROR(STATISTICS, "columnErr [%s]", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(STATISTICS, "Try,To,Open,file:[%s],%u", file_name, column);
        res = statistics_load(file_name, column);
        if(res) {
            LOG_INFO(STATISTICS, "Load,Ok");
        } else {
            LOG_ERROR(STATISTICS, "Load,Err");
        }
    } else {
        LOG_ERROR(STATISTICS, "Usage stl fileName column");
    }
    return res;
}

bool statistics_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(STATISTICS, "Argc:%d", argc);
    res = statistics_expected_value(&RandomVariable);
    if(res) {
        LOG_INFO(STATISTICS, "ExpectedValue %f", RandomVariable.expected_value);
    }

    res = statistics_standard_deviation(&RandomVariable);
    if(res) {
        LOG_INFO(STATISTICS, "StandardDeviation %f", RandomVariable.standard_deviation);
    }

    return res;
}

bool statistics_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(STATISTICS, "Argc:%d", argc);
    res = RandomVariableDiag(&RandomVariable);
    return res;
}

bool statistics_bar_chart_command(int32_t argc, char* argv[]) {
    bool res = false;
    double histogram_step = 0.01;
    uint32_t interanl_cnt = 0;
    if(0 <= argc) {
        interanl_cnt = 1;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &interanl_cnt);
        if(res) {
            RandomVariable.interanl_cnt = interanl_cnt;
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &histogram_step);
        if(res) {
            RandomVariable.histogram_step = histogram_step;
            RandomVariable.interanl_cnt = RandomVariable.spread / histogram_step;
        }
    }

    if(res) {
        LOG_INFO(STATISTICS, "Step:%f, Interval:%u", histogram_step, RandomVariable.interanl_cnt);
        res = statistics_calc_bar_chart(&RandomVariable);
        if(res) {
            LOG_INFO(STATISTICS, "Ok");
        }else {
            LOG_ERROR(STATISTICS, "Error");
        }
    } else {
        LOG_ERROR(STATISTICS, "Usage stb interanls histogramStep");
    }

    return res;
}
