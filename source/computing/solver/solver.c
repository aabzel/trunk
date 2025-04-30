#include "solver.h"

#include "log.h"

#include <stdlib.h>
#include <string.h>

#include "convert.h"
#include "lifo_array.h"
#include "lifo_array_diag.h"

static bool solver_proc_equal(Solver_t* Solver) {
    bool res = false;
    if(EQUATION_PART_LEFT == Solver->equation_part) {
        Solver->cur_state = SOL_ST_EQUAL;
        Solver->equation_part = EQUATION_PART_RIGHT;
        res = true;
    } else {
        res = false;
        LOG_ERROR(SOLVER, "DoubleEqual");
    }
    return res;
}

static bool solver_equation_order1_proc_init(Solver_t* Solver, const char letter) {
    LOG_DEBUG(TEST, "%s():", __FUNCTION__);
    bool res = true;
    switch(letter) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        Solver->const_type = CONST_TYPE_B;
        Solver->cur_state = SOL_ST_INTEGER;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
        break;
    case ' ':
        Solver->cur_state = SOL_ST_INIT;
        break;
    case '+':
        Solver->value_idx = 0;
        Solver->cur_val_sign = 1;
        Solver->cur_state = SOL_ST_PLUS;
        break;
    case '.':
        res = false;
        break;
    case '/':
        res = false;
        break;
    case '-':
        Solver->cur_val_sign = -1;
        Solver->cur_state = SOL_ST_MINUS;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
        break;
    case '=':
        res = false;
        break;
    case '*':
        res = false;
        break;
    case 'x':
        Solver->const_type = CONST_TYPE_A;
        Solver->a[0] = 1.0;
        Solver->a_cnt = 1;
        Solver->cur_state = SOL_ST_EX;
        break;
    }
    return res;
}

static bool solver_equation_order1_proc_equal(Solver_t* Solver, const char letter) {
    bool res = true;
    LOG_DEBUG(TEST, "%s(): Input:[%c]", __FUNCTION__, letter);
    switch(letter) {
    case '.':
        res = false;
        break;
    case 'x': {
        Solver->const_type = CONST_TYPE_A;
        Solver->a[Solver->a_cnt] = -1.0;
        Solver->a_cnt++;
        Solver->cur_state = SOL_ST_EX;
    } break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        Solver->const_type = CONST_TYPE_B;
        Solver->cur_state = SOL_ST_INTEGER;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
    } break;
    case ' ':
        break;
    case '+':
        Solver->const_type = CONST_TYPE_B;
        Solver->value_idx = 0;
        Solver->cur_state = SOL_ST_PLUS;
        break;
    case '/':
        res = false;
        break;
    case '-':
        Solver->const_type = CONST_TYPE_B;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
        Solver->cur_state = SOL_ST_MINUS;
        break;
    case '=':
        res = solver_proc_equal(Solver);
        break;
    case '*':
        res = false;
        break;
    }
    return res;
}

static bool solver_equation_order1_proc_plus(Solver_t* Solver, const char letter) {
    bool res = true;
    LOG_DEBUG(TEST, "%s(): Input:[%c]", __FUNCTION__, letter);
    switch(letter) {
    case 'x': {
        Solver->const_type = CONST_TYPE_A;
        Solver->cur_state = SOL_ST_EX;
        double val = 1.0;
        if(EQUATION_PART_RIGHT == Solver->equation_part) {
            val = -1.0;
        }
        Solver->a[Solver->a_cnt] = val;
        Solver->a_cnt++;
    } break;
    case '1':
    case '0':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        Solver->const_type = CONST_TYPE_B;
        Solver->cur_state = SOL_ST_INTEGER;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
    } break;
    case ' ':
        break;
    case '.':
        res = false;
        break;
    case '+':
        res = false;
        break;
    case '/':
        res = false;
        break;
    case '-':
        res = false;
        break;
    case '=':
        res = false;
        break;
    case '*':
        res = false;
        break;
    }
    return res;
}

