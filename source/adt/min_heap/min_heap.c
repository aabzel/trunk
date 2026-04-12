#include "min_heap.h"

#include "bin_heap.h"
#include "code_generator.h"
#include "common_functions.h"
#include "compiler_const.h"
#include "log.h"

static void min_heap_bubble_up(BinHeapHandle_t* Node, int32_t child_index) {
    while(0 < child_index) {
        int32_t parent_index = (child_index - 1) / 2;
        if(Node->array[parent_index] <= Node->array[child_index]) {
            break;
        } else {
            swap_i32(&Node->array[parent_index], &Node->array[child_index]);
            child_index = parent_index;
        }
    }
}

BinHeapHandle_t* MinHeapGetNode(uint8_t num) {
    BinHeapHandle_t* Node = NULL;
    uint32_t cnt = min_heap_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(num == MinHeapInstance[i].num) {
            if(MinHeapInstance[i].valid) {
                Node = &MinHeapInstance[i];
                break;
            }
        }
    }
    return Node;
}

const BinHeapConfig_t* MinHeapGetConfig(uint8_t num) {
    const BinHeapConfig_t* Config = NULL;
    uint32_t i = 0;
    uint32_t cnt = min_heap_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == MinHeapConfig[i].num) {
            if(MinHeapConfig[i].valid) {
                Config = &MinHeapConfig[i];
                break;
            }
            break;
        }
    }
    return Config;
}

bool min_heap_init_custom(void) {
    bool res = false;
    // LOG_INFO(MIN_HEAP, "Version:%s", MIN_HEAP_VERSION);
    return res;
}

bool min_heap_push(BinHeapHandle_t* Node, const int32_t value) {
    bool res = false;
    if(Node->size < Node->capacity) {
        Node->array[Node->size] = value;
        min_heap_bubble_up(Node, Node->size);
        Node->size++;
        res = true;
    } else {
        LOG_ERROR(MIN_HEAP, "Full");
    }
    return res;
}

static bool min_heap_make_down(BinHeapHandle_t* Node, int32_t index) {
    bool res = true;
    while(index < Node->size) {
        int32_t left_child, right_child, smallest;
        left_child = 2 * index + 1;
        right_child = 2 * index + 2;
        smallest = index;

        if(left_child < Node->size && Node->array[left_child] < Node->array[smallest]) {
            smallest = left_child;
        }
        if(right_child < Node->size && Node->array[right_child] < Node->array[smallest]) {
            smallest = right_child;
        }
        if(smallest == index) {
            break;
        }
        swap_i32(&Node->array[index], &Node->array[smallest]);
        index = smallest;
    }
    return res;
}

bool min_heap_pull(BinHeapHandle_t* const Node, int32_t* const out_val) {
    bool res = true;
    if(0 == Node->size) {
        res = false;
        LOG_DEBUG(MIN_HEAP, "Empty!");
    } else {
        int32_t root_val = 0;
        if(1 == Node->size) {
            Node->size--;
            root_val = Node->array[0];
            res = true;
        } else {
            root_val = Node->array[0];
            Node->array[0] = Node->array[Node->size - 1]; // Move last element to root
            Node->size--;
            min_heap_make_down(Node, 0);
            res = true;
        }
        *out_val = root_val;
        // LOG_DEBUG(MIN_HEAP, "N:%u,OutVal:%d", Node->num, root_val);
    }
    return res;
}

bool min_heap_delete_root(BinHeapHandle_t* const Node) {
    bool res = false;
    int32_t root_value = 0;
    res = min_heap_pull(Node, &root_value);
    if(res) {
        LOG_DEBUG(MIN_HEAP, "DelRoot:%d", root_value);
    }
    return res;
}

/*
  array - in out array
  size - array size
 */
