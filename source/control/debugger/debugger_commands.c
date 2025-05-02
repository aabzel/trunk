#include "debugger_commands.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef HAS_ALLOCATOR
#include "allocator_types.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

#include "convert.h"
#include "data_utils.h"
#include "debugger.h"
#include "log.h"
#include "log_utils.h"
#include "storage.h"
#include "sys_config.h"
#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif
#include "cli_drv.h"
#ifdef HAS_MICROCONTROLLER
#include "microcontroller.h"
#endif
#include "none_blocking_pause.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool cmd_write_memory(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint32_t address = 0u;
        uint32_t value = 0u;
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(DBG, "Invalid address hex value %s", argv[0]);
        } else {
            cli_printf("address: 0x%08x" CRLF, (unsigned int)address);
        }

        res = try_str2uint32(argv[1], &value);
        if(false == res) {
            LOG_ERROR(DBG, "Invalid value %s", argv[1]);
        } else {
            cli_printf("val: 0x%08x" CRLF, (unsigned int)value);
        }

        if(res) {
#ifdef HAS_FLASH
            res = is_flash_addr(address);
#endif
            if(res) {
                LOG_ERROR(DBG, "FlashWriteHasSpesialApi 0x%x", address);
            } else {
                LOG_INFO(DBG, "NotFlashAdr 0x%x", address);
#ifdef HAS_WRITE_ADDR
                LOG_INFO(DBG, "Try Addr[0x%x]=0x%x", address, value);
                res = write_addr_32bit(address, value);
#endif
            }
        }
    } else {
        LOG_ERROR(DBG, "Usage: wm: address value");
        LOG_INFO(DBG, "Usage: address 0xXXXXXXXX");
        LOG_INFO(DBG, "Usage: value 0xXXXXXXXX");
    }
    return res;
}

/* variable address can be obtained from *.elf due to readelf tool*/
bool cmd_read_memory(int32_t argc, char* argv[]) {
    bool res = false;
    char dir = 'f';
    uint32_t num_of_byte = 4u;
    uint32_t address = 0u;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(DBG, "InvalidAddrHexVal %s", argv[0]);
        } else {
            cli_printf("address: 0x%08x" CRLF, (unsigned int)address);
        }
    }
#if 0
    if(1 == argc) {
        uint32_t value = 0u;
        if(res) {
            value = read_addr_32bit(address);
            cli_printf("value: 0x%08x" CRLF, (unsigned int)value);
            print_bit_hint(9,32);
            cli_printf("value: 0b%s" CRLF, utoa_bin32(value));
            print_bit_representation(value);

        }
    }
#endif

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &num_of_byte);
        if(false == res) {
            LOG_ERROR(DBG, "InvalidNumByte %s", argv[1]);
        } else {
            cli_printf("numOfByte: %d " CRLF, (unsigned int)num_of_byte);
        }
    }

    if(3 <= argc) {
        dir = argv[2][0];
    }

    if(res) {
        uint32_t offset = 0, cnt = 0;
        uint8_t value_byte = 0u;
        for(cnt = 0; cnt < num_of_byte; cnt++) {
            value_byte = read_addr_8bit(address + offset);
            cli_printf("%02x", (unsigned int)value_byte);
            if('f' == dir) {
                offset++;
            } else if('r' == dir) {
                offset--;
            }
        }
        cli_printf(CRLF);
    }

    if((0 == argc) || (3 < argc)) {
        LOG_ERROR(DBG, "Usage: read_mem: address num_of_byte dir");
        LOG_INFO(DBG, "Usage: address 0xXXXXXXXX");
        LOG_INFO(DBG, "Usage: num_of_byte [0...]");
        LOG_INFO(DBG, "Usage: dir [f r]");
    }
    return res;
}

#define MAX_RPT_CMD_LEN 50U
bool cmd_repeat(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        char read_command[MAX_RPT_CMD_LEN] = "";
        char temp_command[MAX_RPT_CMD_LEN] = "";
        res = true;
        uint32_t period_ms = 0;
        uint32_t num_of_try = 0;
        strncpy(read_command, argv[0], sizeof(read_command));
        if(res) {
            res = try_str2uint32(argv[1], &period_ms);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to parse period_ms", argv[1]);
            }
        }
        if(res) {
            res = try_str2uint32(argv[2], &num_of_try);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to parse num_of_try", argv[2]);
            }
        }
        uint32_t iter = 0U;
        replace_char(read_command, '_', ' ');
        for(iter = 1; iter <= num_of_try; iter++) {
            cli_printf(CRLF "%03u/%u: execute command [%s]" CRLF, iter, num_of_try, read_command);
            strncpy(temp_command, read_command, sizeof(temp_command));
            CliHandle_t* Node = CliGetNode(1);
            if(Node) {
                Node->run_cmd = false;
                res = cli_process_cmd(1, temp_command);
#ifdef HAS_NORTOS
                wait_in_loop_ms(period_ms);
#endif /*HAS_NORTOS*/
            }
#ifdef HAS_FREE_RTOS
            vTaskDelay(period_ms / portTICK_RATE_MS);
#endif /*HAS_FREE_RTOS*/
        }
    } else {
        LOG_ERROR(DBG, "Usage: rpt command period_ms times");
    }
    return res;
}

