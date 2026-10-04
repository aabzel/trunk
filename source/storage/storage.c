#include "storage.h"

#include <math.h>
#include <string.h>
#include <time.h>

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_W25Q32JV
#include "w25q32jv_drv.h"
#endif

StoragePhysicalQuantity_t storage_units_to_physical_quantity(const StorageUnits_t units) {
    StoragePhysicalQuantity_t physical_quantity = STORAGE_PHYSICAL_QUANTITY_UNDEF;
    switch(units) {
    case STORAGE_UNITS_METER:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LENGTH;
        break;
    case STORAGE_UNITS_NO_UNIT:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_NO;
        break;

    case STORAGE_UNITS_FOOT:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LENGTH;
        break;
    case STORAGE_UNITS_INCH:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LENGTH;
        break;
    case STORAGE_UNITS_YARD:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LENGTH;
        break;
    case STORAGE_UNITS_MILE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LENGTH;
        break;

    case STORAGE_UNITS_GRAM:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_MASS;
        break;
    case STORAGE_UNITS_TON:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_MASS;
        break;

    case STORAGE_UNITS_SECOND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TIME;
        break;
    case STORAGE_UNITS_MINUTE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TIME;
        break;
    case STORAGE_UNITS_HOUR:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TIME;
        break;
    case STORAGE_UNITS_DAY:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TIME;
        break;
    case STORAGE_UNITS_YEAR:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TIME;
        break;
    case STORAGE_UNITS_AMPERE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_CURRENT;
        break;
    case STORAGE_UNITS_VOLT:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_VOLTAGE;
        break;

    case STORAGE_UNITS_COULOMB:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ELECTRIC_CHARGE;
        break;
    case STORAGE_UNITS_OHM:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_RESISTANCE;
        break;
    case STORAGE_UNITS_FARAD:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_CAPACITANCE;
        break;
    case STORAGE_UNITS_HENRY:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_INDUCTANCE;
        break;
    case STORAGE_UNITS_SIEMENS:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ELECTRIC_CONDUCTANCE;
        break;
    case STORAGE_UNITS_WEBER:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_MAGNETIC_FLUX;
        break;
    case STORAGE_UNITS_TESLA:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_MAGNETIC_FLUX_DENSITY;
        break;
    case STORAGE_UNITS_KELVIN:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TEMPERATURE;
        break;
    case STORAGE_UNITS_CELSIUS:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TEMPERATURE;
        break;
    case STORAGE_UNITS_FAHRENHEIT:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TEMPERATURE;
        break;
    case STORAGE_UNITS_CANDELA:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LUMINOUS_INTENSITY;
        break;
    case STORAGE_UNITS_RADIAN:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ANGLE;
        break;
    case STORAGE_UNITS_DEGREE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ANGLE;
        break;
    case STORAGE_UNITS_HERTZ:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_FREQUENCY;
        break;
    case STORAGE_UNITS_JOULE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ENERGY;
        break;
    case STORAGE_UNITS_NEWTON:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_FORCE;
        break;
    case STORAGE_UNITS_KILOPOND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_FORCE;
        break;
    case STORAGE_UNITS_POUND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_FORCE;
        break;
    case STORAGE_UNITS_WATT:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_POWER;
        break;
    case STORAGE_UNITS_HORSE_POWER_HK:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_POWER;
        break;
    case STORAGE_UNITS_HORSE_POWER_HP:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_POWER;
        break;
    case STORAGE_UNITS_PASCAL:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_PRESSURE;
        break;
    case STORAGE_UNITS_BAR:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_PRESSURE;
        break;
    case STORAGE_UNITS_ATMOSPHERE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_PRESSURE;
        break;
    case STORAGE_UNITS_POUND_FORCE_PER_SQUARE_INCH:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_PRESSURE;
        break;
    case STORAGE_UNITS_BECQEREL:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_RADIOACTIVITY;
        break;
    case STORAGE_UNITS_LUMEN:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_LIGHT_FLUX;
        break;
    case STORAGE_UNITS_LUX:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ILLUMINANCE;
        break;
    case STORAGE_UNITS_LITER:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_VOLUME;
        break;
    case STORAGE_UNITS_GALLON_BRITISH:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_VOLUME;
        break;
    case STORAGE_UNITS_GALLON_US:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_VOLUME;
        break;
    case STORAGE_UNITS_CUBIC_INCH:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_VOLUME;
        break;
    case STORAGE_UNITS_METER_PER_SECOND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_SPEED;
        break;
    case STORAGE_UNITS_KILOMETER_PER_HOUR:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_SPEED;
        break;
    case STORAGE_UNITS_MILE_PER_HOUR:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_SPEED;
        break;
    case STORAGE_UNITS_REVOLUTIONS_PER_SECOND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ANGULAR_VELOCITY;
        break;
    case STORAGE_UNITS_REVOLUTIONS_PER_MINUTE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ANGULAR_VELOCITY;
        break;
    case STORAGE_UNITS_COUNTS:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_NO;
        break;
    case STORAGE_UNITS_PERCENT:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_NO;
        break;
    case STORAGE_UNITS_MILLIGRAM_PER_STROKE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_MASS;
        break;
    case STORAGE_UNITS_NEWTON_METER:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_TORQUE;
        break;
    case STORAGE_UNITS_LITER_PER_MINUTE:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_FLOW;
        break;
    case STORAGE_UNITS_BAR_PER_SECOND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_PRESSURE_CHANGE;
        break;
    case STORAGE_UNITS_RADIANS_PER_SECOND:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_ANGULAR_VELOCITY;
        break;
        // case STORAGE_UNITS_METER_PER_SQUARE_SECOND:        physical_quantity= STORAGE_PHYSICAL_QUANTITY_TORQUE;
        // break;
        // case STORAGE_UNITS_WATT_PER_SQUARE_METER:        physical_quantity= STORAGE_PHYSICAL_QUANTITY_/m2; break;
        // case STORAGE_UNITS_RADIANS_PER_SQUARE_SECOND:        physical_quantity= STORAGE_PHYSICAL_QUANTITY_/s2; break;
        // case STORAGE_UNITS_KILOGRAM_PER_SQUARE_METER:        physical_quantity= STORAGE_PHYSICAL_QUANTITY_/m2; break;

    default:
        physical_quantity = STORAGE_PHYSICAL_QUANTITY_UNDEF;
        break;
    }
    return physical_quantity;
}

