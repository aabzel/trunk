#include "debug_info.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "data_utils.h"
#include "log.h"
#include "system.h"
#include "version.h"

#ifdef HAS_BOOT
#include "boot_diag.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_STRING
#include "convert.h"
#endif /*HAS_STRING*/

#ifdef HAS_CRC32
#include "crc32.h"
#endif

#ifdef HAS_LOG_UTILS
#include "log_utils.h"
#include "oprintf.h"
#include "writer_config.h"
#include "writer_generic.h"
#endif

#ifdef STM32F413xx
#include "stm32f4xx_hal.h"
#endif /*STM32F413xx*/

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_DEV_ID
#include "device_id.h"
#endif

#ifdef HAS_LOG
#include "table_utils.h"
#endif

#ifdef HAS_DIAG
#include "system_diag.h"

#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_MICROCONTROLLER
#include "sys_config.h"

#ifdef HAS_BOOT
//#include "boot_cfg.h"
#endif /*HAS_BOOT*/

#endif /*HAS_MICROCONTROLLER*/

#ifdef HAS_X86_64
#include <stdio.h>
#define cli_printf printf
#endif

#if defined(HAS_RELEASE) && defined(HAS_DEBUG)
#error "HAS_RELEASE and HAS_DEBUG can not be simultaneously"
#endif /*HAS_RELEASE and HAS_DEBUG*/

#include "shared_array.h"

extern int main(void);
static bool stack_dir(int32_t* main_local_addr) {
    bool res = false;
    int32_t fun_local = 0;
    if(((void*)main_local_addr) < ((void*)&fun_local)) {
        LOG_INFO(SYS, "Stack grows from small addr to big addr -> ");
    } else {
        LOG_INFO(SYS, "Stack grows from big addr to small addr <- "); /*hangOn here*/
    }
    return res;
}

bool explore_stack_dir(void) {
    bool res = false;
    int32_t main_local = 0;
    res = stack_dir(&main_local);
    return res;
}

#if 0
static bool is_big_endian(void) {
    U32_bit_t bint;
    bint.u32 = 0x01020304;
    return bint.u8[0] == 1;
}
#endif

bool is_little_endian(void) {
    U32_bit_t bint;
    bint.u32 = 0x01020304;
    return (4 == bint.u8[0]);
}

#ifdef HAS_LOG
static bool print_prog_type(void) {
    bool res = false;
    char lText[150] = "";
    strcpy(text, "");
#ifdef CONFIG_NAME
    snprintf(lText, sizeof(lText), "%sConfig:%s,", lText, CONFIG_NAME);
#endif

#ifdef HAS_SYSTEM_DIAG
    BuildType_t prog_type = system_get_prog_type();
    snprintf(lText, sizeof(lText), "%sProgType:%s,", lText, ProgType2str(prog_type));
#endif /*HAS_DEBUG*/

#ifdef HAS_DEBUG
    snprintf(lText, sizeof(lText), "%sDebug,", lText);
#endif /*HAS_DEBUG*/

#ifdef HAS_RELEASE
    snprintf(lText, sizeof(lText), "%sRelease,", lText);
#endif /*HAS_DEBUG*/

    LOG_WARNING(SYS, "%s", lText);
    res = true;
    return res;
}
#endif

void print_sysinfo(void) {
#ifdef HAS_CORTEX_M
    LOG_NOTICE(SYS, "Reset handler: 0x%x ", *((uint32_t*)0x00000004));
    LOG_NOTICE(SYS, "top-of-stack: %x ", *((uint32_t*)0x00000000));
    LOG_NOTICE(SYS, "boot memory start: %x ", *((uint32_t*)0x00000004));
#endif
    // cli_printf("addr of SystemInit() 0x%p" CRLF, SystemInit);
    LOG_NOTICE(SYS, "addr of main() 0x%p", main);
#ifdef HAS_NORTOS
#endif
#ifdef HAS_MICROCONTROLLER
    LOG_NOTICE(SYS, "RAM: %u Byte", RAM_SIZE);
    LOG_NOTICE(SYS, "Flash: %u Byte", ROM_SIZE);
    LOG_NOTICE(SYS, "RAM addr:   0x%08x....0x%08x ", RAM_START, RAM_END);
    LOG_NOTICE(SYS, "Flash addr: 0x%08x....0x%08x ", ROM_START, ROM_END);
#endif
}

