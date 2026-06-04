#include "mx25l6433f_mcal.h"

#include <string.h>

#include "data_types.h"
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "spi_mcal.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "mx25l6433f_config.h"

COMPONENT_GET_NODE( Mx25l6433f, mx25l6433f)
COMPONENT_GET_CONFIG( Mx25l6433f, mx25l6433f)

/*ISO-26262 require verify configuration*/

bool Mx25l6433fIsValidConfig(const Mx25l6433fConfig_t* const Config) {
    bool res = false;
    if (Config) {
        res = true;
        ifn(Config->name)
        {
            LOG_ERROR(MX25L6433F, "MX25L6433F_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool mx25l6433f_init_custom(void) {
    bool res = false;
    LOG_INFO(MX25L6433F, "Version:%u", MX25L6433F_VERSION);
    LOG_INFO(MX25L6433F, "SECTOR_CNT:%u", MX25L6433F_SECTOR_CNT);
    return res;
}

bool mx25l6433f_is_valid_addr(uint32_t address) {
    bool res = false;
    if (address < MX25L6433F_FLASH_SIZE) {
        res = true;
    }
    return res;
}

static bool mx25l6433f_is_aligned_addr(uint32_t address) {
    bool res = false;
    res = mx25l6433f_is_valid_addr(address);
    if (res) {
        uint32_t addr_rem = address & 0x000000FF;
        if (0 == addr_rem) {
            res = true;
        }
    }
    return res;
}

bool pack_24bit_big_endian(uint32_t address, uint8_t* const buff) {
    bool res = false;
    if (buff) {
        buff[0] = (address & 0xFF0000) >> 16;
        buff[1] = (address & 0xFF00) >> 8;
        buff[2] = (address & 0xFF);
        res = true;
    }
    return res;
}

static bool mx25l6433f_write_cmd_address(uint8_t num, Mx25l6433fCommands_t cmd, uint32_t address) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    uint8_t buff[4] = { cmd, 0xFF, 0xFF, 0xFF };
    res = pack_24bit_big_endian(address, &buff[1]);
    if (res) {
        res = spi_mcal_write(Node->spi_num, buff, 4);
    }
    return res;
}

/*10-10. Read Data Bytes (READ)*/
bool mx25l6433f_read(uint8_t num, uint32_t address, uint8_t* data, uint32_t size) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (data) {
        if (size) {
            gpio_logic_level_set(Node->chip_select, 0);
            wait_us(2);
            res = mx25l6433f_write_cmd_address(num, MX25_CMD_NORMAL_READ, address);
            if (res) {
                res = spi_mcal_read(Node->spi_num, data, size);
            }

            gpio_logic_level_set(Node->chip_select, 1);
            wait_us(1);
        }
    }

    return res;
}

bool mx25l6433f_verify(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint8_t byte_read = 0xFF;
    for (i = 0; i < size; i++) {
        res = mx25l6433f_read(num, address + i, &byte_read, 1);
        if (res) {
            if (data[i] == byte_read) {
                ok_cnt++;
            } else {
                LOG_ERROR(MX25L6433F, "i=%u Exp:0x%x Real:0x%x", i, data[i], byte_read);
                break;
            }
        }
    }

    if (size == ok_cnt) {
        res = true;
    } else {
        LOG_ERROR(MX25L6433F, "VerifyErrAt [%u]=0x%02x", i, data[i]);
        res = false;
    }
    return res;
}

bool mx25l6433f_reg_get(uint8_t num, uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
#ifdef HAS_SPI
    res = spi_mcal_write(Node->spi_num, &reg_addr, 1);
    if(res) {
        res = spi_mcal_read(Node->spi_num, reg_val, 1);
    }
#endif /*HAS_SPI*/
    return res;
}

bool mx25l6433f_reg_read_all(uint8_t num) {
    bool res = false;
    uint8_t ok_cnt = 0;

    if (ok_cnt == MX25L6433F_REG_CNT) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

// 10-3. Read Identification (RDID)
bool mx25l6433f_identification_read(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        gpio_logic_level_set(Node->chip_select, 0);
        wait_us(1);
        res = spi_write_byte(Node->spi_num, MX25_CMD_READ_IDENTIFICATION_REGISTER);
        if (res) {
            res = spi_mcal_read(Node->spi_num, Node->identification.byte, 3);
        }
        gpio_logic_level_set(Node->chip_select, 1);
        wait_us(1);
    }

    if (res) {
#ifdef HAS_MX25L6433F_DIAG
        mx25_diag_id( &Node->identification);
#endif
        LOG_INFO(MX25L6433F, "RegID Ok");
        mx25l6433f_is_valid_id(&Node->identification);

    }
    return res;
}

bool mx25l6433f_configuration_read(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    gpio_logic_level_set(Node->chip_select, 0);
    wait_us(1);
    res = spi_write_byte(Node->spi_num, MX25_CMD_READ_CONFIGURATION_REGISTER);
    if (res) {
        Node->configuration.word = spi_read_word(Node->spi_num);
    }

    gpio_logic_level_set(Node->chip_select, 1);
    wait_us(1);
    return res;
}

/*10-4. Read Status Register (RDSR) */
bool mx25l6433f_status_reg_read(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        bool loop = true;
        while (loop) {
            gpio_logic_level_set(Node->chip_select, 0);
            wait_us(1);

            res = spi_write_byte(Node->spi_num, MX25_CMD_READ_STATUS_REGISTER);
            if (res) {
                U16_bit_t un16;
                un16.u16 = 0;
                res = spi_mcal_read_word(Node->spi_num, &un16.u16);
                if (res) {
                    LOG_DEBUG(MX25L6433F, "StatusReg 0x%08x", un16.u16);
                    if (un16.u8[0] == un16.u8[1]) {
                        Node->status.byte = un16.u8[0];
                        res = true;
                        loop = false;
                        // break;
                    } else {
                        res = false;
                        Node->status.byte = un16.u8[1];
                        LOG_WARNING(MX25L6433F, "StatusRegValDiff: 0x%x", un16.u16);
                    }
                }
            }
            gpio_logic_level_set(Node->chip_select, 1);
            wait_us(10);
        }
    }
    return res;
}

