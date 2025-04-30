#include "rle.h"

#include <stdlib.h>
#include <string.h>
/*https://en.wikipedia.org/wiki/Run-length_encoding*/
#include "log.h"
#include "rle_diag.h"

static bool rle_encode_proc(RleEncodeFsm_t* Node, char letter, char* result, uint32_t i) {
    bool res;
    RleEncoderDiag(Node);
    if(0 == i) {
        LOG_WARNING(RLE, "NewChar %c", letter);
        Node->cnt = 1;
        res = true;
    } else {
        if(letter == Node->prev) {
            Node->cnt++;
            res = true;
        } else {
            LOG_WARNING(RLE, "NewChar %c", letter);
            res = true;

            if(1 == Node->cnt) {
                result[Node->out_idx] = Node->prev;
                Node->out_idx++;
                res = true;
            } else if(1 < Node->cnt) {
                // sprintf(Node->temp_str, "%s%c%u", &result[Node->out_idx], Node->prev, Node->cnt);
                sprintf(Node->temp_str, "%c%u", Node->prev, Node->cnt);
                LOG_WARNING(RLE, "+Suffix[%s]", Node->temp_str);
                // sprintf(&result[Node->out_idx], "%s%s", &result[Node->out_idx], Node->temp_str);
                memcpy(&result[Node->out_idx], Node->temp_str, strlen(Node->temp_str));
                Node->out_idx += strlen(Node->temp_str);
                res = true;
            } else {
                res = true;
            }

            Node->cnt = 1;
        }
    }

    if(i == (Node->in_size - 1)) {
        LOG_WARNING(RLE, "LastIndex %u", i);
        if(1 == Node->cnt) {
            LOG_WARNING(RLE, "NewChar %c", letter);
            result[Node->out_idx] = letter;
            Node->out_idx++;
            res = true;
        } else if(1 < Node->cnt) {
            sprintf(Node->temp_str, "%c%u", Node->prev, Node->cnt);
            LOG_WARNING(RLE, "+Suffix[%s]", Node->temp_str);
            // sprintf(&result[Node->out_idx], "%s%s", &result[Node->out_idx], Node->temp_str);
            memcpy(&result[Node->out_idx], Node->temp_str, strlen(Node->temp_str));
            Node->out_idx += strlen(Node->temp_str);
            res = true;
        } else {
            // result[Node->out_idx] = letter;
            res = true;
        }
    }

    Node->prev = letter;
    return res;
}

static bool rle_encode_init(RleEncodeFsm_t* Node, const char* const raw_data, uint32_t in_size) {
    bool res;
    if(Node) {
        Node->prev = '*';
        Node->cnt = 0;
        Node->out_idx = 0;
        Node->in_size = in_size;
        Node->mem_start = raw_data;
        res = true;
    }
    return res;
}

bool rle_encode(const char* const encode_data, uint32_t in_size, char* const encode_result,
                uint32_t* const encode_data_size) {
    // cli_printf(CRLF);
    LOG_DEBUG(RLE, CRLF CRLF "Encode [%s]", encode_data);
    bool res;
    uint32_t i = 0;
    RleEncodeFsm_t Node;
    res = rle_encode_init(&Node, encode_data, in_size);
    for(i = 0; i < in_size; i++) {
        res = rle_encode_proc(&Node, encode_data[i], encode_result, i);
        if(res) {
            LOG_PARN(RLE, "Proc i=%u Ok", i);
        } else {
            LOG_ERROR(RLE, "Err i=%u", i);
        }
    }
    //*encode_data_size = strlen(encode_result);
    *encode_data_size = Node.out_idx;

    return res;
}

int rle_encode_v2(char* chars, int charsSize) {
    uint32_t encode_data_size = 0;
    char* encode_result = (char*)malloc(charsSize);
    if(encode_result) {
        memset(encode_result, 0, charsSize);
        bool res = rle_encode(chars, charsSize, encode_result, &encode_data_size);
        if(res) {
            memset(chars, 0, charsSize);
            memcpy(chars, encode_result, encode_data_size);
            free(encode_result);
        }
    }
    return encode_data_size;
}

uint32_t rle_encode_in_place(char* chars, uint32_t chars_size) {
    uint32_t encode_data_size = 0;
    bool res = rle_encode(chars, chars_size, chars, &encode_data_size);
    if(res) {
        chars[encode_data_size] = 0x00;
    }

    return encode_data_size;
}
