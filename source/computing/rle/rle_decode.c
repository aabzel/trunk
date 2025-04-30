#include "rle.h"

#include <string.h>
/*https://en.wikipedia.org/wiki/Run-length_encoding*/
#include "array.h"
#include "convert.h"
#include "log.h"
#include "rle_diag.h"

static bool rle_decode_init(RleDecodeFsm_t* Node) {
    bool res = false;
    if(Node) {
        Node->state = RLE_DECODER_STATE_UNDEF;
        Node->prev_letter = ' ';
        Node->prev_symbol = ' ';
        Node->cur_char = ' ';
        Node->out_idx = 0;
        Node->input = INPUT_UNDEF;
        Node->d = 0;
        Node->i = 0;
        res = true;
    }
    return res;
}

static bool rle_decode_proc_undef(RleDecodeFsm_t* Node, char* const raw_data) {
    bool res = false;
    switch(Node->input) {
    case INPUT_DIGIT:
        Node->state = RLE_DECODER_STATE_ERROR;
        res = false;
        break;
    case INPUT_LETTER:
        Node->state = RLE_DECODER_STATE_PREV_LETTER;
        res = true;
        break;
    case INPUT_FINISH:
        Node->state = RLE_DECODER_STATE_ERROR;
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool rle_decode_proc_prev_letter(RleDecodeFsm_t* Node, char* const raw_data) {
    bool res = false;
    switch(Node->input) {
    case INPUT_LETTER: {
        if(Node->prev_letter == Node->cur_char) {
            Node->state = RLE_DECODER_STATE_ERROR;
            Node->d = 0;
            res = false;
        } else {
            raw_data[Node->out_idx] = Node->prev_letter;
            Node->out_idx++;
            res = true;
        }
    } break;

    case INPUT_DIGIT: {
        Node->state = RLE_DECODER_STATE_PREV_DIGIT;
        Node->i = 0;
        Node->d = char_to_u8(Node->cur_char);
        res = true;
    } break;

    case INPUT_FINISH: {
        Node->state = RLE_DECODER_STATE_DONE;
        raw_data[Node->out_idx] = Node->prev_letter;
        Node->out_idx++;
        res = true;
    } break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool rle_decode_proc_prev_digit(RleDecodeFsm_t* Node, char* const raw_data) {
    bool res = false;
    switch(Node->input) {
    case INPUT_DIGIT: {
        Node->state = RLE_DECODER_STATE_PREV_DIGIT;
        Node->i++;
        Node->d = Node->d * 10 + char_to_u8(Node->cur_char);
        res = true;
    } break;
    case INPUT_LETTER: {
        Node->state = RLE_DECODER_STATE_PREV_LETTER;

        res = array_pat_set(raw_data + Node->out_idx, Node->d, Node->prev_letter);

        Node->out_idx += Node->d;
        Node->d = 0;
        Node->i = 0;
        res = true;
    } break;
    case INPUT_FINISH: {
        res = array_pat_set(raw_data + Node->out_idx, Node->d, Node->prev_letter);
        Node->state = RLE_DECODER_STATE_DONE;
        Node->out_idx += Node->d;
        res = true;
    } break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool rle_decode_proc_state(RleDecodeFsm_t* Node, char* const raw_data) {
    bool res = false;
    RleDecoderDiag(Node);
    // LOG_DEBUG(RLE, "Decoder Proc St:%s In:%s", RleDecodeState2Str(Node->state),RleDecodeInput2Str(Node->input));
    switch(Node->state) {
    case RLE_DECODER_STATE_UNDEF:
        res = rle_decode_proc_undef(Node, raw_data);
        break;
    case RLE_DECODER_STATE_PREV_LETTER:
        res = rle_decode_proc_prev_letter(Node, raw_data);
        break;
    case RLE_DECODER_STATE_PREV_DIGIT:
        res = rle_decode_proc_prev_digit(Node, raw_data);
        break;
    case RLE_DECODER_STATE_ERROR:
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool rle_decode_proc(RleDecodeFsm_t* Node, char symbol, char* const raw_data) {
    bool res = false;
    Node->cur_char = symbol;
    res = is_dec_digit(symbol);
    if(res) {
        Node->input = INPUT_DIGIT;
    } else {
        Node->input = INPUT_LETTER;
    }

    LOG_DEBUG(RLE, "DecodeProc %c %s", symbol, RleDecodeInput2Str(Node->input));

    res = rle_decode_proc_state(Node, raw_data);

    Node->prev_symbol = symbol;
    if(INPUT_LETTER == Node->input) {
        Node->prev_letter = symbol;
    }
    return res;
}

bool rle_decode(const char* const decode_str, uint32_t in_size, char* const raw_data,
                uint32_t* const decode_data_size) {
    bool res = false;
    if(decode_str) {
        if(in_size) {
            RleDecodeFsm_t Node;
            res = rle_decode_init(&Node);
            uint32_t i = 0;
            for(i = 0; i < in_size; i++) {
                res = rle_decode_proc(&Node, decode_str[i], raw_data);
                if(res) {
                    LOG_PARN(RLE, "DecodeProc i=%u Ok", i);
                } else {
                    LOG_ERROR(RLE, "DecodeErr i=%u", i);
                }
            }

            Node.input = INPUT_FINISH;
            res = rle_decode_proc_state(&Node, raw_data);
        }
    }
    return res;
}