bool mx25l6433f_is_valid_id(const Mx25l6433fRegIdentification_t* const identification) {
    bool res = false;
    if (MANUFACTURER_ID == identification->manufacturer_id) {
        if (MEMORY_TYPE == identification->device_id.memory_type) {
            if (MEMORY_DENSITY == identification->device_id.memory_density) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(MX25L6433F, "MemDencErr 0x%x", identification->device_id.memory_density);
            }

        } else {
            res = false;
            LOG_ERROR(MX25L6433F, "MemTypeErr 0x%x", identification->device_id.memory_type);
        }

    } else {
        res = false;
        LOG_ERROR(MX25L6433F, "ManIdErr 0x%x", identification->manufacturer_id);
    }
    return res;
}

bool mx25l6433f_is_connected(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        res = mx25l6433f_status_reg_read(num);
        if (res) {
            res = mx25l6433f_identification_read(num);
            if (res) {
                res = mx25l6433f_is_valid_id(&Node->identification);
            }
        }
    }
    return res;
}

static bool mx25l6433f_simple_cmd_send(uint8_t num, Mx25l6433fCommands_t cmd) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        gpio_logic_level_set(Node->chip_select, 0);
        wait_us(1);
        res = spi_write_byte(Node->spi_num, cmd);
        gpio_logic_level_set(Node->chip_select, 1);
        wait_us(1);
    }
    return res;
}

bool mx25l6433f_write_activate(uint8_t num, uint32_t time_out) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        uint32_t start_ms = time_get_ms32();
        res = true;
        do {
            res = mx25l6433f_write_enable(num,true);
            res = mx25l6433f_status_reg_read(num);

            uint32_t curr_ms = 0;
            curr_ms = time_get_ms32();
            uint32_t diff_ms = 0;
            diff_ms = curr_ms - start_ms;
            if (time_out < diff_ms) {
                LOG_ERROR(MX25L6433F, "WriteEnableTimeOut %u ms", time_out);
                res = false;
                break;
            }

        } while (0 == Node->status.wel);
        LOG_INFO(MX25L6433F, "WriteEnabled!");
    }
    return res;
}

bool mx25l6433f_reg_set(uint8_t num, uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(MX25L6433F, "Set Reg:0x%02x Val:0x%02x", reg_addr, reg_val);

    return res;
}

