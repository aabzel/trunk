#include "lis3dh_drv.h"

#include <string.h>

//#include "c_defines_generated.h"
#include "array_diag.h"
#include "bit_const.h"
#include "bit_utils.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "vector_mcal.h"

#ifdef HAS_SPI
#include "lis3dh_spi.h"
#endif

#ifdef HAS_I2C
#include "lis3dh_i2c.h"
#endif

COMPONENT_GET_NODE(Lis3dh, lis3dh)
COMPONENT_GET_CONFIG(Lis3dh, lis3dh)

// see Table 10. Operating mode selection
// Table 4. Mechanical characteristics
const Lis3dhOperationModeInfo_t OperationModeInfo[] = {
    {
        .full_scale = LIS3DH_FULL_SCALE_16G,
        .operation_mode = LIS3DH_OPERATION_MODE_LOW_POWER,
        .sensitivity = 192,
        .bit_depth = 8,
        .low_power_enable = 1,
        .high_resolution_enable = 0,
        .name = "LowPow8B",
    },

    {
        .full_scale = LIS3DH_FULL_SCALE_16G,
        .operation_mode = LIS3DH_OPERATION_MODE_NORMAL,
        .sensitivity = 48,
        .bit_depth = 10,
        .low_power_enable = 0,
        .high_resolution_enable = 0,
        .name = "Norm_10b",
    },

    {
        .full_scale = LIS3DH_FULL_SCALE_16G,
        .operation_mode = LIS3DH_OPERATION_MODE_HIGH_RESOLUTION,
        .sensitivity = 12,
        .bit_depth = 12,
        .low_power_enable = 0,
        .high_resolution_enable = 1,
        .name = "HiRes12b",
    },

    {
        .full_scale = LIS3DH_FULL_SCALE_16G,
        .operation_mode = LIS3DH_OPERATION_MODE_ERROR,
        .sensitivity = 0,
        .bit_depth = 0,
        .low_power_enable = 1,
        .high_resolution_enable = 1,
        .name = "Error",
    },

    ////////////////2G
    {
        .full_scale = LIS3DH_FULL_SCALE_2G,
        .operation_mode = LIS3DH_OPERATION_MODE_LOW_POWER,
        .sensitivity = 16,
        .bit_depth = 8,
        .low_power_enable = 1,
        .high_resolution_enable = 0,
        .name = "LowPow8B",
    },

    {
        .full_scale = LIS3DH_FULL_SCALE_2G,
        .operation_mode = LIS3DH_OPERATION_MODE_NORMAL,
        .sensitivity = 4,
        .bit_depth = 10,
        .low_power_enable = 0,
        .high_resolution_enable = 0,
        .name = "Norm_10b",
    },

    {
        .full_scale = LIS3DH_FULL_SCALE_2G,
        .operation_mode = LIS3DH_OPERATION_MODE_HIGH_RESOLUTION,
        .sensitivity = 1,
        .bit_depth = 12,
        .low_power_enable = 0,
        .high_resolution_enable = 1,
        .name = "HiRes12b",
    },
    //////////////////4G
    // TODO

    //////////////////8G

    // TODO

};

uint32_t lis3dh_operation_mode_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(OperationModeInfo);
    return cnt;
}

const Lis3dhOperationModeInfo_t* Lis3dhOpModeInfoGetByOpMode(Lis3dhOperationMode_t operation_mode) {
    Lis3dhOperationModeInfo_t* OpInfo = NULL;
    uint32_t i = 0;
    uint32_t cnt = lis3dh_operation_mode_cnt();
    for(i = 0; i < cnt; i++) {
        if(operation_mode == OperationModeInfo[i].operation_mode) {
            OpInfo = &OperationModeInfo[i];
        }
    }
    return OpInfo;
}

