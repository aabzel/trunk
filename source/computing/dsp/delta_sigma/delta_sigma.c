#include "delta_sigma.h"

#include "code_generator.h"
#include "gpio_mcal.h"
#include "log.h"
#include "timer_mcal.h"

COMPONENT_GET_NODE(DeltaSigma, delta_sigma)
COMPONENT_GET_CONFIG(DeltaSigma, delta_sigma)

int8_t adc_1bit(float value, float comparator_middle) {
    int8_t code = 0;
    if(comparator_middle <= value) {
        code = 1;
    } else if(value < comparator_middle) {
        code = 0;
    } else {
    }

    return code;
}

float dac_1bit(int8_t code, float min, float max) {
    float voltage = 0;
    switch(code) {
    case 1:
        voltage = max;
        break;
    case 0:
        voltage = min;
        break;
    default:
        voltage = min;
        break;
    }

    return voltage;
}

bool delta_sigma_isr_proc_one_ll(DeltaSigmaHandle_t* Node) {
    bool res = false;
    Node->error = Node->target - Node->dac_out;
    Node->sum_error += Node->error;
    Node->pdm = adc_1bit(Node->sum_error, Node->comparator_middle);

    res = gpio_logic_level_set(Node->Pad, (GpioLogicLevel_t)Node->pdm);
    Node->dac_out = dac_1bit(Node->pdm, Node->min, Node->max);
    Node->sample_cnt++;
    return res;
}

/*Can be calles from ISR*/
bool delta_sigma_isr_proc_one(uint8_t num) {
    bool res = false;
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
    if(Node) {
        res = delta_sigma_isr_proc_one_ll(Node);
    }
    return res;
}

bool delta_sigma_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(DELTA_SIGMA, "Proc:%u", num);
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
    if(Node) {
        log_level_t ll = log_level_get(DELTA_SIGMA);
        LOG_PARN(DELTA_SIGMA, "%s", DeltaSigmaNodeToStr(Node));
        Node->up_time_s = ((float)Node->sample_cnt) * Node->sample_time_s;

        Node->error = Node->target - Node->dac_out;
        Node->sum_error += Node->error;
        Node->pdm = adc_1bit(Node->sum_error, Node->comparator_middle);
        if(LOG_LEVEL_DEBUG == ll) {
            cli_printf("%u", Node->pdm);
        }

        res = gpio_logic_level_set(Node->Pad, (GpioLogicLevel_t)Node->pdm);
        Node->dac_out = dac_1bit(Node->pdm, Node->min, Node->max);
        Node->sample_cnt++;
    }
    return res;
}

bool delta_sigma_init_custom(void) {
    bool res = true;
    return res;
}

static bool delta_sigma_init_common(const DeltaSigmaConfig_t* Config, DeltaSigmaHandle_t* Node) {
    bool res = true;
    Node->sample_frequency_hz = Config->sample_frequency_hz;
    Node->target = Config->target;
    Node->Pad = Config->Pad;
    Node->num = Config->num;
    Node->name = Config->name;
    Node->timer_num = Config->timer_num;
    Node->min = Config->min;
    Node->max = Config->max;
    Node->comparator_middle = Config->comparator_middle;
    return res;
}

bool delta_sigma_target_set(uint8_t num, float target) {
    bool res = false;
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
    if(Node) {
        LOG_DEBUG(DELTA_SIGMA, "Target:%f", target);
        Node->target = target;
        res = true;
    }
    return res;
}

float delta_sigma_target_get(uint8_t num) {
    float target = 0.0f;
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
    if(Node) {
        target = Node->target;
    }
    return target;
}

bool delta_sigma_init_one(uint8_t num) {
    LOG_WARNING(DELTA_SIGMA, "INIT:%u", num);
    bool res = false;
    const DeltaSigmaConfig_t* Config = DeltaSigmaGetConfig(num);
    if(Config) {
        LOG_WARNING(DELTA_SIGMA, "%s", DeltaSigmaConfigToStr(Config));
        DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
        if(Node) {
            res = delta_sigma_init_common(Config, Node);
            Node->valid = true;
            Node->sample_cnt = 0;
            Node->dac_out = 0.0;
            Node->sum_error = 0.0;
            Node->error = 0.0;
            Node->up_time_s = 0.0;
            Node->pdm = 0;
            Node->sample_time_s = 1.0 / ((float)Node->sample_frequency_hz);
            // log_level_get_set(MATH, LOG_LEVEL_INFO  );
            // res = true;
            res = gpio_init_out_pad(Config->Pad);
            res = timer_frequency_set(Config->timer_num, Config->sample_frequency_hz);

            res = timer_ctrl(Config->timer_num, true);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(DELTA_SIGMA, DELTA_SIGMA, delta_sigma)
COMPONENT_PROC_PATTERT(DELTA_SIGMA, DELTA_SIGMA, delta_sigma)
