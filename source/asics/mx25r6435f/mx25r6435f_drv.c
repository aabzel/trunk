#include "mx25r6435f_drv.h"

#include <string.h>

#include "data_types.h"
#include "gpio_mcal.h"
#include "log.h"

#include "none_blocking_pause.h"
#include "spi_drv.h"
#include "time_mcal.h"
#include "utils_math.h"

bool mx25r6435f_is_valid_addr(uint32_t address) {
    bool res = false;
    if(address < MX25R6435F_FLASH_SIZE) {
        res = true;
    }
    return res;
}

static bool mx25r6435f_is_aligned_addr(uint32_t address) {
    bool res = false;
    res = mx25r6435f_is_valid_addr(address);
    if(res) {
        uint32_t addr_rem = address & 0x000000FF;
        if(0 == addr_rem) {
            res = true;
        }
    }
    return res;
}

bool pack_24bit_big_endian(uint32_t address, uint8_t* const buff) {
    bool res = false;
    if(buff) {
        buff[0] = (address & 0xFF0000) >> 16;
        buff[1] = (address & 0xFF00) >> 8;
        buff[2] = (address & 0xFF);
        res = true;
    }
    return res;
}

static bool mx25r6435f_write_cmd_address(Mx25r6435fCommands_t cmd, uint32_t address) {
    bool res = false;

    uint8_t buff[4] = {cmd, 0xFF, 0xFF, 0xFF};
    res = pack_24bit_big_endian(address, &buff[1]);
    if(res) {
        res = spi_mcal_write(Mx25r6435fConfig.spi_num, buff, 4);
    }
    return res;
}

/*10-10. Read Data Bytes (READ)*/
bool mx25r6435f_read(uint32_t address, uint8_t* data, uint32_t size) {
    bool res = false;

    if(data) {
        if(size) {
            gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);

            res = mx25r6435f_write_cmd_address(MX25_CMD_NORMAL_READ, address);
            if(res) {
                res = spi_mcal_read(Mx25r6435fConfig.spi_num, data, size);
            }

            gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
        }
    }

    return res;
}

bool mx25r6435f_verify(uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint8_t byte_read = 0xFF;
    for(i = 0; i < size; i++) {
        res = mx25r6435f_read(address + i, &byte_read, 1);
        if(res) {
            if(data[i] == byte_read) {
                ok_cnt++;
            } else {
                LOG_ERROR(MX25R6435F, "i=%u Exp:0x%x Real:0x%x", i, data[i], byte_read);
                break;
            }
        }
    }

    if(size == ok_cnt) {
        res = true;
    } else {
        LOG_ERROR(MX25R6435F, "VerifyErrAt [%u]=0x%02x", i, data[i]);
        res = false;
    }
    return res;
}

bool mx25r6435f_reg_get(uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;
#ifdef HAS_SPI
    res = spi_mcal_write(Mx25r6435fConfig.spi_num, &reg_addr, 1);
    if(res) {
        res = spi_mcal_read(Mx25r6435fConfig.spi_num, reg_val, 1);
    }
#endif /*HAS_SPI*/
    return res;
}

bool mx25r6435f_reg_read_all(void) {
    bool res = false;
    uint8_t ok_cnt = 0;

    if(ok_cnt == MX25R6435F_REG_CNT) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool mx25r6435f_identification_read(void) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);

    res = spi_write_byte(Mx25r6435fConfig.spi_num, MX25_CMD_READ_IDENTIFICATION_REGISTER);
    if(res) {
        res = spi_mcal_read(Mx25r6435fConfig.spi_num, Mx25r6435fItem.identification.byte, 3);
        if(res) {
#ifdef HAS_MX25R6435F_DIAG
            mx25_diag_id(&Mx25r6435fItem.identification);
#endif
            LOG_INFO(MX25R6435F, "RegID Ok");
        }
    }
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
    return res;
}

bool mx25r6435f_configuration_read(void) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);
    res = spi_write_byte(Mx25r6435fConfig.spi_num, MX25_CMD_READ_CONFIGURATION_REGISTER);
    if(res) {
        Mx25r6435fItem.configuration.word = spi_read_word(Mx25r6435fConfig.spi_num);
    }

    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
    return res;
}

