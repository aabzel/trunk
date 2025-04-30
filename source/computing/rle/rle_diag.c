#include "rle_diag.h"

#include "rle_types.h"
#include "log.h"
#include "debug_info.h"

const char* RleDecodeInput2Str(RleDecoderInput_t input) {
    const char*  name ="?";
    switch((uint8_t)input) {
        case INPUT_LETTER:name ="InpLetter"; break;
        case INPUT_DIGIT: name ="InpDigit"; break;
        case INPUT_FINISH: name ="InpFinish"; break;
    }
    return name;
}


const char* RleDecodeState2Str(RleDecoderState_t state) {
    const char*  name ="?";
    switch((uint8_t)state) {
        case RLE_DECODER_STATE_PREV_LETTER:name ="PrevLetter"; break;
        case RLE_DECODER_STATE_PREV_DIGIT: name ="PrevDigit"; break;
        case RLE_DECODER_STATE_ERROR: name ="Err"; break;
        case RLE_DECODER_STATE_DONE: name ="Done"; break;
        case RLE_DECODER_STATE_UNDEF: name ="Init"; break;
    }
    return name;
}

bool RleEncoderDiag(RleEncodeFsm_t* Node){
    bool res = false;
    LOG_DEBUG(RLE, "Encoder Perv:%c Cnt:%u OutIdx:%u", Node->prev, Node->cnt, Node->out_idx);
    res= print_ascii_line(Node->mem_start, Node->in_size, 4);
    return res;
}


bool RleDecoderDiag(RleDecodeFsm_t* Node){
    bool res = false;
    LOG_DEBUG(RLE, "St:[%s] In:[%s] Prev:%c PrevLett:%c N:%d Shift:%u",
            RleDecodeState2Str(Node->state),
            RleDecodeInput2Str(Node->input),
            Node->prev_symbol,
            Node->prev_letter,
            Node->d,
            Node->out_idx);
    return res;
}
