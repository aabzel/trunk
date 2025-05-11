#include "hex_bin_diag.h"

#include <stdio.h>
#include <string.h>

#include "hex_bin.h"
#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif
#include "log.h"
#include "macro_utils.h"
#include "utils_math.h"

const char* HexRecType2Str(HexRecType_t rec_type) {
    const char* name = "?";
    switch((uint8_t)rec_type) {
    case HEX_REC_TYPE_DATA_RECORD:
        name = "DataRec";
        break;
    case HEX_REC_TYPE_END_OF_FILE_RECORD:
        name = "EndOfFileRec";
        break;
    case HEX_REC_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD:
        name = "ExtSegAddrRec";
        break;
    case HEX_REC_TYPE_START_SEGMENT_ADDRESS_RECORD:
        name = "StartSegAddrRec";
        break;
    case HEX_REC_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD:
        name = "ExtLinAddrRec";
        break;
    case HEX_REC_TYPE_START_LINEAR_ADDRESS_RECORD:
        name = "StartLinAddrRec";
        break;
    default:
        name = "";
        break;
    }
    return name;
}

const char* HexFrame2Str(const HexFrame_t* const Frame) {
    static char name[80] = {0};
    if(Frame) {
        snprintf(name, sizeof(name), "Len:%u,Offset:0x%04x,Type:%u,Crc:0x%02x", Frame->rec_len, Frame->load_offset,
                 Frame->rec_type, Frame->crc8.read);
    }
    return name;
}

const char* Data2Str(const uint8_t* const data, uint8_t size) {
    static char name[514] = {0};
    if(data) {
        if(size) {
            memset(name, 0, sizeof(name));
#ifdef HAS_NUM_DIAG
            array2str(data, (uint32_t)size, name, sizeof(name));
#endif
        }
    }
    return name;
}

const char* HexNode2Str(const HexBinHandle_t* const Node) {
    static char name[200] = {0};
    if(Node) {
        snprintf(name, sizeof(name), " ");
#warning TODO
    }
    return name;
}

bool HexNodeDiag(const HexBinHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(HEX_BIN, "File[%s]", Node->hex_file_name);
        LOG_INFO(HEX_BIN, "Line:%u", Node->line_cnt);
        LOG_INFO(HEX_BIN, "Fragments:%u", Node->fragment_cnt);
        LOG_INFO(HEX_BIN, "FwSizeChunks:%u Byte=%f kBytes", Node->bin_size_byte, BYTES_2_KBYTES(Node->bin_size_byte));
        LOG_INFO(HEX_BIN, "FwMatchingSize:%u Byte=%f kBytes", Node->matching_size, BYTES_2_KBYTES(Node->matching_size));
        LOG_INFO(HEX_BIN, "FwDiffSize:%u Byte=%f kBytes", Node->diff_size, BYTES_2_KBYTES(Node->diff_size));
        LOG_INFO(HEX_BIN, "FwSizeAddr:%u Byte=%f kBytes", Node->address_size_byte,
                 BYTES_2_KBYTES(Node->address_size_byte));
        LOG_INFO(HEX_BIN, "FwCRC32:0x%08x", Node->fw_crc23);
    }
    return res;
}

#if 0
const char* NodeToProgressStr(const HexBinHandle_t* const Node) {
    static char name[200] = {0};
    if(Node) {
        uint32_t percent = calc_percent_uu(Node->line_cnt, Node->total_lines);
        uint32_t load_data = Node->address_range.max - Node->address_range.min + 1;
        snprintf(name, sizeof(name), "Prog:%5u/%5u,Data:%7.2f kByte,Chunk:%7.2f kByte,%3u %%", Node->line_cnt,
                 Node->total_lines, BYTES_2_KBYTES(load_data), BYTES_2_KBYTES(Node->bin_size_byte), (uint32_t)percent);
    }
    return name;
}
#endif