static const Lis3dhOperationModeInfo_t* Lis3dhOpModeInfoGetByOpModeAndScale(Lis3dhOperationMode_t operation_mode,
                                                                            Lis3dhFullScale_t full_scale) {
    Lis3dhOperationModeInfo_t* OpInfo = NULL;
    uint32_t i = 0;
    uint32_t cnt = lis3dh_operation_mode_cnt();
    for(i = 0; i < cnt; i++) {
        if(operation_mode == OperationModeInfo[i].operation_mode) {
            if(full_scale == OperationModeInfo[i].full_scale) {
                OpInfo = &OperationModeInfo[i];
            }
        }
    }
    return OpInfo;
}





bool lis3dh_reg_read_ll(Lis3dhHandle_t* Node, Lis3dhRegAddr_t addr, uint8_t* const byte) {
    bool res = false;
    if(Node) {
        switch(Node->interface) {
#ifdef HAS_I2C
            case LIS3DH_IF_I2C: {res = lis3dh_i2c_reg_read_ll(Node,addr,byte);} break;
#endif /*HAS_I2C*/

#ifdef HAS_SPI
            case LIS3DH_IF_SPI: {res = lis3dh_spi_reg_read_ll(Node,addr,byte);} break;
#endif
            default: {
                LOG_ERROR(LIS3DH, "UndefIf:%u", Node->interface);
                res = false;
            }  break;
        }
    }
    return res;
}

#define MILLI_TO_REAL(MILLI) (((float)(MILLI)) / 1000.0)

// see Table 10. Operating mode selection
bool lis3dh_adc_to_real(Lis3dhAcceleration_t* const Acceleration, int8_t mg_per_digit, int8_t bit_depth) {
    bool res = false;
    if(Acceleration) {
        if(0 < mg_per_digit) {
            float scale_g = MILLI_TO_REAL(mg_per_digit);
            Acceleration->AccelReal.dx = ((float)(Acceleration->X.s16)) * scale_g;
            Acceleration->AccelReal.dy = ((float)(Acceleration->Y.s16)) * scale_g;
            Acceleration->AccelReal.dz = ((float)(Acceleration->Z.s16)) * scale_g;
            res = true;
        }
    }
    return res;
}

bool lis3dh_adc_to_real_ll(Lis3dhHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(0 < Node->sensitivity) {
            float scale_g = MILLI_TO_REAL(Node->sensitivity);
            Node->Acceleration.AccelReal.dx = ((float)(Node->Acceleration.X.s16)) * scale_g;
            Node->Acceleration.AccelReal.dy = ((float)(Node->Acceleration.Y.s16)) * scale_g;
            Node->Acceleration.AccelReal.dz = ((float)(Node->Acceleration.Z.s16)) * scale_g;
            float abs = vector_calc_norm_f(&Node->Acceleration.AccelReal);
            DATA_UPDATE(Node->abs_accel, abs);
            res = true;
        }
    }
    return res;
}


bool lis3dh_reg_read_all(uint8_t num) {
    bool res = false;
    const Lis3dhConfig_t* Config = Lis3dhGetConfig(num);
    if(Config) {
        uint8_t i = 0;
        uint8_t ok_cnt = 0;
        for(i = 0; i < LIS3DH_REG_CNT; i++) {
            // res = lis3dh_reg_read(Lis3dhRegVal[i].addr, &Lis3dhRegVal[i].value.byte);
            if(res) {
                ok_cnt++;
            } else {
                // LOG_ERROR(I2C, "Read Reg:0x%02x Err", Lis3dhRegVal[i].addr);
            }
        }

        if(ok_cnt == LIS3DH_REG_CNT) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

static bool lis3dh_is_connected_ll(Lis3dhHandle_t* const Node) {
    bool res = false;
    uint8_t reg_val = 0;
    res = lis3dh_reg_read_ll(Node, LIS3DH_REG_WHO_AM_I, &reg_val);
    if(res) {
        if(LIS3DH_ID_VALUE == reg_val) {
            res = true;
        } else {
            LOG_ERROR(LIS3DH,"Rx:0x%02x,Need:0x%02x", reg_val,LIS3DH_ID_VALUE);
            res = false;
        }
    }
    return res;
}

bool lis3dh_is_connected(uint8_t num) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        res = lis3dh_is_connected_ll(Node);
    }
    return res;
}

