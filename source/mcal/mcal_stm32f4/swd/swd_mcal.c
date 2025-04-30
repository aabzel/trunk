#include "swd_drv.h"

#include <stdbool.h>
#include <stdint.h>

#include "log.h"
#include "stm32f4xx_hal.h"

volatile int32_t ITM_RxBuffer=ITM_RXBUFFER_EMPTY;


bool swd_write(uint8_t* tx_array, uint16_t tx_array_len) {
    bool res = false;
    if(tx_array && tx_array_len){

        LOG_INFO(SWD, "Send Len: %u",tx_array_len);
        uint32_t i = 0 ;
        for(i=0;i<tx_array_len;i++){
            ITM_SendChar(tx_array[i]);
            res = true;
        }
    }
    return res;
}

bool swd_read( uint8_t* rx_array, uint16_t rx_array_len) {
    bool res = false;
    uint32_t i = 0 ;
    for(i=0;i<rx_array_len;i++){
      int32_t val = ITM_ReceiveChar ();
      if(-1!=val){
    	  rx_array[i]=val;
      }
    }
    return res;
}

bool swd_proc(void){
	bool res = false;

	int32_t ret= ITM_CheckChar();
	if(1==ret){
	    LOG_INFO(SWD,"RxChar");
    	int32_t val = ITM_ReceiveChar();
        if(-1!=val){
        	res = true;
            LOG_INFO(SWD,"[%c]",val);
        }
	}
    return res;
}

static uint8_t tx_array[]={0x55,0x31,0x55};
bool swd_init(void) {
    bool res = true;
    res =  swd_write(tx_array, sizeof(tx_array));
    return res;
}
