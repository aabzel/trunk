#include "manchester_decode_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "num_to_str.h"
#include "utils_math.h"

COMPONENT_GET_NODE(ManchesterDecode, manchester_decode)
COMPONENT_GET_CONFIG(ManchesterDecode, manchester_decode)

static const ManchesterDecodeState_t MatchDeCodeStateTable[12][2]={
       // [0][0]={},
        /*prev prev   prev    rx state    cur New State*/
        [MANCH_DECODE_STATE_00_START0][0] =   MANCH_DECODE_STATE_00_START0,
        [MANCH_DECODE_STATE_01_START0][0] =   MANCH_DECODE_STATE_10_START0,
        [MANCH_DECODE_STATE_10_START0][0] =   MANCH_DECODE_STATE_00_START0,
        [MANCH_DECODE_STATE_11_START0][0] =   MANCH_DECODE_STATE_10_DONE  ,
        [MANCH_DECODE_STATE_00_START1][0] =   MANCH_DECODE_STATE_00_START0,
        [MANCH_DECODE_STATE_01_START1][0] =   MANCH_DECODE_STATE_10_DONE  ,
        [MANCH_DECODE_STATE_10_START1][0] =   MANCH_DECODE_STATE_00_START0,
        [MANCH_DECODE_STATE_11_START1][0] =   MANCH_DECODE_STATE_10_DONE  ,
        [MANCH_DECODE_STATE_00_DONE  ][0] =   MANCH_DECODE_STATE_00_START0,
        [MANCH_DECODE_STATE_01_DONE  ][0] =   MANCH_DECODE_STATE_10_START0,
        [MANCH_DECODE_STATE_10_DONE  ][0] =   MANCH_DECODE_STATE_00_START0,
        [MANCH_DECODE_STATE_11_DONE  ][0] =   MANCH_DECODE_STATE_10_DONE  ,
        [MANCH_DECODE_STATE_00_START0][1] =   MANCH_DECODE_STATE_01_DONE  ,
        [MANCH_DECODE_STATE_01_START0][1] =   MANCH_DECODE_STATE_11_START1,
        [MANCH_DECODE_STATE_10_START0][1] =   MANCH_DECODE_STATE_01_DONE  ,
        [MANCH_DECODE_STATE_11_START0][1] =   MANCH_DECODE_STATE_11_START1,
        [MANCH_DECODE_STATE_00_START1][1] =   MANCH_DECODE_STATE_01_DONE  ,
        [MANCH_DECODE_STATE_01_START1][1] =   MANCH_DECODE_STATE_11_START1,
        [MANCH_DECODE_STATE_10_START1][1] =   MANCH_DECODE_STATE_01_START1,
        [MANCH_DECODE_STATE_11_START1][1] =   MANCH_DECODE_STATE_11_START1,
        [MANCH_DECODE_STATE_00_DONE  ][1] =   MANCH_DECODE_STATE_01_DONE  ,
        [MANCH_DECODE_STATE_01_DONE  ][1] =   MANCH_DECODE_STATE_11_START1,
        [MANCH_DECODE_STATE_10_DONE  ][1] =   MANCH_DECODE_STATE_01_START1,
        [MANCH_DECODE_STATE_11_DONE  ][1] =   MANCH_DECODE_STATE_11_START1,
};

