#include "allocator_commands.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "allocator_config.h"
#include "allocator_types.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif
#include "heap_allocator.h"
#include "log.h"
#include "log_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool heap_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        LOG_INFO(HEAP, "HeapStart 0x%p", &ucHeap[0]);
        LOG_INFO(HEAP, "HeapSize %u Byte %f kByte", TOTAL_HEAP_SIZE, ((double)TOTAL_HEAP_SIZE) / 1024.0);
        LOG_INFO(HEAP, "Cnt:%u", h_count());
        res = true;
    } else {
        LOG_ERROR(HEAP, "Usage: hd");
    }
    return res;
}

bool heap_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        void* addr = NULL;
        static const table_col_t cols[] = {
            {5, "num"},        {12, "addr"},       {6, "size"},
#ifdef HAS_DEBUGGER
            {6, "LinkInHeap"}, {6, "LinkOutHeap"},
#endif
            {6, "val"},
        };
        uint32_t num = 0;
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        MemoryChunkHeader_t* MemoryChunkHeader = NULL;
        char temp_str[120];
        char val_str[120];
        for(addr = (void*)&ucHeap[0 + sizeof(MemoryChunkHeader_t)]; addr <= (void*)&ucHeap[TOTAL_HEAP_SIZE - 1];
            addr++) {
            res = h_is_allocated(addr);
            if(res) {
                num++;
#ifdef HAS_DEBUGGER
                LinkCounter_t LinkCounter = {0, 0};
                res = h_count_link(addr, &LinkCounter);
#endif
                MemoryChunkHeader = addr - sizeof(MemoryChunkHeader_t);
                strcpy(val_str, "?");
                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s %08p " TSEP, temp_str, addr);
                snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)MemoryChunkHeader->size);
#ifdef HAS_DEBUGGER
                snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)LinkCounter.in_heap);
                snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)LinkCounter.out_heap);
#endif
                res = hex2ascii(addr, MemoryChunkHeader->size, (uint8_t*)val_str, sizeof(val_str));
                snprintf(temp_str, sizeof(temp_str), "%s 0x%s " TSEP, temp_str, val_str);
                cli_printf(TSEP " %3u %s" CRLF, num, temp_str);
                res = true;
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(HEAP, "Usage: hsc");
    }
    return res;
}

bool heap_malloc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size;
    if(1 == argc) {
        res = try_str2uint32(argv[0], &size);
        if(false == res) {
            LOG_ERROR(HEAP, "ParseErr size [%s]", argv[0]);
        }
    }
    if(res) {
        void* addr = h_malloc(size);
        if(addr) {
            LOG_INFO(HEAP, "Alloc %u Bytes Ok Addr:0x%08p", size, addr);
        } else {
            LOG_ERROR(HEAP, "Alloc %u Bytes Err", size);
        }
    } else {
        LOG_ERROR(HEAP, "Usage: hpm size");
    }
    return res;
}

bool heap_free_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t addr = 0;
    void* addrPtr = NULL;
    if(1 == argc) {
        res = try_str2uint32(argv[0], &addr);
        if(false == res) {
            LOG_ERROR(HEAP, "ParseErr Addr [%s]", argv[0]);
        }
    }
    if(res) {
        addrPtr = (void*)addr;
        res = h_free(addrPtr);
        if(res) {
            LOG_INFO(HEAP, "Free Ok Addr:0x%08p", addrPtr);
        } else {
            LOG_ERROR(HEAP, "Free Addr:0x%08p Err", addrPtr);
        }
    } else {
        LOG_ERROR(HEAP, "Usage: hf addr");
    }
    return res;
}
