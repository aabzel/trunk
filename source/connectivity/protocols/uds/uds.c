#include "uds.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array_diag.h"
#include "board_custom.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "convert.h"
#include "iso_tp.h"
#include "log.h"
#include "param_drv.h"
#include "protocol.h"
#include "storage_diag.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(Uds, uds)
COMPONENT_GET_CONFIG(Uds, uds)

COMPONENT_GET_NODE(Did, did)
COMPONENT_GET_CONFIG(Did, did)

DidHandle_t* DidGetNodeByDid(UdsDid_t did) {
    DidHandle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < did_get_cnt(); i++) {
        if(did == DidInstance[i].did) {
            if(DidInstance[i].valid) {
                Node = &DidInstance[i];
                break;
            }
            break;
        }
    }
    return Node;
}

const RoutineIdentifierConfig_t* RoutineIdentifierGetConfig(UdsRoutineIdentifier_t routine_id) {
    RoutineIdentifierConfig_t* RiConfig = NULL;
    uint32_t i = 0;
    uint32_t cnt = routine_identifier_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(routine_id == RoutineIdentifierConfig[i].routine_identifier) {
            if(RoutineIdentifierConfig[i].valid) {
                RiConfig = &RoutineIdentifierConfig[i];
                break;
            }
            break;
        }
    }
    return RiConfig;
}

const DidConfig_t* DidGetConfigByDid(UdsDid_t did) {
    const DidConfig_t* Config = NULL;
    uint32_t i = 0;
    for(i = 0; i < did_get_cnt(); i++) {
        if(did == DidConfig[i].did) {
            if(DidConfig[i].valid) {
                Config = &DidConfig[i];
                break;
            }
            break;
        }
    }
    return Config;
}

UdsHandle_t* UdsIfToNode(Interfaces_t interface) {
    UdsHandle_t* Node = NULL;
    return Node;
}

bool did_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(UDS, "%u Init", num);
    const DidConfig_t* Config = DidGetConfig(num);
    if(Config) {
        LOG_INFO(DID, "SpotConfig %u,%s", num, DidConfigToStr(Config));
        DidHandle_t* Node = DidGetNode(num);
        if(Node) {
            LOG_INFO(DID, "SpotNode %u", num);
            Node->did = Config->did;
            Node->type = Config->type;
            Node->nvram = Config->nvram;
            Node->name = Config->name;
            Node->size = Config->size;
            Node->access = Config->access;
            Node->valid = true;

            memset(Node->buff, 0, sizeof(Node->buff));

            if(Config->nvram) {
                res = param_get((Id_t)Config->did, Node->buff);
                if(res) {
                    LOG_INFO(DID, "LoadOk");
                } else {
                    LOG_WARNING(DID, "LoadErr");
                }
            }

            if(false == res) {
                res = try_str2type(Config->default_value, Config->type, Node->buff, sizeof(Node->buff));
                if(res) {
                    LOG_INFO(DID, "SetDefaultOk [%s],Type:%s", Config->default_value, StorageTypeToStr(Config->type));
                    if(Config->nvram) {
                        res = param_set((Id_t)Config->did, Node->buff);
                    }
                } else {
                    LOG_WARNING(DID, "SetDefaultErr [%s],Type:%s", Config->default_value,
                                StorageTypeToStr(Config->type));
                }
            }

            LOG_INFO(DID, "Init,%s", DataToValueStr(Node->buff, Config->size, Config->type));
            res = true;
        } else {
            LOG_ERROR(DID, "NodeErr %u", num);
        }
    } else {
        LOG_DEBUG(DID, "NoConfig %u", num);
    }

    return res;
}

bool uds_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(UDS, "%u Init", num);
    const UdsConfig_t* Config = UdsGetConfig(num);
    if(Config) {
        LOG_INFO(UDS, "SpotConfig %u", num);
        UdsHandle_t* Node = UdsGetNode(num);
        if(Node) {
            LOG_INFO(UDS, "SpotNode %u", num);
            Node->iso_tp_num = Config->iso_tp_num;
            Node->state = UDS_STATE_IDLE;
            res = true;
        } else {
            LOG_ERROR(UDS, "NodeErr %u", num);
        }
    } else {
        LOG_DEBUG(UDS, "NoConfig %u", num);
    }

    return res;
}

