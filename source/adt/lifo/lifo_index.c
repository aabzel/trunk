#include "lifo_index.h"

#include "log.h"

#include <stdbool.h>
#include <stddef.h>

bool lifo_index_init(LifoIndexInfo_t* Node, LifoIndex_t size) {
    bool res = false;
    if(Node && size) {
        Node->size = size;
        Node->count = 0U;
        Node->errors = false;
        res = true;
    } else {
        LOG_ERROR(LIFO, "InitErr");
    }
    return res;
}

bool lifo_index_valid(const LifoIndexInfo_t* Node) {
    bool valid = true;
    if(Node->errors) {
        valid = false;
    }
    if(Node->size < 0) {
        valid = false;
    }
    if(Node->size < Node->count) {
        valid = false;
    }
    return valid;
}

LifoIndex_t lifo_index_add(LifoIndexInfo_t* Node) {
    LifoIndex_t index = 0;
    bool res = lifo_index_valid(Node);
    if(res) {
        if(Node->count < Node->size) {
            index = Node->count;
            Node->count++;
        } else {
            index = Node->count - 1;
            LOG_ERROR(LIFO, "Overflow %u", Node->size);
        }
    } else {
        index = Node->count - 1;
        LOG_ERROR(LIFO, "Err");
    }
    return index;
}

LifoIndex_t lifo_index_get(LifoIndexInfo_t* Node) {
    LifoIndex_t index = 0;
    bool res = lifo_index_valid(Node);
    if(res) {
        if(1 <= Node->count) {
            index = Node->count - 1;
            Node->count--;
        } else {
            LOG_ERROR(LIFO, "Empty!");
        }
    }
    return index;
}

LifoIndex_t lifo_index_get_cnt(const LifoIndexInfo_t* Node) { return Node->count; }

LifoIndex_t lifo_index_get_size(const LifoIndexInfo_t* Node) { return Node->size; }

LifoIndex_t lifo_index_get_spare(const LifoIndexInfo_t* Node) { return Node->size - Node->count; }
