/*

CPOL= 0 and CPHA = 0 in Motorola/Freescale nomenclature.
Bytes follow from senior byte to junior byte (Motorola byte order or network byte order)
speed up to 16 MHz
*/
#include "sx1262_drv.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gpio_mcal.h"

#ifdef HAS_FREE_RTOS
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#endif /*HAS_FREE_RTOS*/

#include "array.h"
#include "bit_utils.h"
#include "board_layout.h"
#include "byte_utils.h"
#include "clocks.h"
#include "common_diag.h"
#ifdef HAS_LED
#include "led_drv.h"
#endif
#include "crc8_sae_j1850.h"
#include "data_utils.h"
#include "debug_info.h"
#include "float_utils.h"
#include "gpio_mcal.h"
#include "tim_drv.h"

#ifdef HAS_LOG
#include "cli_utils.h"
#include "log.h"
#endif

#ifdef HAS_RADIO
#include "radio_drv.h"
#endif

#include "none_blocking_pause.h"

#ifdef HAS_RTCM3
#include "rtcm3_protocol.h"
#endif

#ifdef HAS_SPI
#include "spi_drv.h"
#endif
#include "sx1262_config.h"
#include "sx1262_diag.h"
#include "sx1262_re_tx.h"
#include "sx1262_registers.h"
#include "sys_config.h"
#include "task_info.h"
#include "time_mcal.h"

#ifdef HAS_LORA
#include "lora_config.h"
#include "lora_drv.h"
#endif

#ifdef HAS_GFSK
#include "gfsk_config.h"
#include "gfsk_constants.h"
#include "gfsk_diag.h"
#include "gfsk_drv.h"
#endif

#ifndef HAS_SPI
#error "SX1262 requires SPI driver"
#endif

#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#include "tbfp_re_tx_ack_fsm.h"
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_LEGAL_BAND_CHECK
#include "legal_band.h"
#endif

#ifdef HAS_SX1262_DEBUG
#include "sx1262_diag.h"
#endif

#define WAIT_SX1262_MUTEX 1000
bool sx1262_chip_select(bool state) {
    bool res = true;
#ifdef HAS_FREE_RTOS
    if(Sx1262Instance.mutex) {
        if(true == state) {
            if(pdTRUE == xSemaphoreTake(Sx1262Instance.mutex, WAIT_SX1262_MUTEX)) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(SX1262, "MutexBusy");
            }
        }
    } else {
        res = false;
        LOG_ERROR(SX1262, "MutexInitError");
    }
#endif

    if(state && res) {
#ifdef HAS_SPI_SW_CHIP_SELECT
        gpio_set_state(DIO_SX1262_SS, 0);
#ifdef DIO_CAN_SS
        gpio_set_state(DIO_CAN_SS, 1);
#endif
#endif /*HAS_SPI_SW_CHIP_SELECT*/
        res = true;
    } else if(false == state) {
#ifdef HAS_SPI_SW_CHIP_SELECT
        gpio_set_state(DIO_SX1262_SS, 1);
#ifdef DIO_CAN_SS
        gpio_set_state(DIO_CAN_SS, 1);
#endif
#endif /*HAS_SPI_SW_CHIP_SELECT*/
        res = true;
    } else {
        res = false;
    }

#ifdef HAS_FREE_RTOS
    if(Sx1262Instance.mutex) {
        if(false == state) {
            xSemaphoreGive(Sx1262Instance.mutex);
            res = true;
        }
    } else {
        res = false;
        LOG_ERROR(SX1262, "MutexInitError");
    }
#endif
    return res;
}

/*SetDIO3AsTCXOCtrl*/
bool sx1262_set_dio3_as_tcxo_ctrl(Dio3Vol_t vol_code, uint32_t delay) {
    bool res = true;
    uint8_t tx_array[4];
    uint32_t delayValue = (float)delay / 15.625;
    tx_array[1] = (uint8_t)((delayValue >> 16) & 0xFF);
    tx_array[2] = (uint8_t)((delayValue >> 8) & 0xFF);
    tx_array[3] = (uint8_t)(delayValue & 0xFF);
    tx_array[0] = vol_code;
    res = sx1262_send_opcode(OPCODE_SET_DIO3_AS_TCXO_CTRL, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

Sx1262_t Sx1262Instance = {0};

bool sx1262_wait_on_busy(uint32_t time_out_ms) {
    uint32_t start_ms = 0U;
    uint32_t curr_ms = 0U;
    uint32_t diff_ms = 0U;
    bool res = false;
    bool loop = true;
    uint32_t busy_value = 0;
    start_ms = tim_get_ms();
    while(loop) {
        busy_value = gpio_read(DIO_SX1262_BUSY);
        if(0 == busy_value) {
            res = true;
            loop = false;
            break;
        }
        curr_ms = tim_get_ms();
        diff_ms = curr_ms - start_ms;
        if(time_out_ms < diff_ms) {
            res = false;
            loop = false;
            break;
        }
    }
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(SX1262, "WaitBusyErr");
#endif
    }
    return res;
}

bool sx1262_is_connected(void) {
    bool res = false;
    uint64_t read_sync_word = 0;

    res = sx1262_get_packet_type(&Sx1262Instance.packet_type, &Sx1262Instance.dev_status.byte);
    if(res) {
        if(Sx1262Instance.packet_type != PACKET_TYPE_UNDEF) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(SX1262, "PaketTypeErr");
#endif
        }
    }

    res = sx1262_get_sync_word(&read_sync_word);
    if((Sx1262Instance.GfskParam.set_sync_word == read_sync_word) && (true == res)) {
#ifdef HAS_LOG
        LOG_PARN(GFSK, "SyncWordMatch");
#endif
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(GFSK, "SyncWordMisMatch 0x%llx!=0x%llx", Sx1262Instance.GfskParam.set_sync_word, read_sync_word);
#endif
        res = false;
    }

    return res;
}

static bool check_sync_word(uint64_t sync_word) {
    bool res = false;
    uint64_t read_sync_word = 0;
    res = sx1262_set_sync_word(sync_word);
    if(res) {
        res = sx1262_get_sync_word(&read_sync_word);
        if(res) {
            if(sync_word == read_sync_word) {
#ifdef HAS_LOG
                LOG_INFO(SX1262, "Sx1262 Connected!");
#endif
                res = true;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(SX1262, "Set:0x%llx Read:0x%llx", sync_word, read_sync_word);
#endif
                res = false;
            }
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(LORA, "Set:0x%llx Err", sync_word);
#endif
    }
    return res;
}

bool sx1262_is_exist(void) {
    bool res = false;
    res = check_sync_word(0x0012345678abcdef);
    if(true == res) {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "ChipExist");
#endif
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(SX1262, "ChipLack");
#endif
        res = false;
    }
    return res;
}

static bool sx1262_send_opcode_proc(uint8_t op_code, uint8_t* tx_array, uint16_t tx_array_len, uint8_t* out_rx_array,
                                    uint16_t rx_array_len) {
#ifdef HAS_LOG
    LOG_PARN(SX1262, "%s() OpCode:0x%x %s", __FUNCTION__, op_code, OpCodeToStr(op_code));
#endif
    bool res = false;
    if((tx_array_len + OPCODE_SIZE) < (2 * FIFO_SIZE)) {
        res = true;
        static uint8_t tempTxArray[2 * FIFO_SIZE];
        tempTxArray[0] = op_code;
        uint16_t temp_tx_arr_len = tx_array_len + OPCODE_SIZE;

        if((NULL != tx_array) && (0 < tx_array_len)) {
            memcpy(&tempTxArray[1], tx_array, temp_tx_arr_len);
        }

        res = spi_write((SpiName_t)SX1262_SPI_NUM, tempTxArray, temp_tx_arr_len) && res;
        if((0 < rx_array_len) && (NULL != out_rx_array)) {
            res = spi_read((SpiName_t)SX1262_SPI_NUM, out_rx_array, rx_array_len) && res;
        }
    }
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(LORA, "OpCodeProckError 0x%02x", op_code);
#endif
    }

    return res;
}

/*SendOpCode*/
bool sx1262_send_opcode(uint8_t op_code, uint8_t* tx_array, uint16_t tx_array_len, uint8_t* rx_array,
                        uint16_t rx_array_len) {
#ifdef HAS_LOG
    LOG_PARN(SX1262, "SendOpCode 0x%02x %s", op_code, OpCodeToStr(op_code));
#endif
    bool res = false;
    SX1262_CHIP_SELECT(sx1262_send_opcode_proc(op_code, tx_array, tx_array_len, rx_array, rx_array_len));
#ifdef HAS_LOG
    if(false == res) {
        LOG_ERROR(SX1262, "OpCodeError: 0x%02x %s", op_code, OpCodeToStr(op_code));
    }
#endif
    return res;
}

/*SetRxTxFallbackMode*/

/*
  SetRegulatorMode
  By default only the LDO is used. This is useful in low cost applications where the cost
  of the extra self needed for a DC-DC converter is prohibitive.
  Using only a linear regulator implies that the RX or TX current is almost doubled.
  This function allows to specify if DC-DC or LDO is used for power regulation.
  The regulation mode is defined by parameter regModeParam.
 * */
