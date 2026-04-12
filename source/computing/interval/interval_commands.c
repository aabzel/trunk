#include "interval_commands.h"

#include <string.h>

#include "convert.h"
#include "interval.h"
#include "log.h"

static bool interval_read_ab(int32_t argc, char* argv[], IntervalE_t* const pA, IntervalE_t* const pB) {
    bool res = false;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &pA->start);
        log_res(INTERVAL, res, "Astart");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &pA->end);
        log_res(INTERVAL, res, "Aend");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &pB->start);
        log_res(INTERVAL, res, "Bstart");
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &pB->end);
        log_res(INTERVAL, res, "Bend");
    }

    return res;
}

bool interval_merge_command(int32_t argc, char* argv[]) {
    bool res = false;

    IntervalE_t A = {0};
    IntervalE_t B = {0};
    res = interval_read_ab(argc, argv, &A, &B);

    if(res) {
        res = interval_is_merge(&A, &B);
        LOG_INFO(INTERVAL, "%u", res);
    } else {
        LOG_ERROR(INTERVAL, "Usage: io A B");
    }
    return res;
}

bool interval_intersect_command(int32_t argc, char* argv[]) {
    bool res = false;

    IntervalE_t A = {0};
    IntervalE_t B = {0};
    res = interval_read_ab(argc, argv, &A, &B);

    if(res) {
        res = interval_intersect_continuum(&A, &B);
        LOG_INFO(INTERVAL, "%u", res);
    } else {
        LOG_ERROR(INTERVAL, "Usage: ii A B");
    }
    return res;
}

bool interval_dock_command(int32_t argc, char* argv[]) {
    bool res = false;

    IntervalE_t A = {0};
    IntervalE_t B = {0};
    res = interval_read_ab(argc, argv, &A, &B);

    if(res) {
        res = interval_is_dock(&A, &B);
        LOG_INFO(INTERVAL, "%u", res);
    } else {
        LOG_ERROR(INTERVAL, "Usage: id A B");
    }
    return res;
}
