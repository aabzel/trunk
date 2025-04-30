
#ifndef BOARD_INFO_TYPES_H
#define BOARD_INFO_TYPES_H

#include <stdint.h>

#include "gpio_types.h"
#include "board_const.h"
#include "sys_constants.h"
#include "board_custom_types.h"

typedef struct {
    char* designator;
    uint16_t num;
}Connector_t;

typedef struct {
    char* designator;
    uint16_t num;
    uint16_t pin;
}ConnectorPin_t;

typedef struct {
    Pad_t pad;
    ConnectorPin_t conn;
    char* wire_name;
    char* silk;
    facility_t facility;
}Wire_t;

typedef struct {
    ConnectorPin_t conn;
    char *wire_name;
}WirePin_t;

typedef struct {
    Pad_t volt_id_pad;
    double volt_id;
    char* name;
    uint32_t xtall_freq_hz;
    BOARD_CUSTOM_CONFIG
}BoardConfig_t;

#endif /* BOARD_INFO_TYPES_H */
