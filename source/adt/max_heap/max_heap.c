#include "max_heap.h"

#include "code_generator.h"
#include "common_functions.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(MaxHeap, max_heap)
COMPONENT_GET_CONFIG(MaxHeap, max_heap)

static bool max_heap_init_common(const BinHeapConfig_t* const Config, BinHeapHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->array = Config->array;
            Node->capacity = Config->capacity;
            Node->name = Config->name;
            res = false;
        }
    }
    return res;
}

static bool swap_i32(int32_t* const a, int32_t* const b) {
    bool res = false;
    if(a) {
        if(b) {
            int32_t temp = *a;
            *a = *b;
            *b = temp;
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool MaxHeapIsValidConfig(const BinHeapConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(MAX_HEAP, "%u,NameErr", Config->num);
        }

        ifn(Config->capacity) {
            res = false;
            LOG_ERROR(MAX_HEAP, "%u,CapacityErr", Config->num);
        }

        ifn(Config->array) {
            res = false;
            LOG_ERROR(MAX_HEAP, "%u,MemErr", Config->num);
        }
    }
    return res;
}

bool max_heap_init_custom(void) {
    bool res = false;
    // LOG_INFO(MAX_HEAP, "Version:%s", MAX_HEAP_VERSION);
    return res;
}

// Функция для восстановления свойства кучи вверх
static bool max_heap_up(BinHeapHandle_t* Node, int index) {
    bool res = true;
    while(index > 0 && Node->array[(index - 1) / 2] < Node->array[index]) {
        res = swap_i32(&(Node->array[(index - 1) / 2]), &(Node->array[index]));
        index = (index - 1) / 2;
    }
    return res;
}

/*
 Function to add an element to a heap
 */
bool max_heap_push(BinHeapHandle_t* Node, const int32_t value) {
    // LOG_DEBUG(MAX_HEAP,"N:%u,NewVal:%d",Node->num, value);
    bool res = false;
    if(Node->size == Node->capacity) {
        LOG_ERROR(MAX_HEAP, "HeapIsFull!");
        res = false;
    } else {
        Node->array[Node->size] = value;
        Node->size++;
        res = max_heap_up(Node, Node->size - 1);
    }

    log_res(MAX_HEAP, res, "Push");

    return res;
}

// Function to restore the heap property down
static bool max_heap_make_down(BinHeapHandle_t* Node, const int index) {
    bool res = true;
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(Node->array[largest] < Node->array[left]) {
        if(left < Node->size) {
            largest = left;
        }
    }

    if(Node->array[largest] < Node->array[right]) {
        if(right < Node->size) {
            largest = right;
        }
    }

    if(largest != index) {
        res = swap_i32(&Node->array[index], &Node->array[largest]);
        max_heap_make_down(Node, largest);
    }

    return res;
}

bool max_heap_pull(BinHeapHandle_t* const Node, int32_t* const out_val) {
    bool res = false;
    if(out_val) {
        int32_t root_val = 0;
        if(1 == Node->size) {
            Node->size--;
            root_val = Node->array[0];
            res = true;
        } else if(Node->size <= 0) {
            res = false;
            LOG_DEBUG(MAX_HEAP, "empty");
        } else {
            root_val = Node->array[0];
            Node->array[0] = Node->array[Node->size - 1];
            Node->size--;
            res = max_heap_make_down(Node, 0);
        }
        *out_val = root_val;
        // LOG_DEBUG(MAX_HEAP, "N:%u,OutVal:%d", Node->num, root_val);
    }

    return res; // Возвращаем максимальный элемент
}

bool max_heap_delete_root(BinHeapHandle_t* const Node) {
    bool res = false;
    int32_t root_value = 0;
    res = max_heap_pull(Node, &root_value);
    return res;
}

uint32_t max_heap_size(const BinHeapHandle_t* const Node) {
    uint32_t size = 0;
    if(Node) {
        size = Node->size;
    }
    return size;
}

static bool max_heap_is_valid_ll(const BinHeapHandle_t* const Node, const uint32_t parent) {
    bool res = true;
    if (parent < Node->size) {
        uint32_t left = 2 * parent + 1;
        uint32_t right = 2 * parent + 2;
        res = true;

        if (res) {
            if (left < Node->size) {
                if (Node->array[left] <= Node->array[parent]) {
                    res = max_heap_is_valid_ll(Node, left);
                } else {
                    LOG_ERROR(MAX_HEAP, "NotHeap:%u->%u",parent,left);
                    res = false;
                }
            }
        }

        if (res) {
            if (right < Node->size) {
                if (Node->array[right] <= Node->array[parent]) {
                    res = max_heap_is_valid_ll(Node, right);
                } else {
                    LOG_ERROR(MAX_HEAP, "NotHeap:%u->%u",parent,right);
                    res = false;
                }
            }
        }
    }

    return res;
}

bool max_heap_is_valid(const BinHeapHandle_t* const Node){
    bool res = false;
    if(Node->size){
        res = max_heap_is_valid_ll(Node, 0);
    }
    return res;
}

static int32_t max_heap_check_node(BinHeapHandle_t* const Node, const int32_t value, uint32_t my_index) {
    int32_t index = -1;
    if (my_index < Node->size) {
        if (value == Node->array[my_index]) {
            index = my_index;
        } else {
            if (value < Node->array[my_index]) {
                uint32_t left = 2 * my_index + 1;
                index = max_heap_check_node(Node, value, left);
                if (-1 == index) {
                    uint32_t right = 2 * my_index + 2;
                    index = max_heap_check_node(Node, value, right);
                }
            } else {
                index = -1;
            }
        }
    }
    return index;
}

bool max_heap_delete(BinHeapHandle_t* const Node, const int32_t value){
    bool res = false;
    int32_t del_index = max_heap_check_node(Node, value, 0);
    if(0 <= del_index) {
        swap_i32(&Node->array[del_index], &Node->array[Node->size-1]);
        Node->size--;
        res = max_heap_make_down(Node, del_index);
    }
    return res;
}




bool max_heap_check(BinHeapHandle_t* const Node, const int32_t value) {
    bool res = false;
    int32_t index = max_heap_check_node(Node, value, 0);
    if(0<=index) {
         res = true;
    }

    return res;
}

/*
  Look at the max heap root value
 */
bool max_heap_peek(BinHeapHandle_t* const Node, int32_t* const out_val) {
    bool res = false;
    if(out_val) {
        if(Node->size) {
            *out_val = Node->array[0];
            // LOG_DEBUG(MAX_HEAP, "mHeap_%u,Root:%d",Node->num, *out_val);
            res = true;
        }
    }
    return res;
}

/*
  array - in out array
  size - array size
 */
bool max_heap_sort(uint8_t num, int32_t* const array, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < size; i++) {
        res = max_heap_push_h(num, array[i]);
        // LOG_DEBUG(MAX_HEAP, "Push_res:%u", res);
        ok = ok_cnt_update(ok, res);
    }

    if(ok == size) {
        ok = 0;
        for(i = 0; i < size; i++) {
            res = max_heap_pull_h(num, &array[i]);
            // LOG_DEBUG(MAX_HEAP, "Pull_res:%u", res);
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

bool max_heap_init_one_ll(const BinHeapConfig_t* const Config, BinHeapHandle_t* const Node) {
    bool res = false;
    if(Config) {
        // LOG_WARNING(MAX_HEAP, "MAX_HEAP%u", Config->num);
        res = MaxHeapIsValidConfig(Config);
        if(res) {
#ifdef HAS_MAX_HEAP_DIAG
            // LOG_WARNING(MAX_HEAP, "%s", MaxHeapConfigToStr(Config));
#endif
            if(Node) {
                res = max_heap_init_common(Config, Node);
                Node->size = 0;
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(MAX_HEAP, "MAX_HEAP%u,NodeErr", Config->num);
            }
        } else {
            LOG_ERROR(MAX_HEAP, "MAX_HEAP%u,ConfigErr", Config->num);
        }
    } else {
        // LOG_PARN(MAX_HEAP, "MAX_HEAP%u,ConfigErr", Config->num);
    }
    return res;
}

/*
 Hi level API
 */
bool max_heap_init_one(uint8_t num) {
    bool res = false;
    const BinHeapConfig_t* Config = MaxHeapGetConfig(num);
    if(Config) {
        BinHeapHandle_t* Node = MaxHeapGetNode(num);
        if(Node) {
            res = max_heap_init_one_ll(Config, Node);
        }
    }
    return res;
}

bool max_heap_pull_h(uint8_t num, int32_t* const out_val) {
    bool res = false;
    BinHeapHandle_t* Node = MaxHeapGetNode(num);
    if(Node) {
        res = max_heap_pull(Node, out_val);
    }
    return res;
}


bool max_heap_push_h(uint8_t num, const int32_t value) {
    bool res = false;
    BinHeapHandle_t* Node = MaxHeapGetNode(num);
    if(Node) {
        res = max_heap_push(Node, value);
    }
    return res;
}

bool max_heap_delete_h(uint8_t num, int32_t out_val){
    bool res = false;
    BinHeapHandle_t* Node = MaxHeapGetNode(num);
    if(Node) {
        res = max_heap_delete(Node, out_val);
    }
    return res;
}

bool max_heap_check_h(uint8_t num, int32_t out_val) {
    bool res = false;
    BinHeapHandle_t* Node = MaxHeapGetNode(num);
    if(Node) {
        res = max_heap_check(Node, out_val);
    }
    return res;
}

bool max_heap_peek_h(uint8_t num, int32_t* const out_val) {
    bool res = false;
    BinHeapHandle_t* Node = MaxHeapGetNode(num);
    if(Node) {
        res = max_heap_peek(Node, out_val);
    }
    return res;
}

COMPONENT_INIT_PATTERT(MAX_HEAP, MAX_HEAP, max_heap)
