#include "hash_table_s8_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* HashTableS8ConfigToStr(const HashTableS8Config_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* HashTableS8NodeToStr(const HashTableS8Handle_t* const Node) {
    static char lText[400] = {0};
    strcpy(lText, "");
    if(Node) {
        int32_t i = 0;
        for(i = 0; i < 256; i++) {
            if(Node->HashTable[i]) {
                int8_t c = 0;
                for(c = 0; c < Node->HashTable[i]; c++) {
                    int8_t value = ((int8_t)i) - 128;
                    snprintf(lText, sizeof(lText), "%s%d,", lText, value);
                }
            }
        }
    }
    return lText;
}

bool hash_table_s8_diag(void) {
    bool res = false;
    return res;
}
