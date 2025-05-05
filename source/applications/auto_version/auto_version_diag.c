#include "auto_version_diag.h"

#include <stdio.h>

#include "auto_version.h"
#include "log.h"

const char* AutoVersionDiag2Str(const AutoVersionHandle_t* const Node){
    static char text[120]="";
    snprintf(text,sizeof(text),"File:%s", Node->filename);
    return text;
}

bool AutoVersionDiag(const AutoVersionHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(AUTO_VERSION, "%s", AutoVersionDiag2Str(Node));
        res = true;
    }
    return res;
}

bool auto_version_diag(void){
    bool res = true;
    res = AutoVersionDiag(&AutoVersionInstance);
    return res;
}