static bool solver_equation_order1_proc_minus(Solver_t* Solver, const char letter) {
    bool res = true;
    LOG_DEBUG(TEST, "%s(): Input:[%c]", __FUNCTION__, letter);
    switch(letter) {
    case 'x': {
        Solver->const_type = CONST_TYPE_A;
        Solver->cur_state = SOL_ST_EX;
        double val = 1.0;
        if(EQUATION_PART_RIGHT == Solver->equation_part) {
            val = 1.0;
        } else {
            val = -1.0;
        }
        Solver->a[Solver->a_cnt] = val;
        Solver->a_cnt++;
    } break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        Solver->const_type = CONST_TYPE_B;
        Solver->cur_state = SOL_ST_INTEGER;
        Solver->value_str[Solver->value_idx] = letter;
        Solver->value_idx++;
    } break;
    case ' ':
        break;
    case '0':
        res = false;
        break;
    case '.':
        res = false;
        break;
    case '+':
        res = false;
        break;
    case '/':
        res = false;
        break;
    case '-':
        res = false;
        break;
    case '=':
        res = false;
        break;
    case '*':
        res = false;
        break;
    }
    return res;
}

double calc_expression(double value_a, double value_b, char operation) {
    double result = 0.0;
    switch(operation) {
    case '*':
        result = value_a * value_b;
        break;
    case '+':
        result = value_a + value_b;
        break;
    case '-':
        result = value_a - value_b;
        break;
    case '/':
        result = value_a / value_b;
        break;
    }
    return result;
}

