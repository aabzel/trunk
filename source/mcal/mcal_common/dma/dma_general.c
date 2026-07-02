#include "dma_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "dma_config.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "time_mcal.h"

COMPONENT_GET_CONFIG(Dma, dma)
COMPONENT_GET_NODE(Dma, dma)

_WEAK_FUN_
bool dma_memcpy(void* const destination, const void* const source, uint32_t n) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool DmaIsValidConfig(const DmaConfig_t* const Config) {
    bool res = false;
    if(Config) {
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

_WEAK_FUN_
bool dma_stop(uint8_t num) {
    LOG_ERROR(LG_DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

_WEAK_FUN_
bool dma_start(uint8_t num, uint32_t src_address, uint32_t dst_address, uint32_t bytes) {
    bool res = false;
    LOG_ERROR(LG_DMA, "%s NotInplemented", __FUNCTION__);
    return res;
}

COMPONENT_INIT_PATTERT_CNT(LG_DMA, DMA, dma, DMA_COUNT)

#if 0
bool dma_mcal_init(void) {
    bool res = true;
    res = dma_init_custom();
    uint32_t ok = 0;
    uint32_t cnt = dma_get_cnt();
    (void) cnt ;
    uint8_t num = 0;
    for(num = 0; num <= DMA_COUNT; num++) {
        res = dma_init_one(num);
        if(res) {
            ok++;
        } else {
        }
    }
    res = is_equal_u32(ok, DMA_COUNT);
    return res;
}
#endif