bool uds_proc_idle_ll(UdsHandle_t* Node) {
    bool res = true;
    return res;
}

bool uds_proc_wait_responce_ll(UdsHandle_t* Node) {
    bool res = false;
    uint32_t cur_time_ms = time_get_ms32();
    Node->rx_wait_ms = cur_time_ms - Node->tx_time_stamp_ms;
    if(UDS_RX_TIME_OUT_MS < Node->rx_wait_ms) {
        LOG_ERROR(UDS, "NoResponseAfter %u ms", UDS_RX_TIME_OUT_MS);
        res = false;
        Node->err_cnt++;
        Node->state = UDS_STATE_IDLE;
    } else {
        res = true;
    }

    return res;
}

bool uds_proc_one(uint8_t num) {
    bool res = false;
    UdsHandle_t* Node = UdsGetNode(num);
    if(Node) {
        switch(Node->state) {
        case UDS_STATE_IDLE:
            res = uds_proc_idle_ll(Node);
            break;
        case UDS_STATE_WAIT_RESPONCE:
            res = uds_proc_wait_responce_ll(Node);
            break;
        default:
            break;
        }
    }
    return res;
}

bool uds_init_custom(void) {
    bool res = true;
    return res;
}

bool did_init_custom(void) {
    bool res = true;
    return res;
}

bool uds_check(void) {
    bool res = true;
    return res;
}

static bool uds_send_ll(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    if(Node) {
        set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
        res = iso_tp_send(Node->iso_tp_num, data, size);
        if(res) {
            Node->tx_time_stamp_ms = time_get_ms32();
            LOG_INFO(UDS, "UDS%u SendOk", Node->num);
            Node->expexted_sid = UDS_SID_READ_DATA_BY_ID;
            Node->state = UDS_STATE_WAIT_RESPONCE;
        } else {
            LOG_ERROR(UDS, "UDS%u SendErr", Node->num);
        }
        // set_log_level(ISO_TP, LOG_LEVEL_INFO);
    } else {
        LOG_ERROR(UDS, "UDS%u NodeErr", Node->num);
    }

    return res;
}

bool uds_send(uint8_t num, const uint8_t* const data, size_t size) {
    bool res = false;
    UdsHandle_t* Node = UdsGetNode(num);
    if(Node) {
        res = uds_send_ll(Node, data, size);
    } else {
        LOG_ERROR(UDS, "UDS%u NodeErr", num);
    }

    return res;
}

/*
 * num - UDS instance
 * DID - Data Identifier
 **/
bool uds_read_data_by_identifier(uint8_t num, uint16_t did) {
    bool res = false;
    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    LOG_INFO(UDS, "UDS%u,Send,DID:0x%04x", num, did);
    UdsHandle_t* Node = UdsGetNode(num);
    if(Node) {
        uint8_t TxBuff[4] = {0};
        TxBuff[0] = UDS_SID_READ_DATA_BY_ID;
        uint16_t did_big_endian = reverse_byte_order_uint16(did);
        memcpy(&TxBuff[1], &did_big_endian, 2);
        res = uds_send_ll(Node, TxBuff, 3);
    } else {
        LOG_ERROR(DID, "UDS%u NodeErr", num);
    }
    return res;
}

bool uds_proc_wait_resp_ll(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    if(data[0] == (Node->expexted_sid + UDS_OK_SHIFT)) {
        res = true;
        LOG_INFO(UDS, "UDS%u,RespOk", Node->num);
    } else {
        LOG_ERROR(UDS, "UDS%u,RespErr", Node->num);
        res = false;
    }
    Node->state = UDS_STATE_IDLE;
    return res;
}

