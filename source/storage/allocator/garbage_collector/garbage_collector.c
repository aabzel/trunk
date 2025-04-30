
#include "garbage_collector.h"
#include "log.h"
#include "heap_allocator.h"

GarbageCollector_t GarbageCollector={.free_cnt=0,};

bool garbage_collector_proc(void){
	bool res = false;
    register void* heap_addr = NULL;
    for(heap_addr=(void*)&ucHeap[ 0+sizeof(MemoryChunkHeader_t) ];
    		heap_addr<=(void*)&ucHeap[ TOTAL_HEAP_SIZE-1 ];
    		heap_addr++){
        res = h_is_allocated(heap_addr);
        if(res){
            LinkCounter_t LinkCounter={.in_heap=0,.out_heap=0};
            res= h_count_link( heap_addr,&LinkCounter);
            if(LinkCounter.out_heap<=1 && (1==LinkCounter.in_heap)){
            	LOG_PARN(HEAP,"LackIfLinkForAddr 0x%p", heap_addr);
            	res=h_free(heap_addr);
            	if(res){
            		GarbageCollector.free_cnt++;
            	}
            }
          //  res = true;
        }
    }
	return res;
}
