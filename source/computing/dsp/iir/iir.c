#include "iir.h"

#include <stdlib.h>

#include "circular_buffer_index.h"
#include "code_generator.h"
#include "float_utils.h"
#include "log.h"

COMPONENT_GET_NODE(Iir, iir)
COMPONENT_GET_CONFIG(Iir, iir)

static bool iir_init_custom(void) {
    bool res = true;
    LOG_INFO(IIR, "CustomInit");
    return res;
}

static bool iir_init_common(const IirConfig_t* Config, IirHandle_t* Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->cut_off_freq_hz = Config->cut_off_freq_hz;
            Node->num = Config->num;
            Node->size = Config->size;
            Node->max_size = Config->max_size;
            Node->a = Config->a;
            Node->b = Config->b;
            Node->x = Config->x;
            Node->y = Config->y;

            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->x[i] = 0.0;
                Node->y[i] = 0.0;
            }
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool IirIsValidConfig(const IirConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }

    if(res) {
        res = false;
        if(Config->size <= Config->max_size) {
            res = true;
        } else {
            LOG_ERROR(IIR, "OrderErr,Order:%u,Max:%u", Config->size, Config->max_size);
        }
    }

    if(res) {
        res = false;
        if(1 <= Config->size) {
            res = true;
        } else {
            LOG_ERROR(IIR, "Order,Err,Size:%u", Config->size);
        }
    }

    if(res) {
        res = false;
        if(Config->cut_off_freq_hz < Config->sample_rate_hz) {
            res = true;
        } else {
            LOG_ERROR(IIR, "CutOffFreqErr");
        }
    }

    if(res) {
        res = false;
        if(0 < Config->sample_rate_hz) {
            res = true;
        } else {
            LOG_ERROR(IIR, "SampleRateErr");
        }
    }

    if(res) {
        res = false;
        if(Config->a) {
            res = true;
        } else {
            LOG_ERROR(IIR, "aErr");
        }
    }
#if 0
    if (res) {
        res = false;
        //Array of feed back coefficients
        if (Config->a[0] < IIR_VICINITY_OF_ZERO) {
            if (-IIR_VICINITY_OF_ZERO < Config->a[0]) {
                res = true;
            } else {
                LOG_ERROR(IIR, "A0SmallErr:%f",Config->a[0]);
            }
        } else {
            LOG_ERROR(IIR, "A0BigErr:%f",Config->a[0]);
        }
    }
#endif

    if(res) {
        res = false;
        if(Config->b) {
            res = true;
        } else {
            LOG_ERROR(IIR, "bErr");
        }
    }

    if(res) {
        res = false;
        if(Config->x) {
            res = true;
        } else {
            LOG_ERROR(IIR, "xErr");
        }
    }

    if(res) {
        res = false;
        if(Config->y) {
            res = true;
        } else {
            LOG_ERROR(IIR, "YErr");
        }
    }

    if(res) {
        res = false;
        if(Config->valid) {
            res = true;
        } else {
            LOG_ERROR(IIR, "ValidErr");
        }
    }

    if(res) {
        res = false;
        if(Config->name) {
            res = true;
        } else {
            LOG_ERROR(IIR, "NameErr");
        }
    }

    return res;
}

bool iir_init_one(uint8_t num) {
    bool res = false;
    const IirConfig_t* Config = IirGetConfig(num);
    if(Config) {
        LOG_WARNING(IIR, "%s", IirConfigToStr(Config));
        res = IirIsValidConfig(Config);
        if(res) {
            IirHandle_t* Node = IirGetNode(num);
            if(Node) {
                res = iir_init_common(Config, Node);
                // b0=for current
                res = circular_buffer_index_init(&Node->xIndexer, Config->size);
                if(res) {
                    // res = circular_buffer_index_init(&Node->yIndexer, Config->size);
                    if(res) {
                        Node->init = true;
                        LOG_INFO(IIR, "InitOk:%u", num);
                    }
                }
            } else {
                LOG_ERROR(IIR, "NodeErr:%u", num);
                res = false;
            }
        } else {
            LOG_ERROR(IIR, "ConfigAbsurdErr:%u", num);
            res = false;
        }
    } else {
        LOG_ERROR(IIR, "ConfErr:%u", num);
        res = false;
    }

    return res;
}

bool iir_lowpas_1st_order(uint8_t num, double k) {
    bool res = false;
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_INFO(IIR, "IIR%u,k:%f", num, k);
        if(1.0 <= k) {
            Node->init = true;
            Node->size = 2;
            Node->proc_cnt = 0;
            // forward
            Node->b[0] = 1.0 / k;
            Node->b[1] = 0.0;
            // feedback
            Node->a[0] = -0.0;
            Node->a[1] = -(k - 1.0) / k;
            res = iir_diag_one(num);
            // res = iir_calc_frequency_response(num);
            // res = iir_calc_frequency_response_norm(num);
        } else {
            LOG_ERROR(IIR, "Too,Small,k:%f", k);
            res = false;
        }
    }
    return res;
}

bool iir_lowpas_1st_order_v2(uint8_t num, double x) {
    bool res = false;
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_INFO(IIR, "IIR%u,x:%f", num, x);
        Node->init = true;
        Node->size = 2;
        Node->proc_cnt = 0;
        // forward
        Node->b[0] = 1.0 - x;
        Node->b[1] = 0.0;
        // feedback
        Node->a[0] = 0.0;
        Node->a[1] = -x;
        res = iir_diag_one(num);
        // res = iir_calc_frequency_response(num);
        // res = iir_calc_frequency_response_norm(num);
    }
    return res;
}
/*
 * M-filter order
 *
 */
bool iir_synthesize(uint8_t num, uint32_t M, double cutoff_frequency_hz, double sampling_frequency_hz) {
    bool res = true;
    return res;
}

COMPONENT_INIT_PATTERT(IIR, IIR, iir)
