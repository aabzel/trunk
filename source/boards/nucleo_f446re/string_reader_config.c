#include "string_reader_config.h"

#include "data_utils.h"
#include "cli_drv.h"

static char FifoData1[100]={0};
static char LineData1[100]={0};

const StringReaderConfig_t StringReaderConfig[] = {
    { 
    .num = 1, 
    .valid = true,
     .echo = true,
      .cli_num= 1, 
      .interface_if = IF_UART2,
       .if_num = 2,
       .name= "UART2",
        .fifo_heap = FifoData1, 
        .fifo_heap_size=sizeof(FifoData1), 
        .string=LineData1, 
        .string_size= sizeof(LineData1),
          .callback =(handle_string_f)(cli_process_cmd), 
          .feedback_led=2,  
           },
};

StringReaderHandle_t StringReaderInstance[]={
    {.num=1, .valid=true, },
};

uint32_t string_reader_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(StringReaderInstance);
    cnt2 = ARRAY_SIZE(StringReaderConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}
