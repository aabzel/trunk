#include "can_misc.h"

#include "can_custom_const.h"

uint8_t CanMacModeToEnableFifo(const CanMacMode_t mac_mode) {
    uint8_t en_fifo = 0;
    switch(mac_mode) {
    case CAN_MAC_MODE_LEGACY_FIFO:
        en_fifo = 1;
        break;
    case CAN_MAC_MODE_ENHANCED_FIFO:
        en_fifo = 1;
        break;
    case CAN_MAC_MODE_MESSAGE_BUFFER:
        en_fifo = 0;
        break;
    default:
        en_fifo = 0;
        break;
    }
    return en_fifo;
}

FLEXCAN_FifoType CanMacModeToFifoType(const CanMacMode_t mac_mode) {
    FLEXCAN_FifoType fifo_type = FLEXCAN_ENHANCED_FIFO;
    switch(mac_mode) {
    case CAN_MAC_MODE_LEGACY_FIFO:
        fifo_type = FLEXCAN_LEGACY_FIFO;
        break;
    case CAN_MAC_MODE_ENHANCED_FIFO:
        fifo_type = FLEXCAN_ENHANCED_FIFO;
        break;
    case CAN_MAC_MODE_MESSAGE_BUFFER:
        fifo_type = FLEXCAN_ENHANCED_FIFO;
        break;
    default:
        fifo_type = FLEXCAN_ENHANCED_FIFO;
        break;
    }
    return fifo_type;
}

bool CanRetToRes(const FLEXCAN_ErrorType ret) {
    bool res = false;
    switch(ret) {
    case FLEXCAN_E_OK:
        res = true;
        break;
    case FLEXCAN_E_INVALID_VERSION:
        res = false;
        break;
    case FLEXCAN_E_FAILED:
        res = false;
        break;
    case FLEXCAN_E_INVALID_PARAM:
        res = false;
        break;
    case FLEXCAN_E_INVALID_SIZE:
        res = false;
        break;
    case FLEXCAN_E_INVALID_SEQUENCE:
        res = false;
        break;
    case FLEXCAN_E_NULL_POINT:
        res = false;
        break;
    case FLEXCAN_E_TIMEOUT:
        res = false;
        break;
    case FLEXCAN_E_BUSY:
        res = false;
        break;
    case FLEXCAN_E_MB_OUTOFRANGE:
        res = false;
        break;
    default:
        break;
    }
    return res;
}

FLEXCAN_ClockSrcType CanClockSourceToClockSrcType(CanClockSource_t clock_source) {
    FLEXCAN_ClockSrcType clock_src_type = FLEXCAN_CLOCK_CANPE;
    switch(clock_source) {
    case CAN_CLOCK_SOURCE_PERIPHERAL:
        clock_src_type = FLEXCAN_CLOCK_CANPE;
        break;
    case CAN_CLOCK_SOURCE_OSCILLATOR:
        clock_src_type = FLEXCAN_CLOCK_INTERFACE;
        break;
    default:
        clock_src_type = FLEXCAN_CLOCK_CANPE;
        break;
    }

    return clock_src_type;
}

CanTxFrame_t CanDataTypeToFrameType(const FLEXCAN_DataType data_type) {
    CanTxFrame_t frame_type = CAN_TX_FRAME_DATA;
    switch(data_type) {
    case FLEXCAN_FRAME_DATA:
        frame_type = CAN_TX_FRAME_DATA;
        break;
    case FLEXCAN_FRAME_REMOTE:
        frame_type = CAN_TX_FRAME_REMOTE;
        break;
    default:
        break;
    }
    return frame_type;
}

FLEXCAN_IdType CanMessageBuffetIdTypeToFrameType(const CanIdentifier_t id_type) {
    FLEXCAN_IdType frame_type = FLEXCAN_ID_STD;
    switch(id_type) {
    case CAN_FRAME_ID_STANDARD:
        frame_type = FLEXCAN_ID_STD;
        break;
    case CAN_FRAME_ID_EXTENDED:
        frame_type = FLEXCAN_ID_EXT;
        break;
    default:
        break;
    }
    return frame_type;
}

uint8_t CanMessageBuffDirToIsTx(const ConnectivitDir_t direction) {
    uint8_t is_tx = 0;
    switch(direction) {
    case CONNECT_DIR_TRANSMIT:
        is_tx = 1;
        break;
    case CONNECT_DIR_RECEIVER:
        is_tx = 0;
        break;
    case CONNECT_DIR_RX_TX:
        is_tx = 1;
        break;
    default:
        is_tx = 0;
        break;
    }
    return is_tx;
}

CanIdentifier_t CanIdTypeToIdentifier(const FLEXCAN_IdType frame_type) {
    CanIdentifier_t id_type = CAN_FRAME_ID_STANDARD;
    switch(frame_type) {
    case FLEXCAN_ID_STD:
        id_type = CAN_FRAME_ID_STANDARD;
        break;
    case FLEXCAN_ID_EXT:
        id_type = CAN_FRAME_ID_EXTENDED;
        break;
    default:
        break;
    }
    return id_type;
}

FLEXCAN_DataType CanFrameTypeToDataType(const CanTxFrame_t frame_type) {
    FLEXCAN_DataType data_type = FLEXCAN_FRAME_DATA;
    switch(frame_type) {
    case CAN_TX_FRAME_DATA:
        data_type = FLEXCAN_FRAME_DATA;
        break;
    case CAN_TX_FRAME_REMOTE:
        data_type = FLEXCAN_FRAME_REMOTE;
        break;
    default:
        data_type = FLEXCAN_FRAME_DATA;
        break;
    }
    return data_type;
}

FLEXCAN_IdType CanMessageIdTyoeToFrameType(const CanIdentifier_t id_type) {
    FLEXCAN_IdType can_id = FLEXCAN_ID_STD;
    switch(id_type) {
    case CAN_FRAME_ID_STANDARD:
        can_id = FLEXCAN_ID_STD;
        break;
    case CAN_FRAME_ID_EXTENDED:
        can_id = FLEXCAN_ID_EXT;
        break;
    default:
        can_id = FLEXCAN_ID_STD;
        break;
    }
    return can_id;
}

#ifdef HAS_CAN_FD
CanFdBitRateSwitch_t CanEnBrsToFdBitRateSwitch(const uint8_t en_brs) {
    CanFdBitRateSwitch_t fd_bit_rate_switch = CAN_FD_BIT_RATE_SWITCH_OFF;
    switch(en_brs) {
    case 1:
        fd_bit_rate_switch = CAN_FD_BIT_RATE_SWITCH_ON;
        break;
    case 0:
        fd_bit_rate_switch = CAN_FD_BIT_RATE_SWITCH_OFF;
        break;
    default:
        break;
    }
    return fd_bit_rate_switch;
}

uint8_t CanFdBitRateSwitchToBrs(const CanFdBitRateSwitch_t bit_rate_switch) {
    uint8_t en_brs = 0;
    switch(bit_rate_switch) {
    case CAN_FD_BIT_RATE_SWITCH_ON:
        en_brs = TRUE;
        break;
    case CAN_FD_BIT_RATE_SWITCH_OFF:
        en_brs = FALSE;
        break;
    default:
        break;
    }
    return en_brs;
}
#endif