bool uds_start_routine(UdsRoutineIdentifier_t routine_identifier) {
    bool res = false;
    /*synchronize settings*/
    res = tera_test_param_proc();

    LOG_INFO(UDS, "UDS,StartRotine,RI:0x%04x=%s", routine_identifier, UdsRoutineIdentifierToStr(routine_identifier));
    switch(routine_identifier) {
    case UDS_ROUTINE_ID_KL30_ON:
        res = kl30_set(true);
        break;
    case UDS_ROUTINE_ID_KL30_OFF:
        res = kl30_set(false);
        break;
    case UDS_ROUTINE_ID_KL15_ON:
        res = kl15_set(true);
        break;

    case UDS_ROUTINE_ID_KL15_OFF:
        res = kl15_set(false);
        break;

    case UDS_ROUTINE_ID_SOS1_ON:
        res = sos1_press(TeraTestState.ButtonHoldTimeMs.sos1);
        break;

    case UDS_ROUTINE_ID_SOS2_ON:
        res = sos2_press(TeraTestState.ButtonHoldTimeMs.sos2);
        break;

    case UDS_ROUTINE_ID_SERVICE_ON:
        res = service_press(TeraTestState.ButtonHoldTimeMs.service);
        break;

    case UDS_ROUTINE_ID_ENS_10HZ:
        res = emergency_notification_system_set(10);
        break;

    case UDS_ROUTINE_ID_ENS_250HZ_500HZ:
        res = ens_set_alt();
        break;

    case UDS_ROUTINE_ID_ENS_250HZ:
        res = emergency_notification_system_set(250);
        break;

    case UDS_ROUTINE_ID_ENS_500HZ:
        res = emergency_notification_system_set(500);
        break;

    case UDS_ROUTINE_ID_ENS_OFF:
        res = emergency_notification_system_set(0);
        break;

    default:
        LOG_ERROR(UDS, "UndefRoutineId:0x04X", routine_identifier);
        break;
    }
    return res;
}

/*startRoutine*/
static bool uds_proc_routine_control_start_rotine(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    if(4 <= size) {
        uint16_t routine_identifier_be = 0;
        memcpy(&routine_identifier_be, &data[2], 2);
        Node->routine_identifier = reverse_byte_order_uint16(routine_identifier_be);
        LOG_DEBUG(UDS, "UDS%u,StartRotine,RI:0x%04x", Node->num, Node->routine_identifier);
        res = uds_start_routine(Node->routine_identifier);
        if(res) {
            Node->tx_frame[0] = UDS_SID_ROUTINE_CONTROL + UDS_OK_SHIFT;
            Node->tx_frame[1] = UDS_RC_START_ROUTINE;
            memcpy(&Node->tx_frame[2], &routine_identifier_be, 2);
            res = uds_send_ll(Node, Node->tx_frame, 4);
        } else {
            LOG_ERROR(UDS, "UDS%u StartRotineErr", Node->num);
        }
    } else {
        LOG_ERROR(UDS, "UDS%u SizeErr:%u Byte", Node->num, size);
    }
    return res;
}

/*stopRoutine*/
static bool uds_proc_routine_control_stop_rotine(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(UDS, "UDS%u,StopRotine", Node->num);
    return res;
}

/*requestRoutineResults*/
static bool uds_proc_routine_control_request_routine_results(UdsHandle_t* Node, const uint8_t* const data,
                                                             size_t size) {
    bool res = false;
    LOG_DEBUG(UDS, "UDS%u,RequestRoutineResults", Node->num);
    return res;
}

static bool uds_proc_rx_did_ll(UdsHandle_t* Node, uint16_t rx_did) {
    bool res = false;
    LOG_DEBUG(UDS, "UDS%u,ProcRxDid:DID0 0x%04x=%s", Node->num, rx_did, UdsDidToStr(rx_did));
    DidHandle_t* DidNode = DidGetNodeByDid(rx_did);
    if(DidNode) {
        Node->tx_frame[0] = UDS_SID_READ_DATA_BY_ID + 0x40;
        uint16_t rx_did_be = reverse_byte_order_uint16(rx_did);
        memcpy(&Node->tx_frame[1], &rx_did_be, 2);
        if(DidNode->size) {
            memcpy(&Node->tx_frame[3], DidNode->buff, DidNode->size);
            res = reverse_byte_order_array(&Node->tx_frame[3], DidNode->size);
            if(res) {
                Node->tx_size = SID_SIZE + DID_SIZE + DidNode->size;
                res = uds_send_ll(Node, Node->tx_frame, Node->tx_size);
                if(res) {
                    LOG_INFO(DID, "UDS%u DidSendOk", Node->num);
                } else {
                    LOG_ERROR(DID, "UDS%u DidSendErr", Node->num);
                }
            }
        }
    } else {
        LOG_ERROR(UDS, "UDS%u,UndefDID 0x%04x", Node->num, rx_did);
    }
    return res;
}

