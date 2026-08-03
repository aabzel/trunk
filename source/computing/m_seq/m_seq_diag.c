#include "m_seq_diag.h"

#include "array_diag.h"
#include "m_seq_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "array_diag.h"
#include "log.h"

const char* MseqConfigToStr(const MseqConfig_t* const Config) {
    strcpy(text, "");
    if (Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sMem:[%s],", text, ArrayU8ToStr(Config->memory,Config->cur_size));
        snprintf(text, sizeof(text), "%sFeedB:[%s],", text, ArrayU8ToStr(Config->feedback,Config->cur_size));
        snprintf(text, sizeof(text), "%sCurSz:%u,", text, Config->cur_size);
        snprintf(text, sizeof(text), "%sMaxSz:%u,", text, Config->max_size);

    }
    return text;
}

const char* MseqNodeToStr(const MseqHandle_t* const Node) {
    strcpy(text, "");
    if (Node) {
        uint32_t m_sec_len = m_seq_get_len(Node->cur_size);
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sCurSz:%u,", text, Node->cur_size);
        snprintf(text, sizeof(text), "%sMaxSz:%u,", text, Node->max_size);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sMem:[%s],", text, ArrayU8ToStr(Node->memory,Node->cur_size));
        snprintf(text, sizeof(text), "%sFeedB:[%s],", text, ArrayU8ToStr(Node->feedback,Node->cur_size));
        snprintf(text, sizeof(text), "%sName:%s,", text, Node->name);
        snprintf(text, sizeof(text), "%sLen:%u,", text, m_sec_len);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool m_seq_diag_one(uint8_t num) {
    bool res = false;
    const MseqConfig_t *Config = MseqGetConfig(num);
    if (Config) {
        LOG_INFO(M_SEQ, "%s", MseqConfigToStr(Config));
        MseqHandle_t *Node = MseqGetNode(num);
        if (Node) {
            LOG_INFO(M_SEQ, "%s", MseqNodeToStr(Node));
            res = true;

            uint32_t m_sec_len = m_seq_get_len(Node->cur_size);
            uint32_t i = 0;
            for (i = 0; i < m_sec_len; i++) {
                int8_t sample = m_seq_get_sample(Node->num);
                cli_printf("%d,", sample);

            }

        }
    }

    return res;
}

bool m_seq_diag(void) {
    bool res = false;
    res = m_seq_diag_one(1);
    return res;
}

