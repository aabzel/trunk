#include "w25q32jv_drv.h"

#include <string.h>

#include "code_generator.h"
#include "hal_mcal.h"
#include "mik32_hal_spifi.h"
#include "spifi_mcal.h"
#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

const W25q32jvOpCodes_t w25q32jv_reg_num_to_op_code(const W25q32jvRegisterIndex_t reg_num) {
    W25q32jvOpCodes_t op_code = W25Q32JV_OPCODE_UNDEF;
    switch(reg_num) {
    case W25Q32JV_STATUS_REG_1:
        op_code = W25Q32JV_READ_SREG1;
        break;
    case W25Q32JV_STATUS_REG_2:
        op_code = W25Q32JV_READ_SREG2;
        break;
    case W25Q32JV_STATUS_REG_3:
        op_code = W25Q32JV_READ_STATUS_REG_3;
        break;
    default:
        op_code = W25Q32JV_OPCODE_UNDEF;
        break;
    }
    return op_code;
}

COMPONENT_GET_NODE(W25q32jv, w25q32jv)
COMPONENT_GET_CONFIG(W25q32jv, w25q32jv)

bool w25q32jv_write_regs(const uint8_t num, const uint8_t sreg1, const uint8_t sreg2) {
    bool res = false;
    res = w25q32jv_write_enable(num);
    W25q32jvHandle_t* Node = W25q32jvGetNode(num);
    if(Node) {
        SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
        if(SpiFi) {

            uint8_t data[2] = {sreg1, sreg2};

            SpiFiRegCmd_t WrRegsCmd = {0};
            WrRegsCmd.opcode = W25Q32JV_WRITE_SREG;
            WrRegsCmd.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
            WrRegsCmd.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;
            WrRegsCmd.intlen = 0;
            WrRegsCmd.dout = SPIFI_CMD_DOUT_FLASH_WRITE;
            WrRegsCmd.datalen = 2;
            WrRegsCmd.poll = SPIFI_CMD_POLL_NO;

            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle,   /* spifi */
                                           WrRegsCmd.dword,  /* cmd */
                                           0,                /* address */
                                           2,                /* bufferSize */
                                           0,                /* readBuffer */
                                           data,             /* writeBuffer */
                                           0,                /* interimData */
                                           HAL_SPIFI_TIMEOUT /* timeout */
            );

            res = MIK32_HalRetToRes(ret);
            res = w25q32jv_wait_busy(num, W25Q32JV_PROGRAM_BUSY_TIMEOUT) && res;
        }
    }
    return res;
}

bool w25q32jv_write_reg2(const uint8_t num, const uint8_t reg_val) {
    bool res = false;
    res = w25q32jv_write_enable(num);
    W25q32jvHandle_t* Node = W25q32jvGetNode(num);
    if(Node) {
        SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
        if(SpiFi) {
            SpiFiRegCmd_t WrReg2Cmd = {0};
            WrReg2Cmd.opcode = W25Q32JV_WRITE_SREG2;
            WrReg2Cmd.intlen = 0;
            WrReg2Cmd.dout = SPIFI_CMD_DOUT_FLASH_WRITE;
            WrReg2Cmd.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
            WrReg2Cmd.datalen = 1;
            WrReg2Cmd.poll = SPIFI_CMD_POLL_NO;
            WrReg2Cmd.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;

            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle,   /* spifi */
                                           WrReg2Cmd.dword,  /* cmd */
                                           0,                /* address */
                                           1,                /* bufferSize */
                                           0,                /* readBuffer */
                                           &reg_val,         /* writeBuffer */
                                           0,                /* interimData */
                                           HAL_SPIFI_TIMEOUT /* timeout */
            );

            res = MIK32_HalRetToRes(ret);
            res = w25q32jv_wait_busy(num, W25Q32JV_PROGRAM_BUSY_TIMEOUT) && res;
        }
    }
    return res;
}

