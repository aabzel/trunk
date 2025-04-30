#include "rle_commands.h"

#include <string.h>

#include "log.h"
#include "rle.h"

bool rle_encode_command(int32_t argc, char* argv[]) {
    bool res = false;
    char data[100] = "0";
    memset(data, 0, sizeof(data));
    uint32_t out_size = 0;
    uint32_t array_len = 0;

    if(1 <= argc) {
        array_len = strlen(argv[0]);
        res = true;
    }

    if(res) {
        res = rle_encode(argv[0], array_len, data, &out_size);
        if(res) {
            LOG_INFO(RLE, "EncodedData [%s]", data);
        } else {
            LOG_ERROR(RLE, "EncodeErr", argv[0]);
        }
    }
    return res;
}

bool rle_decode_command(int32_t argc, char* argv[]) {
    bool res = false;

    char raw_data[100];
    memset(raw_data, 0, sizeof(raw_data));

    uint32_t out_size = 0;
    uint32_t array_len = 0;
    if(1 <= argc) {
        array_len = strlen(argv[0]);
        res = true;
    }

    if(res) {
        LOG_WARNING(RLE, "Decode  [%s] Size: %u Byte", argv[0], array_len);
        res = rle_decode(argv[0], array_len, raw_data, &out_size);
        if(res) {
            LOG_INFO(RLE, "RawData [%s]", raw_data);
        } else {
            LOG_ERROR(RLE, "DecodeErr", argv[0]);
        }
    }
    return res;
}
