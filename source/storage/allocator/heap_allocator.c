#include "heap_allocator.h"

#include <stdbool.h>

#include "allocator_config.h"
#include "log.h"

#ifdef HAS_CORE
#include "core_driver.h"
#endif

uint8_t ucHeap[TOTAL_HEAP_SIZE];

/*Time complexity O(1)*/
bool h_is_allocated(void* addr) {
    bool res = false;
#ifdef HAS_CORE
    res = is_ram_addr((uint32_t)addr);
#else
    res = true;
#endif
    if(res) {
        res = false;
        volatile MemoryChunkHeader_t* MemoryChunkHeader = NULL;
        MemoryChunkHeader = addr - sizeof(MemoryChunkHeader_t);
        if(addr == MemoryChunkHeader->addr) {
            if(0 < MemoryChunkHeader->size) {
                res = true;
            }
        }
    }
    return res;
}

/*Time complexity O(n)*/
static bool h_is_continuously_empty(void* addr, size_t size) {
    bool res = true;
    void* mem = NULL;
    for(mem = addr; mem <= addr + size; mem++) {
        bool res = h_is_allocated(mem);
        if(res) {
            res = false;
            break;
        }
    }
    return res;
}

static bool h_valid_size(size_t size) {
    bool res = false;
    size_t max_size = TOTAL_HEAP_SIZE - sizeof(MemoryChunkHeader_t);
    if(size && (size < max_size)) {
        res = true;
    } else {
#ifdef HAS_HEAP_DEBUG
        LOG_DEBUG(HEAP, "InValidSize Cur:%u Max:%u", size, max_size);
#endif
    }
    return res;
}

/* O(n^2)
 * */
void* h_malloc(size_t size) {
    void* mem = NULL;
    bool res = false;
    /*enter critical section*/
    res = h_valid_size(size);
    if(res) {
        void* addr = NULL;
        void* addr_start = (void*)&ucHeap[0 + sizeof(MemoryChunkHeader_t)];
        void* addr_end = (void*)&ucHeap[TOTAL_HEAP_SIZE - sizeof(MemoryChunkHeader_t)];
        for(addr = addr_start; addr <= addr_end; addr++) {
            res = h_is_allocated(addr);
            if(false == res) {
#ifdef HAS_HEAP_DEBUG
                LOG_DEBUG(HEAP, "SpareAddr 0x%p", addr);
#endif
                res = h_is_continuously_empty(addr, size);
                if(res) {
#ifdef HAS_HEAP_DEBUG
                    LOG_DEBUG(HEAP, "SpareRegion %p %u", addr, size);
#endif
                    MemoryChunkHeader_t* MemoryChunkHeader = NULL;
                    MemoryChunkHeader = addr - sizeof(MemoryChunkHeader_t);
#ifdef HAS_HEAP_DEBUG
                    LOG_DEBUG(HEAP, "Header: %p", MemoryChunkHeader);
#endif
                    MemoryChunkHeader->size = size;
                    MemoryChunkHeader->addr = addr;
                    mem = addr;
                    break;
                }
            } else {
                /*Skip busy memory chunk*/
                MemoryChunkHeader_t* MemoryChunkHeader = addr - sizeof(MemoryChunkHeader_t);
                addr += MemoryChunkHeader->size + sizeof(MemoryChunkHeader_t);
#ifdef HAS_HEAP_DEBUG
                LOG_DEBUG(HEAP, "SkipBusyChunk 0x%p %u Byte", addr, MemoryChunkHeader->size);
                LOG_DEBUG(HEAP, "BysyAddr %p", addr);
#endif
            }
        }
    }
    /*exit critical section*/
    return mem;
}

/*get current number of chunks in heap*/
uint32_t h_count(void) {
    uint32_t cnt = 0;
    bool res = false;
    void* addr = NULL;
    void* addr_start = (void*)&ucHeap[0 + sizeof(MemoryChunkHeader_t)];
    void* addr_end = (void*)&ucHeap[TOTAL_HEAP_SIZE - sizeof(MemoryChunkHeader_t)];
    for(addr = addr_start; addr <= addr_end; addr++) {
        res = h_is_allocated(addr);
        if(res) {
            cnt++;
        }
    }
    return cnt;
}

/*O(1)*/
bool h_free(void* addr) {
    bool res = false;
    /*enter critical section*/
#ifdef HAS_CORE
    res = is_ram_addr((uint32_t)addr);
#else
    res = true;
#endif
    if(res) {
        res = h_is_allocated(addr);
        if(res) {
            MemoryChunkHeader_t* MemoryChunkHeader = NULL;
            MemoryChunkHeader = addr - sizeof(MemoryChunkHeader_t);
            MemoryChunkHeader->size = 0;
            MemoryChunkHeader->addr = 0;
            res = true;
        } else {
            res = false;
            /*May be called from ISR*/
#ifdef HAS_HEAP_DEBUG
            // LOG_ERROR(HEAP,"Addr 0x%08p HasNotBeingAllocated",addr);
#endif
        }
    }
    /*exit critical section*/
    return res;
}

bool h_init(void) {
    bool res = false;
    LOG_INFO(HEAP, "Init");
    res = set_log_level(HEAP, LOG_LEVEL_DEBUG);
    return res;
}

bool h_is_heap_addr(void* addr) {
    bool res = false;
    if((((void*)&ucHeap[0]) <= addr) && (addr <= ((void*)&ucHeap[TOTAL_HEAP_SIZE - 4]))) {
        res = true;
    }
    return res;
}
