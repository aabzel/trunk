#include "cli_native_commands.h"

#include <ctype.h>
#include <inttypes.h>
#include <string.h>

//#include "array.h"
#include "bit_utils.h"
#ifdef HAS_BOOT
#include "boot_cfg.h"
#endif
#include "cli_drv.h"

#ifdef HAS_CLOCK
#include "clocks.h"
#endif

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log_utils.h"
#ifdef HAS_FLASH
#include "flash_drv.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#include "none_blocking_pause.h"
#endif

#include "log.h"
#include "oprintf.h"
#include "str_utils.h"
#include "sys_config.h"
#include "string_reader.h"

#ifdef HAS_WDT
#include "watchdog_drv.h"
#endif /*HAS_WDT*/

#ifdef HAS_TIM
#include "tim_drv.h"
#endif /*HAS_TIM*/

#include "terminal_codes.h"
#include "version.h"

bool cmd_help(int32_t argc, char* argv[]) {
    bool res = false;
    cli_printf("argc %u " CRLF, argc);
    if(3 <= argc) {
        cli_printf("Usage: help [subname1]  " CRLF);
        cli_printf("       help [subname1]  [subname2]" CRLF);
        res = false;
    } else {
        if(0 == argc) {
            help_dump_key(NULL, NULL);
            res = true;
        }
        if(1 == argc) {
            help_dump_key(argv[0], NULL);
            res = true;
        }
        if(2 == argc) {
            help_dump_key(argv[0], argv[1]);
            res = true;
        }
    }

    return res;
}

//  bc 0xxxxxx s bit
//  bc 0xxxxxx r bit
bool cmd_low_level_control(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        uint8_t bit_num = 0xFF;
        uint32_t address = 0u;
        char cmd = 'n';
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(SYS, "Invalid address hex value %s", argv[0]);
        } else {
            cli_printf("address: 0x%08x" CRLF, (unsigned int)address);
        }

        if(res) {
            cmd = argv[1][0];
            cli_printf("cmd: %c" CRLF, cmd);
        }
        if(res) {
            res = try_str2uint8(argv[2], &bit_num);
            if(false == res) {
                LOG_ERROR(SYS, "Invalid bit_num%s", argv[2]);
            } else {
                cli_printf("bit: %u" CRLF, bit_num);
            }
        }
        if(res) {
            res = bit32_control_proc((uint32_t*)address, cmd, bit_num);
            if(false == res) {
                LOG_ERROR(SYS, "Invalid address hex value %s", argv[0]);
            } else {
                cli_printf("bit_control_proc OK" CRLF);
            }
        }

    } else {
        LOG_ERROR(SYS, "Usage: bit_ctrl: address cmd bit");
        LOG_INFO(SYS, "address 0xXXXXXXXX");
        LOG_INFO(SYS, "cmd [s r t]");
        LOG_INFO(SYS, "bit [0...31]");
    }
    return res;
}


bool cmd_sysinfo(int32_t argc, char* argv[]) {
    (void)argv;
    bool res = false;
    if (0==argc) {
    	res = true;
    }

    if(res){
        if(is_little_endian()) {
        	LOG_ERROR(SYS,"LittleEndian" );
        } else {
        	LOG_ERROR(SYS,"BigEndian" );
        }
        explore_stack_dir();
        print_sysinfo();
        res = true;
    } else {
        LOG_ERROR(SYS, "Usage: si");
    }

    return res;
}

bool cmd_wd_test(int32_t argc, char* argv[]) {
    uint32_t delay_in_ms = 1000;
    if(argc != 1) {
        LOG_ERROR(SYS, "Usage: wd_test time_ms");
        return false;
    }
    if(!try_str2uint32(argv[0], &delay_in_ms)) {
        LOG_ERROR(SYS, "Invalid delay value %s", argv[0]);
        return false;
    }
    LOG_WARNING(SYS, "Delay for %" PRIu32 " ms", delay_in_ms);
#ifdef HAS_PRINTF
    flush_printf();
#endif

#ifdef HAS_CLOCK
    wait_ms(delay_in_ms);
#endif
    return true;
}