static bool solver_equation_order1_proc_integer(Solver_t* Solver, const char letter) {
    bool res = true;
    LOG_DEBUG(TEST, "  %s(): Input:[%c]", __FUNCTION__, letter);
    switch(letter) {
    case '\n':
    case '\r': {
        LOG_DEBUG(SOLVER, "ValueStr[%s]", Solver->value_str);
        double value = 0.0;
        res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
            if(EQUATION_PART_RIGHT == Solver->equation_part) {
                value = -value;
            }
            LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
            if(0 < cnt) {
                lifo_arr_diag(&Solver->LifoArray);
            }

            switch((uint8_t)Solver->const_type) {
            case CONST_TYPE_A:
                Solver->a[Solver->a_cnt] = value;
                Solver->a_cnt++;
                break;
            case CONST_TYPE_B:
                Solver->b[Solver->b_cnt] = value;
                Solver->b_cnt++;
                break;
            }
        }
        Solver->value_idx = 0;
        memset(Solver->value_str, 0, MAX_VALUE_LEN);
    } break;
    case 'x': {
        Solver->const_type = CONST_TYPE_A;
        LOG_DEBUG(SOLVER, "ValueStr[%s]", Solver->value_str);
        double value = 0.0;
        res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
            if(EQUATION_PART_RIGHT == Solver->equation_part) {
                value = -value;
            }
            LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
            if(0 < cnt) {
                lifo_arr_diag(&Solver->LifoArray);
            }

            Solver->a[Solver->a_cnt] = value;
            Solver->a_cnt++;
        }
        Solver->value_idx = 0;
        memset(Solver->value_str, 0, MAX_VALUE_LEN);
        Solver->cur_state = SOL_ST_EX;
    } break;

    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        Solver->value_str[Solver->value_idx] = letter;
        Solver->value_idx++;
    } break;

    case ' ':
        break;
    case '+': {
        LOG_DEBUG(SOLVER, "ValueStr[%s] Len:%u", Solver->value_str, Solver->value_idx);
        double value = 0.0;
        res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
            if(EQUATION_PART_RIGHT == Solver->equation_part) {
                value = -value;
            }

            LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
            if(2 == cnt) {
                lifo_arr_diag(&Solver->LifoArray);
                Array_t NodeOp;
                res = lifo_arr_pull(&Solver->LifoArray, &NodeOp);
                Array_t NodeVal;
                res = lifo_arr_pull(&Solver->LifoArray, &NodeVal);
                double val1 = 0.0;
                res = try_strl2double(NodeVal.pArr, NodeVal.size, &val1);
                if(res) {
                    value = calc_expression(value, val1, NodeOp.pArr[0]);
                }
            }

            switch((uint8_t)Solver->const_type) {
            case CONST_TYPE_A:
                Solver->a[Solver->a_cnt] = value;
                Solver->a_cnt++;
                break;
            case CONST_TYPE_B:
                Solver->b[Solver->b_cnt] = value;
                Solver->b_cnt++;
                break;
            }
        }
        Solver->value_idx = 0;
        memset(Solver->value_str, 0, MAX_VALUE_LEN);
        Solver->cur_state = SOL_ST_PLUS;
    } break;
    case '/':
        Solver->cur_state = SOL_ST_DIVIDOR;
        break;
    case '-': {
        LOG_DEBUG(SOLVER, "ValueStr[%s] Len:%u", Solver->value_str, Solver->value_idx);
        double value = 0.0;
        res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
            if(EQUATION_PART_RIGHT == Solver->equation_part) {
                value = -value;
            }
            LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
            if(0 < cnt) {
                lifo_arr_diag(&Solver->LifoArray);
            }
            switch((uint8_t)Solver->const_type) {
            case CONST_TYPE_A:
                Solver->a[Solver->a_cnt] = value;
                Solver->a_cnt++;
                break;
            case CONST_TYPE_B:
                Solver->b[Solver->b_cnt] = value;
                Solver->b_cnt++;
                break;
            }
        }
        Solver->value_idx = 0;
        memset(Solver->value_str, 0, MAX_VALUE_LEN);

        Solver->value_str[Solver->value_idx] = '-';
        Solver->value_idx = 1;

        Solver->cur_state = SOL_ST_MINUS;
    } break;
    case '=': {
        LOG_DEBUG(SOLVER, "ValueStr[%s]", Solver->value_str);
        double value = 0.0;
        res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
            if(EQUATION_PART_RIGHT == Solver->equation_part) {
                value = -value;
            }

            LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
            if(0 < cnt) {
                lifo_arr_diag(&Solver->LifoArray);
            }

            Solver->b[Solver->b_cnt] = value;
            Solver->b_cnt++;
        }
        Solver->value_idx = 0;
        memset(Solver->value_str, 0, MAX_VALUE_LEN);
        res = solver_proc_equal(Solver);
    } break;
    case '*': {
        LOG_DEBUG(SOLVER, "ValueStr[%s]", Solver->value_str);
        double value = 0.0;
        res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
        }

        LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
        if(0 < cnt) {
            lifo_arr_diag(&Solver->LifoArray);
        }

        char* str_val = strdup(Solver->value_str);
        if(str_val) {
            Array_t node = {
                .size = Solver->value_idx,
                .pArr = str_val,
            };
            res = lifo_arr_push(&Solver->LifoArray, node);
        }

        str_val = strdup("*");
        if(str_val) {
            Array_t node = {
                .size = 1,
                .pArr = str_val,
            };
            res = lifo_arr_push(&Solver->LifoArray, node);
        }
        Solver->value_idx = 0;
        memset(Solver->value_str, 0, MAX_VALUE_LEN);
        Solver->cur_state = SOL_ST_MULT;
    } break;
    }
    return res;
}

static bool solver_equation_order1_proc_dot(Solver_t* Solver, const char letter) {
    bool res = false;
    LOG_DEBUG(TEST, "  %s(): Input:[%c]", __FUNCTION__, letter);
    return res;
}

static bool solver_equation_order1_proc_fraction(Solver_t* Solver, const char letter) {
    bool res = false;
    LOG_DEBUG(TEST, "  %s(): Input:[%c]", __FUNCTION__, letter);
    return res;
}

static bool solver_equation_order1_proc_dividor(Solver_t* Solver, const char letter) {
    bool res = false;
    LOG_DEBUG(TEST, "  %s(): Input:[%c]", __FUNCTION__, letter);
    return res;
}