bool mx25r6435f_status_reg_read(void) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);

    res = spi_write_byte(Mx25r6435fConfig.spi_num, MX25_CMD_READ_STATUS_REGISTER);
    if(res) {
        U16_bit_t un16;
        un16.u16 = 0;
        res = spi_api_read_word(Mx25r6435fConfig.spi_num, &un16.u16);
        if(res) {
            LOG_DEBUG(MX25R6435F, "StatusReg  0x%x", un16.u16);
            if(un16.u8[0] == un16.u8[1]) {
                Mx25r6435fItem.status.byte = un16.u8[0];
                res = true;
            } else {
                res = true;
                Mx25r6435fItem.status.byte = un16.u8[1];
                LOG_WARNING(MX25R6435F, "StatusRegValDiff  0x%x", un16.u16);
            }
        }
    }
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
    return res;
}

bool mx25r6435f_is_connected(void) {
    bool res = false;
    res = mx25r6435f_status_reg_read();
    if(res) {
        res = mx25r6435f_identification_read();
        if(res) {
            res = false;
            if(MANUFACTURER_ID == Mx25r6435fItem.identification.manufacturer_id) {
                if(MEMORY_TYPE == Mx25r6435fItem.identification.device_id.memory_type) {
                    if(MEMORY_DENSITY == Mx25r6435fItem.identification.device_id.memory_density) {
                        res = true;
                    } else {
                        LOG_ERROR(MX25R6435F, "MemDencErr  0x%x",
                                  Mx25r6435fItem.identification.device_id.memory_density);
                    }

                } else {
                    LOG_ERROR(MX25R6435F, "MemTypeErr 0x%x", Mx25r6435fItem.identification.device_id.memory_type);
                }

            } else {
                LOG_ERROR(MX25R6435F, "ManIdErr  0x%x", Mx25r6435fItem.identification.manufacturer_id);
            }
        }
    }
    return res;
}

static bool mx25r6435f_simple_cmd_send(Mx25r6435fCommands_t cmd) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);
    res = spi_write_byte(Mx25r6435fConfig.spi_num, cmd);
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
    return res;
}

static bool mx25r6435f_write_activate(uint32_t time_out) {
    bool res = false;
    uint32_t start_ms = time_get_ms32();
    uint32_t curr_ms = 0;
    uint32_t diff_ms = 0;
    res = true;
    do {
        res = mx25r6435f_simple_cmd_send(MX25_CMD_WRITE_ENABLE);
        res = mx25r6435f_status_reg_read();

        curr_ms = time_get_ms32();
        diff_ms = curr_ms - start_ms;
        if(time_out < diff_ms) {
            LOG_ERROR(MX25R6435F, "WriteEnableTimeOut %u ms", time_out);
            res = false;
            break;
        }

    } while(0 == Mx25r6435fItem.status.wel);
    LOG_INFO(MX25R6435F, "WriteEnabled!");
    return res;
}

bool mx25r6435f_reg_set(uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(MX25R6435F, "Set Reg:0x%02x Val:0x%02x", reg_addr, reg_val);

    return res;
}

bool mx25r6435f_erase_verify(uint32_t address, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint8_t read_data = 0;
    for(i = 0; i < size; i++) {
        res = mx25r6435f_read(address + i, &read_data, 1);
        if(res) {
            if(0xFF == read_data) {
                ok_cnt++;
            } else {
                LOG_ERROR(MX25R6435F, "%u EraseError Val:0x%02x", i, read_data);
                res = false;
                break;
            }
        }
    }

    if(ok_cnt == size) {
        res = true;
    } else {
        LOG_ERROR(MX25R6435F, "EraseError");
        res = false;
    }
    return res;
}

bool mx25r6435f_erase_sector(uint32_t address) {
    bool res = false;

    res = mx25r6435f_write_activate(1000);
    if(res) {
        gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);
        res = mx25r6435f_write_cmd_address(MX25_CMD_SECTOR_ERASE, address);
        gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);

        if(res) {
            res = mx25r6435f_wait_write_done(MX25_WR_TIMEOUT_MS);
            res = mx25r6435f_erase_verify(address, MX25R6435F_SECTOR_SIZE);
        }
    }

    return res;
}

/*10-24. Deep Power-down (DP)*/
bool mx25r6435f_deep_power_down(void) {
    bool res = false;
    res = mx25r6435f_simple_cmd_send(MX25_CMD_DEEP_POWER_DOWN);
    return res;
}

Mx25r6435fCommands_t BlockSize2Cmd(Mx25BlockSize_t block_size) {
    Mx25BlockSize_t cmd = MX25_BLOCK_UNDEF;
    switch(block_size) {
    case MX25_BLOCK_4K:
        cmd = MX25_CMD_SECTOR_ERASE;
        break;
    case MX25_BLOCK_32K:
        cmd = MX25_CMD_BLOCK_ERASE_32KB;
        break;
    case MX25_BLOCK_64K:
        cmd = MX25_CMD_BLOCK_ERASE_64KB;
        break;
    default:
        cmd = MX25_CMD_NO_OPERATION;
        break;
    }
    return cmd;
}

