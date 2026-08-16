#include "dc_cut_filter_mcal.h"

#include "code_generator.h"
#include "log.h"
#include "rational_num.h"

COMPONENT_GET_NODE(DcCutFilter, dc_cut_filter)
COMPONENT_GET_CONFIG(DcCutFilter, dc_cut_filter)

/*ISO-26262 require verify configuration*/
bool DcCutFilterIsValidConfig(const DcCutFilterConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(DC_CUT_FILTER, "DC_CUT_FILTER_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(0.0f < Config->alfa) {
            LOG_ERROR(DC_CUT_FILTER, "DC_CUT_FILTER_%u,alfaSmall,Err", Config->num);
            res = false;
        }

        ifn(Config->alfa < 1.0f) {
            LOG_ERROR(DC_CUT_FILTER, "DC_CUT_FILTER_%u,alfaBig,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool dc_cut_filter_proc_sample(uint8_t num, const int32_t x_n, int32_t* const y_n) {
    bool res = false;
    DcCutFilterHandle_t* Node = DcCutFilterGetNode(num);
    if(Node) {
        if(y_n) {
            int32_t e_n = (Node->numerator * Node->a_n_1) / Node->denominator;
            int32_t a_n = x_n + e_n;
            *y_n = a_n - Node->a_n_1;
            res = true;
            Node->a_n_1 = a_n;
        }
    }
    return res;
}

bool dc_cut_filter_init_custom(void) {
    bool res = false;
    LOG_INFO(DC_CUT_FILTER, "Version:%u", DC_CUT_FILTER_VERSION);
    return res;
}

bool dc_cut_filter_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(DC_CUT_FILTER, "DC_CUT_FILTER_%u,Proc", num);
    DcCutFilterHandle_t* Node = DcCutFilterGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool dc_cut_filter_init_common(const DcCutFilterConfig_t* const Config, DcCutFilterHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->alfa = Config->alfa;
            res = true;
        }
    }
    return res;
}

bool dc_cut_filter_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DC_CUT_FILTER, "DC_CUT_FILTER_%u", num);
    const DcCutFilterConfig_t* Config = DcCutFilterGetConfig(num);
    res = DcCutFilterIsValidConfig(Config);
    if(res) {
#ifdef HAS_DC_CUT_FILTER_DIAG
        LOG_WARNING(DC_CUT_FILTER, "%s", DcCutFilterConfigToStr(Config));
#endif
        DcCutFilterHandle_t* Node = DcCutFilterGetNode(num);
        if(Node) {
            res = dc_cut_filter_init_common(Config, Node);
            res = float_to_rational_number(Node->alfa, &Node->numerator, &Node->denominator);
            Node->a_n_1 = 0;
            Node->spin = 0;
            Node->valid = true;
            Node->init = true;
            LOG_WARNING(DC_CUT_FILTER, "%s", DcCutFilterNodeToStr(Node));
        } else {
            LOG_ERROR(DC_CUT_FILTER, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(DC_CUT_FILTER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(DC_CUT_FILTER, DC_CUT_FILTER, dc_cut_filter)
COMPONENT_PROC_PATTERT(DC_CUT_FILTER, DC_CUT_FILTER, dc_cut_filter)
