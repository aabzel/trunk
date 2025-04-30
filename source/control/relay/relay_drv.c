#include "relay_drv.h"

#include "log.h"
#include "param_ids.h"
#include "relay_config.h"
#include "relay_constants.h"
#include "relay_diag.h"
#include "relay_types.h"

static Relay_t* relay_get_inst_by_di_index(DI_index_E di_index) {
    Relay_t* instanse = NULL;
    uint32_t i = 0;
    uint32_t cnt = relay_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Relay[i].di_index == di_index) {
            instanse = &Relay[i];
        }
    }
    return instanse;
}

DI_state_E DI_getInputState(DI_index_E di_index) {
    LOG_DEBUG(RELAY, "GetState %u", di_index);
    DI_state_E state = DI_state_UNDEF;
    if(di_index < DI_index_NUMBER) {
        Relay_t* instance = NULL;
        instance = relay_get_inst_by_di_index(di_index);
        if(instance) {
            /*TODO: Implement later based on GPIO*/
#ifdef HAS_RELAY_DEBUG
            state = instance->real_state;
#endif
        }
    }
    return state;
}

static Relay_t* relay_get_inst_by_do_index(DO_index_E do_index) {
    Relay_t* instance = NULL;
    uint32_t i = 0;
    uint32_t cnt = relay_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Relay[i].do_index == do_index) {
            instance = &Relay[i];
        }
    }
    return instance;
}

void DO_setOutputState(DO_index_E do_index, DO_state_E state) {
    LOG_DEBUG(RELAY, "SetState %u %u", do_index, state);
    if((do_index < DO_index_NUMBER) && (DO_state_OFF == state || DO_state_ON == state)) {
        Relay_t* inst = relay_get_inst_by_do_index(do_index);
        if(inst) {
            LOG_INFO(RELAY, "Index: %u Set  %u", (uint8_t)do_index, state);
            inst->set_state = state;
            /*TODO Add GPIO LowLevelControl code*/
        } else {
            LOG_ERROR(RELAY, "LackOfIndex: %u", (uint8_t)do_index);
        }
    }
}

void DO_setOutputStateReal(DO_index_E do_index, DO_state_E state) {
    LOG_DEBUG(RELAY, "SetState %u %u", do_index, state);
    if((do_index < DO_index_NUMBER) && (DO_state_OFF == state || DO_state_ON == state)) {
        Relay_t* inst = relay_get_inst_by_do_index(do_index);
        if(inst) {
            LOG_INFO(RELAY, "Index: %u Set  %u", (uint8_t)do_index, state);
#ifdef HAS_RELAY_DEBUG
            inst->real_state = (DI_state_E)state;
#endif
            /*TODO Add GPIO LowLevelControl code*/
        } else {
            LOG_ERROR(RELAY, "LackOfIndex: %u", (uint8_t)do_index);
        }
    }
}

bool relay_init(void) {
    bool res = false;
    uint32_t cnt = relay_get_cnt();
    LOG_INFO(RELAY, "Spot:%u Relays", cnt);
    set_log_level(RELAY, LOG_LEVEL_INFO);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        Relay[i].cur_state = DI_getInputState(Relay[i].di_index);
        res = true;
    }
    return res;
}

static bool relay_proc_on(Relay_t* instance) {
    bool res = false;
    switch(instance->cur_state) {
    case DI_state_OFF:
        LOG_ERROR(RELAY, "InIndex:%u Open", instance->di_index);
        instance->status = RELAY_ST_OPEN;
        instance->err_cnt++;
        res = false;
        break;
    case DI_state_ON:
        instance->status = RELAY_ST_OK;
        break;
    case DI_state_UNDEF:
        LOG_DEBUG(RELAY, "DiInd: %u SensorErr", (uint8_t)instance->di_index);
        instance->status = RELAY_ST_SENSOR_ERROR;
        instance->err_cnt++;
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool relay_proc_off(Relay_t* instance) {
    bool res = false;
    switch(instance->cur_state) {
    case DI_state_OFF:
        instance->status = RELAY_ST_OK;
        res = true;
        break;
    case DI_state_ON:
        LOG_ERROR(RELAY, "InIndex:%u Welded", instance->di_index);
        instance->status = RELAY_ST_WELDED;
        instance->err_cnt++;
        res = false;
        break;
    case DI_state_UNDEF:
        LOG_DEBUG(RELAY, "DiInd: %u SensorErr", (uint8_t)instance->di_index);
        instance->status = RELAY_ST_SENSOR_ERROR;
        instance->err_cnt++;
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool relay_proc_one(Relay_t* instance) {
    bool res = false;
    if(instance) {
        if(instance->init) {
            LOG_DEBUG(RELAY, "ProcRelay %u %u", instance->di_index, instance->di_index);
            instance->cur_state = DI_getInputState(instance->di_index);
            if(instance->cur_state != instance->set_state) {
                LOG_DEBUG(RELAY, "Set Index:%u State:%s", instance->do_index, RelayOutState2Str(instance->set_state));
                DO_setOutputState(instance->do_index, instance->set_state);
            }

            switch(instance->set_state) {
            case DO_state_OFF:
                res = relay_proc_off(instance);
                break;
            case DO_state_ON:
                res = relay_proc_on(instance);
                break;
            default:
                res = false;
                break;
            }
            res = true;
        }
    }

    return res;
}

bool relay_proc(void) {
    bool res = false;
    uint32_t i = 0;
    LOG_DEBUG(RELAY, "ProcRelays");
    for(i = 0; i < relay_get_cnt(); i++) {
        res = relay_proc_one(&Relay[i]);
    }
    return res;
}