#ifdef __GNUC__
static bool pring_gcc_info(void) {
    bool res = true;
    char lText[150] = "";
    strcpy(lText, "");
#ifdef __GNUC__
    snprintf(lText, sizeof(lText), "%sGNUC:%u,", lText, __GNUC__);
#endif

#ifdef __GNUC_MINOR__
    snprintf(lText, sizeof(lText), "%sGNUC_MINOR:%u,", lText, __GNUC_MINOR__);
#endif

#ifdef __GNUC_PATCHLEVEL__
    snprintf(lText, sizeof(lText), "%sGNUC_PATCHLEVEL:%u,", lText, __GNUC_PATCHLEVEL__);
#endif

#ifdef __STRICT_ANSI__
    snprintf(lText, sizeof(lText), "%sSTRICT_ANSI,", lText);
#endif

#ifdef __VERSION__
    snprintf(lText, sizeof(lText), "%sversion:[%s],", lText, __VERSION__);
#endif

#ifdef __OPTIMIZE__
    snprintf(lText, sizeof(lText), "%soptimize,", lText);
#endif

#ifdef __OPTIMIZE_SIZE__
    snprintf(lText, sizeof(lText), "%sOptSize,", lText);
#endif

#ifdef __NO_INLINE__
    snprintf(lText, sizeof(lText), "%sNoInline,", lText);
#endif

#ifdef __REGISTER_PREFIX__
    snprintf(lText, sizeof(lText), "%sRegPrefix,", lText);
#endif

#ifdef __SIZE_TYPE__
    snprintf(lText, sizeof(lText), "%sSizeTypeSize:%u,", lText, sizeof(__SIZE_TYPE__));
#endif

    LOG_INFO(SYS, "GCC:%s", lText);
    return res;
}
#endif

#ifdef HAS_MICROCONTROLLER
bool check_main(void) {
    bool res = true;

#ifdef HAS_GENERIC
    res = flash_is_generic((uint32_t*)main);
#else /*HAS_GENERIC*/

#ifdef HAS_BOOTLOADER
    res = flash_is_bootloader((uint32_t*)main);
#endif /*HAS_BOOTLOADER*/

#ifdef HAS_MBR
    res = flash_is_mbr((uint32_t)main);
#endif /*HAS_MBR*/

#endif /*HAS_GENERIC*/
    return res;
}
#endif /*HAS_MICROCONTROLLER*/

static bool print_hw_version(void) {
    bool res = true;
    char lText[300] = "";
    strcpy(lText, "");

#ifdef BOARD_NAME
    snprintf(lText, sizeof(lText), "%sboard:[%s],", lText, BOARD_NAME);
#endif

#ifdef MCU_NAME
    snprintf(lText, sizeof(lText), "%sMCU:[%s],", lText, MCU_NAME);
#endif

#ifdef HAS_DEV_ID
    snprintf(lText, sizeof(lText), "%sSerial:0x%llu,", lText, get_device_serial());
#endif /*HAS_DEV_ID*/

#ifdef HAS_MAC
    uint64_t ble_mac = get_ble_mac();
    LOG_WARNING(SYS, "MAC:0x%llu", ble_mac);
#endif /*HAS_MAC*/

#ifdef HAS_DEV_ID
    uint32_t cpi_id = cpu_get_id();
#endif /*HAS_DEV_ID*/
    LOG_WARNING(SYS, "%s", lText);
    return res;
}

static bool print_compiler_version(void) {
    bool res = true;
    char lText[300] = "";
    strcpy(lText, "");
#ifdef __TI_COMPILER_VERSION__
    snprintf(lText, sizeof(lText), "%sTIcompilerVer:%u,", lText, __TI_COMPILER_VERSION__);
#endif

#ifdef __GNUC__
    snprintf(lText, sizeof(lText), "%sCompiler:GCC,", lText);
    res = pring_gcc_info();
#endif /*__GNUC__*/

#ifdef __STDC__
    snprintf(lText, sizeof(lText), "%sCstd:%u,", lText, __STDC__);
#endif

    snprintf(lText, sizeof(lText), "%sStdCver:%lu,", lText, __STDC_VERSION__);
#ifdef __STDC_HOSTED__
    snprintf(lText, sizeof(lText), "%sStdHosted:%u,", lText, __STDC_HOSTED__);
#endif

#ifdef __cplusplus
    snprintf(lText, sizeof(lText), "%sC++ IsUsed,", lText);
#endif

    LOG_WARNING(SYS, "%s", lText);
    return res;
}

