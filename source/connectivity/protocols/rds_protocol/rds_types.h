#ifndef RDS_TYPES_H
#define RDS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "rds_constants.h"

typedef union {
    uint16_t word;
    struct {
        uint16_t prog_ref_num : 8;       /*Programme Reference Number*/
        uint16_t prog_area_coverage : 4; /*Program Area Coverage*/
        uint16_t country_code : 4;       /*Country Code */
    };
} ProgramId_t;

typedef union {
    uint16_t word;
    ProgramId_t program_id; /*Program Identification Code*/
} BlockA_t;

/*Figure 10*/
typedef union {
    uint16_t word;
    struct {
        uint16_t app : 5;        /* Rest of the bits are group type dependent */
        uint16_t pty : 5;        /*Program Type */
        uint16_t tp : 1;         /*Traffic Program. Indicates this channel includes periodic traffic reports. */
        uint16_t b0 : 1;         /*If B0=0 then Message Group Type A else Type B */
        uint16_t group_type : 4; /*Group Type */
    };
} BlockB_t;

typedef union {
    uint8_t byte[2];
    uint16_t word;
    uint16_t payload; /* Group Specific Payload*/
} BlockC_t;

typedef union {
    uint8_t byte[2];
    uint16_t word;
    uint16_t payload; /*Group Specific Payload*/
} BlockD_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        uint64_t ch4 : 8;     //     RadioText
        uint64_t ch3 : 8;     //     RadioText
        uint64_t ch2 : 8;     //     RadioText
        uint64_t ch1 : 8;     //     RadioText
        uint64_t segment : 4; // Text segment
        uint64_t flag : 1;    //  Text flag
        uint64_t pty : 5;
        uint64_t tp : 1; //
        uint64_t b0 : 1; //
        uint64_t group_type : 4;
        uint64_t pi_code : 16;
    };
} RadioText2A_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        uint64_t ch2 : 8; //     RadioText
        uint64_t ch1 : 8; //     RadioText
        uint64_t pi_code1 : 16;
        uint64_t segment : 4; // Text segment
        uint64_t flag : 1;
        uint64_t pty : 5;
        uint64_t tp : 1;
        uint64_t b0 : 1;
        uint64_t group_type : 4;
        uint64_t pi_code : 16;
    };
} RadioText2B_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        uint64_t ch2 : 8;       //
        uint64_t ch1 : 8;       //
        uint64_t alt_freq1 : 8; /*Alternative freq code*/
        uint64_t alt_freq2 : 8; //
        uint64_t segment : 2;   // Text segment
        uint64_t di : 1;
        uint64_t ms : 1;
        uint64_t ta : 1;
        uint64_t pty : 5;
        uint64_t tp : 1;
        uint64_t b0 : 1;
        uint64_t group_type : 4;
        uint64_t pi_code : 16;
    };
} BasicTuning0A_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        uint64_t ch4 : 8;     //
        uint64_t ch3 : 8;     //
        uint64_t ch2 : 8;     //
        uint64_t ch1 : 8;     //
        uint64_t segment : 1; // Text segment
        uint64_t res : 3;
        uint64_t ab : 1;  /**/
        uint64_t pty : 5; /*Programme type*/
        uint64_t tp : 1;
        uint64_t b0 : 1;
        uint64_t group_type : 4;
        uint64_t pi_code2 : 16; /*Programme identification*/
    };
} ProgTyteNameA_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        uint64_t res1 : 16;     //
        uint64_t pi_code1 : 16; /*Programme identification*/
        uint64_t res : 5;
        uint64_t pty : 5; /*Programme type*/
        uint64_t tp : 1;
        uint64_t b0 : 1;
        uint64_t group_type : 4;
        uint64_t pi_code2 : 16; /*Programme identification*/
    };
} ProgTyteNameB_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        uint64_t ch2 : 8; //
        uint64_t ch1 : 8; //
        uint64_t pi_code1 : 16;
        uint64_t segment : 2; // Text segment
        uint64_t di : 1;
        uint64_t ms : 1;  /*Music speech sw code */
        uint64_t ta : 1;  /*Traffic accounsment*/
        uint64_t pty : 5; /*Programme type*/
        uint64_t tp : 1;
        uint64_t b0 : 1;
        uint64_t group_type : 4;
        uint64_t pi_code2 : 16; /*Programme identification*/
    };
} BasicTuning0B_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    uint64_t dqwprd;
    struct {
        BlockD_t BlockD;
        BlockC_t BlockC;
        BlockB_t BlockB;
        BlockA_t BlockA;
    };
    struct {
        uint64_t loc_time_offset : 6;   // Local Time Offset
        uint64_t min : 6;               // UTC Minutes
        uint64_t hour : 5;              // UTC Hours
        uint64_t mod_jul_day_code : 17; /*Modified Julian Day Number/code */
        uint64_t res : 3;
        uint64_t pty : 5;
        uint64_t tp : 1;
        uint64_t b0 : 1;
        uint64_t group_type : 4;
        uint64_t pi_code : 16;
    };
} ClockTimeDate_t;

typedef union {
    uint64_t dqwprd;
    uint16_t word[4];
    struct {
        uint64_t pi_code : 16;
        uint64_t group_type : 4;
        uint64_t b0 : 1;
        uint64_t tp : 1;
        uint64_t pty : 5;
        uint64_t res : 3;
        uint64_t mod_jul_day_code : 17; /*Modified Julian day code*/
        uint64_t hour : 5;
        uint64_t min : 6;
        uint64_t loc_time_offset : 6;
    };
} ClockTimeDateInv_t;

typedef union {
    uint8_t byte[8];
    uint16_t word[4];
    ClockTimeDate_t ClockTimeDate;
    RadioText2A_t RadioTextFrame2A;
    RadioText2B_t RadioTextFrame2B;
    BasicTuning0A_t BasicTuning0A;
    ProgTyteNameA_t ProgTyteNameA;
    ProgTyteNameB_t ProgTyteNameB;
    BasicTuning0B_t BasicTuning0B;
    struct {
        BlockD_t BlockD;
        BlockC_t BlockC;
        BlockB_t BlockB;
        BlockA_t BlockA;
    };
} RdsMessage_t;

typedef struct {
    RdsMessage_t Message;
    uint32_t time_cnt;
    uint32_t text_cnt;
    uint32_t rx_pkt_cnt;
    char RadioText[65];
    char ProgServiceName[9];
    char ProgTypeName[9];
} RdsProtocol_t;

typedef struct {
    uint8_t CountryCode;
    char* name;
} CountryCodeInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* RDS_TYPES_H */
