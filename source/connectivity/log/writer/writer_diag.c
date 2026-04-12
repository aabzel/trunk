#include "writer_diag.h"

#include "diag_inc.h"
#include "interfaces_diag.h"
#include "log.h"

bool writer_diag(void) { return false; }

const char* WriterConfigToStr(const WriterConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sIF:%s,", text, InterfaceTypeToStr(Config->inter_face));
        snprintf(text, sizeof(text), "%sTxArray:%p,", text, Config->TxArray);
        snprintf(text, sizeof(text), "%stx_array_size:%u,", text, Config->tx_array_size);
    }
    return text;
}
