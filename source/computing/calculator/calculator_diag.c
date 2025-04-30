#include "calculator_diag.h"

#include <stdio.h>

const char* CalcNode2Str(const Calculator_t* const  Node) {
    static char name[80]="";
    snprintf(name,
            sizeof(name),
            "Text[%s], Prev:[..%c%c],Cur: [%c]",
            Node->text,
            Node->prev_prev_char,
            Node->prev_char,
            Node->cur_char);
    return name;
}

const char* Operation2Str(Operation_t op){
    const char* name = "?";
    switch( (uint8_t) op){
        case OPERATION_SUM: name = "+";break;
        case OPERATION_SUBTRACTION:name = "-"; break;
        case OPERATION_MULTIPLICATION: name = "*";break;
        case OPERATION_DIVISION: name = "/";break;
        case OPERATION_XOR: name = "xor";break;
        case OPERATION_POW: name = "pow";break;
        case OPERATION_AND: name = "and";break;
        case OPERATION_OR: name = "or";break;

    default: name = "Err";break;
    }
    return name;
}

const char* OperationNode2Str(const OperationData_t* const Node){
    static char name[80]="";
    snprintf(name,
            sizeof(name),
            "%f %s %f",
            Node->val_left,
            Operation2Str(Node->operation),
            Node->val_right );
    return name;
}