/*
  Read Data (03h)
  num - ASIC num
  address - 24 bit address 24-bit address (A23-A0) into the DI pin.
            0....0x00FFFFFF
  data - out data
  size - 1....256
 */
#define SPIFI_WRITE_BUFFER NULL
#define SPIFI_INTERIM_DATA 0
bool w25q32jv_read_data(uint8_t num, const uint32_t address, uint8_t* const data, const uint16_t size) {
    bool res = false;
    // run
    if(size) {
        W25q32jvHandle_t* Node = W25q32jvGetNode(num);
        if(Node) {
            // run
            SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
            if(SpiFi) {
                // run
                SpiFiRegCmd_t RegCmd = {0};
                RegCmd.opcode = W25Q32JV_READ_DATA;
                RegCmd.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_3ADDR;
                RegCmd.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
                RegCmd.intlen = 0;
                RegCmd.poll = SPIFI_CMD_POLL_NO;
                RegCmd.dout = SPIFI_CMD_DOUT_FLASH_READ;
                RegCmd.datalen = size;

                // no run
                HAL_StatusTypeDef ret = HAL_ERROR;
                ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle, RegCmd.dword, address, size, data, SPIFI_WRITE_BUFFER,
                                               SPIFI_INTERIM_DATA, HAL_SPIFI_TIMEOUT);
                // led_mono_ctrl(  2, true);
                res = MIK32_HalRetToRes(ret);
            }
        }
    }
    return res;
}

bool w25q32jv_write_enable(const uint8_t num) {
    bool res = false;
    W25q32jvHandle_t* Node = W25q32jvGetNode(num);
    if(Node) {
        SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
        if(SpiFi) {
            SpiFiRegCmd_t CmdWrEn = {0};
            CmdWrEn.opcode = W25Q32JV_WRITE_ENABLE;
            CmdWrEn.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;
            CmdWrEn.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
            CmdWrEn.intlen = 0;
            CmdWrEn.poll = SPIFI_CMD_POLL_NO;
            CmdWrEn.datalen = 0;
            CmdWrEn.dout = SPIFI_CMD_DOUT_FLASH_WRITE;

            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle, CmdWrEn.dword, 0, 0, 0, 0, 0, HAL_SPIFI_TIMEOUT);
            res = MIK32_HalRetToRes(ret);
        }
    }
    return res;
}

bool w25q32jv_read_reg(const uint8_t num, const W25q32jvRegisterIndex_t reg_num, W25q32jvRegUniversal_t* const uReg) {
    bool res = false;
    W25q32jvHandle_t* Node = W25q32jvGetNode(num);
    if(Node) {
        SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
        if(SpiFi) {
            SpiFiRegCmd_t RdRegCmd = {0};
            RdRegCmd.opcode = w25q32jv_reg_num_to_op_code(reg_num);
            RdRegCmd.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
            RdRegCmd.dout = SPIFI_CMD_DOUT_FLASH_READ;
            RdRegCmd.intlen = 0;
            RdRegCmd.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;
            RdRegCmd.poll = SPIFI_CMD_POLL_NO;
            RdRegCmd.datalen = 1;

            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle, RdRegCmd.dword, 0, /*Addr*/
                                           1,                                 /*Size*/
                                           &uReg->byte, 0,                    /* write Buffer */
                                           0,                                 /*interim Data*/
                                           HAL_SPIFI_TIMEOUT);

            res = MIK32_HalRetToRes(ret);
        }
    }
    return res;
}

bool w25q32jv_wait_busy(const uint8_t num, const uint32_t timeout) {
    bool res = false;
    uint32_t cnt = 0;
    bool loop = true;
    while(loop) {
        cnt++;
        W25q32jvRegUniversal_t uReg;
        uReg.byte = 0;
        res = w25q32jv_read_reg(num, W25Q32JV_STATUS_REG_1, &uReg);
        if(res) {
            if(uReg.Status1.busy) {
                loop = true;
            } else {
                loop = false;
                res = true;
            }
        }

        if(timeout < cnt) {
            loop = false;
            res = false;
        }
    }

    return res;
}