static bool uds_is_mirror_bytes(StorageType_t type) {
    bool res = false;
    switch((uint8_t)type) {
    case TYPE_STRING:
    case TYPE_ARRAY:
    case TYPE_OPERATION:
    case TYPE_TIME_DATE:
    case TYPE_STRUCT: {
        res = false;
    } break;

    case TYPE_INT32:
    case TYPE_UINT32_HEX:
    case TYPE_UINT32:
    case TYPE_INT16:
    case TYPE_INT64:
    case TYPE_FLOAT:
    case TYPE_DOUBLE:
    case TYPE_UINT64:
    case TYPE_UINT16: {
        res = true;
    } break;
    }
    return res;
}

static bool uds_proc_rx_write_data_by_id_ll(uint16_t did, const uint8_t* const data_big_endian, size_t size) {
    bool res = false;
    LOG_INFO(UDS, "WriteDID:0x%04x,Size:%u byte", did, size);
    DidHandle_t* DidNode = DidGetNodeByDid(did);
    if(DidNode) {
        LOG_DEBUG(UDS, "DID:0x%04x=%s", did, DidNode->name);
        if(ACCESS_READ_WRITE == DidNode->access) {
            uint8_t DataRec[50] = {0};
            if(size < sizeof(DataRec)) {
                memcpy(DataRec, data_big_endian, size);
                res = uds_is_mirror_bytes(DidNode->type);
                if(res) {
                    res = false;
                    res = reverse_byte_order_array(DataRec, DidNode->size);
                }
                memcpy(DidNode->buff, DataRec, DidNode->size);
                res = param_set(did, DataRec);
                if(res) {
                    LOG_INFO(UDS, "DID:0x%04x WriteOk", did);
                    res = true;
                } else {
                    LOG_ERROR(UDS, "DID:0x%04x WriteErr", did);
                    res = false;
                }
            } else {
                LOG_ERROR(UDS, "TooBigSize:%u bytes", size);
                res = false;
            }

        } else {
            LOG_ERROR(UDS, "ReadOnlyDID:0x%04x", did);
            res = false;
        }
    } else {
        LOG_ERROR(UDS, "UndefDIDWrite:0x%04x", did);
        res = false;
    }
    return res;
}

static bool uds_proc_rx_write_data_by_id(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(UDS, "UDS%u,RxWriteDataByIdentifier,Size:%u byte", Node->num, size);
    uint16_t rx_did = 0;
    memcpy(&rx_did, &data[1], DID_SIZE);
    rx_did = reverse_byte_order_uint16(rx_did);
    size_t drec_size = size - 3;
    LOG_DEBUG(UDS, "UDS%u,RxDID:0x%04x,Size:%u byte", Node->num, rx_did, drec_size);
    res = uds_proc_rx_write_data_by_id_ll(rx_did, &data[3], drec_size);
    if(res) {
        Node->tx_frame[0] = UDS_SID_WRITE_DATA_BY_IDENTIFIER + UDS_OK_SHIFT;
        memcpy(&Node->tx_frame[1], &data[1], DID_SIZE);
        res = uds_send_ll(Node, Node->tx_frame, SID_SIZE + DID_SIZE);
    } else {
        LOG_ERROR(UDS, "UDS%u WriteDataByIdErr", Node->num);
    }

    return res;
}

