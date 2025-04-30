#include "solver_slae.h"

#include <stdint.h>

#include "float_utils.h"
#include "log.h"

SolverSlae_t SolverSlae = {0};

const char* SlaeToStr(const SolverSlae_t* const Solver) {
    static char name[80] = {0};
    return name;
}

bool solver_slae_init(SolverSlae_t* const Solver, double x1, double y1, double x2, double y2) {
    bool res = false;
    return res;
}

bool solver_slae_calc_ab(SolverSlae_t* const Solver) {
    bool res = false;
    if(Solver) {
        double denominator = Solver->M[1].x - Solver->M[0].x;
        double y1 = Solver->M[0].y;
        double y2 = Solver->M[1].y;

        double x1 = Solver->M[0].x;
        double x2 = Solver->M[1].x;
        Solver->a = (y2 - y1) / denominator;
        Solver->b = (y1 * x2 - x1 * y2) / denominator;
        LOG_INFO(SOLVER, "y=ax+b, y=(%f)x+(%f)", Solver->a, Solver->b);
        res = true;
    }
    return res;
}

double solver_slae_calc_y(SolverSlae_t* const Solver, double x) {
    double y = 0.0;
    if(Solver) {
        y = Solver->a * x + Solver->b;
        LOG_INFO(SOLVER, "y(%f)=%f", x, y);
    }
    return y;
}

double solver_slae_calc_x(SolverSlae_t* const Solver, double y) {
    double x = 0.0;
    bool res = is_double_equal_absolute(Solver->a, 0.0, 0.00001);
    if(false == res) {
        x = (y - Solver->b) / Solver->a;
        LOG_INFO(SOLVER, "x(y)=x(%f)=%f", y, x);
    }
    return x;
}
