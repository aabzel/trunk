#include "gpio_dac_mcal.h"

#include "code_generator.h"
#include "fifo_char.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(GpioDac, gpio_dac)
COMPONENT_GET_CONFIG(GpioDac, gpio_dac)

/*ISO-26262 require verify configuration*/
bool GpioDacIsValidConfig(const GpioDacConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(GPIO_DAC, "GPIO_DAC_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->PadOut.byte) {
            LOG_ERROR(GPIO_DAC, "GPIO_DAC_%u,PadOut,Err", Config->num);
            res = false;
        }

        ifn(Config->timer_num) {
            LOG_ERROR(GPIO_DAC, "GPIO_DAC_%u,timer_num,Err", Config->num);
            res = false;
        }

        ifn(Config->sample_freq_hz) {
            LOG_ERROR(GPIO_DAC, "GPIO_DAC_%u,sample_freq_hz,Err", Config->num);
            res = false;
        }

    }
    return res;
}

static bool gpio_dac_init_custom(void) {
    bool res = false;
    LOG_INFO(GPIO_DAC, "Version:%s", GPIO_DAC_VERSION);
    return res;
}

bool gpio_dac_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(GPIO_DAC, "GPIO_DAC_%u,Proc", num);
    GpioDacHandle_t* Node = GpioDacGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool gpio_dac_write(uint8_t num, uint8_t * samples, const uint32_t cnt) {
    bool res = false;
    GpioDacHandle_t* Node = GpioDacGetNode(num);
    if(Node) {
        res = fifo_push_array(&Node->TxFiFo, samples, cnt);
    }
    return res;
}


static bool gpio_dac_init_common(const GpioDacConfig_t* const Config, GpioDacHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->PadOut = Config->PadOut;
            Node->timer_num = Config->timer_num;
            Node->sample_freq_hz = Config->sample_freq_hz;
            res = true;
        }
    }
    return res;
}

static bool gpio_dac_init_node(GpioDacHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->valid = true;
        res = true;
    }
    return res;
}

bool gpio_dac_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(GPIO_DAC, "GPIO_DAC_%u", num);
    const GpioDacConfig_t* Config = GpioDacGetConfig(num);
    if(Config) {
        res = GpioDacIsValidConfig(Config);
        if(res) {
#ifdef HAS_GPIO_DAC_DIAG
            LOG_WARNING(GPIO_DAC, "%s", GpioDacConfigToStr(Config));
#endif
            GpioDacHandle_t* Node = GpioDacGetNode(num);
            if(Node) {
                res = gpio_dac_init_common(Config, Node);
                res = gpio_dac_init_node(Node);
                Node->valid = true;
                Node->init = true;
            } else {
                LOG_ERROR(GPIO_DAC, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(GPIO_DAC, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(GPIO_DAC, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(GPIO_DAC, GPIO_DAC, gpio_dac)
COMPONENT_PROC_PATTERT(GPIO_DAC, GPIO_DAC, gpio_dac)
