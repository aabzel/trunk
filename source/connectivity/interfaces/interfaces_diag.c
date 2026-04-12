#include "interfaces_diag.h"

#include <stddef.h>

#include "interfaces_types.h"
#include "macro_utils.h"
#include "diag_inc.h"

const char* IfBusRoleToStr(const IfBusRole_t bus_role) {
    const char* name = "?";
    switch(bus_role) {
        case BUS_ROLE_MASTER: name = "Master"; break;
        case BUS_ROLE_SLAVE: name = "Slave"; break;
        default: name = "?"; break;
    }
    return name;
}

const char* IfBitOrderToStr(const IfBitOrder_t bit_order) {
    const char* name = "?";
    switch(bit_order) {
        case BIT_ORDER_MSB: name = "Msb1st"; break;
        case BIT_ORDER_LSB: name = "Lsb1st"; break;
        default: name = "??"; break;
    }
    return name;
}

static const InterfaceNameInfo_t InterfaceNameInfo[] = {
    { .inter_face = INTERFACE_NAME_LOOPBACK, .name = "LoopBack", .valid = true,    },
    { .inter_face = INTERFACE_NAME_BLACKHOLE, .name = "BlackHole", .valid = true,    },
    { .inter_face = INTERFACE_NAME_CAN, .name = "CAN", .valid = true,    },
    { .inter_face = INTERFACE_NAME_SERIAL_PORT, .name = "SERIAL_PORT", .valid = true,    },
    { .inter_face = INTERFACE_NAME_UART, .name = "UART", .valid = true,    },
    { .inter_face = INTERFACE_NAME_SDIO, .name = "SDIO", .valid = true,    },
    { .inter_face = INTERFACE_NAME_STDIO, .name = "STDIO", .valid = true,    },
    { .inter_face = INTERFACE_NAME_RS232, .name = "RS232", .valid = true,    },
    { .inter_face = INTERFACE_NAME_RS485, .name = "RS485", .valid = true,    },
    { .inter_face = INTERFACE_NAME_ISO_TP, .name = "ISO_TP", .valid = true,    },
};

const InterfaceNameInfo_t* InterfaceNameToInfo(const InterfaceName_t if_name) {
    const InterfaceNameInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(InterfaceNameInfo);
    for(i = 0; i < cnt; i++) {
        if(if_name == InterfaceNameInfo[i].inter_face) {
            if(InterfaceNameInfo[i].valid) {
                Info = &InterfaceNameInfo[i];
                break;
            }
        }
    }
    return Info;
}

const char* InterfaceNameToStr(const InterfaceName_t if_name) {
    const char* name = "?";
    const InterfaceNameInfo_t* Info = InterfaceNameToInfo(if_name);
    if(Info) {
        name = Info->name;
    }
    return name;
}

const char* InterfaceTypeToStrShort(const InterfaceType_t inter_face) {
    static char Temp[30]={0};
    memset(Temp,0,sizeof(Temp));
    strcpy(Temp, "");
    snprintf(Temp, sizeof(Temp), "%s", InterfaceNameToStr(inter_face.interface_name));
    snprintf(Temp, sizeof(Temp), "%s%u", Temp, inter_face.num);
    return Temp;
}

const char* InterfaceToStr(const InterfaceType_t inter_face) {
    const char* name = "?";
    name = InterfaceTypeToStrShort( inter_face) ;
    return name;
}

const char* InterfaceTypeToStr(const InterfaceType_t inter_face) {
    static char lText[80]={0};
    strcpy(lText, "");
    snprintf(lText, sizeof(lText), "%sIfCode:0x%04x=", lText, inter_face.word);
    snprintf(lText, sizeof(lText), "%s%u,", lText, inter_face.word);
    snprintf(lText, sizeof(lText), "%s%s", lText, InterfaceTypeToStrShort(inter_face));
    return lText;
}