bool sx1262_set_regulator_mode(uint8_t reg_mode_param) {
    bool res = true;
    uint8_t tx_array[1];
    tx_array[0] = reg_mode_param;
    res = sx1262_send_opcode(OPCODE_SET_REGULATOR_MODE, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/*
   SetRfFrequency
   The command SetRfFrequency(...) is used to set the frequency of the RF frequency mode.
*/
bool sx1262_set_rf_frequency(uint32_t rf_frequency_hz, uint32_t freq_xtal_hz) {
    bool res = false;
    double freq_step = ((double)((double)freq_xtal_hz / (double)FREQ_DIV));
#ifdef HAS_LOG
    LOG_INFO(SX1262, "FreqStep: %f", freq_step);
#endif
    uint32_t frf_code = (uint32_t)(((double)rf_frequency_hz) / freq_step);
#ifdef HAS_LOG
    LOG_INFO(SX1262, "RfFreq:%u FreqXtal_hz: %u FrfCode: %u", rf_frequency_hz, freq_xtal_hz, frf_code);
#endif
    uint8_t tx_array[4] = {0};
    Type32Union_t u32val;
    u32val.u32 = frf_code;
    u32val.u32 = reverse_byte_order_uint32(u32val.u32);
    memcpy(tx_array, &u32val.u32, sizeof(u32val.u32));
    res = sx1262_send_opcode(OPCODE_SET_RF_FREQUENCY, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}
/*
  SetBufferBaseAddress

  This command sets the base addresses in the data buffer in all modes of operations
  for the packet handing operation in TX and RX mode. The usage and definition of those
  parameters are described in the different packet type sections.
*/
bool sx1262_set_buffer_base_addr(uint8_t tx_base_addr, uint8_t rx_base_addr) {
#ifdef HAS_LOG
    LOG_PARN(SX1262, "%s()", __FUNCTION__);
#endif
    bool res = false;
    uint8_t tx_array[2] = {0};
    tx_array[0] = tx_base_addr;
    tx_array[1] = rx_base_addr;
    res = sx1262_send_opcode(OPCODE_SET_BUFFER_BASE_ADDR, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

static uint8_t get_prev_circular(uint8_t addr, uint8_t inter) {
    uint8_t val = addr;
    uint8_t i = 0;
    for(i = 0; i < 2; i++) {
        if(0 < val) {
            val -= 1; /*subtraction matters*/
        } else {
            val = 255;
        }
    }
    return val;
}
/*
  GetRxBufferStatus

  This command returns the length of the last received packet (PayloadLengthRx)
  and the address of the first byte received (rx_start_buffer_pointer).
  It is applicable to all modems. The address is an offset relative to the first byte of the data buffer.
  */
bool sx1262_get_rxbuff_status(uint8_t* out_payload_length_rx, uint8_t* out_rx_start_buffer_pointer) {
    bool res = false;
    // uint8_t tx_array[3];
    // memset(tx_array, 0xFF, sizeof(tx_array));
    uint8_t rx_array[4];
    memset(rx_array, 0xFF, sizeof(rx_array));
    res = sx1262_send_opcode(OPCODE_GET_RX_BUFFER_STATUS, NULL, 0, rx_array, sizeof(rx_array));
    if(res) {
        Sx1262Instance.status = rx_array[1];
        if(out_payload_length_rx) {
            *out_payload_length_rx = rx_array[2];
        }
        if(out_rx_start_buffer_pointer) {
            *out_rx_start_buffer_pointer = rx_array[3];
#if 1
            *out_rx_start_buffer_pointer = get_prev_circular(*out_rx_start_buffer_pointer, 2);
#endif
        }
    }
    return res;
}
/*
  SetRx
  The command SetRx() sets the device in receiver mode.
 * */
bool sx1262_start_rx(uint32_t timeout_s) {
#ifdef HAS_LOG
    LOG_PARN(SX1262, "StartRx");
#endif
    bool res = true;
    res = sx1262_clear_fifo() && res;
    res = sx1262_set_buffer_base_addr(TX_BASE_ADDRESS, RX_BASE_ADDRESS) && res;
    res = sx1262_set_rx_gain((RxGain_t)Sx1262Instance.rx_gain) && res;
    uint8_t tx_array[3];
    /*from senior byte to junior byte*/
    // uint32_t timeout_s_be = reverse_byte_order_uint24(timeout_s);
    // timeout_s_be = timeout_s_be<<8;
    // memcpy(tx_array,&timeout_s_be,3);
    // LOG_DEBUG(GFSK,"timeout_s 0x%08x timeout_s_be 0x%08x",timeout_s,timeout_s_be);

    tx_array[0] = MASK_8BIT & (timeout_s >> 16);
    tx_array[1] = MASK_8BIT & (timeout_s >> 8);
    tx_array[2] = MASK_8BIT & (timeout_s);

    res = sx1262_send_opcode(OPCODE_SET_RX, tx_array, sizeof(tx_array), NULL, 0) && res;
#ifdef HAS_LOG
    LOG_DEBUG(SX1262, "StartRx");
#endif
    return res;
}

bool is_power_valid(int8_t power) {
    bool res = false;
    if((-7 <= power) && (power <= 22)) {
        res = true;
    }
    return res;
}
/*
   SetTxParams
   Set output power and ramp time for the PA
   This command sets the TX output power by using the parameter power and the TX ramping
   time by using the parameter RampTime. This command is available for all protocols selected.
*/
bool sx1262_set_tx_params(int8_t power, uint8_t ramp_time) {
#ifdef HAS_LOG
    LOG_DEBUG(SX1262, "SetTxParams");
#endif
    bool res = false;
    res = is_power_valid(power);
    if(false == res) {
        power = DFLT_OUT_POWER;
    }
    uint8_t tx_array[2] = {0};
    tx_array[0] = (uint8_t)power;
    tx_array[1] = ramp_time;
    res = sx1262_send_opcode(OPCODE_SET_TX_PARAMS, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/*SetDIO2AsRfSwitchCtrl*/
bool sx1262_set_dio2_as_rf_switch_ctrl(Dio2Mode_t mode) {
    bool res = false;
    uint8_t tx_array[1] = {0};
    tx_array[0] = (uint8_t)mode;
    res = sx1262_send_opcode(OPCODE_SET_DIO2_AS_RFSWITCH, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/* SetPacketParams
 * This command is used to set the parameters of the packet handling block.
 * */
bool sx1262_set_lora_packet_params(LoRaPacketParam_t* lora) {
#ifdef HAS_LOG
    LOG_PARN(LORA, "SetPacketParams");
#endif
    bool res = false;
    if(lora) {
        uint8_t tx_array[9];
        memset(tx_array, 0xFF, sizeof(tx_array));
        uint16_t preamble_length_be = 0;
        preamble_length_be = reverse_byte_order_uint16(lora->preamble_length);
        memcpy(tx_array, &preamble_length_be, 2);
        tx_array[2] = lora->header_type;
        tx_array[3] = lora->payload_length;
        tx_array[4] = lora->crc_type;
        tx_array[5] = lora->invert_iq;
        res = sx1262_send_opcode(OPCODE_SET_PACKET_PARAMS, tx_array, 6, NULL, 0);
    }

    return res;
}

/* SetPacketParams
 * This command is used to set the parameters of the packet handling block.
 * */
bool sx1262_set_packet_params(PacketParam_t* packParam) {
#ifdef HAS_LOG
    LOG_PARN(SX1262, "%s()", __FUNCTION__);
#endif
    bool res = false;
    switch(packParam->packet_type) {
#ifdef HAS_LORA
    case PACKET_TYPE_LORA:
        res = sx1262_set_lora_packet_params(&packParam->proto.lora);
        break;
#endif /*HAS_LORA*/
#ifdef HAS_GFSK
    case PACKET_TYPE_GFSK:
        res = sx1262_set_gfsk_packet_params(&packParam->proto.gfsk);
        break;
#endif /*HAS_GFSK*/
    default:
        res = false;
        break;
    }
    return res;
}

/*
  ResetStats
  This command resets the value read by the command GetStats.
  To execute this command, the OpCode is 0x00 followed by 6 zeros (so 7 zeros in total).
*/
bool sx1262_reset_stats(void) {
    bool res = false;
    uint8_t tx_array[6] = {0};
    memset(tx_array, 0x00, sizeof(tx_array));
    res = sx1262_send_opcode(OPCODE_RESET_STATS, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/*
  SetStandby
  cli: sxo 0x80 0x01 0
  The command SetStandby(...) is used to set the device in a configuration mode which is at an
  intermediate level of consumption. In this mode, the chip is placed in halt mode waiting for
  instructions via SPI. This mode is dedicated to chip configuration using high level commands such as
  SetPacketType(...).

  By default, after battery insertion or reset operation (pin NRESET goes low), the chip will enter in STDBY_RC mode
  running with a 13 MHz RC clock.
*/
bool sx1262_set_standby(StandbyMode_t stdby_config) {
#ifdef HAS_LOG
    LOG_DEBUG(SX1262, "SetStandby");
#endif
    bool res = true;
    uint8_t tx_array[1];
    tx_array[0] = (uint8_t)stdby_config;
    res = sx1262_send_opcode(OPCODE_SET_STANDBY, tx_array, sizeof(tx_array), NULL, 0);
    StandbyMode_t stdby_read;
    stdby_read = sx1262_get_standby();
    if(stdby_read != stdby_config) {
        LOG_ERROR(SX1262, "StandbySetErr: Set:%s Read:%s", StandbyToStr(stdby_config), StandbyToStr(stdby_read));
    } else {
        LOG_INFO(SX1262, "StandbySetOk: %s", StandbyToStr(stdby_read));
    }
    return res;
}

StandbyMode_t sx1262_get_standby(void) {
    StandbyMode_t standby_mode = STDBY_UNFED;
    Sx1262Status_t dev_status;
    dev_status.byte = 0;
    bool res = sx1262_get_status(&dev_status.byte);
    if(res) {
        switch(dev_status.chip_mode) {
        case CHP_MODE_STBY_RC:
            standby_mode = STDBY_RC;
            break;
        case CHP_MODE_STBY_XOSC:
            standby_mode = STDBY_XOSC;
            break;
        default:
            standby_mode = STDBY_UNFED;
            break;
        }
    }
    return standby_mode;
}

/*
  SetPacketType

  The command SetPacketType(...) sets the SX1261 radio in LoRa® or in FSK mode.
  The command SetPacketType(...) must be the first of the radio configuration sequence.
  The parameter for this command is PacketType.
*/
bool sx1262_set_packet_type(RadioPacketType_t packet_type) {

    LOG_INFO(SX1262, "SetPackType %u %s", packet_type, WireLessIfToStr(packet_type));

    bool res = false;
    res = sx1262_set_standby(STDBY_RC);
    if(res) {
        uint8_t tx_array[1];
        tx_array[0] = packet_type;
        res = sx1262_send_opcode(OPCODE_SET_PACKET_TYPE, tx_array, sizeof(tx_array), NULL, 0);
    }

    return res;
}

/*
  SetDioIrqParams
  This command is used to set the IRQ flag.
*/
bool sx1262_set_dio_irq_params(uint16_t irqMask, uint16_t dio1Mask, uint16_t dio2Mask, uint16_t dio3Mask) {
    bool res = false;
    Type64Union_t u64val;
    u64val.u16[3] = reverse_byte_order_uint16(irqMask);
    u64val.u16[2] = reverse_byte_order_uint16(dio1Mask);
    u64val.u16[1] = reverse_byte_order_uint16(dio2Mask);
    u64val.u16[0] = reverse_byte_order_uint16(dio3Mask);
    res = sx1262_send_opcode(OPCODE_SET_DIO_IRQ_PARAMS, &u64val.u8[0], sizeof(Type64Union_t), NULL, 0);
    return res;
}
/*
  ClearDeviceErrors
  This commands clears all the errors recorded in the device.
  The errors can not be cleared independently.
*/
bool sx1262_clear_dev_error(void) {
    bool res = false;
    uint8_t tx_array[2];
    memset(tx_array, 0x00, sizeof(tx_array));
    uint8_t rx_array[3];
    memset(rx_array, 0x00, sizeof(rx_array));
    res = sx1262_send_opcode(OPCODE_CLEAR_DEVICE_ERRORS, tx_array, sizeof(tx_array), rx_array, sizeof(rx_array));
    if(res) {
        Sx1262Instance.status = rx_array[1];
    }
    return res;
}
/*
  ClearIrqStatus 0x02
  sxo 0x02 0xFFFF 0
  This command clears an IRQ flag in the IRQ register.
  */
bool sx1262_clear_irq(uint16_t clear_irq_param) {
    bool res = false;
    uint16_t clear_irq_param_be;
    uint8_t tx_array[2];
    memset(tx_array, 0xFF, sizeof(tx_array));
    clear_irq_param_be = reverse_byte_order_uint16(clear_irq_param);
    memcpy(tx_array, &clear_irq_param_be, sizeof(uint16_t));
    res = sx1262_send_opcode(OPCODE_CLEAR_IRQ_STATUS, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

bool sx1262_clear_fifo(void) {
    bool res = false;
    LOG_DEBUG(SX1262, "ClnFiFo");
    uint8_t tx_array[TX_SIZE + 1];
    memset(tx_array, 0x00, sizeof(tx_array));
    res = sx1262_send_opcode(OPCODE_WRITE_BUFFER, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/*SetCadParams*/
bool sx1262_set_cad_params(CadNunSym_t cad_symbol_num, uint8_t cad_det_peak, /*See App Application note AN1200.48 */
                           uint8_t cad_det_min,                              /*See App Application note AN1200.48 */
                           CadExtMode_t cad_exit_mode, uint32_t cad_timeout) {
    bool res = false;
    uint8_t tx_array[7]; /**/
    memset(tx_array, 0x00, sizeof(tx_array));
    tx_array[0] = (uint8_t)cad_symbol_num;
    tx_array[1] = (uint8_t)cad_det_peak;
    tx_array[2] = (uint8_t)cad_det_min;
    tx_array[3] = (uint8_t)cad_exit_mode;
    uint32_t cad_timeout_be = reverse_byte_order_uint24(cad_timeout);
    memcpy(&tx_array[4], &cad_timeout_be, 3);
    res = sx1262_send_opcode(OPCODE_SET_CAD_PARAM, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/*

  The command SetModulationParams(...) is used to configure the modulation parameters of the radio.
  Depending on the packet type selected prior to calling this function, the parameters will
  be interpreted differently by the chip.
*/
bool sx1262_set_modulation_params(Sx1262_t* instance) {
    bool res = false;
    switch(instance->packet_param.packet_type) {
#ifdef HAS_LORA
    case PACKET_TYPE_LORA:
        res = sx1262_set_lora_modulation_params(&instance->lora_mod_params);
        break;
#endif
#ifdef HAS_GFSK
    case PACKET_TYPE_GFSK:
        res = sx1262_set_gfsk_modulation_params(&instance->gfsk_mod_params);
        break;
#endif /*HAS_GFSK*/
    default:
        res = false;
        break;
    }

    return res;
}

/*
  SetSleep
  The command SetSleep(...) is used to set the device in SLEEP mode with the lowest current consumption possible. This
  command can be sent only while in STDBY mode (STDBY_RC or STDBY_XOSC). After the rising edge of NSS, all blocks are
  switched OFF except the backup regulator if needed and the blocks specified in the parameter sleepConfig.
*/
bool sx1262_set_sleep(uint8_t sleep_config) {
    bool res = false;
    uint8_t tx_array[1];
    tx_array[0] = sleep_config;
    res = sx1262_send_opcode(OPCODE_SET_SLEEP, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

/* SetPaConfig
 * SetPaConfig is the command which is used to differentiate the SX1261 from the SX1262.
 * When using this command, the user selects the PA to be used by the device as well as
 * its configuration.
 */
bool sx1262_set_pa_config(uint8_t pa_duty_cycle, uint8_t hp_max, uint8_t device_sel, uint8_t pa_lut) {
#ifdef HAS_LOG
    LOG_DEBUG(SX1262, "SetPaConfig");
#endif
    bool res = false;
    /*For SX1262, paDutyCycle should not be higher than 0x04.*/
    if(pa_duty_cycle <= 0x04) {
        uint8_t tx_array[4];
        memset(tx_array, 0x00, sizeof(tx_array));
        tx_array[0] = pa_duty_cycle;
        tx_array[1] = hp_max;
        tx_array[2] = device_sel;
        tx_array[3] = pa_lut;
        res = sx1262_send_opcode(OPCODE_SET_PA_CONFIG, tx_array, sizeof(tx_array), NULL, 0);
    }
    return res;
}

/*WriteBuffer*/
bool sx1262_write_buffer(uint8_t offset, uint8_t* payload, uint16_t payload_len) {
    bool res = false;
    if((NULL != payload) && (payload_len <= FIFO_SIZE)) {
        static uint8_t tx_array[FIFO_SIZE + 1];
        memset(tx_array, 0x00, sizeof(tx_array));
        tx_array[0] = offset;
        memcpy(&tx_array[1], payload, payload_len);
        res = sx1262_send_opcode(OPCODE_WRITE_BUFFER, tx_array, payload_len + 1, NULL, 0);
    }
    return res;
}

bool sx1262_set_payload(uint8_t* payload, uint8_t size) {
    bool res = false;
    res = sx1262_write_buffer(TX_BASE_ADDRESS, payload, size);
    return res;
}

static bool calc_power_param(uint8_t output_power_dbm, uint8_t* pa_duty_cycle, uint8_t* hp_max) {
    bool res = false;
    switch(output_power_dbm) {
    case 22:
        (*pa_duty_cycle) = 0x04;
        (*hp_max) = 0x07;
        res = true;
        break;
    case 20:
        (*pa_duty_cycle) = 0x03;
        (*hp_max) = 0x05;
        res = true;
        break;
    case 17:
        (*pa_duty_cycle) = 0x02;
        (*hp_max) = 0x03;
        res = true;
        break;
    case 14:
        (*pa_duty_cycle) = 0x02;
        (*hp_max) = 0x02;
        res = true;
        break;
    default:
        LOG_ERROR(SX1262, "WrongPower: %d dBm %6.3f W", output_power_dbm, dbm2watts(output_power_dbm));
        *pa_duty_cycle = 0x04;
        *hp_max = 0x07;
        res = false;
        break;
    }
    return res;
}

static bool sx1262_conf_tx(int8_t output_power_dbm) {
#ifdef HAS_LOG
    LOG_PARN(SX1262, "%s()", __FUNCTION__);
#endif
    // page 100
    // 14.3 Circuit Configuration for Basic Rx Operation
    bool res = true;
    res = is_power_valid(output_power_dbm);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(SX1262, "InvaOutPwr: %d dBm %6.3f W", output_power_dbm, dbm2watts(output_power_dbm));
#endif
        output_power_dbm = DFLT_OUT_POWER;
    } else {
        LOG_INFO(SX1262, "OutPwr: %d dBm %6.3f W", output_power_dbm, dbm2watts(output_power_dbm));
    }

    uint8_t pa_duty_cycle = 0;
    uint8_t hp_max = 0;
    res = calc_power_param(output_power_dbm, &pa_duty_cycle, &hp_max);
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "OutPwr: %d dBm %6.3f W", output_power_dbm, dbm2watts(output_power_dbm));
#endif
    } else {
        LOG_ERROR(SX1262, "WrongPower: %d dBm %6.3f W", output_power_dbm, dbm2watts(output_power_dbm));
#ifdef HAS_LOG
        LOG_WARNING(SX1262, "DfltOutPwr: %d dBm %6.3f W", DFLT_OUT_POWER, dbm2watts(DFLT_OUT_POWER));
#endif
    }
    res = sx1262_set_pa_config(pa_duty_cycle, hp_max, DEV_SEL_SX1262, 0x01) && res;
    res = sx1262_set_tx_params(output_power_dbm, SET_RAMP_3400US) && res;
    res = sx1262_set_buffer_base_addr(TX_BASE_ADDRESS, RX_BASE_ADDRESS) && res;

    return res;
}
#if 0
bool sx1262_conf_rx(void) {
    // page 100
    // 14.3 Circuit Configuration for Basic Rx Operation
    bool res = true;
    // res = sx1262_start_rx(RX_CONTINUOUS_MODE) && res;
    return res;
}
#endif

bool sx1262_wakeup(void) {
    uint8_t status = 0;
    bool res = true;
    res = sx1262_get_status(&status) && res;
    res = sx1262_set_standby(STDBY_RC) && res;
    return res;
}

static bool sx1262_init_gpio(void) {
    bool res = true;
#ifdef CC26X2
    GPIO_setConfig(CONF_GPIO_LORA_RST, gpio_get_cfg_dio(DIO_SX1262_RST));
    GPIO_setConfig(CONF_GPIO_LORA_CS, gpio_get_cfg_dio(DIO_SX1262_SS));
    GPIO_setConfig(CONF_GPIO_LORA_BSY, gpio_get_cfg_dio(DIO_SX1262_BUSY));

    GPIO_setConfig(CONF_GPIO_LORA_INT, gpio_get_cfg_dio(DIO_SX1262_INT));
    GPIO_setCallback(CONF_GPIO_LORA_INT, dio28_fall_call_back);
    GPIO_enableInt(CONF_GPIO_LORA_INT);
#endif

    gpio_set_state(DIO_SX1262_SS, 1);
    gpio_set_state(DIO_SX1262_RST, 1);
    return res;
}

bool sx1262_reset(void) {
    bool res = true;
    gpio_set_state(DIO_SX1262_RST, 1);
    wait_ms(20);
    gpio_set_state(DIO_SX1262_RST, 0);
    wait_ms(50);
    gpio_set_state(DIO_SX1262_RST, 1);
    wait_ms(20);
    return res;
}

bool sx1262_int_isr(Sx1262_t* sx1262Instance) {
    bool res = false;
    if(sx1262Instance) {
        res = true;
        sx1262Instance->int_cnt++;
    }

    return res;
}

float dbm2watts(int32_t dbm) {
    float watts = 0.0f;
    watts = powf(10.0f, ((float)dbm) / 10.0f) / 1000.0f;
    return watts;
}
#if 0
#ifdef HAS_LOG
#define LOAD_PARAM(PAR_ID, VARIABLE, EXP_LEN, VAR_NAME, DEF_VAL, PARSER_FUNC)                                          \
    do {                                                                                                               \
        uint16_t file_len = 0;                                                                                         \
        res = flash_fs_get(PAR_ID, (uint8_t*)&VARIABLE, sizeof(VARIABLE), &file_len);                                  \
        if((true == res) && ((EXP_LEN) == file_len)) {                                                                 \
            LOG_INFO(SX1262, "Set" VAR_NAME "FromParams %u [%s]", VARIABLE, PARSER_FUNC(VARIABLE));                    \
        } else {                                                                                                       \
            LOG_WARNING(SX1262, "SetDflt" VAR_NAME " %u [%s]", VARIABLE, PARSER_FUNC(DEF_VAL));                        \
            VARIABLE = DEF_VAL;                                                                                        \
            res = false;                                                                                               \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0);
#else
#define LOAD_PARAM(PAR_ID, VARIABLE, EXP_LEN, VAR_NAME, DEF_VAL, PARSER_FUNC)                                          \
    do {                                                                                                               \
        uint16_t file_len = 0;                                                                                         \
        res = flash_fs_get(PAR_ID, (uint8_t*)&VARIABLE, sizeof(VARIABLE), &file_len);                                  \
        if(!((true == res) && ((EXP_LEN) == file_len))) {                                                              \
            VARIABLE = DEF_VAL;                                                                                        \
            res = false;                                                                                               \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0);
#endif
#endif

/*SetTx*/
static bool sx1262_set_tx(uint32_t timeout_s) {
    bool res = true;
    uint8_t buff[3];
    /*from senior byte to junior byte*/
    // uint32_t timeout_s_be = reverse_byte_order_uint24(timeout_s);
    // timeout_s_be=timeout_s_be<<8;
    // LOG_INFO(SX1262,"timeout_s 0x%08x timeout_s_be 0x%08x",timeout_s,timeout_s_be);
    // memcpy(buff,&timeout_s_be,3);
    buff[0] = MASK_8BIT & (timeout_s >> 16);
    buff[1] = MASK_8BIT & (timeout_s >> 8);
    buff[2] = MASK_8BIT & (timeout_s);
    res = sx1262_send_opcode(OPCODE_SET_TX, buff, 3, NULL, 0) && res;
    return res;
}

bool sx1262_start_tx(uint8_t* tx_buf, uint16_t tx_len, uint32_t timeout_s) {
    bool res = true;
    if(false == Sx1262Instance.tx_mute) {
        if(Sx1262Instance.tx_done) {
            Sx1262Instance.tx_done = false;
            if((NULL != tx_buf) && (0 < tx_len) && (tx_len <= SX1262_MAX_FRAME_SIZE)) {
                Sx1262Instance.cnt.byte_tx += tx_len;
                res = sx1262_clear_fifo();
                res = sx1262_set_buffer_base_addr(TX_BASE_ADDRESS, RX_BASE_ADDRESS) && res;
                res = sx1262_set_payload(tx_buf, tx_len) && res;
                // Sx1262Instance.packet_param.proto.lora.payload_length = tx_len;
                // res = sx1262_set_packet_params(&Sx1262Instance.packet_param);
#ifdef HAS_LOG
                LOG_DEBUG(SX1262, "TxLen:%u", tx_len);
                if(Sx1262Instance.tx_debug) {
                    print_mem(tx_buf, tx_len, true, false, true, true);
                }
#endif
            } else {
                LOG_ERROR(SX1262, "TxLenErr:%u Max%u", tx_len, SX1262_MAX_FRAME_SIZE);
                res = false;
            }
            if(res) {
                // res = sx1262_write_buffer(offset, tx_buf, tx_len) && res;
#ifdef HAS_SX1262_BIT_RATE
                Sx1262Instance.tx_last_size = tx_len;
                Sx1262Instance.tx_start_time_stamp_ms = tim_get_ms();
#endif          /*HAS_SX1262_BIT_RATE*/
                /*TODO: Set Red Led on*/
#ifdef LED_INDEX_RED
                led_on(&Led[LED_INDEX_RED]);
#endif
#ifdef HAS_HARVESTER_V1
                /*Workaround*/
                gpio_set_state(DIO_GNSS_SAFEBOOT_N, 0);
#endif
                res = sx1262_set_tx(timeout_s);
                if(res) {
                    Sx1262Instance.tx_size_max = max8u(Sx1262Instance.tx_size_max, tx_len);
                } else {
                    LOG_ERROR(SX1262, "SetTx");
                }
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(SX1262, "BusyTxInProc");
#endif
            Sx1262Instance.err_tx_busy_cnt++;
            res = false;
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(SX1262, "TxMuteLen:%u byte", tx_len);
#endif
        res = false;
    }
    return res;
}

/*GetIrqStatus
 * sxo 0x12 0 3
 * sxo 0x12 0x000000 3*/
bool sx1262_get_irq_status(Sx1262IRQs_t* out_irq_stat) {
    bool res = false;
    uint8_t rx_array[4];
    memset(rx_array, 0xFF, sizeof(rx_array));
    res = sx1262_send_opcode(OPCODE_GET_IRQ_STATUS, NULL, 0, rx_array, sizeof(rx_array));
    if(res) {
        uint16_t irq_stat = 0;
        Sx1262Instance.status = rx_array[1]; /*Diag Status*/
        memcpy(&irq_stat, &rx_array[2], 2);
        // irq_stat = reverse_byte_order_uint16(irq_stat);
        out_irq_stat->word = irq_stat;
    }
    return res;
}

/*
  GetDeviceErrors
  This commands returns possible errors flag that could occur
  during different chip operation as described below.
 */
bool sx1262_get_dev_err(uint16_t* op_error) {
    bool res = false;
    uint8_t rx_array[4];
    memset(rx_array, 0x00, sizeof(rx_array));
    res = sx1262_send_opcode(OPCODE_GET_DEVICE_ERRORS, NULL, 0, rx_array, sizeof(rx_array));
    if(res) {
        Sx1262Instance.status = rx_array[1];
        *op_error = copy_and_rev16(&rx_array[2]);
    } else {
        *op_error = 0x0000;
    }

    return res;
}

/*
  GetPacketType
  CLI: sxo 0x11 0x0000 3
  CLI: sxo 0x11 0 3
  The command GetPacketType() returns the current operating packet type of the radio.
*/
bool sx1262_get_packet_type(RadioPacketType_t* const packet_type, uint8_t* status) {
    bool res = false;

    uint8_t tx_array[2];
    memset(tx_array, 0xFF, sizeof(tx_array));
    /*Code Sample from Semtech sends just one NOP byte*/
    uint8_t rx_array[3];
    memset(rx_array, 0xFF, sizeof(rx_array));
    res = sx1262_send_opcode(OPCODE_GET_PACKET_TYPE, tx_array, 1, rx_array, sizeof(rx_array));
    if(res) {
        (*status) = rx_array[1];
        (*packet_type) = (RadioPacketType_t)rx_array[2];
    } else {
        (*packet_type) = PACKET_TYPE_NONE;
    }
    return res;
}

/*
  GetStatus (page 95 in datasheet)
sxo 0xC0 0 2      2a2a
sxo 0xC0 0 1
sxo 0xC0 0x00 1   2a
sxo 0xC0 0x00 2
sxgs
*/
bool sx1262_get_status(uint8_t* out_status) {
    bool res = false;
    if(NULL != out_status) {
#if defined(CC26X2) || defined(HAS_STM32)
        uint8_t tx_array = 0x00;
        /*Code Sample from Semtech sends just 0 NOP bytes*/
        uint8_t rx_array[2] = {0xFF, 0xFF};
        res = sx1262_send_opcode(OPCODE_GET_STATUS, &tx_array, 0, rx_array, sizeof(rx_array));
        if(res) {
            (*out_status) = rx_array[1];
        }
#endif
#ifdef ESP32
        uint8_t tx_array = 0x00;
        uint8_t rx_array[2] = {0xFF, 0xFF};
        res = sx1262_send_opcode(OPCODE_GET_STATUS, &tx_array, 1, rx_array, sizeof(rx_array));
        if(res) {
            (*out_status) = rx_array[1];
        }

        // uint8_t rx_array = 0x00;
        // res = sx1262_send_opcode(OPCODE_GET_STATUS, NULL, 0, &rx_array, 1);
        //*out_status = rx_array;
#endif

#if 0
        uint8_t rx_array[1] = {0x00};
        // uint8_t tx_array = 0xFF;
        res = sx1262_send_opcode(OPCODE_GET_STATUS, NULL, 0, &rx_array[0], sizeof(rx_array));
        *out_status = rx_array[0];
#endif
    }
    return res;
}

/*
 GetPacketStatus
 * */

bool sx1262_get_packet_status(Sx1262_t* instance) {
    bool res = false;
    if(instance) {
        uint8_t rx_array[5];
        memset(rx_array, 0xFF, sizeof(rx_array));
        res = sx1262_send_opcode(OPCODE_GET_PACKET_STATUS, NULL, 0, rx_array, sizeof(rx_array));
        if(res) {
            Sx1262Instance.status = rx_array[1];
            switch(instance->packet_param.packet_type) {
#ifdef HAS_GFSK
            case PACKET_TYPE_GFSK: {
                instance->PacketStatus.gfsk.RxStatus.byte = rx_array[2];
                instance->PacketStatus.gfsk.rssi_sync = -rx_array[3] / 2;
                instance->PacketStatus.gfsk.rssi_avg = -rx_array[4] / 2;
                gfsk_proc_rx_status(instance->PacketStatus.gfsk.RxStatus);
            } break;
#endif
#ifdef HAS_LORA
            case PACKET_TYPE_LORA: {
                instance->PacketStatus.lora.rssi_pkt = -rx_array[2] / 2;
                instance->PacketStatus.lora.signal_rssi_pkt = rx_array[3] / 4;
                instance->PacketStatus.lora.snr_pkt = -rx_array[4] / 2;
            } break;
#endif
            case PACKET_TYPE_LR_FHSS: {
                res = false;
            } break;

            default: {
                res = false;
            } break;
            }
        }
    }
    return res;
}

/*GetRssiInst
  Returns the instantaneous measured RSSI while in Rx mode
  */
bool sx1262_get_rssi_inst(int8_t* out_rssi_inst) {
    bool res = false;
    int8_t rssi_inst = 0;
    uint8_t rx_array[3];
    memset(rx_array, 0xFF, sizeof(rx_array));
    res = sx1262_send_opcode(OPCODE_GET_RSSIINST, NULL, 0, rx_array, sizeof(rx_array));
    if(res) {
        Sx1262Instance.status = rx_array[1];
        rssi_inst = -(rx_array[2] >> 1); /*Signal power in dBm*/
        if(NULL != out_rssi_inst) {
            *out_rssi_inst = rssi_inst;
        }
    }
    return res;
}

/*GetStats*/
bool sx1262_get_statistic(Sx1262_t* inst) {
    bool res = false;

    if(inst) {
        uint8_t rx_array[16];
        memset(rx_array, 0xFF, sizeof(rx_array));
        res = sx1262_send_opcode(OPCODE_GET_STATS, NULL, 0, rx_array, sizeof(rx_array));
        if(res) {
            Sx1262Instance.status = rx_array[1];
            switch(inst->packet_param.packet_type) {
#ifdef HAS_LORA
            case PACKET_TYPE_LORA: {
                inst->interface[0].interface = IF_LORA;
                inst->interface[0].nb_pkt_received = copy_and_rev16(&rx_array[2]);
                inst->interface[0].nb_pkt_crc_error = copy_and_rev16(&rx_array[4]);
                inst->interface[0].nb_pkt_header_err = copy_and_rev16(&rx_array[6]);
            } break;
#endif
#ifdef HAS_GFSK
            case PACKET_TYPE_GFSK: {
                inst->interface[1].interface = IF_GFSK;
                inst->interface[1].nb_pkt_received = copy_and_rev16(&rx_array[2]);
                inst->interface[1].nb_pkt_crc_error = copy_and_rev16(&rx_array[4]);
                inst->interface[1].nb_pkt_length_error = copy_and_rev16(&rx_array[6]);
            } break;
#endif
            default: {
            } break;
            }
        }
    }
    return res;
}

static bool sx1262_proc_irq_status(Sx1262IRQs_t* irq_status) {
    bool res = false;
    if(irq_status) {
        if(0 < (MASK_10BIT & irq_status->word)) {
            Sx1262Instance.irq_cnt.total += (uint16_t)count_set_bits((uint32_t)MASK_10BIT & irq_status->word);
            res = true;
        }

        if(irq_status->TxDone) {
            Sx1262Instance.irq_cnt.tx_done++;
            LOG_DEBUG(SX1262, "TxDoneIrq");
#ifdef HAS_TBFP_RETX
            res = tbfp_retx_tx_done(IF_SX1262);
#endif /*HAS_TBFP_RETX*/
        }
        if(irq_status->RxDone) {
            Sx1262Instance.irq_cnt.rx_done++;
            LOG_DEBUG(SX1262, "RxDoneIrq");
            res = sx1262_proc_data_aval();
#ifdef HAS_HARVESTER_V1
            /*Workaround*/
            gpio_set_state(DIO_GNSS_SAFEBOOT_N, 1);
#endif
            res = sx1262_start_rx(RX_CONTINUOUS_MODE);
        }
        if(irq_status->PreambleDetected) {
            Sx1262Instance.irq_cnt.preamble_detected++;
            LOG_DEBUG(SX1262, "PreDetIrq");
        }
        if(irq_status->SyncWordValid) {
            Sx1262Instance.irq_cnt.syncword_valid++;
            LOG_INFO(SX1262, "SyncWordValidIrq");
        }
        if(irq_status->HeaderValid) {
            Sx1262Instance.irq_cnt.header_valid++;
            LOG_INFO(SX1262, "HeaderValidIrq");
        }
        if(irq_status->CrcErr) {
            Sx1262Instance.irq_cnt.crc_err++;
            LOG_ERROR(SX1262, "CrcErrIrq");
        }
        if(irq_status->CadDone) {
            Sx1262Instance.irq_cnt.cad_done++;
            LOG_INFO(SX1262, "CadDoneIrq");
        }
        if(irq_status->CadDetected) {
            Sx1262Instance.irq_cnt.cad_detected++;
            LOG_DEBUG(SX1262, "CadDetIrq");
        }
        if(irq_status->Timeout) {
            Sx1262Instance.irq_cnt.timeout++;
            LOG_DEBUG(SX1262, "TimeOutIrq");
        }
    }
    res = sx1262_clear_irq(0xFFFF);
    return res;
}

/*
  ReadBuffer
  cli: sxrf offset len
  This function allows reading (n-3) bytes of payload received starting at offset.
  Note that the NOP must be sent after sending
  the offset.
 */
bool sx1262_read_buffer(int16_t offset, uint8_t* out_payload, uint16_t payload_len) {
    bool res = false;

    if((out_payload) && (payload_len <= FIFO_SIZE) && (0 <= offset) && (offset <= (FIFO_SIZE - 1))) {
        static uint8_t rx_array[FIFO_SIZE + 3];
        memset(rx_array, 0xFF, sizeof(rx_array));

        uint8_t tx_array[FIFO_SIZE + 3];
        tx_array[0] = (uint8_t)offset;
        res = sx1262_send_opcode(OPCODE_READ_BUFFER, tx_array, payload_len + 1, rx_array, payload_len + 3); //+3 was
        if(res) {
            memcpy(out_payload, &rx_array[3], payload_len);
        }
    }
    return res;
}

bool sx1262_get_rx_payload(uint8_t* out_payload, uint16_t* out_size, uint16_t max_size, uint8_t* crc8) {
    LOG_DEBUG(SX1262, "LoadPayloadFromSPI %u", max_size);
    bool res = false;
    uint16_t rx_payload_len = 0;
    uint8_t len = 0;
    uint8_t calc_crc8 = 0;
    uint8_t rx_start_buffer_pointer = 0;
    res = sx1262_get_rxbuff_status(&len, &rx_start_buffer_pointer); /*Ignore that vals*/
#ifdef HAS_LOG
    if(res) {
        LOG_DEBUG(SX1262, "Start %u RxLen %u", rx_start_buffer_pointer, len);
    }
#endif
    // rx_start_buffer_pointer = 0; /*We know RX base in compile time*/
    rx_payload_len = 255; /* One LoRa Frame Must contain one TBFP frame!*/
    // rx_payload_len = len; // Just for stream of bytes. (unreliable).
    if(rx_payload_len <= max_size) {
        res = sx1262_read_buffer(rx_start_buffer_pointer, out_payload, (uint16_t)rx_payload_len);
        *out_size = rx_payload_len;
        calc_crc8 = crc8_sae_j1850_calc(out_payload, rx_payload_len);
        *crc8 = calc_crc8;
    } else {
        *out_size = 0;
    }
    return res;
}

static bool sx1262_proc_chip_mode(ChipMode_t chip_mode) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(SX1262, "ChipMode %u %s", chip_mode, chip_mode2str(chip_mode));
#endif
    static ChipMode_t prev_chip_mode = CHP_MODE_UNDEF;
    static uint32_t chip_mode_rc = 0;
    static uint32_t chip_mode_xosc = 0;
    static uint32_t chip_mode_fs = 0;
    static uint32_t chip_mode_tx = 0;
    if(chip_mode != prev_chip_mode) {
#ifdef HAS_LOG
        LOG_DEBUG(SX1262, "ChipMode:%u %s", chip_mode, chip_mode2str(chip_mode));
#endif
    }

    switch(chip_mode) {
    case CHP_MODE_STBY_RC: {
        if(prev_chip_mode == chip_mode) {
            chip_mode_rc++;
            res = false;
        } else {
            chip_mode_rc = 0;
        }
        if(40 < chip_mode_rc) {
            chip_mode_rc = 0;
#ifdef HAS_LOG
            LOG_WARNING(SX1262, "Hang on in STBY_RC");
#endif
            res = sx1262_init();
        }
    } break;
    case CHP_MODE_STBY_XOSC: {
        if(prev_chip_mode == chip_mode) {
            chip_mode_xosc++;
            res = false;
        } else {
            chip_mode_xosc = 0;
        }
        if(100 < chip_mode_xosc) {
            chip_mode_xosc = 0;
#ifdef HAS_LOG
            LOG_WARNING(SX1262, "Hang on in STBY_XOSC");
#endif
            res = sx1262_init();
        }
    } break;
    case CHP_MODE_FS: {
        if(prev_chip_mode == chip_mode) {
            chip_mode_fs++;
            res = false;
        } else {
            chip_mode_fs = 0;
        }
        if(100000 < chip_mode_fs) {
            chip_mode_fs = 0;
#ifdef HAS_LOG
            LOG_WARNING(SX1262, "Hang on in FS");
#endif
            res = sx1262_init();
        }
    } break;
    case CHP_MODE_RX: {
        int8_t rssi_inst = 0;
        Sx1262Instance.tx_done = true;
        res = sx1262_get_rssi_inst(&rssi_inst);
        if(res) {
            Sx1262Instance.rssi_inst = rssi_inst;
        }
    } break;
    case CHP_MODE_TX: {
        if(prev_chip_mode == chip_mode) {
            chip_mode_tx++;
            res = false;
        } else {
            chip_mode_tx = 0;
        }
        if(1000 < chip_mode_tx) {
            chip_mode_tx = 0;
#ifdef HAS_LOG
            LOG_WARNING(SX1262, "HangOnInTx");
#endif
            res = sx1262_init();
        }
    } break;

    default:
        res = false;
        break;
    }
    prev_chip_mode = chip_mode;
    return res;
}

#ifdef HAS_SX1262_BIT_RATE
static bool sx1262_calc_bit_rate(uint32_t bytes, float* tx_real_bit_rate, uint32_t* tx_duration_ms) {
    bool res = false;
    float bit_rate = 0.0f;
    uint32_t duration_ms = 0;
    uint32_t tx_done_time_stamp_ms = tim_get_ms();
    duration_ms = tx_done_time_stamp_ms - Sx1262Instance.tx_start_time_stamp_ms;
    bit_rate = ((float)(bytes * 8 * 1000)) / (((float)duration_ms));
#ifdef HAS_FLASH_FS
    uint16_t file_len = 0;
    res = flash_fs_get(PAR_ID_MAX_BIT_RATE, (uint8_t*)&Sx1262Instance.tx_max_bit_rate,
                       sizeof(Sx1262Instance.tx_max_bit_rate), &file_len);
#endif
    if(Sx1262Instance.tx_max_bit_rate < bit_rate) {
        Sx1262Instance.tx_max_bit_rate = bit_rate;
#ifdef HAS_FLASH_FS
        res = flash_fs_set(PAR_ID_MAX_BIT_RATE, (uint8_t*)&Sx1262Instance.tx_max_bit_rate,
                           sizeof(Sx1262Instance.tx_max_bit_rate));
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(SX1262, "SaveMaxLoRaBitRateErr");
#endif
        }
#endif
    }
    if(tx_real_bit_rate && tx_duration_ms) {
        *tx_real_bit_rate = bit_rate;
        *tx_duration_ms = duration_ms;
    }
    return res;
}
#endif /*HAS_SX1262_BIT_RATE*/

bool sx1262_proc_data_aval(void) {
    bool res = false;

    uint16_t rx_size = 0;
    uint8_t rx_payload[RX_SIZE + 1] = {0};
    memset(rx_payload, 0x00, sizeof(rx_payload));
    Sx1262Instance.rx_done_cnt++;

    rx_size = 0;
    uint8_t cur_crc8 = 0;
    res = sx1262_get_rx_payload(rx_payload, &rx_size, RX_SIZE, &cur_crc8);
    if(res) {
        res = is_arr_pat(rx_payload, rx_size, 0x00);
        if(false == res) {
            Sx1262Instance.cnt.byte_rx += rx_size;
            res = sx1262_clear_fifo();

            Sx1262Instance.rx_size_max = max8u(Sx1262Instance.rx_size_max, rx_size);

            if(Sx1262Instance.debug) {
#ifdef HAS_LOG
                LOG_INFO(SX1262, "Rx %u byte", rx_size);
                res = print_mem(rx_payload, rx_size, Sx1262Instance.show_bin, Sx1262Instance.show_ascii, true,
                                Sx1262Instance.is_packet);
#endif
            }
#ifdef HAS_LORA
            res = radio_proc_payload(rx_payload, rx_size);
#endif /*HAS_LORA*/
            // led_blink(&Led[LED_INDEX_RED], 10);
        } else {
            LOG_INFO(SX1262, "AllZeros %u bytes", rx_size);
        }

    } else {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "DataReadErr");
#endif
    }
    return res;
}

static bool sx1262_poll_status(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(SX1262, "PollStatus");
#endif
    Sx1262_t tempSx1262Instance = {0};
    memset(&tempSx1262Instance, 0x00, sizeof(tempSx1262Instance));

    uint32_t int_diff = Sx1262Instance.int_cnt - Sx1262Instance.int_cnt_prev;
    Sx1262Instance.int_cnt_prev = Sx1262Instance.int_cnt;
    if(0 < int_diff) {
        LOG_DEBUG(SX1262, "NewIntCnt: +%u", int_diff);
    }
    tempSx1262Instance.irq_stat.word = 0;
    res = sx1262_get_irq_status(&tempSx1262Instance.irq_stat);
    if(res) {
        Sx1262Instance.irq_stat = tempSx1262Instance.irq_stat;
        sx1262_proc_irq_status(&tempSx1262Instance.irq_stat);
        // Sx1262Instance.irq_stat.word = 0;
    }

    // RadioPacketType_t packet_type = PACKET_TYPE_UNDEF;
    // res = sx1262_get_packet_type(&packet_type, &tempSx1262Instance.dev_status.byte);
    res = sx1262_get_status(&tempSx1262Instance.dev_status.byte);
    if(res) {
#ifdef HAS_LOG
        LOG_PARN(SX1262, "Status 0x%02x CmdStat:%s ChipMode:%s", tempSx1262Instance.dev_status.byte,
                 cmd_stat2str(tempSx1262Instance.dev_status.command_status),
                 chip_mode2str(tempSx1262Instance.dev_status.chip_mode));
#endif
        res = true;
        static uint8_t stat_byte_prev = 0;
        Sx1262Instance.dev_status.byte = tempSx1262Instance.dev_status.byte;
        if(Sx1262Instance.dev_status.byte != stat_byte_prev) {
#ifdef HAS_LOG
            LOG_DEBUG(SX1262, "Status:0x%02x Mode:%s Cmd:%s", Sx1262Instance.dev_status.byte,
                      chip_mode2str(Sx1262Instance.dev_status.chip_mode),
                      cmd_stat2str(Sx1262Instance.dev_status.command_status)); /**/
#endif
        }
        stat_byte_prev = Sx1262Instance.dev_status.byte;
        // Sx1262Instance.com_stat = extract_subval_from_8bit(tempSx1262Instance.dev_status, 3, 1);
        switch(Sx1262Instance.dev_status.command_status) {
        case COM_STAT_DATA_AVAIL: {
            res = sx1262_proc_data_aval();
            res = sx1262_start_rx(RX_CONTINUOUS_MODE);
        } break;
        case COM_STAT_COM_TIMEOUT:
#ifdef HAS_LOG
            LOG_WARNING(SX1262, "timeOut");
#endif
            res = false;
            break;
        case COM_STAT_COM_PROC_ERR:
            /*Too frequent call*/
            // LOG_ERROR(SX1262,"Error");
            Sx1262Instance.processing_error++;
            res = false;
            break;
        case COM_STAT_EXE_ERR:
#ifdef HAS_LOG
            LOG_ERROR(SX1262, "FailureToExecuteCommand %u", Sx1262Instance.dev_status.command_status); /**/
#endif
            res = false;
            break;
        case COM_STAT_COM_TX_DONE: {
            Sx1262Instance.tx_done = true;
            Sx1262Instance.tx_done_time_stamp_ms = tim_get_ms();
#ifdef HAS_TBFP_RETX
            res = tbfp_retx_tx_done(IF_SX1262);
#endif /*HAS_TBFP_RETX*/
#ifdef LED_INDEX_RED
            led_off(&Led[LED_INDEX_RED]);
#endif /*LED_INDEX_RED*/
#ifdef HAS_SX1262_BIT_RATE
            float tx_real_bit_rate = 0.0;
            uint32_t tx_duration_ms = 0;
            sx1262_calc_bit_rate(Sx1262Instance.tx_last_size, &tx_real_bit_rate, &tx_duration_ms);
#endif /*HAS_SX1262_BIT_RATE*/

#ifdef HAS_SX1262_BIT_RATE
#ifdef HAS_LOG
            LOG_DEBUG(SX1262, "TxDone %7.1f bit/s=%7.1f byte/s duration: %u ms for %u bytes", tx_real_bit_rate,
                      tx_real_bit_rate / 8, tx_duration_ms, Sx1262Instance.tx_last_size);
#endif
#else
#ifdef HAS_LOG
            LOG_DEBUG(SX1262, "TxDone");
#endif
#endif /*HAS_SX1262_BIT_RATE*/

            Sx1262Instance.tx_done_cnt++;
            LoRaInterface.tx_done_cnt++;
            res = sx1262_start_rx(RX_CONTINUOUS_MODE);
        } break;
        default:
            res = false;
            break;
        }
        // Sx1262Instance.chip_mode = (ChipMode_t)extract_subval_from_8bit(tempSx1262Instance.dev_status, 6, 4);

        res = sx1262_proc_chip_mode((ChipMode_t)Sx1262Instance.dev_status.chip_mode);

        res = sx1262_reset_stats();
    } else {
        LOG_ERROR(SX1262, "GetStatusErr");
    }
    if(Sx1262Instance.sync_rssi) {
        res = sx1262_get_packet_status(&Sx1262Instance);
    }
    return res;
}

static inline bool sx1262_sync_registers(void) {
    bool res = false;
    Sx1262_t tempSx1262Instance = {0};
    memset(&tempSx1262Instance, 0x00, sizeof(tempSx1262Instance));

    tempSx1262Instance.rx_payload_len = 0;
    tempSx1262Instance.rx_buffer_pointer = 0;
    res = sx1262_get_rxbuff_status(&tempSx1262Instance.rx_payload_len, &tempSx1262Instance.rx_buffer_pointer);
    if(res) {
        Sx1262Instance.rx_payload_len = tempSx1262Instance.rx_payload_len;
        Sx1262Instance.rx_buffer_pointer = tempSx1262Instance.rx_buffer_pointer;
    }
#ifdef HAS_SX1262_POLL

    memset(&tempSx1262Instance.interface, 0x0, sizeof(tempSx1262Instance.interface));

    res = sx1262_get_statistic(&tempSx1262Instance);
    if(res) {
        memcpy(&(Sx1262Instance.interface[0]), &(tempSx1262Instance.interface[0]),
               sizeof(tempSx1262Instance.interface));
    }

    tempSx1262Instance.op_error = 0;
    res = sx1262_get_dev_err(&tempSx1262Instance.op_error);
    if(res) {
        // proc_dev_err(op_error);
        Sx1262Instance.op_error = tempSx1262Instance.op_error;
    }
#endif /*HAS_SX1262_POLL*/

    tempSx1262Instance.GfskParam.get_sync_word = 0;
    res = sx1262_get_sync_word(&tempSx1262Instance.GfskParam.get_sync_word);
    if(res) {
        Sx1262Instance.GfskParam.get_sync_word = tempSx1262Instance.GfskParam.get_sync_word;
    }

    Sx1262Instance.wire_int = (uint8_t)gpio_read(DIO_SX1262_INT);
    Sx1262Instance.wire_busy = (uint8_t)gpio_read(DIO_SX1262_BUSY);
    Sx1262Instance.wire_nss = (uint8_t)gpio_read(DIO_SX1262_SS);
    Sx1262Instance.wire_rst = (uint8_t)gpio_read(DIO_SX1262_RST);

    tempSx1262Instance.packet_type = PACKET_TYPE_UNDEF;
    res = sx1262_get_packet_type(&tempSx1262Instance.packet_type, &Sx1262Instance.status);
    if(res) {
        Sx1262Instance.packet_type = tempSx1262Instance.packet_type;
    }
    tempSx1262Instance.rand_num = 0;
    res = sx1262_get_rand(&tempSx1262Instance.rand_num);
    if(res) {
        Sx1262Instance.rand_num = tempSx1262Instance.rand_num;
    }
    return res;
}

/* poll sx1262 registers. Move data from transceiver REG to MCU RAM.
 * verify transceiver and notify user if needed
 * */
bool sx1262_process(void) {
    bool res = false;
    if(Sx1262Instance.init_done) {

#ifdef HAS_LOG
        LOG_PARN(SX1262, "CheckConnectivity=%u", Sx1262Instance.check_connectivity);
#endif
#ifdef HAS_SX1262_RETX
        res = sx1216_retx_proc();
#endif

        if(Sx1262Instance.check_connectivity) {
            res = sx1262_is_connected();
        } else {
            res = true;
        }
        if(res) {
            if(BUSY_CNT_LIMIT < Sx1262Instance.busy_cnt) {
                Sx1262Instance.busy_cnt = 0;
                res = sx1262_init();
            }
#ifdef HAS_TBFP
            uint32_t cur_time_stamp_ms = tim_get_ms();
            res = lora_transmit_from_queue(cur_time_stamp_ms, Sx1262Instance.tx_done_time_stamp_ms, 50,
                                           MAX_LORA_PAYLOAD_SIZE);
#endif

            res = sx1262_poll_status();
            if(Sx1262Instance.sync_reg) {
                res = sx1262_sync_registers();
            }

        } else {
#ifdef HAS_LOG
            LOG_ERROR(SX1262, "Sx1262_SpiLinkLost");
#endif
            res = sx1262_init();
        }
    }

    return res;
}

#ifdef HAS_FREE_RTOS
static void sx1262_thread(void* arg) {
    while(1) {
        if(Sx1262Instance.proc) {
            sx1262_process();
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}
#endif /*HAS_FREE_RTOS*/

static bool sx1262_set_tx_clamp_config_workarround(void) {
    bool res = false;
    uint8_t tx_clamp_config = 0;
    res = sx1262_get_tx_clamp_config(&tx_clamp_config);
    if(res) {
        tx_clamp_config |= 0x1E;
        res = sx1262_set_tx_clamp_config(tx_clamp_config);
    }
    return res;
}

/*see 15.1.2 Workaround 0x08D8*/
static bool sx1262_workarround2(void) {
    bool res = false;
    uint8_t reg_val = 0;
    res = sx1262_read_reg(REG_TX_MODULATION, &reg_val);
    if(res) {
        reg_val |= (1 << 2);
        res = sx1262_write_reg(REG_TX_MODULATION, reg_val);
    }
    return res;
}

bool sx1262_init(void) {
    bool res = true;
    static uint8_t call_cnt = 0;
    if(0 == call_cnt) {
        memset(&Sx1262Instance, 0x00, sizeof(Sx1262Instance));
    }
    Sx1262Instance.tx_mute = false;
#ifdef HAS_FREE_RTOS
    Sx1262Instance.mutex = xSemaphoreCreateMutexStatic(&Sx1262Instance.xMutexBuffer);
    if(NULL == Sx1262Instance.mutex) {
        res = false;
        LOG_ERROR(SX1262, "MutexInitError");
    } else {
        LOG_INFO(SX1262, "MutexInitOk");
    }
#endif
#ifdef ESP32
    Sx1262Instance.proc = true;
    // res = set_log_level(SX1262, LOG_LEVEL_DEBUG);
    // Sx1262Instance.debug = true;
    Sx1262Instance.show_ascii = false;
    // Sx1262Instance.show_bin = true;
    Sx1262Instance.check_connectivity = false;
#else
#ifdef HAS_LOG
    res = set_log_level(LORA, LOG_LEVEL_INFO);
    res = set_log_level(GFSK, LOG_LEVEL_DEBUG);
#endif
    Sx1262Instance.check_connectivity = false;
    Sx1262Instance.show_bin = false;
    Sx1262Instance.tx_mute = false;
#endif /*ESP32*/
    res = sx1262_retx_init();

#ifdef HAS_LOG
    LOG_INFO(SX1262, "InitSX1262...");
#endif
    Sx1262Instance.sync_rssi = true;
    call_cnt = 1;
    Sx1262Instance.tx_done = true;
#ifdef HAS_LORA
    res = sx1262_load_params(&Sx1262Instance);
    if(false == res) {
#ifdef HAS_LOG
        LOG_WARNING(SX1262, "LackOfParam");
#endif
    }
#endif
    res = sx1262_set_tx_clamp_config_workarround();
    if(res) {
        LOG_WARNING(SX1262, "txClampConfigOk");
    } else {
        LOG_WARNING(SX1262, "txClampConfigErr");
    }
    Sx1262Instance.bit_rate = 0;
#ifdef HAS_LORA
    Sx1262Instance.bit_rate =
        lora_calc_data_rate(Sx1262Instance.lora_mod_params.spreading_factor, Sx1262Instance.lora_mod_params.band_width,
                            Sx1262Instance.lora_mod_params.coding_rate);
#endif

#ifdef HAS_LOG
    LOG_INFO(SX1262, "data rate %f bit/s %f byte/s", Sx1262Instance.bit_rate, Sx1262Instance.bit_rate / 8);
#endif

#ifdef HAS_LEGAL_BAND_CHECK
    uint32_t bandwidth_hz = 0;
#ifdef HAS_LORA
    bandwidth_hz = bandwidth2num(Sx1262Instance.lora_mod_params.band_width);
    res = is_band_legal(Sx1262Instance.rf_frequency_hz, bandwidth_hz);
#endif
    if(false == res) {
#ifdef HAS_LOG
        LOG_WARNING(SX1262, "illegal frequencies %u...%u Hz", Sx1262Instance.rf_frequency_hz - bandwidth_hz / 2,
                    Sx1262Instance.rf_frequency_hz + bandwidth_hz / 2);
#endif
    } else {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "frequency setting are legal %u...%u Hz", Sx1262Instance.rf_frequency_hz - bandwidth_hz / 2,
                 Sx1262Instance.rf_frequency_hz + bandwidth_hz / 2);
#endif
    }
#endif /*HAS_LEGAL_BAND_CHECK*/
    gpio_set_state(DIO_SX1262_SS, 1);
    res = sx1262_init_gpio() && res;
#ifdef HAS_LOG
    LOG_WARNING(SX1262, "StartWaitBusy");
#endif
    res = sx1262_reset() && res;
    res = sx1262_wait_on_busy(10000);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(SX1262, "ChipBusy");
#endif
    } else {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "ChipSpare!");
#endif
    }

    if(res) {
        res = sx1262_is_exist();
    }
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(SX1262, "Config...");
#endif
        res = sx1262_wakeup() && res;

        res = sx1262_set_packet_type(Sx1262Instance.packet_param.packet_type) && res;

        res = sx1262_set_rf_frequency(Sx1262Instance.rf_frequency_hz, XTAL_FREQ_HZ) && res;

        res = sx1262_set_regulator_mode(REG_MODE_ONLY_LDO) && res;
        // res = sx1262_set_regulator_mode(REG_MODE_DC_DC_LDO) && res;

        res = sx1262_clear_fifo() && res;
        res = sx1262_set_buffer_base_addr(TX_BASE_ADDRESS, RX_BASE_ADDRESS) && res;

        res = sx1262_clear_dev_error() && res;
#ifdef ESP32
        res = sx1262_set_dio3_as_tcxo_ctrl(DIO3_OUTPUTS_1_6_V, 5000);
#endif
        res = sx1262_set_packet_type(Sx1262Instance.packet_param.packet_type) && res;

        res = sx1262_set_standby(STDBY_XOSC);

#ifdef HAS_LOG
        if(false == res) {
            LOG_ERROR(SX1262, "SetStandByErr");
        }
#endif

        res = sx1262_set_modulation_params(&Sx1262Instance) && res;
#ifdef HAS_LOG
        if(false == res) {
            LOG_ERROR(SX1262, "SX1262SetModParErr");
        }
#endif

        res = sx1262_set_packet_params(&Sx1262Instance.packet_param) && res;
        if(false == res) {
            LOG_ERROR(SX1262, "SetPktParamErr");
        }

        if(PACKET_TYPE_GFSK == Sx1262Instance.packet_param.packet_type) {
            res = sx1262_workarround2() && res;
        }

        res = sx1262_set_dio_irq_params(IQR_MAIN_INT, IQR_MAIN_INT, IQR_MAIN_INT, IQR_MAIN_INT) && res;
        res = sx1262_set_dio2_as_rf_switch_ctrl(DIO2_RF_SW) && res;
#ifdef HAS_GFSK
        res = sx1262_set_whitening_init_value(Sx1262Instance.GfskParam.whitening_init);
        if(false == res) {
            LOG_ERROR(SX1262, "SetWhitenInitValErr");
        }
        res = sx1262_write_reg(REG_BROADCAST_ADDR, Sx1262Instance.GfskParam.broadcast_addr) && res;
        res = sx1262_write_reg(REG_NODE_ADDR, Sx1262Instance.GfskParam.node_addr) && res;
#endif
        res = sx1262_set_sync_word(Sx1262Instance.GfskParam.set_sync_word) && res;
        res = sx1262_set_crc_poly(Sx1262Instance.crc_poly) && res;
        res = sx1262_set_crc_seed(Sx1262Instance.crc_init) && res;
        res = sx1262_set_lora_sync_word(Sx1262Instance.lora_sync_word_set) && res;

        res = sx1262_start_rx(RX_CONTINUOUS_MODE) && res;
        if(res) {
#ifdef HAS_LOG
            LOG_INFO(SX1262, "StartRx");
#endif
        }

        res = sx1262_conf_tx(Sx1262Instance.output_power) && res;
        // res = sx1262_conf_rx() && res;

        // Sx1262Instance.set_sync_word = SYNC_WORD;

        Sx1262Instance.sync_reg = true;
        res = sx1262_start_rx(RX_CONTINUOUS_MODE) && res;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(SX1262, "SX1262LinkErr");
#endif
    }
    if(false == res) {
        task_data[TASK_ID_LORA].on = false;
    }
    // Sx1262Instance.check_connectivity = true;
    if(true == res) {
#ifdef HAS_FREE_RTOS
        xTaskCreate(sx1262_thread, "sx1262", 5000, NULL, 6, NULL);
#endif /*HAS_FREE_RTOS*/
    }
    Sx1262Instance.init_done = res;
    return res;
}

/*SetFs*/
bool sx1262_set_fs(void) {
    bool res = false;
    res = sx1262_send_opcode(OPCODE_SET_FS, NULL, 0, NULL, 0);
    return res;
}

#ifdef HAS_PARAM
bool sx1262_set_modulation(uint16_t modulation) {
    bool res = false;
    uint8_t ok_flag = 0;
#ifdef HAS_LORA
    ModeInfoId_t LinkInfoId;
    LinkInfoId.id = modulation;
    uint8_t val = 0;
    res = is_valid_spreading_factor((SpreadingFactor_t)LinkInfoId.spreading_factor);
    if(res) {
        val = LinkInfoId.spreading_factor;
        res = param_set(PAR_ID_LORA_SF, (uint8_t*)&val);
        if(res) {
            SET_BIT_NUM(ok_flag, 0);
        }
    }

    res = is_valid_bandwidth((BandWidth_t)LinkInfoId.band_width);
    if(res) {
        val = LinkInfoId.band_width;
        res = param_set(PAR_ID_LORA_BW, (uint8_t*)&val);
        if(res) {
            SET_BIT_NUM(ok_flag, 1);
        }
    }

    res = is_valid_coding_rate((LoRaCodingRate_t)LinkInfoId.coding_rate);
    if(res) {
        val = LinkInfoId.coding_rate;
        res = param_set(PAR_ID_LORA_CR, (uint8_t*)&val);
        if(res) {
            SET_BIT_NUM(ok_flag, 2);
        }
    }
#endif

    if(0x07 == ok_flag) {
        res = sx1262_init();
        if(res) {
            SET_BIT_NUM(ok_flag, 3);
        }
    }

    if(0x0F == ok_flag) {
        res = true;
    } else {
        LOG_ERROR(SX1262, "flag: 0x%x=%u", ok_flag, ok_flag);
        res = false;
    }

    return res;
}
#endif

uint32_t calc_fresnel_zone(uint32_t freq_hz, uint32_t distance_m) {
    uint32_t freznel_radius_m = 0;
    double distance_km = ((double)distance_m) / 1000.0;
    double freq_ghz = ((double)freq_hz) / 1000000000.0;
    freznel_radius_m = 8.657 * sqrt(distance_km / freq_ghz);
    return freznel_radius_m;
}

double sx1262_calc_tx_time(Sx1262_t* inst) {
    double tx_time = 0.0;
    if(inst) {
        switch(inst->packet_param.packet_type) {
#ifdef HAS_GFSK
        case PACKET_TYPE_GFSK: {
            tx_time = gfsk_calc_max_frame_tx_time(inst->gfsk_mod_params.bit_rate,
                                                  inst->packet_param.proto.gfsk.preamble_length,
                                                  SyncWordLenCode2Len(inst->packet_param.proto.gfsk.syncword_length),
                                                  GfskCrcType2Len(inst->packet_param.proto.gfsk.crc_type));
        } break;
#endif
#ifdef HAS_LORA
        case PACKET_TYPE_LORA: {
            tx_time = lora_calc_max_frame_tx_time(
                Sx1262Instance.lora_mod_params.spreading_factor, Sx1262Instance.lora_mod_params.band_width,
                Sx1262Instance.lora_mod_params.coding_rate, Sx1262Instance.packet_param.proto.lora.preamble_length,
                Sx1262Instance.packet_param.proto.lora.header_type,
                Sx1262Instance.lora_mod_params.low_data_rate_optimization, NULL, NULL);
        } break;
#endif
        case PACKET_TYPE_LR_FHSS: {
            tx_time = 1.0;
        } break;
        default: {
            tx_time = 0.0;
        } break;
        }
    }
    return tx_time;
}

/*SetTxContinuousWave*/
bool sx1262_set_tx_con_wave(void) {
    bool res = false;
    res = sx1262_send_opcode(OPCODE_SET_TX_CARRIER, NULL, 0, NULL, 0);
    return res;
}

/*SetCad Channel Activity Detection
  Set chip into RX mode with passed CAD parameters
*/
bool sx1262_set_cad(void) {
    bool res = false;
    res = sx1262_send_opcode(OPCODE_SET_CAD, NULL, 0, NULL, 0);
    return res;
}

bool sx1262_check(void) {
    bool res = false;
    uint32_t int_cnt_diff = 0;
    static uint32_t int_cnt_prev = 0;
    int_cnt_diff = Sx1262Instance.int_cnt - int_cnt_prev;
    int_cnt_prev = Sx1262Instance.int_cnt;
    if(0 == int_cnt_diff) {
        LOG_DEBUG(HMON, "LackSx1262GpioInts");
    }
    return res;
}

bool sx1262_calc_byte_rate(void) {
    Sx1262Instance.rx_rate.cur = Sx1262Instance.cnt.byte_rx - Sx1262Instance.cnt_prev.byte_rx;
    Sx1262Instance.rx_rate.min = min32u(Sx1262Instance.rx_rate.min, Sx1262Instance.rx_rate.cur);
    Sx1262Instance.rx_rate.max = max32u(Sx1262Instance.rx_rate.max, Sx1262Instance.rx_rate.cur);
    Sx1262Instance.cnt_prev.byte_rx = Sx1262Instance.cnt.byte_rx;
    Sx1262Instance.tx_rate.cur = Sx1262Instance.cnt.byte_tx - Sx1262Instance.cnt_prev.byte_tx;
    Sx1262Instance.tx_rate.min = min32u(Sx1262Instance.tx_rate.min, Sx1262Instance.tx_rate.cur);
    Sx1262Instance.tx_rate.max = max32u(Sx1262Instance.tx_rate.max, Sx1262Instance.tx_rate.cur);
    Sx1262Instance.cnt_prev.byte_tx = Sx1262Instance.cnt.byte_tx;
    return true;
}

/*
 StopTimerOnPreamble
 * */
