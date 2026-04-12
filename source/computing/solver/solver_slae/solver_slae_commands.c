#include "solver_slae_commands.h"

#include <string.h>

#include "convert.h"
#include "log.h"
#include "solver_slae.h"

bool solver_slae_calc_y_command(int32_t argc, char* argv[]) {
    bool res = false;
    float x = 0.0;

    if(1 <= argc) {
        res = try_str2float(argv[0], &x);
        if(false == res) {
            LOG_ERROR(SOLVER, "ParseErr X %s", argv[0]);
        }
    }

    if(res) {
        float y = solver_slae_calc_y(&SolverSlae, x);
        LOG_ERROR(SOLVER, "Y=%f", y);
    }
    return res;
}

bool solver_slae_calc_x_command(int32_t argc, char* argv[]) {
    bool res = false;
    float y = 0.0;
    if(1 <= argc) {
        res = try_str2float(argv[0], &y);
        if(false == res) {
            LOG_ERROR(SOLVER, "ParseErr Y %s", argv[0]);
        }
    }

    if(res) {
        float x = solver_slae_calc_x(&SolverSlae, y);
        LOG_ERROR(SOLVER, "X=%f", x);
    }
    return res;
}

bool solver_slae_calc_ab_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(1 <= argc) {
        res = try_str2float(argv[0], &SolverSlae.M[0].x);
        if(false == res) {
            LOG_ERROR(SOLVER, "ParseErr X1 %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &SolverSlae.M[0].y);
        if(false == res) {
            LOG_ERROR(SOLVER, "ParseErr Y1 %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &SolverSlae.M[1].x);
        if(false == res) {
            LOG_ERROR(SOLVER, "ParseErr X2 %s", argv[2]);
        }
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &SolverSlae.M[1].y);
        if(false == res) {
            LOG_ERROR(SOLVER, "ParseErr Y2 %s", argv[3]);
        }
    }

    if(res) {
        res = solver_slae_calc_ab(&SolverSlae);
        if(res) {
            LOG_INFO(SOLVER, "Y=(%f)*X +(%f)", SolverSlae.a, SolverSlae.b);
        }
    } else {
        LOG_ERROR(SOLVER, "Usage: sab x1 y1 x2 y2");
    }
    return res;
}
