#include "hashset.h"

#include "crc32.h"
#include "log.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static bool is_hashset_valid(HashSet_t* const Node) {
    bool res = false;
    if(NULL != Node) {
        if(Node->init_done) {
            if(0 < Node->size) {
                if(Node->cnt <= Node->size) {
                    if(NULL != Node->heap) {
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}

/*Array is given outside because dynamic memory prohibited*/
bool hashset_init(HashSet_t* const Node, HashSetEntry_t* heap, uint32_t size) {
    bool res = false;
    LOG_DEBUG(HASHSET, "Init Size:%u", size);
    if(Node && size) {
        if(heap) {
            Node->err_cnt = 0;
            Node->cnt = 0;
            Node->size = size;
            memset(heap, 0, size * sizeof(HashSetEntry_t));
            Node->heap = heap;

            Node->init_done = true;
            res = true;
        }
    }
    return res;
}

uint32_t hashset_check(HashSet_t* Node, uint8_t* mem, uint32_t size) {
    uint32_t cnt = 0;
    LOG_DEBUG(HASHSET, "Check");
    uint32_t i = 0;
    bool res = false;
    res = is_hashset_valid(Node);
    if(res) {
        uint32_t cur_crc = crc32_calc(mem, size);
        LOG_DEBUG(HASHSET, "CheckCrc: 0x%08X", cur_crc);
        for(i = 0; i < Node->size; i++) {
            if(Node->heap[i].crc32 == cur_crc) {
                cnt = Node->heap[i].cnt;
                LOG_DEBUG(HASHSET, "Spot %u", i);
                break;
            }
        }
    }
    return cnt;
}

bool hashset_push(HashSet_t* const Node, const uint8_t* const mem, uint32_t size) {
    bool res = false;
    if(Node && mem && size) {
        LOG_DEBUG(HASHSET, "Push Size:%u", Node->size);
        uint32_t i = 0;
        bool spot = false;
        res = is_hashset_valid(Node);
        if(res) {
            uint32_t cur_crc = crc32_calc(mem, size);
            LOG_DEBUG(HASHSET, "PushCrc: 0x%08X", cur_crc);
            for(i = 0; i < Node->size; i++) {
                if(Node->heap[i].crc32 == cur_crc) {
                    Node->heap[i].cnt++;
                    spot = true;
                    res = true;
                    LOG_DEBUG(HASHSET, "Pushed %u", i);
                    break;
                }
            }
            if(false == spot) {
                LOG_DEBUG(HASHSET, "First");
                for(i = 0; i < Node->size; i++) {
                    if(0 == Node->heap[i].cnt) {
                        Node->heap[i].cnt = 1;
                        Node->heap[i].crc32 = cur_crc;
                        res = true;
                        LOG_DEBUG(HASHSET, "Pushed %u", i);
                        break;
                    }
                }
            }
        }
    }
    return res;
}

bool hashset_pull(HashSet_t* const Node, uint8_t* mem, uint32_t size) {
    bool res = false;
    LOG_DEBUG(HASHSET, "Pull Size %u", Node->size);
    uint32_t i = 0;
    res = is_hashset_valid(Node);
    if(res) {
        uint32_t cur_crc = crc32_calc(mem, size);
        LOG_DEBUG(HASHSET, "PullCrc: 0x%08X", cur_crc);
        for(i = 0; i < Node->size; i++) {
            if(Node->heap[i].crc32 == cur_crc) {
                if(Node->heap[i].cnt) {
                    Node->heap[i].cnt--;
                    res = true;
                } else {
                    Node->heap[i].crc32 = 0;
                }
                break;
            }
        }
    }
    return res;
}

uint32_t hashset_get_count(HashSet_t* const Node) {
    uint32_t ret = 0;
    bool res = false;
    res = is_hashset_valid(Node);
    if(res) {
        ret = Node->cnt;
    }
    return ret;
}

uint32_t hashset_get_size(HashSet_t* const Node) {
    bool res = false;
    uint32_t size = 0;
    res = is_hashset_valid(Node);
    if(res) {
        size = Node->size;
    }
    return size;
}

uint32_t hashset_get_spare(HashSet_t* const Node) {
    bool res = false;
    uint32_t spare = 0;
    res = is_hashset_valid(Node);
    if(res) {
        spare = Node->size - Node->cnt;
    }
    return spare;
}
