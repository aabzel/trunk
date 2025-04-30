#include "circular_buffer_index.h"

#include <stdbool.h>

#include "log.h"

bool circular_buffer_index_init(CircularBufferIndexInfo_t* Node, int32_t size) {
    bool res = false;
    LOG_DEBUG(CIRCULAR_BUFFER, "Init,Size:%u", size);
    if(Node) {
        if(size) {
            Node->cur = 0;
            /*To change CirBuffer size in run-time*/
            Node->size = size;
            Node->init = true;
            res = true;
        }
    }
    return res;
}

#if 0
static bool circular_buffer_index_valid(const CircularBufferIndexInfo_t* Node) {
    bool valid = true;

    if(0 == Node->size) {
        valid = false;
    }

    if( Node->size <=Node->cur) {
        valid = false;
    }

    return valid;
}
#endif

/*
 *size - size of physical  array
 *cur - current physical index [0.... (size-1)]
 *need - virtual index [-(size-1).... 0.... (size-1)]
 *
 * (s8,c0,n-1)   -> r7
 * */
int32_t circular_buffer_index_calc_phy_index(int32_t size, int32_t cur, int32_t need) {
    int32_t phy_index = 0;
    // need 6 size 8 cur 4
    if(need < 0) {
        phy_index = cur + need;
        if(phy_index < 0) {
            phy_index += size;
        }
    } else {
        if(need < size) {
            if(size <= (cur + need)) {
                phy_index = (cur + need) - size;
            } else {
                phy_index = cur + need;
            }
        } else {
            // LOG_ERROR(CIRCULAR_BUFFER, "TooBigIndex,Need:%u,Size:%u", need, size);
        }
    }

    LOG_DEBUG(CIRCULAR_BUFFER, "Calc:Size:%d,Cur:%d,Need:%d,PHY:%d", size, cur, need, phy_index);
    // LOG_DEBUG(CIRCULAR_BUFFER, "Size:%u,Cur:%u,Need:%u->Phy:%u", size, cur, need, phy_index);
    return phy_index;
}

uint32_t circular_buffer_index_add(CircularBufferIndexInfo_t* Node) {
    uint32_t phy_index = 0;
    phy_index = circular_buffer_index_calc_phy_index(Node->size, Node->cur, 0);
    if((phy_index + 1) < Node->size) {
        Node->cur = phy_index + 1;
    } else {
        Node->cur = 0;
    }
    return phy_index;
}

uint32_t circular_buffer_index_get(CircularBufferIndexInfo_t* Node) {
    uint32_t phy_index = 0;
    phy_index = circular_buffer_index_calc_phy_index(Node->size, Node->cur, 0);
    return phy_index;
}

/*
 * need
 */

int32_t circular_buffer_index_get_i(CircularBufferIndexInfo_t* Node, int32_t need) {
    int32_t phy_index;
    phy_index = circular_buffer_index_calc_phy_index(Node->size, Node->cur, need);
    return phy_index;
}

uint32_t circular_buffer_index_get_size(const CircularBufferIndexInfo_t* Node) { return Node->size; }

bool circular_buffer_index_diag(CircularBufferIndexInfo_t* Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(CIRCULAR_BUFFER, "Size:%u Cur:%u Init:%u", Node->size, Node->cur, Node->init);
    }
    return res;
}