static const StorageIdInfo_t StorageIdInfo[] = {
    {
        .id = PAR_ID_BOOT_CNT,
        .type = TYPE_UINT8,
    },
    {
        .id = PAR_ID_REBOOT_CNT,
        .type = TYPE_UINT16,
    },
    {
        .id = PAR_ID_BOOT_CMD,
        .type = TYPE_UINT8,
    },
//  {  .id = PAR_ID_BOOTLOADER_START, .type=TYPE_UINT32_HEX,},
#ifdef HAS_BOOTLOADER
    {
        .id = PAR_ID_APP_CRC32,
        .type = TYPE_UINT32_HEX,
    },
    {
        .id = PAR_ID_APP_LEN,
        .type = TYPE_UINT32,
    },
    {
        .id = PAR_ID_APP_START,
        .type = TYPE_UINT32_HEX,
    },
    {
        .id = PAR_ID_APP_STATUS,
        .type = TYPE_UINT8,
    },
#endif
};

StorageType_t storage_get_id_type(StorageId_t id) {
    StorageType_t type = 0;
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(StorageIdInfo); i++) {
        if(id == StorageIdInfo[i].id) {
            res = true;
            type = StorageIdInfo[i].type;
            break;
        }
    }
    if(false == res) {
#ifdef HAS_STORAGE_DIAG
        LOG_ERROR(STORAGE, "UndefLenForTypeID:%u=%s", type, StorageTypeToStr(type));
#endif
    }
    return type;
}