static bool print_author(void) {
    bool res = true;
    char lText[300] = "";
    strcpy(lText, "");
    snprintf(lText, sizeof(lText), "%sTG:@aabdev,", lText);
    snprintf(lText, sizeof(lText), "%sMadeInRussia", lText);

    LOG_INFO(SYS, "%s", lText);
    return res;
}

static bool print_build_version(void) {
    bool res = true;
    char lText[300] = "";
    strcpy(lText, "");

#ifdef GIT_SHA
    snprintf(lText, sizeof(lText), "%sGitSha:0x%x,", lText, GIT_SHA);
#endif /*GIT_SHA*/

#ifdef SUCCESSFUL_BUILD_COUNTER
    snprintf(lText, sizeof(lText), "%sOkBuildCnt:%u,", lText, SUCCESSFUL_BUILD_COUNTER);
#endif /*SUCCESSFUL_BUILD_COUNTER*/

#ifdef GIT_LAST_COMMIT_HASH
    snprintf(lText, sizeof(lText), "%sGit,Last,Commit:%s,", lText, GIT_LAST_COMMIT_HASH);
#endif /*GIT_LAST_COMMIT_HASH*/

#ifdef GIT_BRANCH
    snprintf(lText, sizeof(lText), "%sGit,Branch:%s,", lText, GIT_BRANCH);
#endif
    snprintf(lText, sizeof(lText), "%smain() Addr:0x%08p,", lText, main);

    LOG_INFO(SYS, "%s", lText);
    return res;
}

static bool print_build_time(void) {
    bool res = true;
    char lText[300] = "";
    strcpy(lText, "");
    snprintf(lText, sizeof(lText), "%sDate:%s,", lText, __DATE__);
    snprintf(lText, sizeof(lText), "%sTime:%s,", lText, __TIME__);
#ifdef __TIMESTAMP__
    snprintf(lText, sizeof(lText), "%sTimeStamp:[%s],", lText, __TIMESTAMP__);
#endif
    LOG_INFO(SYS, "%s", lText);
    return res;
}

bool print_version(void) {
    bool res = true;

    res = print_hw_version();
    res = print_compiler_version();
    res = print_build_version();
    res = print_build_time();
    res = print_author();

    print_prog_type();

#ifndef HAS_MIK32
    res = check_main();
    if(res) {
        LOG_INFO(SYS, "main() Addr:0x%08p", main);
    } else {
        LOG_ERROR(SYS, "main() Addr:0x%08p Error", main);
    }
#endif /*HAS_MICROCONTROLLER*/

#if defined(HAS_CRC32) && defined(HAS_FLASH)
    // uint32_t all_flash_crc = 0;
    // all_flash_crc = crc32_calc(((uint8_t*)APP_START_ADDRESS), APP_SIZE);
    // cli_printf("FlashCRC32:0x%08X" CRLF, all_flash_crc);
#endif /*HAS_FLASH*/

    return res;
}

#ifdef HAS_MICROCONTROLLER
static bool print_app_info(void) {
    bool res = false;
#ifdef HAS_ARM
    uint32_t top_app_stack_val = 0;
    top_app_stack_val = *((uint32_t*)(APP_START_ADDRESS));

    res = is_ram_addr(top_app_stack_val);
    if(res) {
        LOG_INFO(SYS, "AppStackEnd: 0x%08x Offset: %u Byte", top_app_stack_val, top_app_stack_val - RAM_START);
    } else {
        LOG_ERROR(SYS, "AppStackEnd: 0x%08x ", top_app_stack_val);
    }

    uint32_t app_reset_hand_addr = *((uint32_t*)(APP_START_ADDRESS + 4));
#ifdef HAS_FLASH
    res = is_flash_addr(app_reset_hand_addr);
    if(res) {
        LOG_INFO(SYS, "AppResetHandler: 0x%08x ", app_reset_hand_addr);
    } else {
        LOG_ERROR(SYS, "AppResetHandler: 0x%08x ", app_reset_hand_addr);
    }
#endif /*HAS_FLASH*/
#endif /*HAS_ARM*/
    return res;
}
#endif // HAS_MICROCONTROLLER