static const ManchesterDecodeAction_t MatchDeCodeActionTable[12][2]={
     //   prev prev   prev    rx state    cur Action
        [MANCH_DECODE_STATE_00_START0  ][0] = MANCH_DECODE_ACTION_ERROR   ,
        [MANCH_DECODE_STATE_01_START0  ][0] = MANCH_DECODE_ACTION_UNREAL  ,
        [MANCH_DECODE_STATE_10_START0  ][0] = MANCH_DECODE_ACTION_START0  ,
        [MANCH_DECODE_STATE_11_START0  ][0] = MANCH_DECODE_ACTION_RX1     ,
        [MANCH_DECODE_STATE_00_START1  ][0] = MANCH_DECODE_ACTION_ERROR   ,
        [MANCH_DECODE_STATE_01_START1  ][0] = MANCH_DECODE_ACTION_RX1     ,
        [MANCH_DECODE_STATE_10_START1  ][0] = MANCH_DECODE_ACTION_START0  ,
        [MANCH_DECODE_STATE_11_START1  ][0] = MANCH_DECODE_ACTION_RX1     ,
        [MANCH_DECODE_STATE_00_DONE    ][0] = MANCH_DECODE_ACTION_ERROR   ,
        [MANCH_DECODE_STATE_01_DONE    ][0] = MANCH_DECODE_ACTION_START0  ,
        [MANCH_DECODE_STATE_10_DONE    ][0] = MANCH_DECODE_ACTION_START0  ,
        [MANCH_DECODE_STATE_11_DONE    ][0] = MANCH_DECODE_ACTION_RX1     ,

        [MANCH_DECODE_STATE_00_START0  ][1] = MANCH_DECODE_ACTION_RX0     ,
        [MANCH_DECODE_STATE_01_START0  ][1] = MANCH_DECODE_ACTION_UNREAL  ,
        [MANCH_DECODE_STATE_10_START0  ][1] = MANCH_DECODE_ACTION_RX0     ,
        [MANCH_DECODE_STATE_11_START0  ][1] = MANCH_DECODE_ACTION_ERROR   ,
        [MANCH_DECODE_STATE_00_START1  ][1] = MANCH_DECODE_ACTION_RX0     ,
        [MANCH_DECODE_STATE_01_START1  ][1] = MANCH_DECODE_ACTION_START1  ,
        [MANCH_DECODE_STATE_10_START1  ][1] = MANCH_DECODE_ACTION_UNREAL  ,
        [MANCH_DECODE_STATE_11_START1  ][1] = MANCH_DECODE_ACTION_ERROR   ,
        [MANCH_DECODE_STATE_00_DONE    ][1] = MANCH_DECODE_ACTION_RX0     ,
        [MANCH_DECODE_STATE_01_DONE    ][1] = MANCH_DECODE_ACTION_START1  ,
        [MANCH_DECODE_STATE_10_DONE    ][1] = MANCH_DECODE_ACTION_START1  ,
        [MANCH_DECODE_STATE_11_DONE    ][1] = MANCH_DECODE_ACTION_ERROR   ,
};

