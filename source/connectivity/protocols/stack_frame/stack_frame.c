#include "stack_frame.h"

#include <string.h>

#include "code_generator.h"
#include "crc8_autosar.h"
#include "log.h"
#include "protocol.h"
#include "stack_frame_diag.h"
#include "stack_frame_types.h"

COMPONENT_GET_NODE(StackFrame, stack_frame)

COMPONENT_GET_CONFIG(StackFrame, stack_frame)

bool stack_frame_proc(uint8_t num, const uint8_t* const arr, uint16_t length) {
    bool res = false;
    LOG_PROTECTED(STACK_FRAME, "Proc %u byte", length);
    return res;
}

bool stack_frame_init_ll(StackFrameHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->size = 0;
        Node->crc8 = 0;
        memset(Node->data, 0, sizeof(Node->data));
        res = true;
    }

    return res;
}

bool stack_frame_init_one(uint8_t num) {
    bool res = false;
    return res;
}

COMPONENT_INIT_PATTERT(STACK_FRAME, STACK_FRAME, stack_frame)

bool stack_frame_compose_operation(StackFrameHandle_t* const Node, Operation_t operation) {
    bool res = false;
    if(Node) {
        Node->data[0] = STACK_CONTENT_TYPE_OPERATION;
        Node->data[1] = 1;
        Node->data[2] = operation;
        Node->data[3] = crc8_autosar_calc(Node->data, 3);
        Node->size = 4;
        res = true;
    }
    return res;
}

bool stack_frame_compose_double(StackFrameHandle_t* const Node, double value) {
    bool res = false;
    if(Node) {
        Node->data[0] = STACK_CONTENT_TYPE_DOUBLE;
        Node->data[1] = sizeof(double);
        memcpy(&Node->data[2], &value, sizeof(double));
        Node->data[2 + sizeof(double)] = crc8_autosar_calc(Node->data, sizeof(double) + 2);

        Node->size = 3 + sizeof(double);
        res = true;
    }
    return res;
}

bool stack_frame_parse_operation(const Array_t* const Node, Operation_t* const operation) {
    bool res = false;
    if(Node) {
        if(operation) {
            if(Node->pArr) {
                if(SF_OPERATION_SIZE == Node->size) {
                    res = true;
                } else {
                    LOG_ERROR(STACK_FRAME, "ArraySizeErr");
                }
            } else {
                LOG_ERROR(STACK_FRAME, "ArrayPrtErr");
            }
        } else {
            LOG_ERROR(STACK_FRAME, "OpPtrErr");
        }
    } else {
        LOG_ERROR(STACK_FRAME, "ArrayNodeErr");
    }

    if(res) {
        res = false;
        if(STACK_CONTENT_TYPE_OPERATION == Node->pArr[0]) {
            if(1 == Node->pArr[1]) {
                *operation = Node->pArr[2];
                res = true;
            } else {
                LOG_ERROR(STACK_FRAME, "OpSizeErr");
            }
        } else {
            LOG_ERROR(STACK_FRAME, "NotOpErr");
        }
    }
    return res;
}

bool stack_frame_parse_number(const Array_t* const Node, double* const number) {
    bool res = false;
    if(Node) {
        if(number) {
            if(Node->pArr) {
                if(SF_DOUBLE_SIZE == Node->size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
        if(STACK_CONTENT_TYPE_DOUBLE == Node->pArr[0]) {
            if(sizeof(double) == Node->pArr[1]) {
                memcpy(number, &Node->pArr[2], sizeof(double));
                res = true;
            }
        }
    }
    return res;
}
