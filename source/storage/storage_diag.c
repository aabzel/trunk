#include "storage_diag.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "common_diag.h"
#include "data_types.h"
#include "log.h"
#include "storage_config.h"
#include "system_diag.h"

#ifdef HAS_TIME
#include "time_diag.h"
#endif

const char* StoragePhysicalQuantityToStr(const StoragePhysicalQuantity_t phy_qntity) {
    const char* name = "?";
    switch(phy_qntity) {
        case STORAGE_PHYSICAL_QUANTITY_LENGTH:   name = "Length";   break;
        case STORAGE_PHYSICAL_QUANTITY_SPEED:    name = "Speed";  break;
        case STORAGE_PHYSICAL_QUANTITY_MASS:     name = "Mass";  break;
        case STORAGE_PHYSICAL_QUANTITY_ANGULAR_VELOCITY:   name = "AngularVelocity";  break;
        case STORAGE_PHYSICAL_QUANTITY_TIME:     name = "Time";  break;
        case STORAGE_PHYSICAL_QUANTITY_CURRENT:  name = "Current";  break;
        case STORAGE_PHYSICAL_QUANTITY_VOLTAGE:  name = "Voltage"; break;
        case STORAGE_PHYSICAL_QUANTITY_PRESSURE: name = "Pressure";  break;
        case STORAGE_PHYSICAL_QUANTITY_NO: name = "No";  break;
        case STORAGE_PHYSICAL_QUANTITY_FLOW: name = "Flow";  break;
        case STORAGE_PHYSICAL_QUANTITY_ANGLE: name = "Angle";  break;
        case STORAGE_PHYSICAL_QUANTITY_RADIOACTIVITY: name = "Radioactivity";  break;
        case STORAGE_PHYSICAL_QUANTITY_MAGNETIC_FLUX_DENSITY: name = "MagneticFluxDensity";  break;
        case STORAGE_PHYSICAL_QUANTITY_ELECTRIC_CHARGE: name = "ElectricCharge";  break;
        case STORAGE_PHYSICAL_QUANTITY_ILLUMINANCE: name = "Illuminance";  break;
        case STORAGE_PHYSICAL_QUANTITY_RESISTANCE: name = "Resistance";  break;
        case STORAGE_PHYSICAL_QUANTITY_CAPACITANCE: name = "Capacitance";  break;
        case STORAGE_PHYSICAL_QUANTITY_VOLUME: name = "Volume";  break;
        case STORAGE_PHYSICAL_QUANTITY_TORQUE: name = "Torque";  break;
        case STORAGE_PHYSICAL_QUANTITY_LIGHT_FLUX: name = "LightFlux";  break;
        case STORAGE_PHYSICAL_QUANTITY_FREQUENCY: name = "Frequency";  break;
        case STORAGE_PHYSICAL_QUANTITY_INDUCTANCE: name = "Inductance";  break;
        case STORAGE_PHYSICAL_QUANTITY_ELECTRIC_CONDUCTANCE: name = "ElectricConductance";  break;
        case STORAGE_PHYSICAL_QUANTITY_TEMPERATURE: name = "Temperature";  break;
        case STORAGE_PHYSICAL_QUANTITY_PRESSURE_CHANGE: name = "PressureChange";  break;
        case STORAGE_PHYSICAL_QUANTITY_MAGNETIC_FLUX: name = "MagneticFlux";  break;
        case STORAGE_PHYSICAL_QUANTITY_ENERGY: name = "Energy";  break;
        case STORAGE_PHYSICAL_QUANTITY_LUMINOUS_INTENSITY: name = "LuminousIntensity";  break;
        case STORAGE_PHYSICAL_QUANTITY_FORCE: name = "Force";  break;
        case STORAGE_PHYSICAL_QUANTITY_POWER: name = "Power";  break;
        default: name = "?"; break;
    }
    return name;
}