/*
 The Chip Erase instruction sets all memory within the device to the erased state of all 1s (FFh).

 While the Chip Erase cycle is in progress, the Read Status Register
 instruction may still be accessed to check the status of the BUSY bit.

 The BUSY bit is a 1 during the Chip Erase cycle and becomes a 0 when
 finished and the device is ready to accept other instructions again.
 After the Chip Erase cycle has finished the Write Enable Latch (WEL)
 bit in the Status Register is cleared to 0.
 */
bool w25q32jv_chip_erase(const uint8_t num) {
    bool res = false;

    res = w25q32jv_write_enable(num);

    W25q32jvHandle_t* Node = W25q32jvGetNode(num);
    if(Node) {
        SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
        if(SpiFi) {
            //
            SpiFiRegCmd_t CmdWrEn = {0};
            CmdWrEn.opcode = W25Q32JV_CHIP_ERASE;
            CmdWrEn.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR;
            CmdWrEn.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
            CmdWrEn.poll = SPIFI_CMD_POLL_NO;
            CmdWrEn.dout = SPIFI_CMD_DOUT_FLASH_WRITE;
            CmdWrEn.intlen = 0;
            CmdWrEn.datalen = 0;

            HAL_StatusTypeDef ret = HAL_ERROR;
            ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle, CmdWrEn.dword, 0, /*address*/
                                           0,                                /*bufferSize*/
                                           0,                                /*readBuffer*/
                                           0,                                /*writeBuffer*/
                                           0,                                /*interimData*/
                                           HAL_SPIFI_TIMEOUT);
            res = MIK32_HalRetToRes(ret);

            res = w25q32jv_wait_busy(num, W25Q32JV_PROGRAM_BUSY_TIMEOUT) && res;
        }
    }
    return res;
}

/*
The Sector Erase instruction sets all memory within a specified sector (4K-bytes) to the erased
state of all 1s (FFh).

A Write Enable instruction must be executed before the device will accept the Sector Erase
Instruction (Status Register bit WEL must equal 1).

The instruction is initiated by driving the /CS pin low and shifting the instruction
code “20h” followed a 24-bit sector address (A23-A0).

The /CS pin must be driven high after the eighth bit of the last byte has been latched.
If this is not done the Sector Erase instruction will not be executed.
After /CS is driven high, the self-timed Sector Erase instruction will commence for a time
duration of tSE (See AC Characteristics).

While the Sector Erase cycle is in progress, the Read Status Register instruction may still
be accessed for checking the status of the BUSY bit.

The BUSY bit is a 1 during the Sector Erase cycle and becomes a 0 when the cycle is finished and the
device is ready to accept other instructions again.
After the Sector Erase cycle has finished the Write Enable Latch (WEL) bit in the Status
Register is cleared to 0.
The Sector Erase instruction will not be executed if the addressed page is protected by the
Block Protect (CMP, SEC, TB, BP2, BP1, and BP0) bits or the Individual Block/Sector Locks.
   */
