#include "dtmf_diag.h"

#include <stdio.h>
#include <string.h>

#include "dtmf_drv.h"
#include "writer_config.h"
#include "log.h"
#include "table_utils.h"
#include "dtmf_config.h"


bool dtmf_diag(void) {
    bool res = false;
    LOG_INFO(DTMF, "Diag");
    static const table_col_t cols[] = {
            {5, "num"},
            {7, "I2sNum"},
            {7, "DacNum"},
            {6, "TxSample"},
    };
    uint32_t i = 0;
    uint32_t cnt = dtmf_get_cnt();
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char log_line[150];
    for(i=0; i <= cnt; i++) {
        DtmfHandle_t* Node = DtmfGetNode(i);
        if (Node) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %u " TSEP, log_line, Node->num);
            snprintf(log_line, sizeof(log_line), "%s %u " TSEP, log_line, Node->i2s_num);
            snprintf(log_line, sizeof(log_line), "%s %u " TSEP, log_line, Node->dac_num);
            snprintf(log_line, sizeof(log_line), "%s %p " TSEP, log_line, Node->tx_sample);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool DtmfConfigDiag(const DtmfConfig_t * const Config) {
    bool res = false;
    if(Config) {
        char text[80]="";
        snprintf(text,sizeof(text),"I2S%u,DAC%u,%s",
                Config->i2s_num,
                Config->dac_num,
                Config->name );
        LOG_INFO(DTMF,"%s",text);
        res = true;
    }
    return res;
}

bool DtmfNimbleDiag(const DtmfKeyPadFreq_t* const Node){
    bool res = false;
    if(Node){
        char text[80]="";
        snprintf(text,sizeof(text),"Key[%c],Code:0x%x,Low:%u Hz,Hi: %u Hz",
                Node->letter,
                Node->code,
                Node->freq_small_hz,
                Node->freq_big_hz                );
        LOG_INFO(DTMF,"%s",text);
        res = true;
    }
    return res;
}