bool mx25l6433f_erase_verify(uint8_t num, uint32_t address, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    for (i = 0; i < size; i++) {
        uint8_t read_data = 0;
        res = mx25l6433f_read(num, address + i, &read_data, 1);
        if (res) {
            if (0xFF == read_data) {
                ok_cnt++;
            } else {
                LOG_DEBUG(MX25L6433F, "EraseError:Addr:0x%x,Offset:%u=Val:0x%x!=0xFF", address+i,i, read_data);
                res = false;
                //break;
            }
        }
    }

    if (ok_cnt == size) {
        res = true;
    } else {
        LOG_ERROR(MX25L6433F, "EraseError.%u/%u", ok_cnt, size);
        res = false;
    }
    return res;
}

/* 10-15. Sector Erase (SE) */
bool mx25l6433f_erase_sector(uint8_t num, uint32_t address) {
    bool res = false;
    LOG_WARNING(MX25L6433F, "MX25L6433F_%u,EraseError:Addr:0x%08x", num, address);
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        res = mx25l6433f_write_activate(num, 1000);
        if (res) {
            gpio_logic_level_set(Node->chip_select, 0);
            wait_us(2);
            res = mx25l6433f_write_cmd_address(num, MX25_CMD_SECTOR_ERASE, address);
            gpio_logic_level_set(Node->chip_select, 1);
            wait_ms(25);
            if (res) {
                res = mx25l6433f_wait_write_done(num, MX25_SECTOR_ERASE_TIMEOUT_MS);
                //wait_ms(200);
                res = mx25l6433f_erase_verify(num, address, MX25L6433F_SECTOR_SIZE);
            }
        }
    }

    return res;
}

/*10-24. Deep Power-down (DP)*/
bool mx25l6433f_deep_power_down(uint8_t num) {
    bool res = false;
    res = mx25l6433f_simple_cmd_send(num, MX25_CMD_DEEP_POWER_DOWN);
    return res;
}

Mx25l6433fCommands_t BlockSize2Cmd(Mx25BlockSize_t block_size) {
    Mx25l6433fCommands_t cmd = MX25_CMD_UNDEF;
    switch (block_size) {
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

bool mx25l6433f_erase_chip(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    gpio_logic_level_set(Node->chip_select, 0);
    res = spi_write_byte(Node->spi_num, MX25_CMD_CHIP_ERASE);
    gpio_logic_level_set(Node->chip_select, 1);
    return res;
}

bool mx25l6433f_erase_block(uint8_t num, uint32_t address, Mx25BlockSize_t block_size) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    res = mx25l6433f_write_enable(num, true);
    if (res) {
        gpio_logic_level_set(Node->chip_select, 0);
        Mx25l6433fCommands_t cmd = BlockSize2Cmd(block_size);
        res = mx25l6433f_write_cmd_address(num, cmd, address);
        gpio_logic_level_set(Node->chip_select, 1);
    }

    return res;
}

/* 10-22. Page Program (PP)
 * (page 28 )Figure 12. Program/Erase flow with read array data
 */
bool mx25l6433f_page_program(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_WARNING(MX25L6433F, "PageProg,Addr:0x%x %u byte", address,size);
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        res = mx25l6433f_is_aligned_addr(address);
        if (res) {
            res = false;
            if (data) {
                res = false;
                if (MX25L6433F_PAGE_SIZE == size) {
                    res = true;
                } else {
                    LOG_ERROR(MX25L6433F, "SizeErr %u byte", size);
                }
            } else {
                LOG_ERROR(MX25L6433F, "DataErr");
            }
        } else {
            LOG_ERROR(MX25L6433F, "AddrErr 0x%0x", address);
        }

        if (res) {
            res = mx25l6433f_write_activate(num, MX25_WR_TIMEOUT_MS);
        }

        if (res) {
            gpio_logic_level_set(Node->chip_select, 0);
            wait_us(1);
            res = mx25l6433f_write_cmd_address(num, MX25_CMD_PAGE_PROGRAM, address);
            if (res) {
                res = spi_mcal_write(Node->spi_num, data, size);
            }
            gpio_logic_level_set(Node->chip_select, 1);

            if (res) {
                res = mx25l6433f_wait_write_done(num, MX25_WR_TIMEOUT_MS);
            }

            res = mx25l6433f_verify(num, address, data, size);
            if (res) {
                LOG_INFO(MX25L6433F, "VeryfyOk");
            } else {
                LOG_ERROR(MX25L6433F, "VeryfyErr");
            }
        }
    }
    return res;
}

