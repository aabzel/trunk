#include "sdio_mcal.h"

#include "code_generator.h"
#include "sdio_config.h"
#include "sdio_types.h"

COMPONENT_GET_NODE(Sdio, sdio)
COMPONENT_GET_CONFIG(Sdio, sdio)

#ifdef HAS_IO_BANG
#error "SDIO component prohibited in IO-BANG build"
#endif

static bool sdio_init_custom(void) {
    bool res = true;
    return res;
}

bool sdio_init_common(const SdioConfig_t* const Config, SdioHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->name = Config->name;
            Node->bit_rate_hz = Config->bit_rate_hz;
            Node->interrupt_on = Config->interrupt_on;
            Node->move_mode = Config->move_mode;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool SdioIsValidConfig(const SdioConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(LG_SDIO, "NameErr");
            res = false;
        }

        ifn(0 < Config->bit_rate_hz) {
            LOG_ERROR(LG_SDIO, "BitRate,Err");
            res = false;
        }

        ifn(0 < Config->move_mode) {
            LOG_ERROR(LG_SDIO, "MoveMode,Err");
            res = false;
        }
    }
    return res;
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

COMPONENT_INIT_PATTERT(LG_SDIO, SDIO, sdio)
COMPONENT_PROC_PATTERT(LG_SDIO, SDIO, sdio)