const char* StorageUnitsToStr(const StorageUnits_t storage_uints) {
    char* name = "?";
    switch(storage_uints) {
    case STORAGE_UNITS_NO_UNIT: name = "NoUnits"; break;
    case STORAGE_UNITS_METER: name = "meter";        break;
    case STORAGE_UNITS_FOOT: name = "foot";        break;
    case STORAGE_UNITS_INCH: name = "inch";        break;
    case STORAGE_UNITS_YARD: name = "yard";        break;
    case STORAGE_UNITS_MILE: name = "mile";        break;
    case STORAGE_UNITS_GRAM: name = "Gram";        break;
    case STORAGE_UNITS_TON:  name = "ton";        break;
    case STORAGE_UNITS_SECOND: name = "Sec";        break;
    case STORAGE_UNITS_MINUTE: name = "Minute";        break;
    case STORAGE_UNITS_HOUR: name = "Hour";        break;
    case STORAGE_UNITS_DAY:  name = "Day";        break;
    case STORAGE_UNITS_YEAR: name = "Year";        break;
    case STORAGE_UNITS_AMPERE: name = "Ampere";        break;
    case STORAGE_UNITS_VOLT:        name = "Volt";        break;
    case STORAGE_UNITS_COULOMB:        name = "Coulomb";        break;
    case STORAGE_UNITS_OHM:        name = "Ohm";        break;
    case STORAGE_UNITS_FARAD:        name = "Farad";        break;
    case STORAGE_UNITS_HENRY:        name = "Henry";        break;
    case STORAGE_UNITS_SIEMENS:        name = "Siemens";        break;
    case STORAGE_UNITS_WEBER:        name = "Weber";        break;
    case STORAGE_UNITS_TESLA:        name = "Tesla";        break;
    case STORAGE_UNITS_KELVIN:        name = "Kelvin";        break;
    case STORAGE_UNITS_CELSIUS:        name = "Celsius";        break;
    case STORAGE_UNITS_FAHRENHEIT:        name = "Fahrenheit";        break;
    case STORAGE_UNITS_CANDELA:        name = "candela";        break;
    case STORAGE_UNITS_RADIAN:        name = "rad";        break;
    case STORAGE_UNITS_DEGREE:        name = "deg";        break;
    case STORAGE_UNITS_HERTZ:        name = "Hz";        break;
    case STORAGE_UNITS_JOULE:        name = "joule";        break;
    case STORAGE_UNITS_NEWTON:        name = "Newton";        break;
    case STORAGE_UNITS_KILOPOND:        name = "kilopond";        break;
    case STORAGE_UNITS_POUND:        name = "pound";        break;
    case STORAGE_UNITS_WATT:        name = "watt";        break;
    case STORAGE_UNITS_HORSE_POWER_HK:        name = "horsePw(metric)";        break;
    case STORAGE_UNITS_HORSE_POWER_HP:        name = "horsePw(UKUS)";        break;
    case STORAGE_UNITS_PASCAL:        name = "Pascal";        break;
    case STORAGE_UNITS_BAR:        name = "bar";        break;
    case STORAGE_UNITS_ATMOSPHERE:        name = "atm";        break;
    case STORAGE_UNITS_POUND_FORCE_PER_SQUARE_INCH:        name = "poundForce/(inch^2)";        break;
    case STORAGE_UNITS_BECQEREL:        name = "becqerel";        break;
    case STORAGE_UNITS_LUMEN:        name = "lumen";        break;
    case STORAGE_UNITS_LUX:        name = "lux";        break;
    case STORAGE_UNITS_LITER:        name = "liter";        break;
    case STORAGE_UNITS_GALLON_BRITISH:        name = "gallon(UK)";        break;
    case STORAGE_UNITS_GALLON_US:        name = "gallon(US)";        break;
    case STORAGE_UNITS_CUBIC_INCH:        name = "cubic inch cu";        break;
    case STORAGE_UNITS_METER_PER_SECOND:        name = "meterPerSec";        break;
    case STORAGE_UNITS_KILOMETER_PER_HOUR:        name = "km/h";        break;
    case STORAGE_UNITS_MILE_PER_HOUR:        name = "mph";        break;
    case STORAGE_UNITS_REVOLUTIONS_PER_SECOND:        name = "RPS";        break;
    case STORAGE_UNITS_REVOLUTIONS_PER_MINUTE:        name = "PRM";        break;
    case STORAGE_UNITS_COUNTS:        name = "counts";        break;
    case STORAGE_UNITS_PERCENT:        name = "%%";        break;
    case STORAGE_UNITS_MILLIGRAM_PER_STROKE:        name = "mg/stroke";        break;
    case STORAGE_UNITS_METER_PER_SQUARE_SECOND:        name = "m/s2";        break;
    case STORAGE_UNITS_NEWTON_METER:        name = "Nm";        break;
    case STORAGE_UNITS_LITER_PER_MINUTE:        name = "liter/min";        break;
    case STORAGE_UNITS_WATT_PER_SQUARE_METER:        name = "watt/m2";        break;
    case STORAGE_UNITS_BAR_PER_SECOND:        name = "bar/s";        break;
    case STORAGE_UNITS_RADIANS_PER_SECOND:        name = "rad/s";       break;
    case STORAGE_UNITS_RADIANS_PER_SQUARE_SECOND:        name = "rad/s2";        break;
    case STORAGE_UNITS_KILOGRAM_PER_SQUARE_METER:        name = "kg/m2";        break;

    default:        name = "?";        break;
    }
    return name;
}