/*ISO-26262 require verify configuration*/
bool ManchesterDecodeIsValidConfig(const ManchesterDecodeConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(MANCHESTER_DECODE, "MANCHESTER_DECODE_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

uint8_t manchester_decode_out_to_val(const ManchesterDecodeAction_t out) {
    uint8_t sample = 0xFF ;
    switch(out) {
        case MANCH_DECODE_ACTION_RX0: sample = 0 ;break;
        case MANCH_DECODE_ACTION_RX1: sample = 1 ;break;
        default:  sample = 0xFF ;break;
    }
    return sample;
}

bool manchester_decode_proc_sample(const uint8_t num, const uint8_t in, uint8_t* const out) {
    bool res = false;
    ManchesterDecodeHandle_t *Node = ManchesterDecodeGetNode(num);
    if (Node) {
        //LOG_DEBUG(MANCHESTER_DECODE, "%s,Proc:%u",ManchesterDecodeNodeToStr(Node), in);
        Node->prev_state = Node->state;
        Node->out = MatchDeCodeActionTable[Node->state][in];
        //LOG_DEBUG(MANCHESTER_DECODE, "Out:%s",ManchesterDecodeActionToStr(Node->out));
        Node->state = MatchDeCodeStateTable[Node->state][in];
        //LOG_DEBUG(MANCHESTER_DECODE, "NewState:%s",ManchesterDecodeStateToStr(Node->state));
        switch (Node->out) {
            case MANCH_DECODE_ACTION_RX0: {
                *out = 0;
                res = true;
            } break;

            case MANCH_DECODE_ACTION_RX1: {
                *out = 1;
                res = true;
            } break;


            case MANCH_DECODE_ACTION_ERROR: {
                Node->error_cnt++;
                Node->cur_flow = 0;
                 res = false;
             } break;

            case MANCH_DECODE_ACTION_UNREAL: {
                Node->error_cnt++;
                Node->cur_flow = 0;
                 res = false;
                 *out = 0xFF;
             } break;
            default:

                res = false;
                *out = 0xFF;
                break;
        }
        if(res) {
            Node->cur_flow++;
            Node->max_flow = MATH_MAX(Node->max_flow ,Node->cur_flow);
            uint32_t order= ((int32_t)Node->rx_cnt) + ((int32_t) Node->rx_cnt_phase);
            uint8_t bitNum = 7 - ( order % 8);
            Node->rx_byte= bit_u8_ctrl( Node->rx_byte, bitNum,   *out);
            Node->rx_cnt++;
            if (0==bitNum) {
                LOG_NOTICE(MANCHESTER_DECODE, "h%02x-%s", Node->rx_byte, utoa_bin8(Node->rx_byte));
            }
            LOG_DEBUG(MANCHESTER_DECODE, "[%u]=%u",  Node->rx_cnt, *out);
        }
    }

    return res;
}

bool manchester_decode_array(uint8_t num,
                             const uint8_t* const EncodedData,
                             const uint32_t encoded_data_size,
                             uint8_t* const DecodedData,
                             const uint32_t decoded_data_size) {
    bool res = false;
    if ( decoded_data_size >= (encoded_data_size/2)) {
    LOG_DEBUG(MANCHESTER_DECODE, "EnSize:%u,DecSize:%u", encoded_data_size,decoded_data_size);
        uint32_t i = 0;
        uint32_t rx_bit=0;
        for (i = 0; i < encoded_data_size; i++) {
            int32_t b = 7;
            for (b = 7; 0 <= b; b--) {
                uint8_t in = CHECK_BIT_NUM(EncodedData[i], b);
                uint8_t bit_val = 0xFF;
                bool spot_bit = manchester_decode_proc_sample(num, in, &bit_val);
                if (spot_bit) {
                    uint32_t byte_num = rx_bit/8 ;
                    uint32_t bit_num = 7-(rx_bit%8); // 0 1 2 3 4 5 6 7 0 1 2 3 4
                    DecodedData[byte_num]= bit_u8_ctrl(DecodedData[byte_num], bit_num, bit_val);
                    rx_bit++;
                }
            }
        }
        res = true;
    }
    return res;
}

bool manchester_decode_init_custom(void) {
    bool res = false;
    LOG_INFO(MANCHESTER_DECODE, "Version:%u", MANCHESTER_DECODE_VERSION);
    return res;
}

bool manchester_decode_init_common(const ManchesterDecodeConfig_t* const Config, ManchesterDecodeHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool manchester_decode_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(MANCHESTER_DECODE, "MANCHESTER_DECODE_%u", num);
    const ManchesterDecodeConfig_t *Config = ManchesterDecodeGetConfig(num);
    res = ManchesterDecodeIsValidConfig(Config);
    if(res) {
#ifdef HAS_MANCHESTER_DECODE_DIAG
        LOG_WARNING(MANCHESTER_DECODE, "%s", ManchesterDecodeConfigToStr(Config));
#endif
        ManchesterDecodeHandle_t *Node = ManchesterDecodeGetNode(num);
        if(Node) {
            res = manchester_decode_init_common(Config, Node);
            Node->state = MANCH_DECODE_STATE_01_DONE;
            Node->prev_state = MANCH_DECODE_STATE_01_DONE;
            Node->rx_cnt = MANCH_DECODE_STATE_01_DONE;
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(MANCHESTER_DECODE, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(MANCHESTER_DECODE, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(MANCHESTER_DECODE, MANCHESTER_DECODE, manchester_decode)
