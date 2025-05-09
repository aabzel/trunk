#include "hex_bin.h"

#include <string.h>

#ifdef HAS_PC
#include <stdio.h>
#include <stdlib.h>
#endif

#include "array.h"
#include "byte_utils.h"
#include "convert.h"
#include "crc32.h"
#include "data_utils.h"
#include "file_api.h"
#include "log.h"
#include "std_includes.h"
#include "debug_info.h"
#include "time_mcal.h"
#include "str_utils.h"
#include "byte_utils.h"
#include "macro_utils.h"

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_FW_LOADER
#include "fw_loader.h"
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader.h"
#endif

#ifdef HAS_FILE
//#include "utils_file.h"
#endif

/*
 https://microsin.net/programming/pc/intel-hex-file-format.html
 https://en.wikipedia.org/wiki/Intel_HEX
 */

bool hex_bin_init(void) {
    bool res = false;
    LOG_WARNING(HEX_BIN, "Init");
    res = true;
    return res;
}

bool is_hex_file(const char* const file_name) {
    bool res = false;
    if(file_name) {
        const char* substr = str_case_str(file_name, ".hex");
        if(substr) {
            res = true;
        }
    }
    return res;
}

static bool hex_ceck_crc(const HexFrame_t* const Frame) {
    bool res = false;
    LOG_PARN(HEX_BIN, "CheckCrc8");
    if(Frame) {
#ifdef HAS_HEX_BIN_DIAG
        LOG_PARN(HEX_BIN, "%s", HexFrame2Str(Frame));
#endif
        uint8_t crc_acc = 0;
        uint16_t chksum = 0;
        crc_acc += Frame->rec_len;
        crc_acc += WORD_HI_BYTE(Frame->load_offset);
        crc_acc += WORD_LO_BYTE(Frame->load_offset);
        crc_acc += Frame->rec_type;
        uint16_t i = 0;
        for(i = 0; i < Frame->rec_len; i++) {
            crc_acc += Frame->data[i];
        }

        crc_acc += Frame->crc8.read;

        chksum = 0x100 - crc_acc;
        LOG_PARN(HEX_BIN, "chksum 0x%04x", chksum);
        if(0 == crc_acc) {
            res = true;
            LOG_PARN(HEX_BIN, "Crc8Ok");
        } else {
            res = false;
            LOG_ERROR(HEX_BIN, "Crc8Err 0x%02x", crc_acc);
        }
    }
    return res;
}

static bool hex_flash_write(HexBinHandle_t* const Node) {
    bool res = false;
    if(Node->frame.data) {
        if(Node->frame.rec_len) {
#ifdef HAS_HEX_BIN_DIAG
            LOG_PARN(HEX_BIN, "Write,Addr:0x%08x,Size:%3u Byte,Data:%s",
                     Node->address.u32,
                     Node->frame.rec_len,
                     Data2Str(Node->frame.data, Node->frame.rec_len)
                     );
#endif
            uint32_t relative_adress = Node->address.u32 - Node->base_address;
            uint32_t relative_adress_end = relative_adress + Node->frame.rec_len;
            LOG_PARN(HEX_BIN, "Write,Addr:0x%08x,Size:%3u Byte", relative_adress, Node->frame.rec_len);
            if(relative_adress_end < Node->address_size_byte) {
                res = true;
#ifdef HAS_FW_LOADER
                res = fw_loader_write(Node->fw_loader_num,
                                      relative_adress,
                                      Node->frame.data,
                                      Node->frame.rec_len);
                log_parn_res(HEX_BIN,  res, "FwLoaderWrite");
#endif

#ifdef HAS_FLASH
                res = flash_mcal_write(Node->address.u32, Node->frame.data, Node->frame.rec_len);
                if(res) {
                    LOG_DEBUG(HEX_BIN, "FlashWriteOk Addr:0x%08x.Size:%u", Node->address.u32, Node->frame.rec_len);
                } else {
                    LOG_ERROR(HEX_BIN, "FlashWriteErr Addr:0x%08x.Size:%u", Node->address.u32, Node->frame.rec_len);
                }
#endif /*HAS_FLASH*/

#ifdef HAS_PC
                memcpy(&Node->bin_data[relative_adress], Node->frame.data, Node->frame.rec_len);
#endif
            } else {
                cli_printf(CRLF);
                LOG_ERROR(HEX_BIN, "ArrayOverFlow:RelativeEndAdress:%u,TotalSize:%u Byte", relative_adress_end,
                          Node->address_size_byte);
                res = false;
            }
        } else {
            LOG_ERROR(HEX_BIN, "LenErr");
        }
    } else {
        LOG_ERROR(HEX_BIN, "DataErr");
    }
    return res;
}