bool cmd_wd_test_hw(int32_t argc, char* argv[]) {
    uint32_t delay_in_ms = 1000;
    if(argc != 1) {
        LOG_ERROR(SYS, "Usage: wd_test_hw time_ms");
        return false;
    }
    if(!try_str2uint32(argv[0], &delay_in_ms)) {
        LOG_ERROR(SYS, "Invalid delay value %s", argv[0]);
        return false;
    }
    LOG_WARNING(SYS, "Delay for %" PRIu32 " ms", delay_in_ms);
#ifdef HAS_PRINTF
    flush_printf();
#endif
    
    uint32_t end_time =0;
#ifdef HAS_CLOCK
    end_time = time_get_ms32() + delay_in_ms;
    while(time_get_ms32() <= end_time) {
#ifdef HAS_SWT
        wdt_reset_sw();
#endif
    }
#endif /*HAS_CLOCK*/
    
    return true;
}

bool cmd_version(int32_t argc, char* argv[]) {
    (void)(argv);
    bool res = false;

    if(0==argc){
        res = true;
    }

    if(res){
        print_version();
    }else{
        LOG_ERROR(SYS, "Usage: vi");
    }
    return res;
}

bool dump_cmd_result(bool res) {
        if(res) {
            cli_putstr("!OK" CRLF);
        } else {
            cli_putstr("!ERROR" CRLF);
        }

    return res;
}

bool dump_cmd_result_ex(bool res, const char* message) {
    if(res) {
        cli_printf("!OK %s" CRLF, message);
    } else {
        cli_printf("!ERROR %s" CRLF, message);
    }

    return res;
}


#ifdef HAS_TEST_FIRMWARE_COMMANDS
bool cmd_calc(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint64_t value64u = 0;
        res = try_str2uint64(argv[0], &value64u);
        if(res) {
            cli_printf("spot uint64 %llu" CRLF, value64u);
            print_64bit_types((void*)&value64u);
        }

        uint16_t value16u = 0;
        res = try_str2uint16(argv[0], &value16u);
        if(res) {
            cli_printf("spot uint16 %u" CRLF, value16u);
            print_16bit_types((void*)&value16u);
        }

        int16_t value16i = 0;
        res = try_str2int16(argv[0], &value16i);
        if(res) {
            cli_printf("spot int16 %d" CRLF, value16i);
            print_16bit_types((void*)&value16i);
        }

    } else {
        LOG_ERROR(SYS, "Usage: lfun func_address_hex");
    }
    return res;
}
#endif

#ifdef HAS_TEST_FIRMWARE_COMMANDS
bool cmd_ascii(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint16_t byte = 0;
        for(byte = 0; byte <= 0xFF; byte++) {
            cli_printf("0x%02x %d [%c]" CRLF, byte, byte, byte);
        }
    } else if(1 == argc) {
        res = true;
        uint8_t byte = 0;
        res = try_str2uint8(argv[0], &byte);
        if(false == res) {
            LOG_ERROR(SYS, "unable to read value %s", argv[0]);
        }
        if(res) {
            cli_printf("0x%02x %d [%c]" CRLF, byte, byte, byte);
        }
    } else {
        LOG_ERROR(SYS, "Usage: ascii [byte]");
    }
    return res;
}
#endif

bool cmd_echo(int32_t argc, char *argv []) {
    bool echo = false;
    bool res = false;
    if(0 == argc) {
        res = cli_toggle_echo();
    }else if (1==argc) {
        res = try_str2bool(argv[0], &echo);
        if (false == res) {
            LOG_ERROR(SYS, "Unable parse status %s",argv[0]);
        }
        res = cli_set_echo(echo);
        if ( res ) {
            LOG_INFO(SYS, "OK");
        }
    } else {
        LOG_ERROR(SYS, "Usage: echo state");
    }

    return res;
}

bool cmd_beep(int32_t argc, char* argv[]){
    bool res = true;
    uint8_t cnt=0;
    if(0==argc){
    	cnt=1;
    }

    if(1==argc) {
        res = try_str2uint8(argv[0], &cnt);
    }

    uint8_t i=0;
    for (i=0;i<cnt;i++){
        cli_printf("Beep"BEEP CRLF);

    }
    return res;
}