bool print_sys_info(void) {
    bool res = false;
    char lText[300] = {0};
    snprintf(lText, sizeof(lText), "%sAddrOfMain:0x%8p,", lText, main);
    snprintf(lText, sizeof(lText), "%ssizeof(size_t):%u Byte,", lText, sizeof(size_t));
    res = is_little_endian();
    if(res) {
        snprintf(lText, sizeof(lText), "%sLittle-Endian,", lText);
    } else {
        snprintf(lText, sizeof(lText), "%sBig-Endian,", lText);
    }
#ifdef HAS_BOOT_DIAG
    boot_diag();
#endif

#ifdef HAS_CMSIS
    snprintf(lText, sizeof(lText), "%sSCB->VTOR:0x%08x,", lText, SCB->VTOR);
#endif /*HAS_CMSIS*/

#ifdef HAS_MICROCONTROLLER
    print_app_info();
#endif /*HAS_MICROCONTROLLER*/
    // explore_stack_dir();
    LOG_INFO(SYS, "%s", lText);
    // LOG_DEBUG(SYS, "InfoEnd");
    return res;
}

#ifdef HAS_TYPE_CALC
/*platform spesific data type calculator */
static bool print_u16_un(U16_bit_t un) {
#ifdef HAS_BIN_2_STR
    cli_printf("un 0x%04x 0b_%s" CRLF, un.u16, utoa_bin16(un.u16));
#endif
    cli_printf("s16: %d " CRLF, un.s16);
    cli_printf("u16: %u " CRLF, un.u16);
    cli_printf("u8: %u %u" CRLF, un.u8[0], un.u8[1]);
    cli_printf("s8: %d %d" CRLF, un.s8[0], un.s8[1]);
    return true;
}
#endif

#ifdef HAS_TYPE_CALC
bool print_u64_un(U64_bit_t un) {
    uint8_t i = 0;
#ifdef HAS_BIN_2_STR
    cli_printf("un 0x%16llx 0b_%s" CRLF, un.u64, utoa_bin64(un.u64));
#endif
    cli_printf("s64: %lld " CRLF, un.s64);
    cli_printf("u64: %llu " CRLF, un.u64);

    for(i = 0; i < 2; i++) {
        cli_printf("0x%08x ", un.u32[i]);
    }
    cli_printf(CRLF);

    for(i = 0; i < 2; i++) {
        cli_printf("%d ", un.s32[i]);
    }
    cli_printf(CRLF);

    for(i = 0; i < 4; i++) {
        cli_printf("0x%04x ", un.u16[i]);
    }
    cli_printf(CRLF);

    for(i = 0; i < 4; i++) {
        cli_printf("%d ", un.s16[i]);
    }
    cli_printf(CRLF);

    for(i = 0; i < 8; i++) {
        cli_printf("0x%02x ", un.u8[i]);
    }
    cli_printf(CRLF);

    for(i = 0; i < 8; i++) {
        cli_printf("%d ", un.s8[i]);
    }
    cli_printf(CRLF);
    return true;
}
#endif

#ifdef HAS_TYPE_CALC
bool print_16bit_types(void* val) {
    U16_bit_t union16bit = {0};
    memcpy(&union16bit, val, 2);

    print_u16_un(union16bit);
#ifdef HAS_BIN_2_STR
    cli_printf("Reverse bytes in %u" CRLF, union16bit.u16);
#endif

    union16bit.u16 = reverse_byte_order_uint16(union16bit.u16);
    print_u16_un(union16bit);
    return true;
}
#endif

#ifdef HAS_TYPE_CALC
bool print_64bit_types(void* val) {
    U64_bit_t union64bit = {0};
    memcpy(&union64bit.u64, val, 8);

    print_u64_un(union64bit);
#ifdef HAS_BIN_2_STR
    cli_printf("Reverse bytes in %llu" CRLF, union64bit.u64);
#endif

    union64bit.u64 = reverse_byte_order_uint64(union64bit.u64);
    print_u64_un(union64bit);
    return true;
}
#endif

#if defined(HAS_LOG) && !defined(ESP32)
bool print_vector_table(uint32_t vectors_table_base) {
    uint32_t* addres = 0;
    uint32_t offset = 0, num = 0;
    cli_printf(CRLF "Vector table" CRLF);
    for(offset = 0, num = 0; offset <= 4 * 53; offset += 4, num++) {
        addres = (uint32_t*)(vectors_table_base + offset);
        cli_printf("number %2u Addr: 0x%08p Handler: 0x%08x" CRLF, num, addres, *(addres));
    }
    return true;
}
#endif

