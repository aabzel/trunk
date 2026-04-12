#include "hash_table_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* HashTableConfigToStr(const HashTableConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sSize:%u,", text, Config->size);
        snprintf(text, sizeof(text), "%sMem:%p,", text, Config->Memory);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* HashTableCellToStr(const HashTableCell_t* const Cell) {
    strcpy(text, "");
    if(Cell) {
        snprintf(text, sizeof(text), "%sCnt:%u,", text, Cell->cnt);
        snprintf(text, sizeof(text), "%sVal:%d,", text, Cell->value);
        snprintf(text, sizeof(text), "%sCollF:%d,", text, Cell->collision_flag);
    }
    return text;
}

const char* HashTableNodeToStr(const HashTableHandle_t* const Node) {
    static char lText[200] = {0};
    strcpy(lText, "");
    if(Node) {
        int32_t i = 0;
        for(i = 0; i < Node->size; i++) {
            if(Node->Memory[i].cnt) {
                int32_t c = 0;
                for(c = 0; c < Node->Memory[i].cnt; c++) {
                    snprintf(lText, sizeof(lText), "%s%d,", lText, Node->Memory[i].value);
                }
            }
        }
    }
    return lText;
}

bool hash_table_diag(void) {
    bool res = false;
    return res;
}
