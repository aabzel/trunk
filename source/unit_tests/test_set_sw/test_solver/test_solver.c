#include "test_solver.h"

#include "solver.h"
#include "unit_test_check.h"

bool test_solver(void) {
    bool res = true;
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SOLVER, LOG_LEVEL_DEBUG);

    Solver_t Solver;

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_FALSE(solver_equation_order1(&Solver, "0x=0"));
    ASSERT_TRUE(Solver.inf_solution);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2x+0=0"));
    ASSERT_EQ_DOUBLE(0.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "1+x=2"));
    ASSERT_EQ_DOUBLE(1.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2=-x"));
    ASSERT_EQ_DOUBLE(-2.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "-x=-1"));
    ASSERT_EQ_DOUBLE(1.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_FALSE(solver_equation_order1(&Solver, "x=x+2"));
    ASSERT_TRUE(Solver.no_solution);

    // 2x+3x-6x=x+2
    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2x+3x-6x=x+2"));
    ASSERT_EQ_DOUBLE(-1.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2x=x"));
    ASSERT_EQ_DOUBLE(0.0, Solver.x);
    ASSERT_FALSE(Solver.inf_solution);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_FALSE(solver_equation_order1(&Solver, "x=x"));

    // x+5-3+x=6+x-2   x+5-3+2-6=0 x+5-1-6=0 x+5-7=0 x-2=0
    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "x+5-3+x=6+x-2"));
    ASSERT_EQ_DOUBLE(2.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2x+3.5=-2.8"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2-1*x=36.6"));

    // 2*2+4x=-48*x+10    52x-6=0   52x=6    x=6/52
    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2*2+4x=-48*x+10"));
    ASSERT_EQ_DOUBLE(0.1153846154, Solver.x);

    // 4x -6=0  4x-6=0  4x=6 x=6/4
    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2*2+4x=10"));
    ASSERT_EQ_DOUBLE(1.5, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2x+4x=10"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_FALSE(solver_equation_order1(&Solver, "0x=1"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_FALSE(solver_equation_order1(&Solver, "5=6"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "x5+3=15.5"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "+3.7-2.54x=2.2+2.85"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2+1x=10"));

    //-2.5x+1.5=-8   -2.5x+1.5+8=0  -2.5x+9.5=0  2.5x=9.5 x=9.5/2.5
    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "-2.5x+1.5=-8"));
    ASSERT_EQ_DOUBLE(3.8, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "15=3+7x"));
    ASSERT_EQ(1.714, Solver.x);
    //-7x+15-3=0   -7x+12=0    -7x=-12   x=12/7

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "2=x"));
    ASSERT_EQ(2.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "x=2"));
    ASSERT_EQ(2.0, Solver.x);

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_FALSE(solver_equation_order1(&Solver, "x=x"));

    ASSERT_TRUE(solver_init(&Solver));
    ASSERT_TRUE(solver_equation_order1(&Solver, "15 =  3 +  7x"));
    ASSERT_EQ(1.714, Solver.x);

    set_log_level(SOLVER, LOG_LEVEL_INFO);

    return res;
}
