#include "m_seq_config.h"

#include "data_utils.h"


static uint8_t GeneratedCode1[1024]={0};
static uint8_t Mseq6[10]=      { 0 };
static uint8_t feedback6[10] = { 0, 0, 0, 1, 1 };

static uint8_t GeneratedCode2[1024]={0};
static uint8_t Mseq7[10]=      { 0};
//static int8_t feedback7[10] = { 1, 0, 0, 0, 0, 1 };
static uint8_t feedback7[10] = { 1, 1, 0, 1, 1 };
//error { 0, 1, 1, 0, 0, 0 };
//error { 1, 0, 0, 1, 0, 0 };
//error { 1, 0, 0, 0, 1, 0 };
//error { 0, 1, 0, 0, 1, 0 };
//error { 0, 1, 0, 0, 0, 1 };
//error { 0, 0, 1, 0, 1, 0 };
//error { 0, 0, 1, 0, 0, 1 };
//error { 0, 0, 0, 1, 0, 1 };
//error { 0, 0, 0, 1, 1, 0 };

#if 0
0.455,135,W,[Mseq],M_SEQ_2,Spot,FeedBack:33=100001,feed
0.467,137,W,[Mseq],M_SEQ_2,Spot,FeedBack:48=110000,feed
0.470,138,W,[Mseq],M_SEQ_2,Spot,FeedBack:51=110011,feed

0.460,136,W,[Mseq],M_SEQ_2,Spot,FeedBack:45=101101,feed
0.476,139,W,[Mseq],M_SEQ_2,Spot,FeedBack:54=110110,feed
0.481,140,W,[Mseq],M_SEQ_2,Spot,FeedBack:55=110111,feed
0.487,141,W,[Mseq],M_SEQ_2,Spot,FeedBack:57=111001,feed
#endif



const MseqConfig_t MseqConfig[] = {
    {
        .num = 1,
        .cur_size = 5,
        .max_size = ARRAY_SIZE(Mseq6),
        .memory = Mseq6,
        .feedback = feedback6,
        .generated_code = GeneratedCode1,
        .code_size = ARRAY_SIZE(GeneratedCode1),
        .valid = true,
        .name = "MAX_LEN_SEQ1",
    },

    {
        .num = 2,
        .cur_size = 5,
        .generated_code = GeneratedCode2,
        .code_size = ARRAY_SIZE(GeneratedCode2),
        .max_size = ARRAY_SIZE(Mseq7),
        .memory = Mseq7,
        .feedback = feedback7,
        .valid = true,
        .name = "MAX_LEN_SEQ2",
    },
};

MseqHandle_t MseqInstance[] = {
    {        .num = 1,        .valid = true,    },
    {        .num = 2,        .valid = true,    },
};

COMPONENT_GET_CNT(Mseq, m_seq)


