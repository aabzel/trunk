#include "dma_mcal.h"

#include "log.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "microcontroller_const.h"

COMPONENT_GET_CONFIG(Dma, dma)
COMPONENT_GET_NODE(Dma, dma)


_WEAK_FUN_ bool DmaIsValidConfig(const DmaConfig_t* const Config) {
    bool res = false ;
    if(Config){
        res = true;
    }
    return res;
}

_WEAK_FUN_ bool dma_init_one(uint8_t num) {
    LOG_ERROR(LG_DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

_WEAK_FUN_ bool dma_init_custom(void) {
    LOG_ERROR(LG_DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

COMPONENT_INIT_PATTERT_CNT(LG_DMA, DMA, dma, DMA_COUNT)
