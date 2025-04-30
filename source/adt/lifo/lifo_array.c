#include "lifo_array.h"

#include "array.h"
#include "lifo_array_diag.h"
#include "log.h"

#include <stdlib.h>
#include <string.h>

bool is_lifo_arr_valid(LifoArray_t *const Node) {
    bool res = false;
    res = lifo_index_valid(&Node->lifoState);
    if ((NULL != Node) && (Node->init_done) && res) {
        res = true;
    } else {
        LOG_ERROR(LIFO, "ArrayErr");
        res = false;
    }
    return res;
}

bool lifo_arr_init(LifoArray_t *const Node, Array_t *const heap, LifoIndex_t capacity) {
    bool res = false;
    if ((NULL != Node) && (0 < capacity)) {
        if (heap) {
            (void) memset(heap, 0x00, capacity * (sizeof(Array_t)));
            lifo_index_init(&(Node->lifoState), capacity);
            Node->pDataArray = heap;
            Node->init_done = true;
            res = true;
        }
    }
    return res;
}

LifoIndex_t lifo_arr_get_count(LifoArray_t *const Node) {
    LifoIndex_t ret;
    ret = Node->lifoState.count;
    return ret;
}

LifoIndex_t lifo_arr_get_size(LifoArray_t *const Node) {
    LifoIndex_t ret;
    ret = Node->lifoState.size;
    return ret;
}

bool lifo_arr_push(LifoArray_t *const Node, Array_t Item) {
    bool res = false;
    res = is_lifo_arr_valid(Node);
    if (res) {
        if (Node->lifoState.count < Node->lifoState.size) {
            res = true;
        } else {
            res = false;
        }
    }
    if (res) {
        Node->pDataArray[Node->lifoState.count] = Item;
        (void) lifo_index_add(&(Node->lifoState));
        res = true;
    }
    return res;
}

bool lifo_arr_pull(LifoArray_t *const Node, Array_t *const node) {
    bool res = false;
    res = is_lifo_arr_valid(Node);

    if (res) {
        if (0u < Node->lifoState.count) {
            res = true;
        } else {
            res = false;
        }
    }
    if (res) {
        *node = Node->pDataArray[Node->lifoState.count - 1];
        memset(&Node->pDataArray[Node->lifoState.count - 1], 0x00, sizeof(Array_t));
        (void) lifo_index_get(&(Node->lifoState));
    }
    return res;
}

bool lifo_arr_pack_frame(uint8_t *out_buf, uint32_t buf_size, LifoArray_t *const Node,
        uint32_t *buff_len) {
    bool res = false;
    if (out_buf && (0 < buf_size) && Node) {
        uint32_t rem_size = buf_size;
        uint32_t frame_cnt = 0;
        uint32_t index = 0;
        Array_t Item = { .size = 0, .pArr = NULL };
        do {
            res = lifo_arr_peek(Node, &Item);
            if (res) {
                if (Item.pArr) {
                    if (Item.size < rem_size) {
                        memcpy(&out_buf[index], Item.pArr, Item.size);
                        frame_cnt++;
                        index += Item.size;
                        rem_size -= Item.size;
                        res = lifo_arr_del_first(Node);
                    } else {
                        break;
                    }
                } else {
                    res = false;
                }
            } else {
                res = true;
                break;
            }
        } while (0 < rem_size);
        if (buff_len) {
            *buff_len = buf_size - rem_size;
        }
    }
    return res;
}

bool lifo_arr_del_first(LifoArray_t *const Node) {
    bool res = false;
    Array_t Item = { 0, NULL };
    res = lifo_arr_pull(Node, &Item);
    if (res) {
        res = false;
        if (Item.size) {
            if (Item.pArr) {
                res = true;
                free(Item.pArr);
            }
        }
    }
    return res;
}

bool lifo_arr_delete_cnt(const LifoArray_t *const Node, uint32_t cnt) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    for (i = 0; i < cnt; i++) {
        res = lifo_arr_del_first(Node);
        if (res) {
            ok++;
        }
    }
    if (ok == cnt) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