bool mx25r6435f_erase_chip(void) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);
    res = spi_write_byte(Mx25r6435fConfig.spi_num, MX25_CMD_CHIP_ERASE);
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
    return res;
}

bool mx25r6435f_erase_block(uint32_t address, Mx25BlockSize_t block_size) {
    bool res = false;

    res = mx25r6435f_write_enable(true);
    if(res) {
        gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);
        Mx25r6435fCommands_t cmd = BlockSize2Cmd(block_size);
        res = mx25r6435f_write_cmd_address(cmd, address);
        gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);
    }

    return res;
}

/* 10-22. Page Program (PP)
 * (page 28 )Figure 12. Program/Erase flow with read array data
 */
bool mx25r6435f_page_program(uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_INFO(MX25R6435F, "PageProg %u byte", size);

    res = mx25r6435f_is_aligned_addr(address);
    if(res) {
        res = false;
        if(data) {
            res = false;
            if(MX25R6435F_PAGE_SIZE == size) {
                res = true;
            } else {
                LOG_ERROR(MX25R6435F, "SizeErr %u byte", size);
            }
        } else {
            LOG_ERROR(MX25R6435F, "DataErr");
        }
    } else {
        LOG_ERROR(MX25R6435F, "AddrErr 0x%0x", address);
    }

    if(res) {
        res = mx25r6435f_write_activate(MX25_WR_TIMEOUT_MS);
    }

    if(res) {
        gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);
        res = mx25r6435f_write_cmd_address(MX25_CMD_PAGE_PROGRAM, address);
        if(res) {
            res = spi_mcal_write(Mx25r6435fConfig.spi_num, data, size);
        }
        gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);

        if(res) {
            res = mx25r6435f_wait_write_done(MX25_WR_TIMEOUT_MS);
        }

        res = mx25r6435f_verify(address, data, size);
        if(res) {
            LOG_INFO(MX25R6435F, "VeryfyOk");
        } else {
            LOG_ERROR(MX25R6435F, "VeryfyErr");
        }
    }
    return res;
}

bool mx25r6435f_write_aligned_page(uint32_t aligned_addresses, const uint8_t* const data, uint32_t size) {
    bool res = false;
    res = mx25r6435f_is_aligned_addr(aligned_addresses);
    if(res) {
        if(MX25R6435F_PAGE_SIZE == size) {
            res = mx25r6435f_page_program(aligned_addresses, data, size);
        } else if(size < MX25R6435F_PAGE_SIZE) {
            uint8_t buff[MX25R6435F_PAGE_SIZE];
            memset(buff, 0xFF, sizeof(buff));
            res = mx25r6435f_read(aligned_addresses, buff, MX25R6435F_PAGE_SIZE);
            if(res) {
                memcpy(buff, data, size);
                res = mx25r6435f_page_program(aligned_addresses, buff, MX25R6435F_PAGE_SIZE);
            }
        } else {
            LOG_INFO(MX25R6435F, "VastSize %u byte", size);
            res = false;
        }
    }
    return res;
}

bool mx25r6435f_write_page(uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_INFO(MX25R6435F, "WritePage Addr:0x%08x size %u byte", address, size);

    if(size <= MX25R6435F_PAGE_SIZE) {
        uint32_t addr_rem = address & 0x000000FF;
        uint32_t aligned_addresses = address & 0xFFFFFF00;
        LOG_INFO(MX25R6435F, "ReadPage AligAddr:0x%08x RemAddr:0x%x", aligned_addresses, addr_rem);

        if(0 == addr_rem) {
            LOG_WARNING(MX25R6435F, "WriteInPageStart");
            res = mx25r6435f_write_aligned_page(address, data, size);
        } else {
            uint8_t buff[MX25R6435F_PAGE_SIZE * 2];
            memset(buff, 0xFF, sizeof(buff));
            if(MX25R6435F_PAGE_SIZE < (addr_rem + size)) {
                LOG_WARNING(MX25R6435F, "WriteOnPageBorder");
                res = mx25r6435f_read(aligned_addresses, buff, 2 * MX25R6435F_PAGE_SIZE);
                if(res) {
                    memcpy(&buff[addr_rem], data, size);
                    res = mx25r6435f_page_program(aligned_addresses, &buff[0], MX25R6435F_PAGE_SIZE);
                    res = mx25r6435f_page_program(aligned_addresses + MX25R6435F_PAGE_SIZE, &buff[MX25R6435F_PAGE_SIZE],
                                                  MX25R6435F_PAGE_SIZE);
                }
            } else if((addr_rem + size) <= MX25R6435F_PAGE_SIZE) {
                LOG_WARNING(MX25R6435F, "WriteInPageMiddle");
                res = mx25r6435f_read(aligned_addresses, buff, MX25R6435F_PAGE_SIZE);
                if(res) {
                    memcpy(&buff[addr_rem], data, size);
                    res = mx25r6435f_page_program(aligned_addresses, buff, MX25R6435F_PAGE_SIZE);
                }
            } else {
            }
        }
    } else {
        LOG_INFO(MX25R6435F, "BigSize %u byte", size);
    }
    return res;
}