bool mx25l6433f_write_aligned_page(uint8_t num, uint32_t aligned_addresses, const uint8_t* const data, uint32_t size) {
    bool res = false;
    res = mx25l6433f_is_aligned_addr(aligned_addresses);
    if (res) {
        if (MX25L6433F_PAGE_SIZE == size) {
            res = mx25l6433f_page_program(num, aligned_addresses, data, size);
        } else
            if (size < MX25L6433F_PAGE_SIZE) {
                uint8_t buff[MX25L6433F_PAGE_SIZE];
                memset(buff, 0xFF, sizeof(buff));
                res = mx25l6433f_read(num, aligned_addresses, buff, MX25L6433F_PAGE_SIZE);
                if (res) {
                    memcpy(buff, data, size);
                    res = mx25l6433f_page_program(num, aligned_addresses, buff, MX25L6433F_PAGE_SIZE);
                }
            } else {
                LOG_INFO(MX25L6433F, "VastSize %u byte", size);
                res = false;
            }
    }
    return res;
}

bool mx25l6433f_write_page(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_INFO(MX25L6433F, "WritePage Addr:0x%08x size %u byte", address, size);

    if (size <= MX25L6433F_PAGE_SIZE) {
        uint32_t addr_rem = address & 0x000000FF;
        uint32_t aligned_addresses = address & 0xFFFFFF00;
        LOG_INFO(MX25L6433F, "ReadPage AligAddr:0x%08x RemAddr:0x%x", aligned_addresses, addr_rem);

        if (0 == addr_rem) {
            LOG_WARNING(MX25L6433F, "WriteInPageStart");
            res = mx25l6433f_write_aligned_page(num, address, data, size);
        } else {
            uint8_t buff[MX25L6433F_PAGE_SIZE * 2];
            memset(buff, 0xFF, sizeof(buff));
            if (MX25L6433F_PAGE_SIZE < (addr_rem + size)) {
                LOG_WARNING(MX25L6433F, "WriteOnPageBorder");
                res = mx25l6433f_read(num, aligned_addresses, buff, 2 * MX25L6433F_PAGE_SIZE);
                if (res) {
                    memcpy(&buff[addr_rem], data, size);
                    res = mx25l6433f_page_program(num, aligned_addresses, &buff[0], MX25L6433F_PAGE_SIZE);
                    res = mx25l6433f_page_program(num, aligned_addresses + MX25L6433F_PAGE_SIZE,
                            &buff[MX25L6433F_PAGE_SIZE], MX25L6433F_PAGE_SIZE);
                }
            } else
                if ((addr_rem + size) <= MX25L6433F_PAGE_SIZE) {
                    LOG_WARNING(MX25L6433F, "WriteInPageMiddle");
                    res = mx25l6433f_read(num, aligned_addresses, buff, MX25L6433F_PAGE_SIZE);
                    if (res) {
                        memcpy(&buff[addr_rem], data, size);
                        res = mx25l6433f_page_program(num, aligned_addresses, buff, MX25L6433F_PAGE_SIZE);
                    }
                } else {
                }
        }
    } else {
        LOG_INFO(MX25L6433F, "BigSize %u byte", size);
    }
    return res;
}

bool mx25l6433f_write(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_INFO(MX25L6433F, "Write Addr:0x%x size %u byte", address, size);
    uint32_t write_ok = 0;
    uint32_t page_cnt = size / MX25L6433F_PAGE_SIZE;
    LOG_INFO(MX25L6433F, "Write %u pages", page_cnt);
    uint32_t rem = size % MX25L6433F_PAGE_SIZE;
    LOG_INFO(MX25L6433F, "rem %u bytes", rem);

    uint32_t p = 0;
    for (p = 0; p < page_cnt; p++) {
        res = mx25l6433f_write_page(num, address + p * MX25L6433F_PAGE_SIZE, &data[MX25L6433F_PAGE_SIZE * p],
                MX25L6433F_PAGE_SIZE);
        if (res) {
            write_ok += MX25L6433F_PAGE_SIZE;
        }
    }

    if (rem) {
        res = mx25l6433f_write_page(num, address + MX25L6433F_PAGE_SIZE * page_cnt,
                &data[page_cnt * MX25L6433F_PAGE_SIZE], rem);
        if (res) {
            write_ok += rem;
        }
    }

    if (size == write_ok) {
        LOG_INFO(MX25L6433F, "WriteOk");
    } else {
        LOG_ERROR(MX25L6433F, "WriteErr");
    }

    return res;
}