/*
 * faddr 4 0x02004000
 * */
bool cmd_find_addr(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t phy_start = 0;
    uint32_t phy_end = 0;
    if(4 == argc) {
        res = true;
        uint16_t byte_num = 0;
        uint32_t value = 0;
        if(res) {
            res = try_str2uint16(argv[0], &byte_num);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to byte_num %s", argv[0]);
            }
        }

        if(res) {
            res = try_str2uint32(argv[1], &value);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to parse value %s", argv[1]);
            }
        }

        if(res) {
            res = try_str2uint32(argv[2], &phy_start);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to parse mem %s", argv[2]);
            }
        }

        if(res) {
            res = try_str2uint32(argv[3], &phy_end);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to parse mem %s", argv[3]);
            }
        }

        if(res) {
            res = find_addr_by_val(byte_num, value, phy_start, phy_end);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to find addr for value %u", byte_num, value);
            }
        }
    } else {
        LOG_ERROR(DBG, "Usage: fadr val_len value phy_start phy_end");
        LOG_INFO(DBG, "val_len [1 2 4]");
        LOG_INFO(DBG, "byte_num 32bitval");
    }
    return res;
}

bool cmd_launch_function(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint32_t function_address = 0;
        void (*function_ptr)(void);
        if(res) {
            res = try_str2uint32(argv[0], &function_address);
            if(false == res) {
                LOG_ERROR(DBG, "Unable to parse address %s", argv[0]);
            }
        }
        if(res) {
            function_ptr = (void (*)(void))function_address;
            function_ptr();
        }

    } else {
        LOG_ERROR(DBG, "Usage: lfun func_address_hex");
    }
    return res;
}

static bool h_count_link_diag(char* key_word1, char* key_word2) {
    bool res = false;
#if defined(HAS_ALLOCATOR) && defined(HAS_MICROCONTROLLER)
    res = set_log_level(DBG, LOG_LEVEL_INFO);
    static const table_col_t cols[] = {
        {5, "num"},
        {12, "addr"},
        {6, "LinkInHeap"},
        {6, "LinkOutHeap"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t num = 1;
    char temp_str[120];
    uint8_t* ram_mem = NULL;
    for(ram_mem = (uint8_t*)RAM_START; ram_mem <= (uint8_t*)(RAM_END - sizeof(uint32_t)); ram_mem++) {
        num++;
        LinkCounter_t LinkCounter = {0, 0};
        /*How many pointers contain  address ram_mem? */
        strcpy(temp_str, TSEP);
        res = h_count_link((void*)ram_mem, &LinkCounter);
        snprintf(temp_str, sizeof(temp_str), "%s %08p " TSEP, temp_str, ram_mem);
        snprintf(temp_str, sizeof(temp_str), "%s h%u " TSEP, temp_str, (unsigned int)LinkCounter.in_heap);
        snprintf(temp_str, sizeof(temp_str), "%s o%u " TSEP, temp_str, (unsigned int)LinkCounter.out_heap);
        if(is_contain(temp_str, key_word1, key_word2)) {
            cli_printf(TSEP " %3u %s" CRLF, num, temp_str);
            num++;
        }

        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    res = set_log_level(DBG, LOG_LEVEL_DEBUG);
#endif
    return res;
}

bool count_link_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_ALLOCATOR
    uint32_t addr = 0;

    if(1 == argc) {
        res = try_str2uint32(argv[0], &addr);
        if(false == res) {
            LOG_ERROR(DBG, "ParseErr Addr [%s]", argv[0]);
        }
    }
    if(res) {
        LinkCounter_t LinkCounter = {0, 0};
        res = h_count_link((void*)addr, &LinkCounter);
        LOG_INFO(DBG, "Addr 0x%p LinkCnt: inHeap %u outHeap %u", addr, LinkCounter.in_heap, LinkCounter.out_heap);
    } else {
        LOG_ERROR(DBG, "Usage: lc Addr");
    }
#endif
    return res;
}

bool count_all_link_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = h_count_link_diag(keyWord1, keyWord2);
    } else {
        LOG_ERROR(DBG, "Usage: lca key1");
    }
    return res;
}

bool read_register_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0x20000000;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(DBG, "ParseErr Addr [%s]", argv[0]);
        }
    }

    if(res) {
        uint32_t value = read_register(address);
        LOG_INFO(DBG, "Addr[0x%08x]=0x%08x", address, value);
#ifdef HAS_BIN_2_STR
        // PrintReg32(value);
        cli_printf("Address:*(0x%p):Value:0x%04x=%u=0b%s" CRLF, address, value, value, utoa_bin32(value));
#endif
    } else {
        LOG_ERROR(DBG, "Usage: rr address");
    }
    return res;
}