bool mx25r6435f_write(uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_INFO(MX25R6435F, "Write Addr:0x%x size %u byte", address, size);
    uint32_t write_ok = 0;
    uint32_t page_cnt = size / MX25R6435F_PAGE_SIZE;
    LOG_INFO(MX25R6435F, "Write %u pages", page_cnt);
    uint32_t rem = size % MX25R6435F_PAGE_SIZE;
    LOG_INFO(MX25R6435F, "rem %u bytes", rem);

    uint32_t p = 0;
    for(p = 0; p < page_cnt; p++) {
        res = mx25r6435f_write_page(address + p * MX25R6435F_PAGE_SIZE, &data[MX25R6435F_PAGE_SIZE * p],
                                    MX25R6435F_PAGE_SIZE);
        if(res) {
            write_ok += MX25R6435F_PAGE_SIZE;
        }
    }

    if(rem) {
        res = mx25r6435f_write_page(address + MX25R6435F_PAGE_SIZE * page_cnt, &data[page_cnt * MX25R6435F_PAGE_SIZE],
                                    rem);
        if(res) {
            write_ok += rem;
        }
    }

    if(size == write_ok) {
        LOG_INFO(MX25R6435F, "WriteOk");
    } else {
        LOG_ERROR(MX25R6435F, "WriteErr");
    }

    return res;
}

bool mx25r6435f_erase_mem(uint32_t address, uint32_t size) {
    bool res = false;
    LOG_WARNING(MX25R6435F, "Errase Addr:0x%x size %u byte", address, size);
    /*TODO: Implement later*/
#warning TODO Implement later
    return res;
}

bool mx25r6435f_zero(uint32_t address, uint32_t size) {
    bool res = false;
    uint8_t z_data[MX25R6435F_PAGE_SIZE];
    memset(z_data, 0, sizeof(z_data));
    uint32_t page_cnt = size / sizeof(z_data);
    uint32_t rem = size % sizeof(z_data);
    uint32_t ok_cnt = 0;
    uint32_t b = 0;
    for(b = 0; b < page_cnt; b++) {
        res = mx25r6435f_write(address + sizeof(z_data) * b, z_data, sizeof(z_data));
        if(res) {
            ok_cnt += sizeof(z_data);
        }
    }

    if(rem) {
        res = mx25r6435f_write(address + sizeof(z_data) * page_cnt, z_data, rem);
        if(res) {
            ok_cnt += rem;
        }
    }

    if(size == ok_cnt) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

bool mx25r6435f_read_sfdp(uint32_t address, uint16_t* word) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);

    uint8_t buff[5] = {MX25_CMD_READ_SFDP, 0xFF, 0xFF, 0xFF, 0xFF};

    pack_24bit_big_endian(address, &buff[1]);

    res = spi_mcal_write(Mx25r6435fConfig.spi_num, buff, 5);
    if(res) {
        if(word) {
            *word = spi_read_word(Mx25r6435fConfig.spi_num);
        }
    }
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);

    return res;
}

bool mx25r6435f_reset_hw(void) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.reset.byte, 1);
    gpio_logic_level_set(Mx25r6435fConfig.reset.byte, 0);
    wait_ms(2);
    gpio_logic_level_set(Mx25r6435fConfig.reset.byte, 1);
    /*Standby mode*/
    return res;
}

bool mx25r6435f_reset(void) {
    bool res = false;
    LOG_INFO(MX25R6435F, "Reset");
    res = mx25r6435f_simple_cmd_send(MX25_CMD_RESET_ENABLE);
    wait_ms(1);
    res = mx25r6435f_simple_cmd_send(MX25_CMD_RESET_MEMORY);

    return res;
}

uint32_t mx25r6435f_reg_cnt(void) { return MX25R6435F_REG_CNT; }

