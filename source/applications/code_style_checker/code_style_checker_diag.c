#include "code_style_checker_diag.h"

#include <stdio.h>
#include <string.h>

#include "code_style_checker.h"
#include "log.h"

const char* CodeStyleCheckerDiagToStr(const CodeStyleCheckerHandle_t* const Node){
	char* name = "?";
	return name;
}

bool CodeStyleCheckerDiag(const CodeStyleCheckerHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(CODE_STYLE_CHECKER, "%s", CodeStyleCheckerDiagToStr(Node));
        res = true;
    }
    return res;
}

bool code_style_checker_diag(void){
    bool res = true;
    res = CodeStyleCheckerDiag(&CodeStyleCheckerInstance);
    return res;
}