// see Table 17. Transfer when master is writing one byte to slave
bool lis3dh_reg_write_ll(Lis3dhHandle_t* Node, Lis3dhRegAddr_t addr, uint8_t byte) {
    bool res = false;
    if(Node) {
        LOG_INFO(LIS3DH, "Set,Reg:0x%02x=%s,Val:0x%02x", addr, Lis3dhRegAddrToName(addr), byte);
        switch(Node->interface) {
#ifdef HAS_I2C
            case LIS3DH_IF_I2C: {res = lis3dh_i2c_reg_write_ll(Node, addr, byte); } break;
#endif /*HAS_I2C*/

#ifdef HAS_SPI
            case LIS3DH_IF_SPI: {res = lis3dh_spi_reg_write_ll(Node, addr, byte); } break;
#endif /*HAS_SPI*/
            default:
                LOG_ERROR(LIS3DH, "UndefIf:%u", Node->interface);
                res = false;
            	break;
        }
    } else {
    }
    return res;
}

/*Figure 9. Writing One Byte of Data to the LIS3DH*/
bool lis3dh_reg_write(uint8_t num, Lis3dhRegAddr_t addr, uint8_t byte) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        res = lis3dh_reg_write_ll(Node, addr, byte);
    } else {
        LOG_ERROR(LIS3DH, "%u", num);
    }
    return res;
}

bool lis3dh_reg_write_verify(uint8_t num, Lis3dhRegAddr_t addr, uint8_t set_byte) {
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(LIS3DH, "SetVerify Reg:0x%02x Val:0x%02x", addr, set_byte);
    res = lis3dh_reg_write(num, addr, set_byte);
    if(res) {
        uint8_t byte_read = 0;
        res = lis3dh_reg_read(num, addr, &byte_read);
        if(byte_read == set_byte) {
            res = true;
            LOG_DEBUG(LIS3DH, "SetVerifyReg:0x%02x,Val:0x%02x Ok", addr, set_byte);
        } else {
            LOG_ERROR(LIS3DH, "VerifyErrReg:0x%02x,Set:0x%02x!=Get:0x%02x", addr, set_byte, byte_read);
            res = false;
        }
    }

    return res;
}

bool lis3dh_reset(uint8_t num) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
    }
    return res;
}

bool lis3dh_is_valid_addr(uint8_t addr) {
    bool res = false;
    const AsicReg8bitInfo_t* Node = Lis3dhRegAddrToInfo(addr);
    if(Node) {
        res = true;
    }

    return res;
}

bool lis3dh_reg_read(uint8_t num, Lis3dhRegAddr_t addr, uint8_t* const byte) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        LOG_DEBUG(LIS3DH, "Read,Reg:0x%02x",  addr);
        res = lis3dh_reg_read_ll(Node, addr, byte);
        if(res) {
            LOG_PARN(LIS3DH, "ReadOk,Reg:0x%02x,Val:0x%02x", addr, *byte);
        } else {
            LOG_ERROR(LIS3DH, "ReadErr,Reg:0x%02x=%s", addr, Lis3dhRegAddrToName(addr));
        }
    }
    return res;
}

bool lis3dh_init_custom(void) {
    log_level_get_set(LIS3DH, LOG_LEVEL_INFO);
    return true;
}