static const StorageTypeInfo_t StorageSizeInfo[] = {
    {
        .type = TYPE_TIME_DATE,
        .len = sizeof(struct tm),
    },
    {
        .type = TYPE_UINT8,
        .len = 1,
    },
    {
        .type = TYPE_BOOL,
        .len = 1,
    },
    {
        .type = TYPE_INT8,
        .len = 1,
    },
    {
        .type = TYPE_UINT16,
        .len = 2,
    },
    {
        .type = TYPE_INT16,
        .len = 2,
    },
    {
        .type = TYPE_UINT32,
        .len = 4,
    },
    {
        .type = TYPE_UINT32_HEX,
        .len = 4,
    },
    {
        .type = TYPE_INT32,
        .len = 4,
    },
    {
        .type = TYPE_UINT64,
        .len = 8,
    },
    {
        .type = TYPE_UINT64,
        .len = 8,
    },
    {
        .type = TYPE_INT64,
        .len = 8,
    },
    {
        .type = TYPE_DOUBLE,
        .len = 8,
    },
    {
        .type = TYPE_FLOAT,
        .len = 4,
    },
    {
        .type = TYPE_STRUCT,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
    {
        .type = TYPE_ARRAY,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
    {
        .type = TYPE_STRING,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
    {
        .type = TYPE_OPERATION,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
};

uint32_t storage_get_type_len(StorageType_t type) {
    uint32_t len = 0;
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(StorageSizeInfo); i++) {
        if(type == StorageSizeInfo[i].type) {
            res = true;
            len = StorageSizeInfo[i].len;
            break;
        }
    }
    if(false == res) {
#ifdef HAS_STORAGE_DIAG
        LOG_ERROR(STORAGE, "UndefLenForTypeID:%u=%s", type, StorageTypeToStr(type));
#endif
    }
    return len;
}

#ifdef HAS_TBFP
static uint8_t storage_data[STORAGE_DATA_SIZE] = {0};

#define STORAGE_DATA_OFFSET sizeof(StorageFrameHeader_t)
/*
 * tbfp_num - TBFP instance NUM
 * payload- tbfp frame payload
 * size - tbfp frame payload size
 */
bool storage_proc_cmd(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size) {
    bool res = false;
    if(payload) {
        if(size) {
            // runs
            StorageFrameHeader_t Header = {0};
            memcpy(&Header, payload, sizeof(StorageFrameHeader_t));

            memset(storage_data, 0x00, STORAGE_DATA_SIZE);
            memcpy(storage_data, payload, sizeof(StorageFrameHeader_t));

#ifdef HAS_STORAGE_DIAG
            LOG_DEBUG(STORAGE, "%s", StorageFrameHeaderToStr(&Header));
#endif
            switch(Header.operation) {
            case ACCESS_WRITE_ONLY: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_prog_page(Header.asic_num, Header.address, &payload[STORAGE_DATA_OFFSET], Header.size);
#endif
#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, TBFP_FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
#endif
            } break;
            case ACCESS_ERASE: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_chip_erase(Header.asic_num);
#endif

#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, TBFP_FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
#endif
            } break;

            case ACCESS_READ_ONLY: {
                if(Header.size < STORAGE_DATA_SIZE) {
                    res = true;
#ifdef HAS_W25Q32JV
                    res = w25q32jv_read_data(Header.asic_num, Header.address,
                                             &storage_data[sizeof(StorageFrameHeader_t)], Header.size);

#endif

#ifdef HAS_TBFP
                    res = tbfp_send_frame(tbfp_num, TBFP_FRAME_ID_STORAGE, storage_data,
                                          sizeof(StorageFrameHeader_t) + Header.size);
#endif

                } else {
#ifdef HAS_LOG
                    LOG_ERROR(STORAGE, "TooBigSize:%u,Max:%u", Header.size, STORAGE_DATA_SIZE);
#endif
                }
            } break;
            default:
                break;
            }
        }
    }
    return res;
}
#endif

bool StorageIsValidParam(const StorageItem_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(Config->parser) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,Parser,ID:%u", Config->id);
#endif
            res = false;
        }

        uint32_t type_len = storage_get_type_len(Config->type);
        if(type_len < Config->len) {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,LenTooBit,ID:%u,TypeLen:%u", Config->id, type_len);
#endif
            res = false;
        }

        if(Config->len) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,Len,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->default_value) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,DefVal,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->name) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,Name,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->type) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,type,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->id) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,id");
#endif
            res = false;
        }

        if(Config->facility) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,facility,ID:%u", Config->id);
#endif
            res = false;
        }
    }
    return res;
}

/*TODO: implement bin search */
StorageType_t storage_get_type(const StorageId_t id) {
    StorageType_t ret_type = TYPE_UNDEF;
    uint16_t i = 0;
    uint32_t cnt = storage_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == StorageArray[i].id) {
            ret_type = StorageArray[i].type;
            break;
        }
    }
    return ret_type;
}

float storage_scale_to_factor(const StorageScale_t scale) {
    float factor = powf(10.0, (float)scale);
    return factor;
}

uint32_t storage_get_len(const StorageId_t id) {
    uint32_t size = 0;
    StorageItem_t* Node = StorageGetNode(id);
    if(Node) {
        size = Node->len;
    } else {
        StorageType_t type = storage_get_id_type(id);
        size = storage_get_type_len(type);
    }
    return size;
}

StorageItem_t* StorageGetNode(const StorageId_t id) {
    StorageItem_t* Node = NULL;
#ifdef HAS_STORE_FS
    uint16_t i = 0;
    uint32_t cnt = storage_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == StorageArray[i].id) {
            Node = &StorageArray[i];
            break;
        }
    }
