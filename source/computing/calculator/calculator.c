#include "calculator.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "calculator_diag.h"
#include "convert.h"
#include "float_utils.h"
#include "lifo_array.h"
#include "lifo_array_diag.h"
#include "log.h"
#include "protocol_const.h"
#include "stack_frame.h"
#include "stack_frame_diag.h"

static Array_t Array[100] = {0};

static bool calc_operation_proc(OperationData_t* const OperNode) {
    bool res = false;
    LOG_DEBUG(CALC, "PerformOperation %s", OperationNode2Str(OperNode));
    switch((uint8_t)OperNode->operation) {

    case OPERATION_AND: {
        uint32_t left = (uint32_t)OperNode->val_left;
        uint32_t right = (uint32_t)OperNode->val_right;
        uint32_t result = left & right;
        LOG_DEBUG(CALC, "%u and %u=%u", left, right, result);
        OperNode->result = (double)result;
        res = true;
    } break;

    case OPERATION_OR: {
        uint32_t left = (uint32_t)OperNode->val_left;
        uint32_t right = (uint32_t)OperNode->val_right;
        uint32_t result = left | right;
        LOG_DEBUG(CALC, "%u or %u=%u", left, right, result);
        OperNode->result = (double)result;
        res = true;
    } break;

    case OPERATION_XOR: {
        uint32_t left = (uint32_t)OperNode->val_left;
        uint32_t right = (uint32_t)OperNode->val_right;
        uint32_t result = left ^ right;
        LOG_DEBUG(CALC, "%u xor %u=%u", left, right, result);
        OperNode->result = (double)result;
        res = true;
    } break;

    case OPERATION_SUM: {
        OperNode->result = OperNode->val_left + OperNode->val_right;
        res = true;
    } break;

    case OPERATION_POW: {
        OperNode->result = pow(OperNode->val_left, OperNode->val_right);
        res = true;
    } break;

    case OPERATION_SUBTRACTION: {
        OperNode->result = OperNode->val_left - OperNode->val_right;
        res = true;
    } break;

    case OPERATION_MULTIPLICATION: {
        OperNode->result = OperNode->val_left * OperNode->val_right;
        res = true;
    } break;

    case OPERATION_DIVISION: {
        res = double_is_zero(OperNode->val_right);
        if(false == res) {
            OperNode->result = OperNode->val_left / OperNode->val_right;
            res = true;
        } else {
            LOG_ERROR(CALC, "DivZeroErr");
            res = false;
        }
    } break;

    default: {
        res = false;
    } break;
    }

    if(res) {
        LOG_DEBUG(CALC, "OperationResult %f", OperNode->result);
    } else {
        LOG_ERROR(CALC, "OperationErr");
    }

    return res;
}

static bool calc_update_lifo(Calculator_t* const Node);

static bool lifo_array_pull_multiple(LifoArray_t* const Node, uint32_t num) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < num; i++) {
        Array_t ArrObj = {0};
        res = lifo_arr_pull(Node, &ArrObj);
        if(res) {
            ok++;
        }
    }

    if(ok == num) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

static bool calc_push_number(Calculator_t* const Node, double number) {
    bool res = false;
    LOG_DEBUG(CALC, "SpotNumber %f", number);

    StackFrameHandle_t StackFrame = {0};
    res = stack_frame_compose_double(&StackFrame, number);
    if(res) {
        uint8_t* stack_frame = (uint8_t*)malloc(StackFrame.size);
        if(stack_frame) {
            memcpy(stack_frame, StackFrame.data, StackFrame.size);
            Array_t node = {
                .size = StackFrame.size,
                .pArr = stack_frame,
            };
            res = lifo_arr_push(&Node->LifoArray, node);
            if(res) {
                LOG_DEBUG(CALC, "LifoPushNumOk");
                LifoArrayDiag(&Node->LifoArray, PROTO_STACK_FRAME);
                // calc_update_lifo(Node);
            } else {
                LOG_ERROR(CALC, "LifoPushNumErr");
            }
        }
    }
    return res;
}

