#ifndef HEX_BIN_TYPES_H
#define HEX_BIN_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include "hex_bin_const.h"
#include "data_types.h"
#include "crc_types.h"
#include "time_mcal.h"
#include "file_api_types.h"

typedef struct {
    uint8_t rec_len;  /*byte*/
    uint16_t load_offset;  /**/
    HexRecType_t rec_type;  /**/
    uint8_t data[32];
    Crc8_t crc8;
}HexFrame_t;

#define HEX_BIN_COMMON_VARIABLES \
    bool valid;

typedef struct{
    HEX_BIN_COMMON_VARIABLES
}HexBinConfig_t;

typedef struct{
    HEX_BIN_COMMON_VARIABLES
    bool init;
    bool already_the_same; /*flag to prevent updating when FW already the same*/
#ifdef HAS_PC
    uint8_t* bin_data;
#endif
    FILE* HexFilePtr;
    int32_t total_lines;
    size_t line_len;
    size_t matching_size;
    size_t diff_size;
    size_t line_cnt; /*Hex file line*/
    size_t bin_size_byte; /*sum of data chunks*/
    size_t address_size_byte; /*address space size*/
    char hex_line[80];
    char hex_file_name[80];
    char only_file_name[80];
    Type32Union_t address;
    U32Value_t address_range;
    uint32_t fw_crc23;
    uint32_t base_address; /*binary start addr of firmware*/
    uint32_t next_exp_address;  /*for   continuity check*/
    uint32_t fragment_cnt; /* */
    HexFrame_t frame;
    FileApiHandle_t FileItem;
    TimeStampSec_t time_stamp;
}HexBinHandle_t;


#endif /* HEX_BIN_TYPES_H */