#endif
    return Node;
}

/*TODO: Test it
  buff [in]
  size [in]
  type [in]
  Value [out]
  */
bool storage_data_to_value(const uint8_t* const buff, const uint32_t size, const StorageType_t type,
                           StorageUnivervalType_t* const Value) {
    bool res = false;

    if(buff) {
        if(size) {
            if(Value) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        switch(type) {
        case TYPE_STRING:
            if(size < sizeof(Value->temp)) {
                memcpy(Value->temp, buff, size);
                res = true;
            }
            break;

        case TYPE_ARRAY:
            if(size <= sizeof(Value->temp)) {
                memcpy(Value->temp, buff, size);
                res = true;
            }
            break;

        case TYPE_TIME_DATE: {
#ifdef HAS_TIME_DIAG
            memcpy(&Value->time_date, buff, sizeof(struct tm));
            res = true;
#endif /*HAS_TIME_DIAG*/
        } break;

        case TYPE_INT8:
        case TYPE_BOOL:
        case TYPE_UINT8:
            if(1 == size) {
                memcpy(&Value->u8, buff, 1);
                res = true;
            }
            break;

        case TYPE_INT16:
        case TYPE_UINT16:
            if(2 == size) {
                memcpy(&Value->u16, buff, 2);
                res = true;
            }
            break;

        case TYPE_INT32:
        case TYPE_UINT32_HEX:
        case TYPE_UINT32:
            if(4 == size) {
                memcpy(&Value->u32, buff, 4);
                res = true;
            }
            break;

        case TYPE_INT64:
        case TYPE_UINT64:
            if(8 == size) {
                memcpy(&Value->u64, buff, 8);
                res = true;
            }
            break;

        case TYPE_STRUCT:
            memcpy(&Value->temp, buff, size);
            res = true;
            break;

        case TYPE_FLOAT:
            if(4 == size) {
                memcpy(&Value->real_float, buff, 4);
                res = true;
            }
            break;

        case TYPE_DOUBLE:
            if(8 == size) {
                memcpy(&Value->real_double, buff, 8);
                res = true;
            }
            break;
            //--

        default:
            res = false;
            break;
        } /*switch*/
    }
    return res;
}

bool storage_data_to_float(const StorageUnivervalType_t* const Value, const StorageType_t type, float* const real) {
    bool res = false;
    float real_temp = 0.0f;
    switch(type) {
    case TYPE_BOOL: {
        real_temp = (float)Value->logic;
        res = true;
    } break;

    case TYPE_INT8: {
        real_temp = (float)Value->u8;
        res = true;
    } break;

    case TYPE_UINT8: {
        real_temp = (float)Value->u8;
        res = true;
    } break;

    case TYPE_INT16: {
        real_temp = (float)Value->u16;
        res = true;
    } break;

    case TYPE_UINT16: {
        real_temp = (float)Value->u16;
        res = true;
    } break;

    case TYPE_INT32: {
        real_temp = (float)Value->s32;
        res = true;
    } break;

    case TYPE_UINT32: {
        real_temp = (float)Value->u32;
        res = true;
    } break;

    case TYPE_UINT32_HEX: {
        real_temp = (float)Value->u32;
        res = true;
    } break;

    case TYPE_INT64: {
        real_temp = (float)Value->s64;
        res = true;
    } break;

    case TYPE_UINT64: {
        real_temp = (float)Value->u64;
        res = true;
    } break;

    case TYPE_FLOAT: {
        real_temp = (float)Value->real_float;
        res = true;
    } break;

    case TYPE_DOUBLE: {
        real_temp = (float)Value->real_double;
        res = true;
    } break;

    case TYPE_BINARY_CODED_DECIMAL: {
        // TODO
    } break;

#if 0
        case TYPE_INT24: {        } break;
        case TYPE_STRUCT: {        } break;
        case TYPE_STRING: { } break;
        case TYPE_TIME_DATE: {} break;
        case TYPE_OPERATION: {} break;
        case TYPE_ARRAY: {} break;
        case TYPE_UINT: {} break;
        case TYPE_INT: {} break;
        case TYPE_FORMULA:{} break;
        case TYPE_BIT_MAP: {} break;
        case TYPE_ENUM: { } break;
#endif

    default: {
        res = false;
    } break;
    }

    if(real) {
        if(res) {
            *real = real_temp;
        }
    } else {
        res = false;
    }
    return res;
}
