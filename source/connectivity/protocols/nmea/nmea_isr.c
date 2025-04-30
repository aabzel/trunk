#include "nmea_isr.h"

#include "fifo_char.h"

bool nmea_proc_byte_isr(NmeaHandle_t* const Node, uint8_t rx_byte){
    bool res = false;
    if(Node){
        res = fifo_push((FifoChar_t* ) &(Node->RxFifo), (char)rx_byte);
        if(res) {
            Node->rx_byte_cnt++;
        } else {
            Node->rx_error_cnt++;
        }
    }
    return res;
}