static bool hex_continuity_check(HexBinHandle_t* const Node, uint32_t* const dropped_size) {
    bool res = false;
    if(Node->fragment_cnt) {
        if(Node->next_exp_address == Node->address.u32) {
            res = true;
        } else {
            int32_t diff = Node->address.u32 - Node->next_exp_address;
            if(dropped_size) {
                *dropped_size = (uint32_t)diff;
            }
            LOG_WARNING(HEX_BIN, "Line:%u, ContinuityErr! ExpAddr:0x%08x,Cur:0x%08x,DropOut:%d Byte", Node->line_cnt,
                        Node->next_exp_address, Node->address.u32, diff);
            res = false;
        }
    } else {
        res = true;
    }
    Node->next_exp_address = Node->address.u32 + Node->frame.rec_len;
    return res;
}

static bool hex_proc_rec_type(HexBinHandle_t* const Node, bool write) {
    bool res = false;
    switch((uint8_t)Node->frame.rec_type) {
    case HEX_REC_TYPE_DATA_RECORD: {
        Node->address.u16[0] = Node->frame.load_offset;
        if(0 == Node->fragment_cnt) {
            Node->base_address = Node->address.u32;
            cli_printf(CRLF);
            LOG_WARNING(HEX_BIN, "BaseAddr: 0x%08x", Node->base_address);
        }
        uint32_t dropped_size = 0;
        res = hex_continuity_check(Node, &dropped_size);
        if(res) {
            Node->fw_crc23 = crc32_stream_calc(Node->fw_crc23, Node->frame.data, Node->frame.rec_len);
            LOG_PARN(HEX_BIN, "ContinuityOk");
        } else {
            uint32_t i = 0;
            for(i = 0; i < dropped_size; i++) {
                uint8_t zero_byte = 0;
                Node->fw_crc23 = crc32_stream_calc(Node->fw_crc23, &zero_byte, 1);
            }
            LOG_WARNING(HEX_BIN, "DataContinuityViolation");
            res = true;
        }

        if(write) {
            res = hex_flash_write(Node);
            log_parn_res(HEX_BIN, res, "Write");
        } else {

            DATA_UPDATE(Node->address_range, Node->address.u32);
            DATA_UPDATE(Node->address_range, Node->address.u32 + Node->frame.rec_len);
            Node->address_size_byte = Node->address_range.max - Node->address_range.min + 1;
            Node->bin_size_byte += Node->frame.rec_len;
#ifdef HAS_FLASH
            /*code executes on MCU*/
            uint8_t* on_chip_addr = (uint8_t*)Node->address.u32;
            size_t diff = 0;
            res = array_is_equal_ext(on_chip_addr, Node->frame.data, Node->frame.rec_len, &diff);
            if(false == res) {
                /*Diff*/
                res = true;
                Node->diff_size += diff;
                Node->already_the_same = false;
            } else {
                Node->matching_size += Node->frame.rec_len;
                /*Equal*/
            }
#else
            /*code executes on PC*/
            Node->diff_size += Node->frame.rec_len;
            Node->already_the_same = false;
#endif /*HAS_FLASH*/
        }

        Node->fragment_cnt++;
    } break;
    case HEX_REC_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD: {
        uint16_t hi_word = 0;
        memcpy(&hi_word, Node->frame.data, 2);
        Node->address.u16[1] = reverse_byte_order_uint16(hi_word);
        LOG_DEBUG(HEX_BIN, "ExtLinAddrRec: 0x%04x****", Node->address.u16[1]);
        res = true;
    } break;
    case HEX_REC_TYPE_END_OF_FILE_RECORD:
        LOG_WARNING(HEX_BIN, "EndOfFile");
        res = true;
        break;
    case HEX_REC_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD:
        LOG_ERROR(HEX_BIN, "Not implemented");
        res = false;
        break;
    case HEX_REC_TYPE_START_SEGMENT_ADDRESS_RECORD:
        LOG_ERROR(HEX_BIN, "Not implemented");
        res = false;
        break;
    case HEX_REC_TYPE_START_LINEAR_ADDRESS_RECORD: {
        if(4 == Node->frame.rec_len) {
            uint32_t start_addr = 0;
            memcpy(&start_addr, Node->frame.data, 4);
            LOG_WARNING(HEX_BIN, "StartAddr: 0x%08x", reverse_byte_order_uint32(start_addr));
            res = true;
        }
    } break;
    default:
        LOG_ERROR(HEX_BIN, "RecTypeErr 0x%02x", Node->frame.rec_type);
        res = false;
        break;
    }
    return res;
}

