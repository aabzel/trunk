#include "mx25l6433f_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(Mx25l6433f, mx25l6433f)
COMPONENT_GET_CONFIG(Mx25l6433f, mx25l6433f)


/*ISO-26262 require verify configuration*/

bool Mx25l6433fIsValidConfig(const Mx25l6433fConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(MX25L6433F, "MX25L6433F_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}


bool mx25l6433f_init_custom(void) {
    bool res = false;
    LOG_INFO(MX25L6433F, "Version:%u", MX25L6433F_VERSION);
    return res;
}


bool mx25l6433f_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(MX25L6433F, "MX25L6433F_%u,Proc", num);
    Mx25l6433fHandle_t* Node = Mx25l6433fGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}


bool mx25l6433f_init_common(const Mx25l6433fConfig_t* const Config, Mx25l6433fHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}


bool mx25l6433f_raw_reg_diag(uint8_t i) {
    bool res = false;
    return res;
}

bool mx25l6433f_write(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size){

}

bool mx25l6433f_wait_write_done(uint8_t num, uint32_t time_out){

}


/* 10-22. Page Program (PP)
 * (page 28 )Figure 12. Program/Erase flow with read array data
 */
bool mx25l6433f_page_program(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size) {
    bool res = false;
    LOG_INFO(MX25R6435F, "PageProg,Addr:%x,Size:%u byte",address, size);
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {


    res = mx25l6433f_is_aligned_addr(address);
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
        res = mx25l6433f_write_activate(num, MX25_WR_TIMEOUT_MS);
    }

    if(res) {
        gpio_logic_level_set(Node->chip_select, 0);
        res = mx25l6433f_write_cmd_address(MX25_CMD_PAGE_PROGRAM, address);
        if(res) {
            res = spi_mcal_write(Node->spi_num, data, size);
        }
        gpio_logic_level_set(Node->chip_select, 1);

        if(res) {
            res = mx25l6433f_wait_write_done(MX25_WR_TIMEOUT_MS);
        }

        res = mx25l6433f_verify(address, data, size);
        if(res) {
            LOG_INFO(MX25R6435F, "VeryfyOk");
        } else {
            LOG_ERROR(MX25R6435F, "VeryfyErr");
        }
    }
    }
    return res;
}


bool mx25l6433f_read(uint8_t num, uint32_t address, uint8_t* data, uint32_t size) {
    bool res = false;
    Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
    if (Node) {
        if (data) {
            if (size) {
                gpio_logic_level_set(Node->chip_select, GPIO_LVL_LOW);
                res = mx25l6433f_write_cmd_address(MX25_CMD_NORMAL_READ, address);
                if (res) {
                    res = spi_mcal_read(Node->spi_num, data, size);
                }
                gpio_logic_level_set(Node->chip_select, GPIO_LVL_HI);
            }
        }
    }
    return res;
}


bool mx25l6433f_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(MX25L6433F, "MX25L6433F_%u", num);
    const Mx25l6433fConfig_t *Config = Mx25l6433fGetConfig(num);
    res = Mx25l6433fIsValidConfig(Config);
    if(res) {
#ifdef HAS_MX25L6433F_DIAG
        LOG_WARNING(MX25L6433F, "%s", Mx25l6433fConfigToStr(Config));
#endif
        Mx25l6433fHandle_t *Node = Mx25l6433fGetNode(num);
        if(Node) {
            res = mx25l6433f_init_common(Config, Node);
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(MX25L6433F, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(MX25L6433F, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(MX25L6433F, MX25L6433F, mx25l6433f)
COMPONENT_PROC_PATTERT(MX25L6433F, MX25L6433F, mx25l6433f)
