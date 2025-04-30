#ifndef SW_NVRAM_TYPES_H
#define SW_NVRAM_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_DOT
#include <stdio.h>
#endif

#include "sw_nvram_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t not_deleted : 1; /*0-deleted node*/
        uint8_t freshness : 1;   /*0-old node 1-new node*/
        uint8_t res : 6;
    };
} NvRamNodeState_t;

typedef struct {
    uint32_t page_start;
    uint32_t size;
    uint32_t prefix;
    uint8_t num;
} NvRamPageConfig_t;

typedef struct {
    uint8_t num;
    char* name;
    NvRamPageConfig_t page[2];
    uint8_t nor_flash_num;
    // uint32_t start_mem;
    bool valid;
} NvRamConfig_t;

typedef struct {
    uint32_t plane;
    uint32_t inverted;
} NvRamAddr_t;
//
typedef struct {
    uint16_t signature;        /*0 2+*/
    uint16_t data_crc16;       /*2 2+*/
    NvRamAddr_t address;       /*4 8+*/
    uint32_t write_counter;    /*4+*/
    uint32_t write_time_stamp; /*4+*/
    uint32_t left_node_addr;   /*4+*/
    uint32_t right_node_addr;  /*4+*/
    uint32_t data_size;        /*4+*/
    uint16_t name_size;        /*2+*/
    NvRamNodeState_t state;    /*1+*/
    DataType_t data_type;      /*1+*/
} __attribute__((packed)) NvRamHeader_t;

typedef struct {
    uint8_t num;
    uint32_t entry_cnt;
    uint32_t phy_end_addr;
    uint32_t start_mem;
    uint32_t end_physical_address;
    uint32_t spare_size;
    uint32_t del_cnt;

    NvRamPage_t active_page;
    uint8_t nor_flash_num;
    bool init;
    bool valid;
    char temp_str[250];
    NvRamPageConfig_t page[2];
#ifdef HAS_DOT
    FILE* dot_file;
#endif
} NvRamItem_t;

typedef bool EntryActionFoo_t(NvRamItem_t* Node, NvRamHeader_t* Header, uint32_t base);

#endif /*SW_NVRAM_TYPES_H*/
