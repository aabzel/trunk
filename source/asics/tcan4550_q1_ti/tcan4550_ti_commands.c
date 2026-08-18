
#include "tcan4550_ti_commands.h"

#include <stdio.h>

#include "TCAN4550.h"
#include "TCAN4x5x_Data_Structs.h"
#include "TCAN_hl.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "io_utils.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"

bool tcan4550_ti_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = init_tcan();
        if(res) {
            LOG_INFO(CAN, "init OK");
        } else {
            LOG_ERROR(CAN, "init fail");
        }

    } else {
        LOG_ERROR(CAN, "Usage: ci");
    }
    return res;
}

bool tcan4550_ti_read_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t address = 0;
    uint32_t reg_val = 0;
    if(1 == argc) {
        res = try_str2uint16(argv[0], &address);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract address %s", argv[0]);
        }
    } else {
        LOG_ERROR(CAN, "Usage: crr addr");
    }
    if(true == res) {
        reg_val = AHB_READ_32(address);
        if(res) {
            io_printf("0x%08x 0b%s" CRLF, reg_val, utoa_bin32(reg_val));
        } else {
            LOG_ERROR(CAN, "read error");
        }
    }
    return res;
}

bool tcan4550_ti_set_mode_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dev_mode = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dev_mode);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract mode %s", argv[0]);
        }
    }

    if(res && (1 == argc)) {
        TCAN4x5x_Device_SetMode((TCAN4x5x_Device_Mode_Enum)dev_mode);
        if(res) {
            LOG_INFO(CAN, "OK ");
        } else {
            LOG_ERROR(CAN, "err");
        }
    } else {
        LOG_ERROR(CAN, "Usage: csm mode");
    }
    return res;
}

bool tcan4550_ti_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t address = 0;
    uint8_t len = 0;
    uint8_t data[32] = "";
    memset(data, 0xFF, sizeof(data));
    if(2 == argc) {
        res = try_str2uint16(argv[0], &address);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract address %s", argv[0]);
        }
        res = try_str2uint8(argv[1], &len);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract len %s", argv[1]);
        }
    } else {
        LOG_ERROR(CAN, "Usage: cr addr len");
    }
    if(true == res) {

        if(res) {
            print_mem(data, sizeof(data), true, true, true, true);
        } else {
            LOG_ERROR(CAN, "read error");
        }
    }
    return res;
}

bool tcan4550_ti_write_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t address = 0;
    uint32_t reg_val = 0;
    if(1 <= argc) {
        res = try_str2uint16(argv[0], &address);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract address %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &reg_val);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract reg_val %s", argv[1]);
        }
    }

    if((true == res) && (2 == argc)) {
        AHB_WRITE_32(address, reg_val);
        LOG_INFO(CAN, "write addr 0x%x val 0x%x ok", address, reg_val);

    } else {
        LOG_ERROR(CAN, "Usage: cwr addr reg");
    }
    return res;
}

bool tcan4550_ti_clear_mram_command(int32_t argc, char* argv[]) {
    bool res = false;
    TCAN4x5x_MRAM_Clear();
    return res;
}
// cs 0x55 0x1122334455667788

bool tcan4550_ti_send(uint16_t id, uint64_t data64) {
    bool res = true;

    Type64Union_t un64 = {0};
    un64.u64 = data64; // Define the data payload
    /* Define the CAN message we want to send*/
    TCAN4x5x_MCAN_TX_Header header = {0}; // Remember to initialize to 0, or you'll get random garbage!

    header.DLC =
        MCAN_DLC_8B; // Set the DLC to be equal to or less than the data payload (it is ok to pass a 64 byte data array
                     // into the WriteTXFIFO function if your DLC is 8 bytes, only the first 8 bytes will be read)
    header.ID = id;  // Set the ID
    header.FDF = 0;  // CAN FD frame enabled
    header.BRS = 0;  // Bit rate switch enabled
    header.EFC = 0;
    header.MM = 0;
    header.RTR = 0;
    header.XTD = 0; // We are not using an extended ID in this example
    header.ESI = 0; // Error state indicator

    TCAN4x5x_MCAN_WriteTXBuffer(
        0, &header, &un64.u8[0]); // This function actually writes the header and data payload to the TCAN's MRAM in the
                                  // specified TX queue number. It returns the bit necessary to write to TXBAR, but does
                                  // not necessarily require you to use it. In this example, we won't, so that we can
                                  // send the data queued up at a later point.
    TCAN4x5x_MCAN_TransmitBufferContents(
        0); // Now we can send the TX FIFO element 0 data that we had queued up earlier but didn't send.

    return res;
}

bool tcan4550_ti_send_frame_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    uint64_t data64 = 0;
    if(1 <= argc) {
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract id %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint64(argv[1], &data64);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract data %s", argv[1]);
        }
    }

    if(res) {
        res = tcan4550_ti_send(id, data64);
        if(res) {
            LOG_INFO(CAN, "send id: 0x%06x data: 0x%llx ok", id, data64);
        } else {
            LOG_ERROR(CAN, "Unable to send frame");
        }
    }
    return res;
}
