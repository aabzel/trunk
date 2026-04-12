#include "writer_config.h"

#include "data_utils.h"
#include "writer_types.h"

WriterHandle_t* curWriterPtr = NULL;

void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);

const WriterConfig_t WriterConfig[] = {
};

WriterHandle_t WriterInstance[] = {
};

uint32_t writer_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(WriterInstance);
    cnt2 = ARRAY_SIZE(WriterConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
