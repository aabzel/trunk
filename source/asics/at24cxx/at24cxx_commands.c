#include "at24cxx_commands.h"

#include <limits.h>
#include <stdio.h>

#include "at24cxx_diag.h"
#include "at24cxx_drv.h"
#include "at24cxx_read_drv.h"
#include "at24cxx_write_drv.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"

bool at24cxx_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = at24cxx_diag();
    }
    return res;
}

bool at24cxx_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(res) {
        res = at24cxx_init_one(num);
    }
    return res;
}

#ifdef HAS_AT24CXX_WRITE
bool at24cxx_erase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t address = 0;
    uint32_t size = 0;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &address);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr address  %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &size);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr size %s", argv[2]);
        }
    }

    if(res) {
        res = at24cxx_erase(num, address, size);
        if(res) {
            LOG_INFO(AT24C, "EraseOk");
        } else {
            LOG_ERROR(AT24C, "EraseErr Addr:0x%x Size:%u", address, size);
        }
    } else {
        LOG_ERROR(AT24C, "Usage ate Num addr size");
    }
    return res;
}

bool at24cxx_erase_chip_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(res) {
        res = at24cxx_erase_chip(num);
        if(res) {
            LOG_INFO(AT24C, "EraseChipOk");
        } else {
            LOG_ERROR(AT24C, "EraseChipErr");
        }
    }
    return res;
}

bool at24cxx_write_pattern_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    uint8_t pattern = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &pattern);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr pattern %s", argv[1]);
        }
    }

    if(res) {
        res = at24cxx_write_pattern(num, pattern);
    } else {
        LOG_ERROR(AT24C, "Usage atp Num Pattern");
    }
    return res;
}

bool at24cxx_write_byte_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    uint8_t address = 0;
    uint8_t data = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &address);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr address  %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &data);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr Data %s", argv[2]);
        }
    }

    if(res) {
        LOG_INFO(AT24C, "Write Addr 0x%x, Byte 0x%x", address, data);
        res = at24cxx_write_byte(num, address, data);
        if(res) {
            LOG_INFO(AT24C, "WriteOk Addr 0x%x, Byte 0x%x", address, data);
        }
    } else {
        LOG_ERROR(AT24C, "Usage atwb Num Addr Byte");
    }
    return res;
}
#endif

bool at24cxx_read_byte_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    uint8_t address = 0;
    uint8_t data = 0x55;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &address);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr address  %s", argv[1]);
        }
    }

    if(res) {
        res = at24cxx_read_byte(num, address, &data);
        if(res) {
            LOG_INFO(AT24C, "ReadByte 0x%02x", data);
        } else {
            LOG_ERROR(AT24C, "ReadError");
        }
    } else {
        LOG_ERROR(AT24C, "Usage atb Num Addr Byte");
    }
    return res;
}

bool at24cxx_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t address = 0;
    uint8_t buff[AT24CXX_PAGE_BUFFER_SIZE] = {0};
    memset(buff, 0x00, sizeof(buff));
    uint32_t size = 0;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &address);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr address  %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &size);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr size %s", argv[2]);
        } else {
            if(AT24CXX_PAGE_BUFFER_SIZE < size) {
                LOG_ERROR(AT24C, "SizeErr %u", size);
                res = false;
            }
        }
    }

    if(res) {
        res = at24cxx_read(num, address, buff, size);
        if(res) {
            LOG_INFO(AT24C, "ReadOk 0x%x", address);

            print_mem(buff, size, true, false, true, true);

        } else {
            LOG_ERROR(AT24C, "ReadErr Addr:0x%x Size:%u", address, size);
        }
    } else {
        LOG_ERROR(AT24C, "Usage: atr Num Addr size");
    }
    return res;
}

bool at24cxx_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t buff[AT24CXX_PAGE_BUFFER_SIZE];
    memset(buff, 0x00, sizeof(buff));
    size_t size = 0;
    uint8_t address = 0;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &address);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr address  %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], buff, sizeof(buff), &size);
        if(false == res) {
            LOG_WARNING(AT24C, "ExtractHexArrayErr  [%s]", argv[2]);
            snprintf((char*)buff, sizeof(buff), "%s", argv[2]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = at24cxx_write(num, address, buff, size);
        if(res) {
            LOG_INFO(AT24C, "WriteOk 0x%x", address);
        } else {
            LOG_ERROR(AT24C, "WriteErr 0x%x", address);
        }
    } else {
        LOG_ERROR(AT24C, "Usage atw Num Addr Data");
    }
    return res;
}

bool at24cxx_write_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr num  %s", argv[0]);
        }
    }

    if(1 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(AT24C, "ParseErr OnOff  %s", argv[1]);
        }
    }
    if(res) {
        res = at24cxx_write_ctrl(num, on_off);
        if(res) {
            LOG_INFO(AT24C, "WriteEnOk");
        } else {
            LOG_ERROR(AT24C, "WriteEnErr");
        }
    }
    return res;
}
