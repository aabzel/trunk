#include "trng_mcal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array.h"
#include "code_generator.h"
#include "common_diag.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#include "trng_custom.h"

/*
  https://learnc.info/c/random.html
*/

bool tRngIsValidConfig(const tRngConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(TRNG, "%u,NameErr", Config->num);
            res = false;
        }
    }
    return res;
}

bool trng_get_byte(uint8_t* const byte) {
    bool res = false;
    if(byte) {
        *byte = rand() % 256;
        res = true;
    }

    return res;
}

bool trng_get_word(uint16_t* const word) {
    bool res = false;
    if(word) {
        *word = rand() % 0xFFFF;
        res = true;
    }
    return res;
}

bool trng_get_qword(uint64_t* const qword) {
    bool res = false;
    if(qword) {
        *qword = rand() % 0xFFFFFFFFFFFFFFFF;
        res = true;
    }
    return res;
}

bool trng_get_dword(uint32_t* const dword) {
    bool res = false;
    if(dword) {
        *dword = trng_static_get_rand();
        res = true;
    }
    return res;
}

bool trng_get_s32(int32_t* const sdword) {
    bool res = false;
    if(sdword) {
        *sdword = rand();
        res = true;
    }
    return res;
}

bool trng_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(TRNG, "TRNG%u,Proc", num);
    tRngHandle_t* Node = tRngGetNode(num);
    if(Node) {
        res = trng_get_qword(&Node->qword);
        res = trng_get_dword(&Node->dword);
        res = trng_get_word(&Node->word);
        res = trng_get_byte(&Node->byte);
        LOG_DEBUG(TRNG, "TRNG%u,%s", num, tRngNodeToStr(Node));
        Node->spin++;
    }
    return res;
}

bool trng_init_custom(void) {
    bool res = true;
    LOG_WARNING(TRNG, "CustomInit");
    srand(time(NULL));
    return res;
}

bool trng_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(TRNG, "TRNG%u,Init..", num);
    const tRngConfig_t* Config = tRngGetConfig(num);
    if(Config) {
        LOG_WARNING(TRNG, "SpotCfg:%s", tRngConfigToStr(Config));
        res = tRngIsValidConfig(Config);
        if(res) {
            tRngHandle_t* Node = tRngGetNode(num);
            if(Node) {
                res = trng_init_common(Config, Node);
                res = trng_init_node(Node);
                int r1 = rand();
                Node->init = true;
                LOG_INFO(TRNG, "TRNG%u,Init,Ok,Val:%d", num, r1);
                LOG_INFO(TRNG, "TRNG%u,%s", num, tRngNodeToStr(Node));
                log_level_get_set(TRNG, LOG_LEVEL_INFO);
            } else {
                res = false;
                LOG_ERROR(TRNG, "NodeErr");
            }
        }
    } else {
        LOG_DEBUG(TRNG, "TRNG%u NoConfig", num);
    }
    return res;
}
