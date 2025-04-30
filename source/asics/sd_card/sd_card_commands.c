#include "sd_card_commands.h"

#include <inttypes.h>
#include <stdint.h>

#include "array.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#ifdef HAS_FAT_FS
#include "diskio.h"
#endif
#include "log.h"
#include "sd_card_config.h"
#include "sd_card_diag.h"
#include "sd_card_drv.h"
#include "spi_drv.h"
#include "table_utils.h"

bool cmd_sd_card_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {

        uint8_t ret = sd_disk_initialize();
        if(RES_OK == ret) {
            LOG_INFO(SD_CARD, "InitOk");
            res = true;
        } else {
            LOG_ERROR(SD_CARD, "InitOk");
        }
    }
    return res;
}

bool cmd_sd_card_74ones_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sent_74_ones();
    if(false == res) {
        LOG_ERROR(SD_CARD, "74 ones train error");
        res = false;
    } else {
        LOG_INFO(SD_CARD, "74 ones train fine!");
    }
    return res;
}

// cmd arg crc
bool cmd_sd_card_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(SD_CARD, "argc %u ", argc);
    uint8_t cmd = 0;
    uint32_t arg = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &cmd);
        if(false == res) {
            LOG_ERROR(SD_CARD, "ParseErr cmd  %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &arg);
        if(false == res) {
            LOG_ERROR(SD_CARD, "ParseErr arg  %s", argv[1]);
        }
    }

    if(res) {
        uint8_t ret = SD_sendCommand(cmd, arg);
        const SdCommandInfo_t* Node = SdCmdGetNode(cmd);
        if(Node) {
            uint8_t response = 0xFF;
            res = sd_fetch_resp(&response);
            if(res) {
                LOG_INFO(SD_CARD, "ret 0x%02x ", res);
                uint8_t buff[512 + 10];
                uint16_t remaining_bytes = Node->ret_len - 1;
                res = sd_read(buff, remaining_bytes);
                print_hex_buf(buff, Node->ret_len + 2);
                LOG_INFO(SD_CARD, "Sd_sendCommand cmd 0x%02x arg 0x%08x ret 0x%02x ", cmd, arg, ret);
            } else {
                LOG_ERROR(SD_CARD, "NoResp");
            }
        }
    } else {
        LOG_ERROR(SD_CARD, "Usage: sdsc cmd arg crc");
    }
    return res;
}

bool cmd_sd_card_write_sector(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(SD_CARD, "argc %u ", argc);
    if(1 == argc) {
        res = true;
        uint32_t block_numb = 0;
        if(res) {
            res = try_str2uint32(argv[0], &block_numb);
            if(false == res) {
                LOG_ERROR(SD_CARD, "ParseErr block_numb  %s", argv[0]);
            }
        }

        if(res) {
            uint8_t buff[512 + 1];
            array_incr(buff, 512);
            res = sd_write_sector(block_numb, buff);
            if(res) {
                LOG_INFO(SD_CARD, "WriteBlockNumb %u OK", block_numb);
            } else {
                LOG_ERROR(SD_CARD, "WriteBlockNumb %u Err", block_numb);
            }
        }
    } else {
        LOG_ERROR(SD_CARD, "Usage: sdw block_numb");
    }
    return res;
}

bool cmd_sd_card_read_sector(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(SD_CARD, "argc %u ", argc);
    if(1 == argc) {
        res = true;
        uint32_t sector = 0;
        if(res) {
            res = try_str2uint32(argv[0], &sector);
            if(false == res) {
                LOG_ERROR(SD_CARD, "ParseErr sector  %s", argv[0]);
            }
        }

        if(res) {
            uint8_t buff[512 + 1];
            memset(buff, 0x00, sizeof(buff));
            DRESULT ret = SD_disk_read(0, buff, sector, 0);
            if(RES_OK == ret) {
                LOG_INFO(SD_CARD, "read sector %u OK", sector);
            } else {
                LOG_ERROR(SD_CARD, "error read sector %u", sector);
            }
            print_hex_buf(buff, 512);
        }
    } else if(2 == argc) {
        res = true;
        uint32_t block_numb = 0;
        uint32_t uniq_cnt = 0;
        if(res) {
            res = try_str2uint32(argv[0], &block_numb);
            if(false == res) {
                LOG_ERROR(SD_CARD, "ParseErr block_numb  %s", argv[0]);
            }
        }
        uint8_t buff[512 + 1];
        while(0 == uniq_cnt) {
            memset(buff, 0x00, sizeof(buff));
            res = sd_read_sector(block_numb, buff);
            if(res) {
                res = uniq_array(buff, 512);
                if(res) {
                    LOG_INFO(SD_CARD, "uniq block_num %u ", block_numb);
                    uniq_cnt++;
                    print_hex_buf(buff, 512);
                }
            }
            block_numb++;
        }
    } else {
        LOG_ERROR(SD_CARD, "Usage: sdr block_numb");
    }
    return res;
}

bool cmd_sd_card_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    res = is_card_connected();
    if(res) {
        LOG_INFO(SD_CARD, "Connected");
        res = sd_read_registers();
        if(false == res) {
            LOG_ERROR(SD_CARD, "ReadRegErr");
        }
        res = sd_card_diag(&SdCardInstance);
    } else {
        LOG_ERROR(SD_CARD, "Disconnected");
    }
    return res;
}

bool cmd_sd_card_ioctl(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t ctrl = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &ctrl);
        if(false == res) {
            LOG_ERROR(SD_CARD, "ParseErr ctrl  %s", argv[0]);
        }
    }
    if(res) {
        uint8_t buff[512 + 1];
        DRESULT ret = sd_disk_ioctl(0, ctrl, buff);
        LOG_INFO(SD_CARD, "SD_disk_ioctl ret 0x%02x ", ret);
    } else {
        LOG_ERROR(SD_CARD, "Usage: sdt ctrl");
    }
    return res;
}

bool cmd_sd_card_power_on(int32_t argc, char* argv[]) {
    bool res = false;
    res = sd_card_power_on();
    return res;
}

bool cmd_sd_card_read_csd_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = sd_card_read_csd(&SdCardInstance.CSD);
        if(res) {
            print_hex(SdCardInstance.CSD.byte, sizeof(CSD_t));
            res = sd_parse_csd(&SdCardInstance.CSD);
        } else {
            LOG_ERROR(SD_CARD, "ReadCSDerror");
        }
    } else {
        LOG_ERROR(SD_CARD, "Usage: sdrcsd");
    }

    return res;
}