static bool solver_equation_order1_proc_mult(Solver_t* Solver, const char letter) {
    bool res = true;
    LOG_DEBUG(TEST, "  ProcMultState Input:[%c]", letter);
    switch(letter) {
    case 'x': {
        double value = 0.0;
        Solver->const_type = CONST_TYPE_A;
        LifoIndex_t cnt = lifo_arr_get_count(&Solver->LifoArray);
        if(0 < cnt) {
            lifo_arr_diag(&Solver->LifoArray);
            Array_t NodeOp;
            res = lifo_arr_pull(&Solver->LifoArray, &NodeOp);
            Array_t NodeVal;
            res = lifo_arr_pull(&Solver->LifoArray, &NodeVal);
            // double val1 = 0.0;
            res = try_strl2double(NodeVal.pArr, NodeVal.size, &value);
            if(res) {
                // value = calc_expression(value,val1 , NodeOp.pArr[0]);
            }
        }
        // LOG_DEBUG(SOLVER,"ValueStr[%s]",Solver->value_str);
        // res = try_strl2double(Solver->value_str, Solver->value_idx, &value);
        if(res) {
            LOG_NOTICE(SOLVER, "Value:[%f] Type %u", value, Solver->const_type);
            if(EQUATION_PART_RIGHT == Solver->equation_part) {
                value = -value;
            }
            switch((uint8_t)Solver->const_type) {
            case CONST_TYPE_A:
                Solver->a[Solver->a_cnt] = value;
                Solver->a_cnt++;
                break;
            case CONST_TYPE_B:
                Solver->b[Solver->b_cnt] = value;
                Solver->b_cnt++;
                break;
            }
        } else {
        }
        Solver->cur_state = SOL_ST_EX;
    } break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        // Solver->const_type=CONST_TYPE_A;
        Solver->cur_state = SOL_ST_INTEGER;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
    } break;
    case ' ':
        break;
    case '.':
        res = false;
        break;
    case '0':
        res = false;
        break;
    case '+':
        res = false;
        break;
    case '-':
        res = false;
        break;
    case '/':
        res = false;
        break;
    case '=':
        res = false;
        break;
    case '*':
        res = false;
        break;
    }
    return res;
}

static bool solver_equation_order1_proc_ex(Solver_t* Solver, const char letter) {
    bool res = true;
    LOG_DEBUG(TEST, "  ProcExState Input:[%c]", letter);
    switch(letter) {
    case '0':
        res = false;
        break;
    case '.':
        res = false;
        break;
    case 'x':
        res = false;
        break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        Solver->const_type = CONST_TYPE_A;
        Solver->value_str[0] = letter;
        Solver->value_idx = 1;
    } break;
    case ' ':
        break;
    case '+':
        Solver->cur_state = SOL_ST_PLUS;
        Solver->value_idx = 0;
        break;
    case '-':
        Solver->value_str[0] = '-';
        Solver->value_idx = 1;
        Solver->cur_state = SOL_ST_MINUS;
        break;
    case '/':
        Solver->const_type = CONST_TYPE_A;
        Solver->cur_state = SOL_ST_DIVIDOR;
        break;
    case '=':
        res = solver_proc_equal(Solver);
        break;
    case '*':
        Solver->cur_state = SOL_ST_MULT;
        break;
    }
    return res;
}

