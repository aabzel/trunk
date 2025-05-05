#include "keylog.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#endif
#include "log.h"
#include "keyboard.h"
#include "fat_fs_drv.h"
#include "fifo_array.h"
#include "keyboard.h"

KeyLog_t KeyLog = {0};

#ifndef HAS_KEYBOARD
#error "+HAS_KEYBOARD"
#endif

bool save_key(const KeyBoard_t* const KeyNode) {
    bool res = false;
    if (KeyNode) {
        char text[80];
        snprintf(text,sizeof(text),"%s",KeyBoard2Str(KeyNode));
        LOG_DEBUG(KEYLOG,"%s",text);
        res = fat_fs_write(KEYLOG_FILE, text);
        if(false==res){
            LOG_ERROR(FAT_FS, "WriteLineErr File[%s] Text:[%s]",KEYLOG_FILE,text);
        }
    }
    return res;
}

bool keylog_proc(void) {
    bool res = false;

    TbfpProtocol_t* TbfpNode = TbfpIf2Node(IF_FAT_FS);
    uint32_t ok_cnt = 0;
    bool fifo_valid = true;
    while(fifo_valid){
        char rx_byte = 0;
        fifo_valid = fifo_pull(&KeyLog.Fifo, &rx_byte);
        if(fifo_valid) {
            res = tbfp_proc_byte(TbfpNode, rx_byte);
            if(res){
            	ok_cnt++;
            } else {
            	LOG_ERROR(KEYLOG,"ProcByte:0x%x Err",rx_byte);
            }
        }
    }

    if(0 < ok_cnt) {
    	res = true;
    	LOG_DEBUG(KEYLOG,"Proc %u byte",ok_cnt);
    }else {
    	res = false;
    }

    return res;
}

static char heap[KEYLOG_HEAP_SIZE];

bool keylog_mcal_init(void) {
    bool res = true;
    set_log_level(KEYLOG,LOG_LEVEL_INFO);

    res = fifo_init(&KeyLog.Fifo , heap, sizeof(heap));

    //res= fifo_arr_init(&KeyLog.fifo, heap, KEYLOG_HEAP_SIZE);
    if(res) {
        LOG_INFO(KEYLOG,"FifoInitOk");
    }else{
    	LOG_ERROR(KEYLOG,"FifoInitErr");
    }
    return res;
}