#define ASCII_SEP "|"
bool print_ascii_line(char* buff, uint16_t size, uint16_t indent) {
    uint16_t i = 0;
    bool res = false;
    res = print_indent(indent);
    cli_printf(ASCII_SEP);
    for(i = 0; i < size; i++) {
#ifdef HAS_REPLACE_FORMATTER_CHARACTERS
        if(0x08 == buff[i]) {
            cli_printf("[BS]");
        } else if(0x00 == buff[i]) {
            cli_printf(" ");
        } else if(0x0A == buff[i]) {
            cli_printf("[LF]");
        } else if(0x0D == buff[i]) {
            cli_printf("[CR]");
        } else {
            cli_printf("%c", buff[i]);
        }
#else
        cli_printf("%c", buff[i]);
#endif
    }
    cli_printf(ASCII_SEP);
    return res;
}

bool print_indent(uint16_t indent) {
    bool res = true;
    uint16_t i = 0;
    if(indent < 80) {
        res = true;
        for(i = 0; i < indent; i++) {
            cli_printf(" ");
        }
    }
    return res;
}

static bool print_offset(uint16_t offset) {
    bool res = false;
    if(0 < offset) {
        res = true;
        uint16_t i = 0;
        for(i = 0; i < offset; i++) {
            cli_printf(" ");
        }
    }
    return res;
}

const char* OffSetToStr(uint32_t offset) {
    memset(text, 0, sizeof(text));
    if(0 < offset) {
        if((offset / 2) < sizeof(text)) {
            uint16_t i = 0;
            for(i = 0; i < offset / 2; i++) {
                text[i] = ' ';
            }
            text[offset] = 0x00;
        }
    }
    return text;
}

bool print_bit_hint(uint16_t offset, uint32_t bitness) {
    int32_t bit = 0;
    uint8_t cnt = 0;
    bool res = false;
    if(bitness) {
        res = true;
        print_offset(offset);
        for(bit = bitness - 1; 0 <= bit; bit--) {
            cli_printf("%d", bit / 10);
            cnt++;
            if(4 == cnt) {
                cnt = 0;
                cli_printf(" ");
            }
        }
        cnt = 0;
        cli_printf(CRLF);
        print_offset(offset);
        for(bit = bitness - 1; 0 <= bit; bit--) {
            cli_printf("%d", bit % 10);
            cnt++;
            if(4 == cnt) {
                cnt = 0;
                cli_printf(" ");
            }
        }
        cli_printf(CRLF);
    }
    return res;
}

#ifdef HAS_LOG
bool print_bit_representation(uint32_t val) {
    bool res = true;
    int32_t bit_index = 0;
    table_col_t cols[32];
    for(bit_index = 31; 0 <= bit_index; bit_index--) {
        cols[bit_index].width = 2;
        cols[bit_index].name = "";
    }
    cli_printf("value: %u" CRLF "value: 0x%x " CRLF, val, val);
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf(TSEP);
    for(bit_index = 31; 0 <= bit_index; bit_index--) {
        cli_printf("%2d" TSEP, bit_index);
    }
    cli_printf(CRLF);
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf(TSEP);

    for(bit_index = 31; 0 <= bit_index; bit_index--) {
        cli_printf("%2u" TSEP, (((uint32_t)1) << bit_index) == (val & (((uint32_t)1) << bit_index)));
    }
    cli_printf(CRLF);
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf(CRLF);
    return res;
}
#endif

#ifdef HAS_FLASH
static bool print_text_addresses(uint32_t cur_stack_val, uint32_t top_stack_val) {
    bool res = false;
    bool out_res = false;
    uint32_t cur_addr = 0;
    uint32_t num = 1;
    if(cur_stack_val < top_stack_val) {
        for(cur_addr = cur_stack_val; cur_addr < (top_stack_val - 4); cur_addr++) {
            uint32_t* ram_addr = (uint32_t*)cur_addr;
            res = is_flash_addr((uint32_t)*ram_addr);
            if(res) {
                cli_printf("%3u addr[0x%08x]=0x%08x" CRLF, num, cur_addr, (uint32_t)*ram_addr);
                out_res = true;
                num++;
            }
        }
    }
    return out_res;
}
#endif

bool print_array(uint8_t* memory, uint32_t size) {
    bool res = false;
    if(memory) {
        if(0 < size) {
            res = true;
            cli_printf("(");
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                if(i == (size - 1)) {
                    cli_printf("%u", memory[i]);
                } else {
                    cli_printf("%u,", memory[i]);
                }
            }
            cli_printf(")" CRLF);
        }
    }
    return res;
}

bool print_mem_ascii(uint8_t* memory, uint32_t size) {
    bool res = false;
    if(NULL != memory) {
        if(0 < size) {
            res = true;
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                cli_printf("%c", (char)memory[i]);
            }
        }
    }
    return res;
}