bool hex_proc_line(HexBinHandle_t* const Node, bool write) {
    bool res = false;
    if(Node) {
        Node->line_len = strlen(Node->hex_line);
        LOG_PARN(HEX_BIN, "Proc Size:%2u Byte,Line:[%s]", Node->line_len, Node->hex_line);
        if(0 < Node->line_len) {
            Node->line_cnt++;
            log_level_t ll = log_level_get(HEX_BIN);
            if(LOG_LEVEL_DEBUG == ll) {
                str_del_char_inplace(Node->hex_line, '\r');
                str_del_char_inplace(Node->hex_line, '\n');
                LOG_PARN(HEX_BIN, "ProcLine:%3u,[%s]", Node->line_cnt, Node->hex_line);
            }
            res = true;
        } else {
            LOG_ERROR(HEX_BIN, "LenErr %u", Node->line_len);
            res = false;
        }
    }

    if(res) {
        if(':' == Node->hex_line[HEX_LINE_OFFSET_PREAMBLE]) {
            LOG_PARN(HEX_BIN, "SpotRECORD_MARK");
            res = try_strl2uint8_hex(&(Node->hex_line[HEX_LINE_OFFSET_REC_LEN]), 2, &Node->frame.rec_len);
            if(res) {
                LOG_PARN(HEX_BIN, "RecLen:%u Byte", Node->frame.rec_len);
            } else {
                LOG_ERROR(HEX_BIN, "ParseRecLenErr [%s]", &Node->hex_line[HEX_LINE_OFFSET_REC_LEN]);
            }
        } else {
            LOG_ERROR(HEX_BIN, "RECORD MARK Err %c", &Node->hex_line[HEX_LINE_OFFSET_PREAMBLE]);
            res = false;
        }
    }

    if(res) {
        res = try_strl2uint16_hex(&Node->hex_line[HEX_LINE_OFFSET_ADDR_LITTLE], 4, &Node->frame.load_offset);
        if(res) {
            LOG_PARN(HEX_BIN, "Offset:0x%04x", Node->frame.load_offset);
            // Node->address.u16[0]=Node->frame.load_offset;
        } else {
            LOG_ERROR(HEX_BIN, "ParseAddrErr [%s]", &Node->hex_line[HEX_LINE_OFFSET_ADDR_LITTLE]);
        }
    }

    if(res) {
        res = try_strl2uint8_hex(&Node->hex_line[HEX_LINE_OFFSET_REC_TYPE], 2, &Node->frame.rec_type);
        if(res) {
#ifdef HAS_HEX_BIN_DIAG
            LOG_PARN(HEX_BIN, "RecType:%u=%s", Node->frame.rec_type, HexRecType2Str(Node->frame.rec_type));
#endif
        } else {
            LOG_ERROR(HEX_BIN, "ParseAddrErr [%s]", &Node->hex_line[HEX_LINE_OFFSET_REC_TYPE]);
        }
    }

    if(res) {
        if(Node->frame.rec_len) {
            uint32_t out_array_len = 0;
            LOG_PARN(HEX_BIN, "ParseData:%u byte", Node->frame.rec_len * 2);
            res = try_strl2array(&Node->hex_line[HEX_LINE_DATA_OFFSET], Node->frame.rec_len * 2, Node->frame.data,
                                 sizeof(Node->frame.data), &out_array_len);
            if(res) {
                if(Node->frame.rec_len == out_array_len) {
                    LOG_PARN(HEX_BIN, "ParseDataOk");
                    // array_u8_print(Node->frame.data, Node->frame.rec_len);
                    // cli_printf(CRLF);
                } else {
                    LOG_ERROR(HEX_BIN, "ParseDataLenErr [%u] Byte", out_array_len);
                    res = false;
                }
            } else {
                LOG_ERROR(HEX_BIN, "ParseDataErr [%s]", &Node->hex_line[9]);
            }
        }
    }

    if(res) {
        uint8_t crc_index = HEX_LINE_DATA_OFFSET + Node->frame.rec_len * 2;
        res = try_strl2uint8_hex(&Node->hex_line[crc_index], 2, &Node->frame.crc8.read);
        if(res) {
            LOG_PARN(HEX_BIN, "Crc8:0x%x", Node->frame.crc8.read);
        } else {
            LOG_ERROR(HEX_BIN, "ParseCrcErr [%s]", &Node->hex_line[crc_index]);
        }
    }

    if(res) {
        res = hex_ceck_crc(&Node->frame);
        if(res) {
            LOG_PARN(HEX_BIN, "CrcOk");
            res = hex_proc_rec_type(Node, write);
            log_parn_res(HEX_BIN,res,"RecType");
        } else {
            LOG_ERROR(HEX_BIN, "CrcErr");
        }
    }

    return res;
}