bool mx25l6433f_erase_mem(uint8_t num, uint32_t address, uint32_t size) {
    bool res = false;
    LOG_WARNING(MX25L6433F, "Errase Addr:0x%x size %u byte", address, size);
    /*TODO: Implement later*/
#warning TODO Implement later
    return res;
}

bool mx25l6433f_zero(uint8_t num, uint32_t address, uint32_t size) {
    bool res = false;
    uint8_t z_data[MX25L6433F_PAGE_SIZE];
    memset(z_data, 0, sizeof(z_data));
    uint32_t page_cnt = size / sizeof(z_data);
    uint32_t rem = size % sizeof(z_data);
    uint32_t ok_cnt = 0;
    uint32_t b = 0;
    for (b = 0; b < page_cnt; b++) {
        res = mx25l6433f_write(num, address + sizeof(z_data) * b, z_data, sizeof(z_data));
        if (res) {
            ok_cnt += sizeof(z_data);
        }
    }

    if (rem) {
        res = mx25l6433f_write(num, address + sizeof(z_data) * page_cnt, z_data, rem);
        if (res) {
            ok_cnt += rem;
        }
    }

    if (size == ok_cnt) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

bool mx25l6433f_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(MX25L6433F, "MX25L6433F_%u,Proc", num);
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        Node->spin++;
    }
    return res;
}

bool mx25l6433f_read_sfdp(uint8_t num, uint32_t address, uint16_t* word) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    gpio_logic_level_set(Node->chip_select, 0);

    uint8_t buff[5] = { MX25_CMD_READ_SFDP, 0xFF, 0xFF, 0xFF, 0xFF };

    pack_24bit_big_endian(address, &buff[1]);

    res = spi_mcal_write(Node->spi_num, buff, 5);
    if (res) {
        if (word) {
            *word = spi_read_word(Node->spi_num);
        }
    }
    gpio_logic_level_set(Node->chip_select, 1);

    return res;
}

bool mx25l6433f_reset_hw(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    gpio_logic_level_set(Node->reset, 1);
    gpio_logic_level_set(Node->reset, 0);
    wait_ms(2);
    gpio_logic_level_set(Node->reset, 1);
    /*Standby mode*/
    return res;
}

bool mx25l6433f_reset(uint8_t num) {
    bool res = false;
    LOG_INFO(MX25L6433F, "Reset");
    res = mx25l6433f_simple_cmd_send(num, MX25_CMD_RESET_ENABLE);
    wait_ms(1);
    res = mx25l6433f_simple_cmd_send(num, MX25_CMD_RESET_MEMORY);

    return res;
}

uint32_t mx25l6433f_reg_cnt(void) {
    return MX25L6433F_REG_CNT;
}

bool mx25l6433f_electronic_signature_read(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    gpio_logic_level_set(Node->chip_select, 0);
    wait_us(1);
    uint8_t buff[4] = { MX25_CMD_READ_ELECTRONIC_ID, 0xFF, 0xFF, 0xFF };
    res = spi_mcal_write(Node->spi_num, buff, 4);
    if (res) {
        Node->electronic_signature = spi_read_byte(Node->spi_num);
    }

    gpio_logic_level_set(Node->chip_select, 1);
    wait_us(1);
    return res;
}