static bool solver_equation_order1_proc(Solver_t* Solver, const char letter) {
    bool res = false;
    // LOG_DEBUG(TEST, "%s(): Input:[%c]", __FUNCTION__, letter);
    switch(Solver->cur_state) {
    case SOL_ST_EX:
        res = solver_equation_order1_proc_ex(Solver, letter);
        break;
    case SOL_ST_INIT:
        res = solver_equation_order1_proc_init(Solver, letter);
        break;
    case SOL_ST_PLUS:
        res = solver_equation_order1_proc_plus(Solver, letter);
        break;
    case SOL_ST_MINUS:
        res = solver_equation_order1_proc_minus(Solver, letter);
        break;
    case SOL_ST_INTEGER:
        res = solver_equation_order1_proc_integer(Solver, letter);
        break;
    case SOL_ST_DOT:
        res = solver_equation_order1_proc_dot(Solver, letter);
        break;
    case SOL_ST_FRACTION:
        res = solver_equation_order1_proc_fraction(Solver, letter);
        break;
    case SOL_ST_EQUAL:
        res = solver_equation_order1_proc_equal(Solver, letter);
        break;
    case SOL_ST_DIVIDOR:
        res = solver_equation_order1_proc_dividor(Solver, letter);
        break;
    case SOL_ST_MULT:
        res = solver_equation_order1_proc_mult(Solver, letter);
        break;
    }
    return res;
}

bool solver_calc(Solver_t* Solver) {
    bool res = false;
    uint32_t i = 0;
    double a_total = 0.0;
    double b_total = 0.0;
    for(i = 0; i < Solver->a_cnt; i++) {
        a_total += Solver->a[i];
    }
    for(i = 0; i < Solver->b_cnt; i++) {
        b_total += Solver->b[i];
    }

    LOG_DEBUG(SOLVER, "Solve [(%f)x+(%f)=0]", a_total, b_total);
    if(0.0 != a_total) {
        Solver->x = -b_total / a_total;
        LOG_WARNING(SOLVER, "X=%f", Solver->x);
        res = true;
    } else {
        if(0.0 != b_total) {
            Solver->no_solution = true;
        } else {
            Solver->inf_solution = true;
        }
        res = false;
        LOG_ERROR(SOLVER, "Division by zero");
    }
    return res;
}

bool solver_equation_order1(Solver_t* Solver, const char* const equation) {
    bool res = false;

    uint32_t err_cnt = 0;
    LOG_INFO(SOLVER, "TryToSolve [%s]", equation);

    if(equation) {
        res = true;
    }

    if(res) {
        res = false;
        uint32_t i = 0;
        uint32_t len = strlen(equation);
        LOG_DEBUG(SOLVER, "[%s] Len %u byte", equation, len);
        for(i = 0; i < len; i++) {
            res = solver_equation_order1_proc(Solver, equation[i]);
            if(false == res) {
                err_cnt++;
                LOG_ERROR(SOLVER, "ProcErr In[%u]=[%c]", i, equation[i]);
                break;
            }
        }
        res = solver_equation_order1_proc(Solver, '\r');
        if(false == res) {
            err_cnt++;
            LOG_ERROR(SOLVER, "ProcErr Terminate");
        }
        // res=solver_equation_order1_proc(Solver, '\n');
        if(0 == err_cnt) {

            res = solver_calc(Solver);
            if(res) {
                Solver->solution_found = true;
            } else {
                err_cnt++;
                Solver->solution_found = false;
                LOG_ERROR(SOLVER, "CalcErr");
            }
        }
    }

    if(err_cnt) {
        res = false;
        LOG_ERROR(SOLVER, "UnableToSolve [%s]", equation);
    }
    return res;
}

bool solver_init(Solver_t* solver_ptr) {
    bool res = false;
    if(solver_ptr) {
        res = lifo_arr_init(&solver_ptr->LifoArray, solver_ptr->ArrayHeap, SOLVER_LIFO_SIZE);
        solver_ptr->cur_state = SOL_ST_INIT;
        solver_ptr->init = true;
        solver_ptr->solution_found = false;
        solver_ptr->inf_solution = false;
        solver_ptr->no_solution = false;
        solver_ptr->equation_part = EQUATION_PART_LEFT;
        solver_ptr->a_cnt = 0;
        solver_ptr->b_cnt = 0;
        solver_ptr->value_idx = 0;
        solver_ptr->x = 0.0;
        memset(solver_ptr->value_str, 0, MAX_VALUE_LEN);
    }
    return res;
}