static bool lis3dh_register_config(uint8_t num, const Lis3dhRegVal_t* const Reg, uint32_t cnt) {
    bool res = false;
    if(Reg) {
        uint32_t ok = 0;
        uint32_t err = 0;
        LOG_WARNING(LIS3DH, "LIS3DH_%u,Cfg,Reg,Cnt:%u", num, cnt);
        if(cnt) {
            uint32_t i = 0;
            for(i = 0; i < cnt; i++) {
                res = lis3dh_reg_write_verify(num, Reg[i].addr, Reg[i].Reg.byte);
                if(res) {
                    ok++;
                }else {
                    err++;
                }
                wait_ms(5);
            }
        }
        if(ok == cnt) {
            LOG_INFO(LIS3DH, "LIS3DH_%u,Cfg,Ok,Cnt:%u",num,ok);
            res = true;
        } else {
            res = false;
            LOG_ERROR(LIS3DH, "LIS3DH_%u,Cfg,Err:%u",num,err);
        }
    }
    return res;
}

static bool lis3dh_init_common(const Lis3dhConfig_t* const Config, Lis3dhHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->bit_depth = Config->bit_depth;
            Node->interface = Config->interface;
#ifdef HAS_I2C
            Node->sa0_pin_value = Config->sa0_pin_value;
            Node->chip_addr = Config->chip_addr;
            Node->i2c_num = Config->i2c_num;
#endif

#ifdef HAS_SPI
            Node->ChipSelect = Config->ChipSelect;
            Node->spi_num = Config->spi_num;
#endif
            Node->num = Config->num;
            Node->valid = true;
            res = float_val_reset(&Node->abs_accel);
        }
    }
    return res;
}