static bool hex_init_one(HexBinHandle_t* const Node, const char* const file_name) {
    bool res = false;
    LOG_WARNING(HEX_BIN, "Init");
    if(Node) {
        memset(&Node->frame, 0, sizeof(Node->frame));
        strcpy(Node->hex_line, "");
        strcpy(Node->hex_file_name, "");
        strcpy(Node->only_file_name, "");

#ifdef HAS_PC
        if(Node->bin_data) {
            LOG_WARNING(HEX_BIN, "FreeBinMem");
            free(Node->bin_data);
        }
        Node->bin_data = NULL;
#endif
        Node->fragment_cnt = 0;
        Node->diff_size = 0;
        Node->fw_crc23 = 0;
        Node->bin_size_byte = 0;
        Node->matching_size = 0;
        Node->already_the_same = false;
        Node->address_size_byte = 0;

        res = data_u32_init(&(Node->address_range));

        Node->next_exp_address = 0;

        Node->address.u32 = 0;
        res = is_hex_file(file_name);
        if(res) {
            strncpy(Node->hex_file_name, file_name, sizeof(Node->hex_file_name));
            LOG_INFO(HEX_BIN, "HexFileName [%s]", Node->hex_file_name);

            strncpy(Node->only_file_name, Node->hex_file_name, sizeof(Node->only_file_name));
            str_del_substr_inplace(Node->only_file_name, ".hex");

            LOG_INFO(HEX_BIN, "OnlyFileName [%s]", Node->only_file_name);
        } else {
            LOG_ERROR(HEX_BIN, "InvalidName [%s]", file_name);
        }
    }
    return res;
}

static bool hex_process_lines_of_file(HexBinHandle_t* const Node, bool write) {
    bool res = false;
    LOG_INFO(HEX_BIN, "ProcLines");
    Node->time_stamp.start = MSEC_2_SEC(time_get_ms32());
    res = file_api_open_re(&Node->FileItem, Node->hex_file_name);
    if(res) {
        res = false;
        Node->line_cnt = 0;
        LOG_INFO(HEX_BIN, "File[%s]OpenOk", Node->hex_file_name);

        for(;;) {
            memset(Node->hex_line, 0, sizeof(Node->hex_line));
            size_t read_len = 0;
            res = file_api_gets(&Node->FileItem, Node->hex_line, sizeof(Node->hex_line), &read_len);
            if(res) {
                LOG_PARN(HEX_BIN, "Len:%u,[%s]", read_len, Node->hex_line);
                if(0 < read_len) {
#ifdef HAS_HEX_BIN_DIAG
                    diag_progress_log(Node->line_cnt, Node->total_lines, 400) ;
#endif
                    res = hex_proc_line(Node, write);
                    if(res) {
                        LOG_PARN(HEX_BIN, "ProcOk,Line:%u", Node->line_cnt);
                    } else {
                        LOG_ERROR(HEX_BIN, "ProcErr,Line:%u", Node->line_cnt);
                    }
                } else {
                    LOG_DEBUG(HEX_BIN, "GetLineLenErr,Len:%u Byte,Str:[%s]", read_len, Node->hex_line);
                    // break;
                }
            } else {
                res = true;
                LOG_WARNING(HEX_BIN, "GetStrErr");
                break;
            }
        }
        res = file_api_close(&Node->FileItem);

        LOG_INFO(HEX_BIN, "Close[%s]Ok" CRLF, Node->hex_file_name);
        Node->time_stamp.end = MSEC_2_SEC(time_get_ms32());
        double durtaion_s = Node->time_stamp.end - Node->time_stamp.start;
        LOG_WARNING(HEX_BIN, "Duration:%u S=%f S", (uint32_t)durtaion_s, durtaion_s);
        Node->next_exp_address = 0;
        Node->fragment_cnt = 0;
#ifdef HAS_HEX_BIN_DIAG
        HexNodeDiag(Node);
#endif
        if(Node->matching_size == Node->bin_size_byte) {
            Node->already_the_same = true;
            LOG_WARNING(HEX_BIN, "AlreadyTheSameFirmware: %u Byte", Node->matching_size);
        }
    } else {
        LOG_ERROR(HEX_BIN, "File:[%s]OpenErr", Node->hex_file_name);
        res = false;
    }
    return res;
}

