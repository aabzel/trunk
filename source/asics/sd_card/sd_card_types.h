#ifndef SD_CARD_TYPES_H
#define SD_CARD_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "gpio_types.h"
#include "sd_card_const.h"

#ifndef HAS_SD_CARD
#error "+HAS_SD_CARD"
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

typedef struct {
    uint8_t cmd;
    int16_t ret_len;
    SdSpiRespType_t resp_type;
    char* name;
} SdCommandInfo_t;

typedef struct {
    uint32_t one1 : 1; /* bit0 */
    uint32_t crc7 : 7;
    uint32_t args;
    uint32_t index : 6;
    uint32_t one2 : 1;
    uint32_t zero : 1;
} __attribute__((__packed__)) SdFramePlane_t;

typedef union {
    uint8_t buff[6];
    struct {
        uint32_t one1 : 1; /* bit0 */
        uint32_t crc7 : 7;
        uint32_t args : 32;
        uint32_t index : 6;
        uint32_t one2 : 1;
        uint32_t zero : 1;
    } __attribute__((__packed__));
} SdFrame_t;

/*Manufacturing date*/
typedef union {
    uint16_t word;
    struct {
        uint8_t month : 4; /* bit0 */
        uint8_t year : 8;
        uint8_t res : 4;
    } __attribute__((__packed__));
} Mdt_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t idle : 1; /* bit0: 0-busy, 1-idle */
        uint8_t erase_reset : 1;/* bit1 */
        uint8_t illegal_cmd : 1;/* bit2 */
        uint8_t com_crc_err : 1;/* bit3 */
        uint8_t errase_sec_err : 1;/* bit4 */
        uint8_t addr_err : 1; /*bit 5 Address error*/
        uint8_t param_err : 1;/* bit6 */
        uint8_t msb_zero : 1; /*bit7 Always 0*/
    } __attribute__((__packed__));
} R1_t;

typedef union {
    uint8_t byte[4];
    uint32_t dword;
    struct {
        uint32_t res1 : 24; /* bit0 */
        uint32_t sw_1_8_accep : 1;
        uint32_t res2 : 4;
        uint32_t uhs_ii_card_status : 1;   /**/
        uint32_t card_capacity_status : 1; /*Bit 30 Card capacity status bit*/
        uint32_t card_power_up_status : 1; /*Bit 31 Card power up status bit*/
    };
} OCR_t;

/*7.3.2.4 Format R3*/
typedef union {
    uint8_t byte[5];
    struct {
        OCR_t ocr;
        R1_t R1;
    } __attribute__((__packed__));
} R3_t;

/*7.3.2.6 Format R7*/
typedef union {
    uint32_t dword;
    struct {
        uint32_t echo_back : 8;        /*7-0*/
        uint32_t voltage_accepted : 4; /*11-8*/
        uint32_t res1 : 16;            /*bit 27-12*/
        uint32_t cmd_version : 4;      /*31-27*/
    } __attribute__((__packed__));
} R7Data_t;

/*7.3.2.6 Format R7*/
typedef union {
    uint8_t buff[5];
    struct {
        struct {
            uint32_t echo_back : 8;        /*7-0 check pattern*/
            uint32_t voltage_accepted : 4; /*11-8 voltage accepted*/
            uint32_t res : 16;             /*bit 27-12*/
            uint32_t cmd_version : 4;      /*31-27 command version*/
        } __attribute__((__packed__));
        R1_t R1;
    } __attribute__((__packed__));
} R7_t;

typedef union {
    uint8_t byte[2];
    uint16_t word;
    struct {
        struct {
            uint16_t card_is_locked : 1;  /*0*/
            uint16_t wp_erase_skip : 1;   /*1*/
            uint16_t error : 1;           /*2*/
            uint16_t cc_error : 1;        /*3*/
            uint16_t card_ecc_failed : 1; /*4*/
            uint16_t wp_violation : 1;    /*5*/
            uint16_t erase_param : 1;     /*6*/
            uint16_t out_of_range : 1;    /*7*/
        } __attribute__((__packed__));
        R1_t R1;
    };
} R2_t;


/*SEND_IF_COND*/
typedef union {
    uint32_t arg;
    struct {
        uint32_t check_pattern : 8;  /*bit 0-7 */
        uint32_t supply_voltage : 4; /*bit 8-11 */
        uint32_t reserved : 20;      /*bit 12-31 */
    };
} Cmd8Arg_t;

/*SD_SEND_OP_COND*/
typedef union {
    uint32_t arg;
    struct {
        uint32_t res1 : 30; /*29...0 */
        uint32_t hcs : 1;   /*30 HCS*/
        uint32_t res2 : 1;  /*31*/
    };
} ACmd41Arg_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t one : 1; /* bit0 */
        uint8_t status : 3;
        uint8_t zero : 1;
        uint8_t res : 3;
    };
} DataResponseToken_t;