static bool calc_update_lifo(Calculator_t* const Node) {
    bool res = false;
    LOG_DEBUG(CALC, "UpdateLifo..");
    if(3 <= Node->LifoArray.lifoState.count) {
        OperationData_t OperationData = {0};
        uint8_t ok = 0;
        Array_t val_right = {0};
        res = lifo_arr_peek_num(&Node->LifoArray, 0, &val_right);
        if(res) {
            res = stack_frame_parse_number(&val_right, &OperationData.val_right);
            if(res) {
                ok++;
                LOG_DEBUG(CALC, "ParseRightNumberOk %f", OperationData.val_right);
            } else {
                LOG_ERROR(CALC, "ParseNumberErr");
            }
        } else {
            LOG_ERROR(CALC, "LifoPeekErr");
        }

        Array_t oper_node = {0};
        res = lifo_arr_peek_num(&Node->LifoArray, 1, &oper_node);
        if(res) {
            res = stack_frame_parse_operation(&oper_node, &OperationData.operation);
            if(res) {
                ok++;

            } else {
                LOG_ERROR(CALC, "ParseOperationErr");
            }
        } else {
            LOG_ERROR(CALC, "LifoPeekErr");
        }

        Array_t val_left = {0};
        res = lifo_arr_peek_num(&Node->LifoArray, 2, &val_left);
        if(res) {
            res = stack_frame_parse_number(&val_left, &OperationData.val_left);
            if(res) {
                ok++;
                LOG_DEBUG(CALC, "ParseLeftNumberOk %f", OperationData.val_left);
            } else {
                LOG_ERROR(CALC, "ParseNumberErr");
            }
        } else {
            LOG_ERROR(CALC, "LifoPeekErr");
        }

        if(3 == ok) {
            res = calc_operation_proc(&OperationData);
            if(res) {
                LOG_DEBUG(CALC, "OpResult: %f", OperationData.result);
                res = lifo_array_pull_multiple(&Node->LifoArray, 3);
                if(res) {
                    res = calc_push_number(Node, OperationData.result);
                }
            }
        }
    } else {
        LOG_DEBUG(CALC, "LifoSmall..");
    }
    return res;
}

/*allowed alphabet:
 *   1 2 3 4 5 6 7 8 9 0 + - * ( ) / ^ . ' '
 *
 *   q-end of line, s-end of line,
 */

static bool calc_push_operation(Calculator_t* const Node, Operation_t operation) {
    bool res = false;
    LOG_DEBUG(CALC, "SpotOperation %s", Operation2Str(operation));
    StackFrameHandle_t StackFrame;
    res = stack_frame_compose_operation(&StackFrame, operation);
    if(res) {
        uint8_t* stack_frame = malloc(StackFrame.size);
        if(stack_frame) {
            memcpy(stack_frame, StackFrame.data, StackFrame.size);
            Array_t node = {
                .size = StackFrame.size,
                .pArr = stack_frame,
            };
            res = lifo_arr_push(&Node->LifoArray, node);
            if(res) {
                LOG_DEBUG(CALC, "LifoPushOpOk");
                LifoArrayDiag(&Node->LifoArray, PROTO_STACK_FRAME);
                // calc_update_lifo(Node);
            } else {
                LOG_ERROR(CALC, "LifoPushOpErr");
            }
        }
    }
    return res;
}

static bool calc_prev_close_proc(Calculator_t* const Node) {
    bool res = false;
    switch(Node->cur_char) {
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
        res = false;
    } break;
    case '+': {
        res = calc_push_operation(Node, OPERATION_SUM);
    } break;
    case '-': {
        res = calc_push_operation(Node, OPERATION_SUBTRACTION);
    } break;
    case '/': {
        res = calc_push_operation(Node, OPERATION_DIVISION);
    } break;
    case '*': {
        res = true;
        // res = calc_push_operation(Node, OPERATION_MULTIPLICATION);
    } break;
    case ')': {
        res = true;
        while(res) {
            res = calc_update_lifo(Node);
        }
        res = true;
    } break;
    case '(': {
        res = true;
        while(res) {
            res = calc_update_lifo(Node);
        }
        res = calc_push_operation(Node, OPERATION_MULTIPLICATION);
        res = true;
    } break;
    case ' ': {
        res = true;
    } break;
    case END_OF_LINE: {
        res = calc_push_number(Node, Node->number);
        while(res) {
            res = calc_update_lifo(Node);
        }
        LOG_DEBUG(CALC, "End");
        res = true;
    } break;
    case START_OF_LINE: {
        res = false;
    } break;
    default: {
    } break;
    }
    return res;
}

