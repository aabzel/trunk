#include "c_generator_diag.h"

#include <stdio.h>
#include <string.h>

#include "c_generator.h"
#include "log.h"

const char* cGeneratorDiag2Str(const cGeneratorHandle_t* const Node) {
    static char text[300] = "";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sFile:%s", text, Node->filename);
        snprintf(text, sizeof(text), "%sFunCnt:%u", text, Node->function_cnt);
        snprintf(text, sizeof(text), "%s{Cnt:%u", text, Node->brace_open_cnt);
        snprintf(text, sizeof(text), "%s}Cnt:%u", text, Node->brace_close_cnt);
        snprintf(text, sizeof(text), "%s{}Cnt:%u", text, Node->brace_cnt);
    }
    return text;
}

bool cGeneratorDiag(const cGeneratorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(C_GENERATOR, "%s", cGeneratorDiag2Str(Node));
        res = true;
    }
    return res;
}

bool c_generator_diag(void) {
    bool res = true;
    res = cGeneratorDiag(&cGeneratorInstance);
    return res;
}