const char* StorageScaleToStr(const StorageScale_t scale) {
    const char* name = "?";
    switch(scale) {
        case STORAGE_SCALE_EXA:    name = "exa";   break;
        case STORAGE_SCALE_PETA:   name = "peta";  break;
        case STORAGE_SCALE_TERA:   name = "tera";  break;
        case STORAGE_SCALE_GIGA:   name = "giga";  break;
        case STORAGE_SCALE_MEGA:   name = "mega";  break;
        case STORAGE_SCALE_KILO:   name = "kilo";  break;
        case STORAGE_SCALE_HECTO:  name = "hecto"; break;
        case STORAGE_SCALE_DECA:   name = "deca";  break;
        case STORAGE_SCALE_DECI:   name = "deci";  break;
        case STORAGE_SCALE_CENTI:  name = "centi"; break;
        case STORAGE_SCALE_MILLI:  name = "milli"; break;
        case STORAGE_SCALE_MICRO:  name = "micro"; break;
        case STORAGE_SCALE_NANO:   name = "nano";  break;
        case STORAGE_SCALE_PICO:   name = "pico";  break;
        case STORAGE_SCALE_FEMTO:  name = "femto"; break;
        case STORAGE_SCALE_ATTO:   name = "atto";  break;
        case STORAGE_SCALE_ONES:   name = "1";      break;
        default:                   name = "no";     break;
    }
    return name;
}


const char* StorageAccessToStr(const StorageAccess_t access) {
    const char* name = "?";
    switch(access) {
        case ACCESS_READ_ONLY:        name = "RO";        break;
        case ACCESS_READ_WRITE:        name = "RW";        break;
        case ACCESS_WRITE_ONLY:        name = "WO";        break;
        case ACCESS_ERASE:        name = "ER";        break;
        default:        name = "?";        break;
    }
    return name;
}

const char* StorageTypeToStr(StorageType_t type) {
    const char* name = "?";
    switch(type) {
    case TYPE_ARRAY:
        name = "Array";
        break;
    case TYPE_UINT8:
        name = "u8";
        break;
    case TYPE_UINT16:
        name = "u16";
        break;
    case TYPE_BOOL:
        name = "Bool";
        break;
    case TYPE_INT8:
        name = "i8";
        break;
    case TYPE_UINT32_HEX:
        name = "u32_hex";
        break;
    case TYPE_UINT32:
        name = "u32";
        break;
    case TYPE_INT16:
        name = "i16";
        break;
    case TYPE_INT32:
        name = "u32";
        break;
    case TYPE_FLOAT:
        name = "Float";
        break;
    case TYPE_STRING:
        name = "Str";
        break;
    case TYPE_INT64:
        name = "i64";
        break;
    case TYPE_UINT64:
        name = "u64";
        break;
    case TYPE_DOUBLE:
        name = "Double";
        break;
    case TYPE_STRUCT:
        name = "Struct";
        break;
    case TYPE_TIME_DATE:
        name = "Time";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

/*TODO: Test it
  buff [in]
  value_len [in]
  type [in]
  out_str [out]
  str_size [in]
  */
bool DataToValStrBuff(const uint8_t* const buff, size_t value_len, StorageType_t type, char* const out_str,
                      size_t str_size) {
    bool res = false;

    if(buff) {
        if(value_len) {
            if(out_str) {
                if(str_size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
        switch(type) {
        case TYPE_STRING:
            if(strlen((char*)buff) < str_size) {
                snprintf(out_str, str_size, "%s", buff);
                res = true;
            }
            break;
        case TYPE_ARRAY:
            if((2 * value_len) < str_size) {
                res = hex2ascii(buff, value_len, (uint8_t*)out_str, str_size);
            }
            break;

        case TYPE_TIME_DATE: {
#ifdef HAS_TIME_DIAG
            struct tm time_date = {0};
            memcpy(&time_date, buff, sizeof(struct tm));
            res = TimeDateToStrExt(&time_date, out_str, str_size);
            if(res) {

            } else {
                LOG_ERROR(STORAGE, "ConvertErr");
            }
#endif /*HAS_TIME_DIAG*/
        } break;
        case TYPE_BOOL:
        case TYPE_UINT8:
            if(1 == value_len) {
                //  Type8Union_t un8;
                //  memcpy(&un8.u8, value, sizeof(Type8Union_t));
                snprintf(out_str, str_size, "%3u", *buff);
                res = true;
            }
            break;

        case TYPE_INT8:
            if(1 == value_len) {
                Type8Union_t un8;
                memcpy(&un8, buff, sizeof(Type8Union_t));
                snprintf(out_str, str_size, "%3d", un8.s8);
                res = true;
            }
            break;

        case TYPE_UINT16:
            if(2 == value_len) {
                Type16Union_t un16;
                memcpy(&un16, buff, sizeof(Type16Union_t));
                snprintf(out_str, str_size, "%" PRIu16, un16.u16);
                res = true;
            }
            break;
        case TYPE_INT16:
            if(2 == value_len) {
                Type16Union_t un16 = {0};
                memcpy(&un16, buff, sizeof(Type16Union_t));
                snprintf(out_str, str_size, "%" PRId16, un16.s16);
                res = true;
            }
            break;
        case TYPE_UINT32:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "%" PRIu32, un32.u32);
                res = true;
            }
            break;
        case TYPE_UINT32_HEX:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "0x%08" PRIx32, un32.u32);
                res = true;
            }
            break;
        case TYPE_INT32:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "%" PRId32, un32.s32);
                res = true;
            }
            break;
        case TYPE_UINT64:
            if(8 == value_len) {
                Type64Union_t un64;
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(out_str, str_size, "%llx", un64.u64);
                res = true;
            }
            break;
        case TYPE_INT64:
            if(8 == value_len) {
                Type64Union_t un64 = {0};
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(out_str, str_size, "%llx", un64.s64);
                res = true;
            }
            break;
        case TYPE_STRUCT:
            if(strlen((char*)buff) < str_size) {
                res = hex2ascii(buff, value_len, (uint8_t*)out_str, str_size);
            }
            break;

        case TYPE_FLOAT:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "%.1f", un32.f32);
                res = true;
            }
            break;
        case TYPE_DOUBLE:
            if(8 == value_len) {
                Type64Union_t un64;
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(out_str, str_size, "%.3f", un64.d64);
                res = true;
            }
            break;
        default:
            res = false;
            break;
        } /*switch*/
    }
    return res;
}

