#ifndef SA51034_REG_TYPES_H
#define SA51034_REG_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "sa51034_const.h"

/* Reg 0x03
 * Control Register*/
typedef union{
    uint8_t byte;
    struct{
        uint8_t frequency : 1; /*0 Switching frequency set to 500kHz */
        uint8_t reserved : 2; /*2-1 res*/
        uint8_t power_limit : 3; /*5-3  Power limit*/
        uint8_t gain : 2; /*7-6  gain */

    };
}Sa51034RegControlRegister_t;

/* Reg 0x01
 * Table 3. Fault Register (0x01)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t res : 2;                       /*bit 0-1  Reserved*/
        uint8_t ld_fault : 1;                  /*2  A load-diagnostics faults has occurred*/
        uint8_t over_current_shutdown  : 1;    /*3 Over current shutdown has occurred*/
        uint8_t pvdd_under_voltage : 1;        /*4 PVDD under-voltage has occurred*/
        uint8_t pvdd_over_voltage : 1;         /*5 PVDD over-voltage has occurred*/
        uint8_t dc_offset_protection : 1;      /*6 DC offset protection has occurred*/
        uint8_t over_temperature_shutdown : 1; /*7 Over-temperature shutdown has occurred*/
    };
}Sa51034RegLatchedFault_t;

/* Reg 0x02
 * Table 4. Status and Load Diagnostic Register (0x02)*/
typedef union{
    uint8_t byte;
    struct{
    	uint8_t short_pvdd : 1;  /* bit 0 Output short to PVDD*/
        uint8_t short_gnd : 1;   /* bit:1 Output short to Ground*/
        uint8_t open_load : 1;   /* bit:2 Open load*/
        uint8_t shorted_load : 1; /*bit:3 Shorted load*/
        uint8_t fault_state : 1; /*bit:4 In a fault state*/
        uint8_t run_load_detect : 1; /*bit:5 Performing load detection*/
        uint8_t mute: 1; /*bit:6 In mute mode*/
        uint8_t play : 1; /*bit:7 In play mode*/
    };
}Sa51034RegStatusAndLoadDiagnostic_t;

typedef union{
    uint8_t byte;
    Sa51034RegLatchedFault_t LatchedFault;
    Sa51034RegStatusAndLoadDiagnostic_t StatusAndLoadDiagnostic ;
    Sa51034RegControlRegister_t ControlRegister;
}Sa51034RegUniversal_t;

#endif /* SA51034_REG_TYPES_H */
