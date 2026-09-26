#include "ublox_neo_6m_config.h"

#include "data_utils.h"
#include "ublox_neo_6m_types.h"

const uBloxNeo6mConfig_t uBloxNeo6mConfig[] = {
    {.num=1, .uart_num=6, .valid=true, },
};

uBloxNeo6mHandle_t uBloxNeo6mInstance[]={
    {.num=1, .valid=true, }
};

COMPONENT_GET_CNT(uBloxNeo6m, ublox_neo_6m)