bool min_heap_sort(uint8_t num, int32_t* const array, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < size; i++) {
        res = min_heap_push_h(num, array[i]);
        // LOG_DEBUG(MIN_HEAP, "Push_res:%u", res);
        ok = ok_cnt_update(ok, res);
    }

    if(ok == size) {
        ok = 0;
        for(i = 0; i < size; i++) {
            res = min_heap_pull_h(num, &array[i]);
            // LOG_DEBUG(MIN_HEAP, "Pull_res:%u", res);
            ok = ok_cnt_update(ok, res);
        }
    }

    if(ok == size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
/*
 Hi level API
 */

bool min_heap_pull_h(uint8_t num, int32_t* const out_val) {
    bool res = false;
    BinHeapHandle_t* Node = MinHeapGetNode(num);
    if(Node) {
        res = min_heap_pull(Node, out_val);
    }
    return res;
}

bool min_heap_push_h(uint8_t num, const int32_t value) {
    bool res = false;
    BinHeapHandle_t* Node = MinHeapGetNode(num);
    if(Node) {
        res = min_heap_push(Node, value);
    }
    return res;
}

bool min_heap_peek_h(uint8_t num, int32_t* const out_val) {
    bool res = false;
    BinHeapHandle_t* Node = MinHeapGetNode(num);
    if(Node) {
        res = min_heap_peek(Node, out_val);
    }
    return res;
}

uint32_t min_heap_size(const BinHeapHandle_t* const Node) {
    uint32_t size = 0;
    if(Node) {
        size = Node->size;
    }
    return size;
}

static int32_t min_heap_check_node(BinHeapHandle_t* const Node,
                                   const int32_t value,
                                   uint32_t my_index) {
    int32_t index = -1;
    if (my_index < Node->size) {
        if (value == Node->array[my_index]) {
            index = my_index;
        } else {
            if (Node->array[my_index] < value) {
                uint32_t left = 2 * my_index + 1;
                index = min_heap_check_node(Node, value, left);
                if (-1 == index) {
                    uint32_t right = 2 * my_index + 2;
                    index = min_heap_check_node(Node, value, right);
                }
            } else {
                index = -1;
            }
        }
    }
    return index;
}


bool min_heap_delete(BinHeapHandle_t* const Node, const int32_t value){
    bool res = false;
    int32_t del_index = min_heap_check_node(Node, value, 0);
    if(0 <= del_index) {
        swap_i32(&Node->array[del_index], &Node->array[Node->size-1]);
        Node->size--;
        res = min_heap_make_down(Node, del_index);
    }
    return res;
}


bool min_heap_check(const BinHeapHandle_t* const Node, int32_t const value){
    bool res = false;
    int32_t index = min_heap_check_node(Node, value, 0);
    if(0 <= index) {
         res = true;
    }

    return res;
}



/*
  Look at the min heap root value
 */
bool min_heap_peek(BinHeapHandle_t* const Node, int32_t* const out_val) {
    bool res = false;
    if(out_val) {
        if(Node->size) {
            *out_val = Node->array[0];
            // LOG_DEBUG(MIN_HEAP, "mHeap_%u,Root:%d",Node->num, *out_val);
            res = true;
        }
    }
    return res;
}


bool min_heap_check_h(uint8_t num, const int32_t value){
    bool res= false;
    BinHeapHandle_t* Node = MinHeapGetNode(num);
    if(Node) {
        res = min_heap_check(Node, value);
    }
    return res;
}

bool min_heap_delete_h(uint8_t num, const int32_t val){
    bool res= false;
    BinHeapHandle_t* Node = MinHeapGetNode(num);
    if(Node) {
        res = min_heap_delete(Node, val);
    }
    return res;
}

bool min_heap_init_one_ll(BinHeapConfig_t* Config, BinHeapHandle_t* Node) {
    bool res = false;
    if(Config) {
        // LOG_WARNING(MIN_HEAP, "MIN_HEAP%u", Config->num);
        res = BinHeapIsValidConfig(Config);
        if(res) {
#ifdef HAS_MIN_HEAP_DIAG
            // LOG_WARNING(MIN_HEAP, "%s", MinHeapConfigToStr(Config));
#endif
            if(Node) {
                res = bin_heap_init_common(Config, Node);
                Node->size = 0;
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(MIN_HEAP, "NodeErr %u", Node->num);
            }
        } else {
            LOG_ERROR(MIN_HEAP, "ConfigErr %u", Node->num);
        }
    } else {
        // LOG_PARN(MIN_HEAP, "ConfigErr %u", Node->num);
    }
    return res;
}

bool min_heap_init_one(uint8_t num) {
    bool res = false;
    // LOG_WARNING(MIN_HEAP, "MIN_HEAP%u", num);
    const BinHeapConfig_t* Config = MinHeapGetConfig(num);
    if(Config) {
        BinHeapHandle_t* Node = MinHeapGetNode(num);
        if(Node) {
            res = min_heap_init_one_ll(Config, Node);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(MIN_HEAP, MIN_HEAP, min_heap)
