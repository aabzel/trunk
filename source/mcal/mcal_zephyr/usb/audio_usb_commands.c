#include "audio_usb_commands.h"

#include "log.h"
#include "audio_usb.h"
#include "audio_usb_config.h"


bool audio_usb_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    } else {
        LOG_ERROR(USB, "Usage: aui");
    }
    if(res) {
        int ret = audio_usb_init();
        if(0 == ret) {
        	LOG_INFO(USB, "InitOk");
        	res = true;
        }else{
            LOG_ERROR(USB, "InitErr");
            res = false;
        }
    }
    return res;
}

bool audio_usb_diag_command(int32_t argc, char* argv[]) {
    bool res = true;
    if(0==argc){
    	res = true;
    }
    if(res){
        LOG_INFO(USB,"spin %u",AudioUsbInstance.spin);
        LOG_INFO(USB,"Rx %u",AudioUsbInstance.rx_cnt);
        LOG_INFO(USB,"RxByte %u",AudioUsbInstance.rx_byte);
        LOG_INFO(USB,"Tx %u",AudioUsbInstance.tx_cnt);
        LOG_INFO(USB,"MinSize: %u",AudioUsbInstance.min_size);
        LOG_INFO(USB,"MaxSize: %u",AudioUsbInstance.max_size);
        LOG_INFO(USB,"Init: %u",AudioUsbInstance.init);
        LOG_INFO(USB,"Err: %u",AudioUsbInstance.err_cnt);
        LOG_INFO(USB,"FifoRxByte: %u", AudioUsbInstance.fifo_rx_byte_cnt);
    }else{
		LOG_ERROR(USB,"Usage: aud");
    }
    return res;
}