void print_hex_buf(const uint8_t* s, uint32_t len) {
    static const unsigned char _tab[] = "0123456789ABCDEF";
    if(0 < len) {
        if(NULL != s) {
            // printf("\n len ID %u \n", len);
            uint16_t sizeOf_tab = sizeof(_tab);
            uint16_t index;
            while(len--) {
                index = (*s >> 4) & 0xF;
                if(index < sizeOf_tab) {
                    cli_printf("%c", _tab[index]);
                }
                index = (*s >> 0) & 0xF;
                if(index < sizeOf_tab) {
                    cli_printf("%c", _tab[index]);
                }
                s++;
            }
        }
    }
    cli_printf(CRLF);
}

#ifdef HAS_BIN_2_STR
bool print_binary(uint8_t const* const buff, uint32_t size) {
    bool res = false;
    if(0 < size) {
        if(buff) {
            switch(size) {
            case 1: {
                cli_printf("%s", utoa_bin8((uint8_t) * ((uint8_t*)buff)));
                res = true;
            } break;
            case 2: {
                cli_printf("%s", utoa_bin16((uint16_t) * ((uint16_t*)buff)));
                res = true;
            } break;
            case 3: {
                cli_printf("%s", utoa_bin24((uint32_t) * ((uint32_t*)buff)));
                res = true;
            } break;
            case 4: {
                cli_printf("%s", utoa_bin32((uint32_t) * ((uint32_t*)buff)));
                res = true;
            } break;
            default:
                cli_printf("????");
                res = false;
                break;
            }
        }
    }
    return res;
}
#endif

#if 0
void error_handler(void) {
#ifdef STM32F413xx
    __disable_irq();
#endif /*STM32F413xx*/
    while(1) {
    }
}
#endif

#ifdef HAS_FLASH
bool parse_stack(void) {
    bool res = false;
    uint32_t cur_stack_val = (uint32_t)&res;
    uint32_t top_stack_val = *((uint32_t*)(APP_START_ADDRESS));
    uint32_t cur_stack_size = top_stack_val - cur_stack_val;
    cli_printf("Stack 0x%08x...0x%08x %u byte %u kByte" CRLF, cur_stack_val, top_stack_val, cur_stack_size,
               cur_stack_size / 1024);
    res = print_text_addresses(cur_stack_val, top_stack_val);

    return res;
}
#endif

bool min_max_diag(U32Value_t* val, char* name) {
    bool res = false;
    if(val && name) {
        static const table_col_t cols[] = {
            {11, "name"}, {7, "min"}, {7, "cur"}, {7, "max"}, {7, "delata"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t delta = val->max - val->min;
        char log_line[150];
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %9s " TSEP, log_line, name);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, val->min);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, val->cur);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, val->max);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, delta);
        cli_printf("%s" CRLF, log_line);
        res = true;
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

const char* ProgressRealToStr(float cur, float total) {
    if(cur <= total) {
        uint32_t progress_x100 = (uint32_t)((10000.0 * cur) / total);
        uint32_t units = progress_x100 / 100;
        uint32_t fraq = progress_x100 % 100;
        // snprintf(text,sizeof(text),"\r %u/%u,%6.2f %%", cur, total, progress);
        snprintf(text, sizeof(text), "%u.%u %%", units, fraq);
    }
    return text;
}

const char* ProgressFloatToStr(float cur, float total) {
    if(cur <= total) {
        uint32_t progress_x100 = (uint32_t)((10000.0 * cur) / total);
        uint32_t units = progress_x100 / 100;
        uint32_t fraq = progress_x100 % 100;
        snprintf(text, sizeof(text), "%u.%u %%", units, fraq);
    }
    return text;
}

const char* ProgressToStr(uint32_t cur, uint32_t total) {
    char* out_text = "?";
    if(cur <= total) {
        out_text = ProgressRealToStr((float)cur, (float)total);
    }
    return out_text;
}

bool print_progress(uint32_t cur, uint32_t total) {
    bool res = false;
    if(cur <= total) {
        cli_printf("\r%s", ProgressToStr(cur, total));
        res = true;
    }
    return res;
}

float diag_progress_log(uint32_t cur, uint32_t total, uint32_t parts) {
    float progress_pp = 0.0;
    if(cur <= total) {
        progress_pp = ((float)(100U * cur)) / ((float)total);
        if(parts < (total / 3)) {
            if(0 == (cur % (total / parts))) {
                cli_printf("\rProgress:%s", ProgressToStr(cur, total));
            }
        }
    }
    return progress_pp;
}