bool mx25l6433f_is_write_in_progress(uint8_t num) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        res = mx25l6433f_status_reg_read(num);
        if (res) {
            if (MX25_WIP_WRITE_OPERATION == Node->status.wip) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

bool mx25l6433f_wait_write_done(uint8_t num, uint32_t time_out) {
    bool res = false;
    bool loop = true;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        uint32_t start_ms = 0U;
        start_ms = time_get_ms32();
        int32_t diff_ms = 0;
        while (loop) {
            res = mx25l6433f_is_write_in_progress(num);
            if (false == res) {
                LOG_INFO(MX25L6433F, "WriteDone %u ms", diff_ms);
                Node->write_time_ms.cur = diff_ms;
                Node->write_time_ms.min = MATH_MIN(diff_ms, Node->write_time_ms.min);
                Node->write_time_ms.max = MATH_MAX(diff_ms, Node->write_time_ms.max);
                loop = false;
                res = true;
            }

            uint32_t curr_ms = 0U;
            curr_ms = time_get_ms32();
            diff_ms = curr_ms - start_ms;
            if (time_out < diff_ms) {
                LOG_ERROR(MX25L6433F, "WriteTimeOut %u ms", time_out);
                res = false;
                loop = false;
            }
        }
    }
    return res;
}

bool mx25l6433f_write_enable(uint8_t num, bool on_off) {
    /*Write Enable (WREN) command: WREN command is required to set the Write Enable Latch bit (WEL) before
     issuing other commands to change data.*/
    bool res = false;
    Mx25l6433fCommands_t cmd = 0;

    switch (on_off) {
        case true: {
            cmd = MX25_CMD_WRITE_ENABLE;
        }
            break;
        case false: {
            cmd = MX25_CMD_WRITE_DISABLE;
        }
            break;
        default:
            break;
    }

    res = mx25l6433f_simple_cmd_send(num, cmd);

    return res;
}

uint8_t mx25l6433f_read_byte(uint8_t num, uint32_t address) {
    uint8_t data = 0x00;
    mx25l6433f_read(num, address, &data, 1);
    return data;
}

bool mx25l6433f_scan(uint8_t num, uint32_t address, uint32_t size, double* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    uint8_t buff[256];
    if (usage_pec && spare && busy) {
        res = true;
        uint32_t i = 0;
        *spare = 0;
        *busy = 0;

        uint32_t chunk = size / sizeof(buff);
        uint32_t rem = size % sizeof(buff);
        uint32_t c = 0;
        for (c = 0; c < chunk; c++) {
            res = mx25l6433f_read(num, address + c * sizeof(buff), buff, sizeof(buff));
            if (res) {
                for (i = 0; i < sizeof(buff); i++) {

                    if (0xFF == buff[i]) {
                        (*spare)++;
                    } else {
                        (*busy)++;
                    }
                }
            }
        }

        res = mx25l6433f_read(num, address + chunk * sizeof(buff), buff, rem);
        if (res) {
            for (i = 0; i < rem; i++) {
                if (0xFF == buff[i]) {
                    (*spare)++;
                } else {
                    (*busy)++;
                }
            }
        }

        *usage_pec = (double) (((double) (100U * (*busy))) / ((double) size));
    }
    return res;
}

bool mx25l6433f_init_common(const Mx25l6433fConfig_t* const Config, Mx25l6433fHandle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->name = Config->name;
            Node->chip_select = Config->chip_select;
            Node->write_protection = Config->write_protection;
            Node->reset = Config->reset;
            Node->spi_num = Config->spi_num;
            Node->num = Config->num;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool mx25l6433f_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(MX25L6433F, "MX25L6433F_%u", num);
    const Mx25l6433fConfig_t *Config = Mx25l6433fGetConfig(num);
    res = Mx25l6433fIsValidConfig(Config);
    if (res) {
#ifdef HAS_MX25L6433F_DIAG
        LOG_WARNING(MX25L6433F, "%s", Mx25l6433fConfigToStr(Config));
#endif
        Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
        if (Node) {
            res = mx25l6433f_init_common(Config, Node);
            Node->valid = true;
            Node->write_time_ms.cur = 0;
            Node->write_time_ms.min = 0xFFFFFFFF;
            Node->write_time_ms.max = 0;
            res = mx25l6433f_is_connected(num);
            if (res) {
                Node->init = true;
            } else {
                LOG_INFO(MX25L6433F, "LinkErr");
            }
            res = mx25l6433f_identification_read(num);
            res = mx25l6433f_electronic_signature_read(num);
            res = mx25l6433f_configuration_read(num);

            res = mx25l6433f_write_enable(num, true);
        } else {
            LOG_ERROR(MX25L6433F, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(MX25L6433F, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT( MX25L6433F, MX25L6433F, mx25l6433f)
COMPONENT_PROC_PATTERT(MX25L6433F, MX25L6433F, mx25l6433f)