static bool uds_proc_rx_read_data_by_id(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(UDS, "UDS%u,RxReadDataIdentifier,Size:%u byte", Node->num, size);
    uint16_t rx_did = 0;
    memcpy(&rx_did, &data[1], 2);
    rx_did = reverse_byte_order_uint16(rx_did);
    LOG_DEBUG(UDS, "UDS%u,RxDID:0x%04x", Node->num, rx_did);
    res = uds_proc_rx_did_ll(Node, rx_did);
    return res;
}

static bool uds_proc_rx_routine_control(UdsHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(UDS, "UDS%u,RxRoutineControl,Size:%u byte", Node->num, size);
    switch(data[1]) {
    case UDS_RC_START_ROUTINE: {
        res = uds_proc_routine_control_start_rotine(Node, data, size);
    } break;
    case UDS_RC_STOP_ROUTINE: {
        res = uds_proc_routine_control_stop_rotine(Node, data, size);
    } break;
    case UDS_RC_REQUEST_ROUTINE_RESULTS: {
        res = uds_proc_routine_control_request_routine_results(Node, data, size);
    } break;
    default:
        res = false;
        break;
    }
    return res;
}

bool uds_proc_rx_data(uint8_t num, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_INFO(UDS, "UDS%u,RxData,Size:%u byte", num, size);
    UdsHandle_t* Node = UdsGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                if(UDS_STATE_IDLE == Node->state) {
                    switch(data[0]) {
                    case UDS_SID_WRITE_DATA_BY_IDENTIFIER: {
                        res = uds_proc_rx_write_data_by_id(Node, data, size);
                    } break;
                    case UDS_SID_ROUTINE_CONTROL: {
                        res = uds_proc_rx_routine_control(Node, data, size);
                    } break;
                    case UDS_SID_READ_DATA_BY_ID: {
                        res = uds_proc_rx_read_data_by_id(Node, data, size);
                    } break;
                    default:
                        LOG_ERROR(UDS, "UDS%u,UndefSID 0x%02x", num, data[0]);
                        break;
                    }
                }

                Node->state = UDS_STATE_IDLE;
                res = print_mem(data, size, true, true, true, true);
                res = true;
                switch((uint8_t)Node->state) {
                case UDS_STATE_WAIT_RESPONCE:
                    res = uds_proc_wait_resp_ll(Node, data, size);
                    break;
                case UDS_STATE_IDLE:
                    break;
                }
            }
        }
    }
    return res;
}

bool did_proc_one(uint8_t num) {
    bool res = false;
    DidHandle_t* Node = DidGetNode(num);
    if(Node) {
        switch((uint32_t)Node->did) {
        case UDS_DID_SERVICE_BUTTON_HOLD_TIME:
        case UDS_DID_SOS2_BUTTON_HOLD_TIME:
        case UDS_DID_SOS1_BUTTON_HOLD_TIME: {
            res = param_get((Id_t)Node->did, Node->buff);
            if(res) {
            } else {
                LOG_ERROR(DID, "DID%u,NVRAMgetErr", num);
            }
        } break;

        case UDS_DID_TIME_STAMP: {
            uint32_t time_s = 0;
            time_s = time_get_s();
            memcpy(Node->buff, &time_s, 4);
            res = true;
        } break;

        case UDS_DID_INPUT_STATES: {
            memcpy(Node->buff, TeraTestState.Input.buff, 2);
            res = true;
        } break;

        case UDS_DID_OUTPUT_STATES: {
            memcpy(Node->buff, TeraTestState.Output.buff, 2);
            res = true;
        } break;

        case UDS_DID_SYSTEM_STATE: {
            memcpy(Node->buff, TeraTestState.System.buff, 2);
            res = true;
        } break;

        case UDS_DID_BOARD_VOLTAGE: {
            memcpy(Node->buff, &TeraTestState.board_voltage_mv, 2);
            res = true;

        } break;

        default:
            res = false;
            break;
        } // switch
    }
    return res;
}

COMPONENT_INIT_PATTERT(UDS, UDS, uds)
COMPONENT_PROC_PATTERT(UDS, UDS, uds)

COMPONENT_INIT_PATTERT(DID, DID, did)
COMPONENT_PROC_PATTERT(DID, DID, did)