static bool hex_file_calc_fw_size(HexBinHandle_t* const Node) {
    bool res = false;
    Node->bin_size_byte = 0;
    Node->address_size_byte = 0;

    res = hex_process_lines_of_file(Node, false);
    if(res) {
        Node->address_size_byte = Node->address_range.max - Node->address_range.min + 1;
    } else {
        LOG_ERROR(HEX_BIN, "ProcessLinesOfFileErr");
        res = false;
    }
    return res;
}

#ifdef HAS_PC
static bool hex_compose_bin(HexBinHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->bin_data) {
            if(0 < Node->address_size_byte) {
                char lText[80] = {0};
                snprintf(lText, sizeof(lText), "%s_generated.bin", Node->only_file_name);
                LOG_INFO(HEX_BIN, "ComposeBin File:[%s],Size:%u Byte...", lText, Node->address_size_byte);
                res = file_array_to_binary_file(lText, Node->bin_data, Node->address_size_byte);
                log_info_res(HEX_BIN, res, "SaveToBin");
            } else {
                LOG_ERROR(HEX_BIN, "SizeErr");
            }
        } else {
            LOG_ERROR(HEX_BIN, "DataErr");
        }
    } else {
        LOG_ERROR(HEX_BIN, "NodeErr");
    }
    return res;
}
#endif

bool hex_to_bin(HexBinHandle_t* const Node, const char* const file_name) {
    bool res = false;
    LOG_WARNING(HEX_BIN, "Hex->Bin");
    // char hex_line[500] = {0};
    //HexBinHandle_t Item = {0};
    Node->fw_loader_num = 1;
    res = hex_init_one(Node, file_name);
    if(res) {
        Node->total_lines = file_line_cnt(file_name);
        if(0 < Node->total_lines) {

            LOG_INFO(HEX_BIN, "Volume:%u Lines", Node->total_lines);

            res = hex_file_calc_fw_size(Node);
            if(res) {
#ifdef HAS_PC
                Node->bin_data = (uint8_t*)malloc(Node->address_size_byte);
                if(Node->bin_data) {
                    LOG_INFO(HEX_BIN, "Malloc Size:%u Byte=%f kByte Ok", Node->address_size_byte,
                             BYTES_2_KBYTES(Node->address_size_byte));
                    memset(Node->bin_data, 0, Node->address_size_byte);
                } else {
                    LOG_ERROR(HEX_BIN, "MallocErr");
                    res = false;
                }
#endif
            }

            if(res) {
                if(Node->diff_size) {
                    LOG_WARNING(HEX_BIN, "NeedToUpdate", Node->diff_size);
                    /*TODO: Save Origin FW*/
#ifdef HAS_BOOTLOADER
                    /*ClearFlash*/
                    res = bootloader_erase_app();
#endif

                    res = hex_process_lines_of_file(Node, true);
                    if(res) {
#ifdef HAS_PC
                        res = hex_compose_bin(Node);
                        log_info_res(HEX_BIN, res, "ComposeBin");
#endif /*HAS_PC*/

#ifdef HAS_PARAM
                        res = param_set(PAR_ID_APP_LEN, &Node->address_size_byte);
                        res = param_set(PAR_ID_APP_CRC32, &Node->fw_crc23);
#endif /*HAS_PARAM*/

#ifdef HAS_BOOTLOADER
                        res = bootloader_launch_app(BOOTLOADER_CMD_LAUNCH_APP);
#endif
                    }
                }
            } else {
                LOG_ERROR(HEX_BIN, "CntLineErr %d", Node->total_lines);
            }
        }
    } else {
        LOG_ERROR(HEX_BIN, "InitErr");
        res = false;
    }
    return res;
}

bool bin_to_hex(const char* const file_name) {
    bool res = false;
    LOG_WARNING(HEX_BIN, "bin>hex");

    return res;
}
