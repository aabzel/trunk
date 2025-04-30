#include "delta_sigma.h"


#include "log.h"
#include "gpio_mcal.h"
#include "code_generator.h"

COMPONENT_GET_NODE(DeltaSigma, delta_sigma)
COMPONENT_GET_CONFIG(DeltaSigma, delta_sigma)

int8_t adc_1bit(double value, double comparator_middle) {
    int8_t code = 0;
    if(comparator_middle <= value) {
        code = 1;
    } else if(value < comparator_middle) {
        code = 0;
    } else {
    }

    return code;
}


double dac_1bit(int8_t code, double min, double max) {
    double voltage = 0;

    switch(code){
        case 1: voltage = max; break;
        case 0: voltage = min; break;
    }

    return voltage;
}

/*Can be calles from ISR*/
bool delta_sigma_isr_proc_one(uint8_t num) {
    bool res = false;
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(  num);
    if (Node) {
        Node->error = Node->target - Node->dac_out;
        Node->sum_error += Node->error;
        Node->pdm = adc_1bit(Node->sum_error, Node->comparator_middle);

        res = gpio_logic_level_set(Node->Pad.byte, (GpioLogicLevel_t) !Node->pdm);
        Node->dac_out = dac_1bit(Node->pdm,Node->min, Node->max);
        Node->sample_cnt++;
    }
    return res;
}

bool delta_sigma_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(DELTA_SIGMA, "Proc:%u", num);
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(  num);
    if (Node) {
        log_level_t ll = log_level_get(DELTA_SIGMA);
        LOG_PARN(DELTA_SIGMA, "%s", DeltaSigmaNodeToStr(Node));
        Node->up_time_s = ((double)Node->sample_cnt)*Node->sample_time_s;

        Node->error = Node->target - Node->dac_out;
        Node->sum_error += Node->error;
        Node->pdm = adc_1bit(Node->sum_error, Node->comparator_middle);
        if (LOG_LEVEL_DEBUG==ll) {
            cli_printf("%u", Node->pdm);
        }

        res = gpio_logic_level_set(Node->Pad.byte, (GpioLogicLevel_t) !Node->pdm);
        Node->dac_out = dac_1bit(Node->pdm,Node->min, Node->max);
        Node->sample_cnt++;
    }
    return res;
}

bool delta_sigma_init_custom(void) {
    bool res = true ;
    log_level_get_set(DELTA_SIGMA, LOG_LEVEL_INFO  );
    return res;
}

bool delta_sigma_init_one(uint8_t num) {
    LOG_WARNING(DELTA_SIGMA, "INIT:%u", num);
    bool res = false;
    const DeltaSigmaConfig_t* Config = DeltaSigmaGetConfig(num);
    if(Config) {
        LOG_WARNING(DELTA_SIGMA, "%s", DeltaSigmaConfigToStr(Config));
        DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
        if(Node) {
            Node->sample_frequency_hz = Config->sample_frequency_hz;
            Node->target = Config->target;
            Node->Pad = Config->Pad;
            Node->num = Config->num;
            Node->min = Config->min;
            Node->max = Config->max;
            Node->comparator_middle = Config->comparator_middle;
            Node->valid = true;
            Node->sample_cnt = 0;
            Node->dac_out = 0.0;
            Node->sum_error = 0.0;
            Node->error = 0.0;
            Node->up_time_s = 0.0;
            Node->pdm = 0;

            Node->sample_time_s = 1.0 / ((double)Node->sample_frequency_hz);
            log_level_get_set(DELTA_SIGMA, LOG_LEVEL_DEBUG  );
            //log_level_get_set(MATH, LOG_LEVEL_INFO  );
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(DELTA_SIGMA, DELTA_SIGMA, delta_sigma)
COMPONENT_PROC_PATTERT(DELTA_SIGMA, DELTA_SIGMA, delta_sigma)