const char* StorageDataToValueStr(const uint8_t* const buff,
                                  const uint32_t size,
                                  const StorageType_t type) {
    static char lText[200]={0};
    strncpy(lText, "?", sizeof(lText));
    if(buff) {
        if(size) {
            bool res = DataToValStrBuff(buff, size, type, lText, sizeof(lText));
            if(false == res) {
                strncpy(lText, "DataErr", sizeof(lText));
            } else {
            }
        } else {
            strncpy(lText, "SizeErr", sizeof(lText));
        }
    } else {
        strncpy(lText, "BuffErr", sizeof(lText));
    }
    return lText;
}

const char* StorageFrameHeaderToStr(const StorageFrameHeader_t* const Header) {
    static char lText[120] = {0};
    if(Header) {
        strcpy(lText, "");
        memset(lText, 0, sizeof(lText));
        snprintf(lText, sizeof(lText), "%sASIC:%u,", lText, Header->asic_num);
        snprintf(lText, sizeof(lText), "%sOp:%s,", lText, StorageAccessToStr(Header->operation));
        snprintf(lText, sizeof(lText), "%sAddr:0x%08x,", lText, Header->address);
        snprintf(lText, sizeof(lText), "%sSize:%u,", lText, Header->size);
    }
    return lText;
}

const char* StorageIdToStr(const StorageId_t id) {
    char* name = "?";
    uint16_t i = 0;
    uint32_t cnt = storage_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == StorageArray[i].id) {
            name = StorageArray[i].name;
            break;
        }
    }
    return name;
}

const char* StorageItemToStr(const StorageItem_t* const Item) {
    static char lText[120] = {0};
    if(Item) {
        strcpy(lText, "");
        memset(lText, 0, sizeof(lText));
        snprintf(lText, sizeof(lText), "%sID%u=", lText, Item->id);
        snprintf(lText, sizeof(lText), "%s%s,", lText, StorageIdToStr(Item->id));
        snprintf(lText, sizeof(lText), "%sTYPE:%s,", lText, StorageTypeToStr(Item->type));
        snprintf(lText, sizeof(lText), "%sLEN:%u,", lText, Item->len);

        if(Item->name) {
            snprintf(lText, sizeof(lText), "%sName:%s,", lText, Item->name);
        }
        if(Item->default_value) {
            snprintf(lText, sizeof(lText), "%sDft:%s,", lText, Item->default_value);
        }
        snprintf(lText, sizeof(lText), "%sHide:%u,", lText, Item->hide);
        snprintf(lText, sizeof(lText), "%sFac:%s,", lText, FacilityToStr(Item->facility));
    }
    return lText;
}
