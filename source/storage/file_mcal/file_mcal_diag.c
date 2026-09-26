#include "file_mcal_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"


const char* FileMcalStateToStr(const FileState_t state) {
    const char* name = "?";
    switch(state) {
        case FILE_STATE_CLOSED: {        name = "Closed";    } break;
        case FILE_STATE_OPEN: {        name = "Open";    } break;
        default: {        name = "?";    } break;
    }
    return name;
}




const char* FileSystemToStr(FileSystem_t file_system) {
    const char* name = "?";
    switch(file_system) {
        case FILE_SYS_FAT_FS: {        name = "FAT_FS";    } break;
        case FILE_SYS_POSIX_API: {        name = "POSIX_API";    } break;
        case FILE_SYS_LITTLE_FS: {        name = "LITTLE_FS";    } break;
        default: {        name = "?";    } break;
    }
    return name;
}

const char* FileSystemTypeToStr(const FileSystemType_t* const pFS){
    static char lText[40]="";
    strcpy(lText, "");
    if(pFS) {
        snprintf(lText, sizeof(lText), "%sFileSys:%s_", lText, FileSystemToStr(pFS->file_system));
        snprintf(lText, sizeof(lText), "%s%u,", lText, pFS->num);
    }
    return lText;
}


const char* FileMcalConfigToStr(const FileMcalConfig_t* const Config) {
    static char lText[40]="";
    strcpy(lText, "");
    if(Config) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%sFileSys:%s,", lText, FileSystemTypeToStr(&Config->fileSystem));
        snprintf(lText, sizeof(lText), "%s%s,", lText, Config->name);
    }
    return lText;
}

const char* FileMcalNodeToStr(const FileMcalHandle_t* const Node){
    static char lText[150]="";
    strcpy(lText, "");
    if(Node) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Node->num);
        snprintf(lText, sizeof(lText), "%sFileName:[%s],", lText, Node->file_name);
        snprintf(lText, sizeof(lText), "%sReadTot:%u Byte,", lText, Node->read_total);
        snprintf(lText, sizeof(lText), "%sWriteTot:%u Byte,", lText, Node->write_total);
        snprintf(lText, sizeof(lText), "%s[%s],", lText, Node->name);
#ifdef HAS_FILE_PC
        snprintf(lText, sizeof(lText), "%sFilePtr:%p,", lText, Node->FilePtr);
#endif
        snprintf(lText, sizeof(lText), "%sSpin:%u,", lText, Node->spin);
        snprintf(lText, sizeof(lText), "%sFileSys:[%s],", lText, FileSystemTypeToStr(( FileSystemType_t*) &Node->fileSystem)   );
        snprintf(lText, sizeof(lText), "%sstate:%s,", lText, FileMcalStateToStr(Node->state)   );
        snprintf(lText, sizeof(lText), "%sInit:%s,", lText, OnOffToStr(Node->init));
        snprintf(lText, sizeof(lText), "%sValid:%s,", lText, OnOffToStr(Node->valid));
    }
    return lText;
}


bool file_mcal_diag_one(uint8_t num) {
    bool res = false;
    return res;
}

bool file_mcal_diag(void) {
    bool res = false;
    res = file_mcal_diag_one(1);
    return res;
}
