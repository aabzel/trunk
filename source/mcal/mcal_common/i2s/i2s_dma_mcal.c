
#include "i2s_dma_mcal.h"


bool i2s_dma_restart(uint8_t num){
    return false ;
}

bool i2s_dma_ctrl(uint8_t num, bool on_off){
    return false ;
}


bool i2s_mcal_write_dma(uint8_t num, SampleType_t* const array, size_t size, DmaMode_t mode){
    return false ;
}


bool i2s_mcal_read_dma(uint8_t num, SampleType_t* const array, size_t size, DmaMode_t mode){
    return false ;
}