bool w25q32jv_erase_sector(const uint8_t num, const uint32_t address) {
    bool res = false;
    W25q32jvHandle_t* Node = W25q32jvGetNode(num);
    if(Node) {
        SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
        if(SpiFi) {
            res = w25q32jv_write_enable(num);
            if(res) {
                SpiFiRegCmd_t RegCmd = {0};
                RegCmd.opcode = W25Q32JV_SECTOR_ERASE_4K;
                RegCmd.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_3ADDR;
                RegCmd.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
                RegCmd.dout = SPIFI_CMD_DOUT_FLASH_WRITE;
                RegCmd.intlen = 0;
                RegCmd.poll = SPIFI_CMD_POLL_NO;
                RegCmd.datalen = 0;

                HAL_StatusTypeDef ret = HAL_ERROR;
                ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle,     /*spifi*/
                                               RegCmd.dword,       /*cmd*/
                                               address,            /*address*/
                                               0,                  /*bufferSize*/
                                               0,                  /*readBuffer*/
                                               (uint8_t*)0,        /*interimData*/
                                               SPIFI_INTERIM_DATA, /*interimData*/
                                               HAL_SPIFI_TIMEOUT   /*timeout*/
                );
                res = MIK32_HalRetToRes(ret);
                res = w25q32jv_wait_busy(num, W25Q32JV_PROGRAM_BUSY_TIMEOUT) && res;
            }
        }
    }
    return res;
}
/*
 The Page Program instruction allows from one byte to 256 bytes
 A Write Enable instruction must be executed before the device will accept the Page
 Program Instruction (Status Register bit WEL= 1).


 While the Page Program cycle is in progress, the Read Status Register instruction
 may still be accessed for checking the status of the BUSY bit.

 size- 1...256
  */
bool w25q32jv_prog_page(uint8_t num, const uint32_t address, const uint8_t* const data, const uint16_t size) {
    bool res = false;

    if(size <= W25Q32JV_PAGE_SIZE) {
        res = true;
    } else {
        res = false;
    }

    if(res) {
        W25q32jvHandle_t* Node = W25q32jvGetNode(num);
        if(Node) {
            SpiFiHandle_t* SpiFi = SpiFiGetNode(Node->spifi_num);
            if(SpiFi) {
                res = w25q32jv_write_enable(num);
                if(res) {
                    SpiFiRegCmd_t RegCmd = {0};
                    RegCmd.opcode = W25Q32JV_PAGE_PROGRAM;
                    RegCmd.frameform = SPIFI_CMD_FRAME_FORM_OPCODE_3ADDR;
                    RegCmd.fieldform = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
                    RegCmd.dout = SPIFI_CMD_DOUT_FLASH_WRITE;
                    RegCmd.intlen = 0;
                    RegCmd.poll = SPIFI_CMD_POLL_NO;
                    RegCmd.datalen = size;

                    HAL_StatusTypeDef ret = HAL_ERROR;
                    ret = HAL_SPIFI_SendCommand_LL(&SpiFi->Handle, RegCmd.dword, address, size, 0, (uint8_t*)data,
                                                   SPIFI_INTERIM_DATA, HAL_SPIFI_TIMEOUT);
                    res = MIK32_HalRetToRes(ret);
                    res = w25q32jv_wait_busy(num, W25Q32JV_PROGRAM_BUSY_TIMEOUT) && res;
                }
            }
        }
    }

    return res;
}

bool w25q32jv_init_custom(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(W25Q32JV, "InitCustom");
#endif
    return res;
}

static bool w25q32jv_init_common(const W25q32jvConfig_t* const Config, W25q32jvHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->spi_num = Config->spi_num;
            Node->spifi_num = Config->spifi_num;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool w25q32jv_init_one(uint8_t num) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(W25Q32JV, "Init");
#endif
    const W25q32jvConfig_t* Config = W25q32jvGetConfig(num);
    if(Config) {
        W25q32jvHandle_t* Node = W25q32jvGetNode(num);
        if(Node) {
            res = w25q32jv_init_common(Config, Node);
            res = true;
        }
    }
    // no led_mono_ctrl(2, true);

    return res;
}

bool w25q32jv_proc_one(uint8_t num) {
    bool res = true;
#ifdef HAS_LOG
    LOG_PARN(W25Q32JV, "Proc:%u", num);
#endif
    return res;
}

COMPONENT_INIT_PATTERT(W25Q32JV, W25Q32JV, w25q32jv)
COMPONENT_PROC_PATTERT(W25Q32JV, W25Q32JV, w25q32jv)