bool lis3dh_operation_mode_get_ll(Lis3dhHandle_t* const Node, Lis3dhOperationMode_t* const operation_mode) {
    bool res = false;
    Lis3dhRegisterCtrlReg1_t CtrlReg1 = {0};
    res = lis3dh_reg_read_ll(Node, LIS3DH_REG_CTRL_REG1, &CtrlReg1.byte);
    if(res) {
        Lis3dhRegisterCtrlReg4_t CtrlReg4 = {0};
        res = lis3dh_reg_read_ll(Node, LIS3DH_REG_CTRL_REG4, &CtrlReg4.byte);
        if(res) {
            res = false;
            uint32_t i = 0;
            uint32_t cnt = ARRAY_SIZE(OperationModeInfo);
            for(i = 0; i < cnt; i++) {
                if(OperationModeInfo[i].low_power_enable == CtrlReg1.lpen) {
                    if(OperationModeInfo[i].high_resolution_enable == CtrlReg4.hr) {
                        *operation_mode = OperationModeInfo[i].operation_mode;
                        Node->operation_mode = OperationModeInfo[i].operation_mode;
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}

bool lis3dh_init_one(uint8_t num) {
    bool res = false;
    const Lis3dhConfig_t* Config = Lis3dhGetConfig(num);
    if(Config) {
        LOG_WARNING(LIS3DH, "Init:%s", Lis3dhConfigToStr(Config));
#warning + Config check
        Lis3dhHandle_t* Node = Lis3dhGetNode(num);
        if(Node) {
            res = lis3dh_init_common(Config, Node);
#ifdef HAS_SPI

            gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
#endif

#ifdef HAS_I2C
            Node->chip_addr = LIS3DH_I2C_ADDR_0;
            if(Node->sa0_pin_value) {
                SET_BIT_NUM(Node->chip_addr, 0);
            } else {
                RESET_BIT_NUM(Node->chip_addr, 0);
            }
#endif

            log_level_get_set(LIS3DH, LOG_LEVEL_DEBUG);

            res = lis3dh_is_connected_ll(Node);
            if(res) {
                LOG_INFO(LIS3DH, "Connected");
                res = lis3dh_register_config(num, Config->RegConfig, Config->cfg_reg_cnt);
            } else {
                LOG_ERROR(LIS3DH, "Cfg,Err");
            }

            log_level_get_set(LIS3DH, LOG_LEVEL_NOTICE);
            if(res) {
                Node->init = true;
                LOG_INFO(LIS3DH, "InitOk");
            }
#ifdef HAS_SPI
            gpio_logic_level_set(Node->ChipSelect.byte, GPIO_LVL_HI);
#endif
        } else {
            LOG_ERROR(LIS3DH, "NodeErr");
        }
    }
    return res;
}

#define LIS3DH_READ_AXIS(AXIS)                                                                                         \
    res = lis3dh_reg_read_ll(Node, LIS3DH_REG_OUT_##AXIS##_L, &Accel.AXIS.u8[0]) && res;                               \
    res = lis3dh_reg_read_ll(Node, LIS3DH_REG_OUT_##AXIS##_H, &Accel.AXIS.u8[1]) && res;                               \
    Accel.AXIS.s16 = Accel.AXIS.s16 >> shift;

bool lis3dh_acceleration_slow_get_ll(Lis3dhHandle_t* Node, Lis3dhAcceleration_t* const Acceleration) {
    bool res = true;
    Lis3dhAcceleration_t Accel = {0};
    int8_t shift = 16 - Node->bit_depth;

    LIS3DH_READ_AXIS(X)
    LIS3DH_READ_AXIS(Y)
    LIS3DH_READ_AXIS(Z)

    if(res) {
        *Acceleration = Accel;
    } else {
        LOG_ERROR(LIS3DH, "Accel,Read,Err");
    }

    return res;
}

bool lis3dh_acceleration_fast_get_ll(Lis3dhHandle_t* Node, Lis3dhAcceleration_t* const Acceleration) {
    bool res = false;
    // if(Node){
    if(Acceleration) {
        int8_t shift = 16 - Node->bit_depth;
        Lis3dhAccelRegs_t Mem;
        memset(Mem.buff, 0, sizeof(Lis3dhAccelRegs_t));
#ifdef HAS_I2C
        uint8_t addr_val = LIS3DH_REG_OUT_X_L;
        res = i2c_api_read_mem(Node->i2c_num, Node->chip_addr, &addr_val, 1, Mem.buff, 6);
#endif
        if(res) {
            Acceleration->X.s16 = Mem.X.s16 >> shift;
            Acceleration->Y.s16 = Mem.Y.s16 >> shift;
            Acceleration->Z.s16 = Mem.Z.s16 >> shift;
            res = true;
        } else {
            LOG_ERROR(LIS3DH, "I2C,Read,Mem,Err");
        }
    }
    //  }
    return res;
}

static int8_t Lis3dhOpMpdeAndScaleToSensitivity(Lis3dhOperationMode_t operation_mode, Lis3dhFullScale_t FullScale) {
    int8_t sensitivity = -1;
    const Lis3dhOperationModeInfo_t* OpInfo = Lis3dhOpModeInfoGetByOpModeAndScale(operation_mode, FullScale);
    if(OpInfo) {
        sensitivity = OpInfo->sensitivity;
    }
    return sensitivity;
}

static int8_t lis3dh_sensitivity_get_ll(Lis3dhHandle_t* const Node) {
    bool res = false;
    int8_t sensitivity = -1;
    if(Node) {
        Lis3dhRegisterCtrlReg4_t CtrlReg4 = {0};
        res = lis3dh_reg_read_ll(Node, LIS3DH_REG_CTRL_REG4, &CtrlReg4.byte);
        if(res) {
            Lis3dhOperationMode_t operation_mode = LIS3DH_OPERATION_MODE_UNDEF;
            res = lis3dh_operation_mode_get_ll(Node, &operation_mode);
            if(res) {
                sensitivity = Lis3dhOpMpdeAndScaleToSensitivity(operation_mode, CtrlReg4.fs);
                Node->sensitivity = sensitivity;
            }
        }
    }
    return sensitivity;
}

int8_t lis3dh_sensitivity_get(uint8_t num) {
    int8_t sensitivity = -1;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        sensitivity = lis3dh_sensitivity_get_ll(Node);
    }
    return sensitivity;
}

bool lis3dh_operation_mode_get(uint8_t num, Lis3dhOperationMode_t* const operation_mode) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        res = lis3dh_operation_mode_get_ll(Node, operation_mode);
    }
    return res;
}

bool lis3dh_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(LIS3DH, "Proc:%u", num);
    const Lis3dhConfig_t* Config = Lis3dhGetConfig(num);
    if(Config) {
        Lis3dhHandle_t* Node = Lis3dhGetNode(num);
        if(Node) {
            if(Node->link_ok){
                // res = lis3dh_acceleration_fast_get_ll(Node, &Node->Acceleration);
                res = lis3dh_acceleration_slow_get_ll(Node, &Node->Acceleration);
                if(res) {
                    res = lis3dh_adc_to_real_ll(Node);
                    Node->unproc_sample = true;
                    if(Node->log_on) {
                        Log.colored = false;
                        LOG_INFO(LIS3DH, "%s", Lis3dhAccelerationToStr(&Node->Acceleration));
                        Log.colored = true;
                    }

                    if(Node->log_inplace_on) {
                        cli_printf("\r%s", Lis3dhAccelerationToStr(&Node->Acceleration));
                    }
                }

            }
        } else {
            LOG_ERROR(LIS3DH, "NodeErr %u", num);
        }
    }
    return res;
}

static bool lis3dh_bit_depth_get_ll(Lis3dhHandle_t* Node, Lis3dhBitDepth_t* const bit_depth) {
    bool res = false;
    if(Node) {
        res = lis3dh_operation_mode_get_ll(Node, &Node->operation_mode);
        if(res) {
            res = false;
            Lis3dhOperationModeInfo_t* OpMode = Lis3dhOpModeInfoGetByOpMode(Node->operation_mode);
            if(OpMode) {
                Node->bit_depth = OpMode->bit_depth;
                *bit_depth = OpMode->bit_depth;
                res = true;
            }
        }
    }
    return res;
}

bool lis3dh_bit_depth_get(uint8_t num, Lis3dhBitDepth_t* const bit_depth) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        res = lis3dh_bit_depth_get_ll(Node, bit_depth);
    }
    return res;
}

static bool lis3dh_link_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(LIS3DH, "Proc,Link:%u", num);
    const Lis3dhConfig_t* Config = Lis3dhGetConfig(num);
    if(Config) {
        Lis3dhHandle_t* Node = Lis3dhGetNode(num);
        if(Node) {
            Node->link_ok = lis3dh_is_connected_ll(Node);
            if(Node->link_ok) {
                LOG_DEBUG(LIS3DH, "%u,Link,Ok", num);
                Node->sensitivity = lis3dh_sensitivity_get_ll(Node);
                Node->bit_depth = 0;
                res = lis3dh_bit_depth_get_ll(Node, &Node->bit_depth);
            } else {
                LOG_ERROR(LIS3DH, "%u,Link,Err", num);
            }
        } else {
            LOG_ERROR(LIS3DH, "NodeErr %u", num);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(LIS3DH, LIS3DH, lis3dh)

static uint32_t lis3dh_link_get_cnt(void) {
    uint32_t cnt = lis3dh_get_cnt();
    return cnt;
}

bool lis3dh_accel_read(uint32_t num, VectorF_t* const AccelReal) {
    bool res = false;
    Lis3dhHandle_t* Node = Lis3dhGetNode(num);
    if(Node) {
        if(Node->unproc_sample) {
            memcpy(AccelReal, &Node->Acceleration.AccelReal, sizeof(VectorF_t));
            Node->unproc_sample = false;
            res = true;
        }
    }
    return res;
}

COMPONENT_PROC_PATTERT(LIS3DH, LIS3DH, lis3dh)
COMPONENT_PROC_PATTERT(LIS3DH, LIS3DH, lis3dh_link)
