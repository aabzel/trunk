#include "can_cat_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "iso_tp_mcal.h"
#include "log.h"
#include "serial_port.h"
#include "slcan.h"

COMPONENT_GET_NODE(CanCat, can_cat)
COMPONENT_GET_CONFIG(CanCat, can_cat)

/*ISO-26262 require verify configuration*/
bool CanCatIsValidConfig(const CanCatConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(CAN_CAT, "%u,NameErr", Config->num);
            res = false;
        }
    }
    return res;
}

bool can_cat_init_custom(void) {
    bool res = false;
    LOG_INFO(CAN_CAT, "Version:%s", CAN_CAT_VERSION);
    return res;
}

bool can_cat_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(CAN_CAT, "Proc %u", i);
    CanCatHandle_t* Node = CanCatGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

#define CAN_NUM 0
bool can_cat_config(uint8_t com_num, uint32_t can_bit_rate, uint32_t my_addr, uint32_t subscribe_addr) {
    bool res = false;
    LOG_WARNING(CAN_CAT, "COM%u,CANbitRate:%u Bit/s,MyID:0x%x,SubScrID:0x%x", com_num, can_bit_rate, my_addr, subscribe_addr);
    res = serial_port_re_init_one(1, com_num, 115200, 0);

    SlCanHandle_t* SlCan = SlCanGetNode(1);
    if(SlCan) {
        SlCan->com_num = com_num;
    }

    IsoTpHandle_t* IsoTp = IsoTpGetNode(1);
    if(IsoTp) {
        IsoTp->my_id = my_addr;
        IsoTp->subscription_id = subscribe_addr;
        IsoTp->interface_if.interface_name = INTERFACE_NAME_CAN;
        IsoTp->interface_if.num = 0;
    }

    if(can_bit_rate) {
        res = can_mcal_baudrate_set(CAN_NUM, can_bit_rate);
    }

    CanHandle_t* Can = CanGetNode(CAN_NUM);
    if(Can) {
        Can->identifier = CAN_FRAME_ID_EXTENDED;
        Can->bit_rate = can_bit_rate;
        Can->slcan_num = 1;
    }
    return res;
}

bool can_cat_init_common(const CanCatConfig_t* const Config, CanCatHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool can_cat_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN_CAT, "CAN_CAT%u", num);
    const CanCatConfig_t* Config = CanCatGetConfig(num);
    if(Config) {
        res = CanCatIsValidConfig(Config);
        if(res) {
#ifdef HAS_CAN_CAT_DIAG
            LOG_WARNING(CAN_CAT, "%s", CanCatConfigToStr(Config));
#endif
            CanCatHandle_t* Node = CanCatGetNode(num);
            if(Node) {
                res = can_cat_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(CAN_CAT, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(CAN_CAT, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(CAN_CAT, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(CAN_CAT, CAN_CAT, can_cat)
COMPONENT_PROC_PATTERT(CAN_CAT, CAN_CAT, can_cat)