static bool calc_prev_open_proc(Calculator_t* const Node) {
    bool res = false;
    Node->number = 0.0;
    switch(Node->cur_char) {
    case '0': {
        // TODO
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
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;
    case '+': {
        // TODO
    } break;
    case '-': {
        // TODO
    } break;
    case '/': {
        res = false;
    } break;
    case '*': {
        res = false;
    } break;
    case ')': {
        res = false;
    } break;
    case '(': {
        // TODO
    } break;
    case ' ': {
    } break;
    case END_OF_LINE: {
        res = false;
    } break;
    case START_OF_LINE: {
        res = false;
    } break;
    default: {
        res = false;
    } break;
    }
    return res;
}

static bool calc_prev_div_proc(Calculator_t* const Node) {
    bool res = false;
    Node->number = 0.0;
    switch(Node->cur_char) {
    case '0': {
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
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;
    case '+': {
    } break;
    case '-': {
    } break;
    case '/': {
    } break;
    case '*': {
    } break;
    case ')': {
    } break;
    case '(': {
    } break;
    case ' ': {
    } break;
    case END_OF_LINE: {
    } break;
    case START_OF_LINE: {
    } break;
    default: {
    } break;
    }
    return res;
}

static bool calc_prev_xor_proc(Calculator_t* const Node) {
    bool res = false;
    Node->number = 0.0;
    switch(Node->cur_char) {
    case '0': {
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
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;

    case '+': {
        res = false;
    } break;
    case '-': {
        res = false;
    } break;
    case '/': {
        res = false;
    } break;
    case '*': {
        res = false;
    } break;

    case '^': {
        res = false;
    } break;

    case ')': {
        res = false;
    } break;
    case '(': {
        // TODO
    } break;
    case ' ': {
    } break;
    case END_OF_LINE: {
        res = false;
    } break;
    case START_OF_LINE: {
        res = false;
    } break;
    default: {
    } break;
    }
    return res;
}

static bool calc_prev_mul_proc(Calculator_t* const Node) {
    bool res = false;
    Node->number = 0.0;
    switch(Node->cur_char) {
    case '0': {
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
        if('*' != Node->prev_prev_char) {
            res = calc_push_operation(Node, OPERATION_MULTIPLICATION);
        }
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;

    case '+': {
        res = false;
    } break;
    case '-': {
        // TODO
        res = true;
    } break;
    case '/': {
        res = false;
    } break;
    case '*': {
        res = calc_push_operation(Node, OPERATION_POW);
    } break;
    case ')': {
        res = false;
    } break;
    case '(': {
        // TODO
    } break;
    case ' ': {
    } break;
    case END_OF_LINE: {
        res = false;
    } break;
    case START_OF_LINE: {
        res = false;
    } break;
    default: {
    } break;
    }
    return res;
}

static bool calc_prev_sub_proc(Calculator_t* const Node) {
    bool res = false;
    Node->number = 0.0;
    switch(Node->cur_char) {
    case '0': {
    } break;
    case '1': {
    } break;
    case '2': {
    } break;
    case '3': {
    } break;
    case '4': {
    } break;
    case '5': {
    } break;
    case '6': {
    } break;
    case '7': {
    } break;
    case '8': {
    } break;
    case '9': {
    } break;
    case '+': {
    } break;
    case '-': {
    } break;
    case '/': {
    } break;
    case '*': {
    } break;
    case ')': {
    } break;
    case '(': {
    } break;
    case ' ': {
    } break;
    case END_OF_LINE: {
    } break;
    case START_OF_LINE: {
    } break;
    default: {
    } break;
    }
    return res;
}

static bool calc_prev_sum_proc(Calculator_t* const Node) {
    bool res = false;
    Node->number = 0.0;
    switch(Node->cur_char) {
    case '0': {
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
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;
    case '+': {
        res = false;
    } break;
    case '-': {
    } break;
    case '/': {
        res = false;
    } break;
    case '*': {
        res = false;
    } break;
    case ')': {
        res = false;
    } break;
    case '(': {
    } break;
    case ' ': {
    } break;
    case END_OF_LINE: {
    } break;
    case START_OF_LINE: {
    } break;
    default: {
    } break;
    }
    return res;
}

static bool calc_prev_digit_proc(Calculator_t* const Node) {
    bool res = false;

    switch(Node->cur_char) {
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
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;
    case ' ': {
        LOG_DEBUG(CALC, "SpotNumber %f", Node->number);
    } break;
    case '+': {
        res = calc_push_number(Node, Node->number);
        res = calc_push_operation(Node, OPERATION_SUM);
        calc_update_lifo(Node);
    } break;
    case '-': {
        res = calc_push_number(Node, Node->number);
        res = calc_push_operation(Node, OPERATION_SUBTRACTION);
        calc_update_lifo(Node);
    } break;
    case '*': {
        res = calc_push_number(Node, Node->number);
        // res = calc_push_operation(Node, OPERATION_MULTIPLICATION);
    } break;
    case '^': {
        res = calc_push_number(Node, Node->number);
        res = calc_push_operation(Node, OPERATION_XOR);
    } break;
    case '/': {
        res = calc_push_number(Node, Node->number);
        res = calc_push_operation(Node, OPERATION_DIVISION);
    } break;
    case '(': {
        res = calc_push_number(Node, Node->number);
        res = calc_push_operation(Node, OPERATION_MULTIPLICATION);

    } break;
    case ')': {
        res = calc_push_number(Node, Node->number);
        calc_update_lifo(Node);
    } break;

    case END_OF_LINE: {
        res = calc_push_number(Node, Node->number);
        while(res) {
            res = calc_update_lifo(Node);
        }
        LOG_DEBUG(CALC, "End");
        res = true;
    } break;

    default: {
        LOG_ERROR(CALC, "UndefChar [%c]", Node->cur_char);
    } break;
    }

    return res;
}

static bool calc_prev_init_proc(Calculator_t* const Node) {
    bool res = false;
    LOG_DEBUG(CALC, "ProcPrevInit");
    switch(Node->cur_char) {
    case '0':
        LOG_ERROR(CALC, "FirstZeroErr");
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
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_char, &digit);
        Node->number *= 10.0;
        Node->number += ((double)digit);
    } break;
    case ' ':
        break;
    case '+':
        break;
    case '-':
        break;
    case '*':
        res = false;
        break;
    case '/':
        res = false;
        break;
    case '(':
        res = true;
        break;
    case ')':
        res = false;
        break;
    case START_OF_LINE:
        res = false;
        break;
    default:
        break;
    }
    return res;
}

static bool calculator_proc(Calculator_t* const Node) {
    LOG_DEBUG(CALC, "Proc %s", CalcNode2Str(Node));
    // LifoArrayDiag(&Node->LifoArray,PROTO_STACK_FRAME);
    bool res = false;
    switch(Node->prev_char) {
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
        res = calc_prev_digit_proc(Node);

        Node->NumberFsm.cur_letter = Node->cur_char;
        number_proc_one(&Node->NumberFsm);
    } break;
    case ' ':
        break;
    case '^': {
        res = calc_prev_xor_proc(Node);
    } break;

    case '*': {
        res = calc_prev_mul_proc(Node);
    } break;
    case '+': {
        res = calc_prev_sum_proc(Node);
        Node->NumberFsm.cur_letter = Node->cur_char;
        number_proc_one(&Node->NumberFsm);
    } break;
    case '-': {
        res = calc_prev_sub_proc(Node);
        Node->NumberFsm.cur_letter = Node->cur_char;
        number_proc_one(&(Node->NumberFsm));
    } break;
    case '/': {
        res = calc_prev_div_proc(Node);
    } break;
    case '(': {
        res = calc_prev_open_proc(Node);
    } break;
    case ')': {
        res = calc_prev_close_proc(Node);
    } break;
    case START_OF_LINE:
        res = calc_prev_init_proc(Node);
        break;
    default:
        break;
    }

    Node->prev_prev_char = Node->prev_char;
    Node->prev_char = Node->cur_char;
    return res;
}

static bool calculator_init(Calculator_t* const Node, const char* const text) {
    bool res = false;
    LOG_DEBUG(CALC, "Init");
    Node->prev_char = START_OF_LINE;
    Node->prev_prev_char = START_OF_LINE;
    Node->number = 0.0;
    Node->text = text;
    res = lifo_arr_init(&Node->LifoArray, Array, ARRAY_SIZE(Array));
    if(res) {
        LOG_DEBUG(CALC, "LifoInitOk");
    } else {
        LOG_ERROR(CALC, "LifoInitError");
    }

    res = text_2_number_init(&Node->NumberFsm);

    // res=stack_frame_init_ll(&Node->StackFrame);
    return res;
}

bool calculator_calc(const char* const text, double* const result) {
    bool res = false;
    int len = strlen(text);
    LOG_DEBUG(CALC, "text [%s] Size %d byte", text, len);
    if(text) {
        if(0 < len) {
            if(result) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        Calculator_t Obj;
        calculator_init(&Obj, text);

        uint32_t ok = 0;
        uint32_t i = 0;
        for(i = 0; i < len; i++) {
            Obj.cur_char = text[i];
            res = calculator_proc(&Obj);
            if(res) {
                ok++;
            } else {
                LOG_ERROR(CALC, "ParseError Text[%d]=%c", i, text[i]);
                break;
            }
        }

        Obj.cur_char = END_OF_LINE;
        res = calculator_proc(&Obj);

        if(ok == len) {
            res = true;
            Array_t LifoTop = {0};
            res = lifo_arr_peek_num(&Obj.LifoArray, 0, &LifoTop);
            if(res) {
                res = stack_frame_parse_number(&LifoTop, result);
            }
        } else {
            res = false;
        }
    }
    return res;
}