typedef union {
    uint8_t byte[16];
    uint16_t word[8];
    uint32_t dword[4];
    uint64_t qword[2];

    struct {
        uint32_t one : 1; /* bit0 */
        uint32_t crc : 7;
        uint32_t res1 : 2;
        uint32_t file_format : 2;
        uint32_t temp_write_protect : 1;
        uint32_t perm_write_protect : 1;
        uint32_t copy : 1;
        uint32_t file_format_grp : 1;
        uint32_t res2 : 5;
        uint32_t write_bl_partial : 1;
        uint32_t write_bl_len : 4;
        uint32_t r2w_factor : 3;
        uint32_t res3 : 2;
        uint32_t wp_grp_enable : 1;
        uint32_t wp_grp_size : 7;
        uint32_t sector_size : 7;
        uint32_t erase_blk_en : 1;
        uint32_t c_size_mult : 3;
        uint32_t vdd_w_curr_max : 3;
        uint32_t vdd_w_curr_min : 3;
        uint32_t vdd_r_curr_max : 3;
        uint32_t vdd_r_curr_min : 3;
        uint32_t c_size : 12;
        uint32_t res4 : 2;
        uint32_t dsr_imp : 1;
        uint32_t read_blk_misalign : 1;
        uint32_t write_blk_misalign : 1;
        uint32_t read_bl_partial : 1;
        uint32_t read_bl_len : 4;
        uint32_t ccc : 12;
        uint32_t tran_speed : 8;
        uint32_t nsac : 8;
        uint32_t taac : 8;
        uint32_t res5 : 6;
        uint32_t csd_structure : 2;
    } __attribute__((__packed__)) V1;
    struct {
        uint32_t one : 1; /* bit0 */
        uint32_t crc : 7;
        uint32_t res1 : 2;
        uint32_t file_format : 2;
        uint32_t temp_write_protect : 1;
        uint32_t perm_write_protect : 1;
        uint32_t copy : 1;
        uint32_t file_format_grp : 1;
        uint32_t res2 : 5;
        uint32_t write_bl_partial : 1;
        uint32_t write_bl_len : 4;
        uint32_t r2w_factor : 3;
        uint32_t res3 : 2;
        uint32_t wp_grp_enable : 1;
        uint32_t wp_grp_size : 7;
        uint32_t sector_size : 7;
        uint32_t erase_blk_en : 1;
        uint32_t res4 : 1;
        uint32_t c_size : 22;
        uint32_t res5 : 6;
        uint32_t dsr_imp : 1;
        uint32_t read_blk_misalign : 1;
        uint32_t write_blk_misalign : 1;
        uint32_t read_bl_partial : 1;
        uint32_t read_bl_len : 4;
        uint32_t ccc : 12;
        uint32_t tran_speed : 8;
        uint32_t nsac : 8;
        uint32_t taac : 8;
        uint32_t res6 : 6;
        uint32_t csd_structure : 2;
    } __attribute__((__packed__)) V2;
} __attribute__((__packed__)) CSD_t;

typedef union {
    uint8_t byte[64];
} SSR_t;

/*Card IDentification Register*/
typedef union {
    uint8_t byte[16];
    uint16_t word[8];
    uint32_t dword[4];
    uint64_t qword[2];
    struct {
        struct {
            uint32_t one : 1;  /*always 1*/
            uint32_t crc : 7;  /*CRC7 checksum*/
            uint32_t mdt : 12; /*manufacturing date*/
            uint32_t res : 4;
        } __attribute__((__packed__));
        uint32_t psn;   /*pruduct serial number*/
        uint8_t prv;    /*Producat revision*/
        uint8_t pnm[5]; /*Product Name*/
        uint16_t oid;   /*Application ID*/
        uint8_t mid;    /*Manufacturer ID*/
    } __attribute__((__packed__));
} CID_t;

typedef union {
    uint8_t byte[4];
    uint32_t dword;
} CSR_t;

typedef union {
    uint8_t byte[8];
    uint64_t qword;
} SCR_t;

typedef struct {
    uint32_t block_len;
    uint8_t spi_num;
    Pad_t chip_sel;
    bool valid;
} SdCardConfig_t;

typedef struct {
    int32_t chip_enable_cnt;
    uint16_t read_crc16;
    uint32_t err_cnt;
    uint32_t read_pat_try_cnt;
    uint32_t memory_capacity;
    uint32_t block_len;
    uint32_t mult;
    uint32_t block_number;
    uint8_t version;
    uint8_t power_flag;
    CSD_t CSD;
    OCR_t OCR;
    CID_t CID;
    SSR_t SSR;
    bool locked;
    uint8_t spi_num;
    bool valid;
} SdCardHandle_t;

#endif /* SD_CARD_TYPES_H */
