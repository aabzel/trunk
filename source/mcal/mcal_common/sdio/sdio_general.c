#include "sdio_mcal.h"

#include "sdio_config.h"
#include "sdio_types.h"

#ifdef HAS_IO_BANG
#error "SDIO component prohibited in IO-BANG build"
#endif

SdioHandle_t* SdioGetNode(uint8_t num) {
    SdioHandle_t* SdioNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < sdio_get_cnt(); i++) {
        if(num == SdioInstance[i].num) {
            if(SdioInstance[i].valid) {
                SdioNode = &SdioInstance[i];
                break;
            }
        }
    }
    return SdioNode;
}

const SdioConfig_t* SdioGetConfNode(uint8_t num) {
    const SdioConfig_t* SdioConfNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < sdio_get_cnt(); i++) {
        if(num == SdioConfig[i].num) {
            if(SdioConfig[i].valid) {
                SdioConfNode = &SdioConfig[i];
            }
        }
    }
    return SdioConfNode;
}

bool SdioIsValid(uint8_t num) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < sdio_get_cnt(); i++) {
        if(num == SdioConfig[i].num) {
            res = true;
        }
    }
    return res;
}