bool mx25r6435f_electronic_signature_read(void) {
    bool res = false;
    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 0);

    uint8_t buff[4] = {MX25_CMD_READ_ELECTRONIC_ID, 0xFF, 0xFF, 0xFF};
    res = spi_mcal_write(Mx25r6435fConfig.spi_num, buff, 4);
    if(res) {
        Mx25r6435fItem.electronic_signature = spi_read_byte(Mx25r6435fConfig.spi_num);
    }

    gpio_logic_level_set(Mx25r6435fConfig.chip_select.byte, 1);

    return res;
}

bool mx25r6435f_is_write_in_progress(void) {
    bool res = false;

    res = mx25r6435f_status_reg_read();
    if(res) {
        if(MX25_WIP_WRITE_OPERATION == Mx25r6435fItem.status.wip) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool mx25r6435f_wait_write_done(uint32_t time_out) {
    bool res = false;
    bool loop = true;
    uint32_t start_ms = 0U;
    start_ms = time_get_ms32();
    uint32_t curr_ms = 0U;
    int32_t diff_ms = 0;
    while(loop) {
        res = mx25r6435f_is_write_in_progress();
        if(false == res) {
            LOG_INFO(MX25R6435F, "WriteDone %u ms", diff_ms);
            Mx25r6435fItem.write_time_ms.cur = diff_ms;
            Mx25r6435fItem.write_time_ms.min = MIN(diff_ms, Mx25r6435fItem.write_time_ms.min);
            Mx25r6435fItem.write_time_ms.max = MAX(diff_ms, Mx25r6435fItem.write_time_ms.max);
            loop = false;
            res = true;
        }

        curr_ms = time_get_ms32();
        diff_ms = curr_ms - start_ms;
        if(time_out < diff_ms) {
            LOG_ERROR(MX25R6435F, "WriteTimeOut %u ms", time_out);
            res = false;
            loop = false;
        }
    }
    return res;
}

bool mx25r6435f_write_enable(bool on_off) {
    /*Write Enable (WREN) command: WREN command is required to set the Write Enable Latch bit (WEL) before
issuing other commands to change data.*/
    bool res = false;
    Mx25r6435fCommands_t cmd = 0;

    switch(on_off) {
    case true: {
        cmd = MX25_CMD_WRITE_ENABLE;
    } break;
    case false: {
        cmd = MX25_CMD_WRITE_DISABLE;
    } break;
    }

    res = mx25r6435f_simple_cmd_send(cmd);

    return res;
}

uint8_t mx25r6435f_read_byte(uint32_t address) {
    uint8_t data = 0x00;
    mx25r6435f_read(address, &data, 1);
    return data;
}

bool mx25r6435f_scan(uint32_t address, uint32_t size, double* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    uint8_t buff[256];
    if(usage_pec && spare && busy) {
        res = true;
        uint32_t i = 0;
        *spare = 0;
        *busy = 0;

        uint32_t chunk = size / sizeof(buff);
        uint32_t rem = size % sizeof(buff);
        uint32_t c = 0;
        for(c = 0; c < chunk; c++) {
            res = mx25r6435f_read(address + c * sizeof(buff), buff, sizeof(buff));
            if(res) {
                for(i = 0; i < sizeof(buff); i++) {

                    if(0xFF == buff[i]) {
                        (*spare)++;
                    } else {
                        (*busy)++;
                    }
                }
            }
        }

        res = mx25r6435f_read(address + chunk * sizeof(buff), buff, rem);
        if(res) {
            for(i = 0; i < rem; i++) {
                if(0xFF == buff[i]) {
                    (*spare)++;
                } else {
                    (*busy)++;
                }
            }
        }

        *usage_pec = (double)(((double)(100U * (*busy))) / ((double)size));
    }
    return res;
}

bool mx25r6435f_init(void) {
    bool res = true;
    LOG_INFO(MX25R6435F, "Init");
    set_log_level(MX25R6435F, LOG_LEVEL_DEBUG);

    Mx25r6435fItem.write_time_ms.cur = 0;
    Mx25r6435fItem.write_time_ms.min = 0xFFFFFFFF;
    Mx25r6435fItem.write_time_ms.max = 0;

#ifdef HAS_SPI
    set_log_level(SPI, LOG_LEVEL_DEBUG);
#endif

    res = mx25r6435f_is_connected();
    if(res) {
        res = mx25r6435f_identification_read();
        res = mx25r6435f_electronic_signature_read();
        res = mx25r6435f_configuration_read();

        res = mx25r6435f_write_enable(true);
    } else {
        LOG_INFO(MX25R6435F, "LinkErr");
    }
#ifdef HAS_SPI
    set_log_level(SPI, LOG_LEVEL_INFO);
#endif /**/

    set_log_level(MX25R6435F, LOG_LEVEL_INFO);
    return res;
}
