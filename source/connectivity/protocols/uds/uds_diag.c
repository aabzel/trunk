#include "uds_diag.h"

#include <stdio.h>

#include "array_diag.h"
#include "debug_info.h"
#include "log.h"
#include "storage_diag.h"
#include "str_utils.h"
#include "table_utils.h"
#include "uds.h"
#include "writer_config.h"

bool uds_diag(void) {
    bool res = false;

    return res;
}

const char* UdsNode2Str(const UdsHandle_t* const Node) {
    static char text[80] = {0};
    if(Node) {
    }
    return text;
}

const char* DidConfigToStr(const DidConfig_t* const Config) {
    static char text[80] = {0};
    if(Config) {
        snprintf(text, sizeof(text), "DID:0x%04x,%s,Def:%s,%u Byte,%s,%s", Config->did, Config->name,
                 Config->default_value, Config->size, StorageAccessToStr(Config->access),
                 StorageTypeToStr(Config->type));
    }
    return text;
}

bool uds_did_diag(uint8_t num) {
    bool res = false;
    uint32_t did_cnt = did_get_cnt();
    if(did_cnt) {
        char log_line[150] = {0};
        static const table_col_t cols[] = {
            {5, "Num"},   {8, "DID"}, {4, "accs"},   {8, "Type"},  {4, "Size"},
            {25, "Name"}, {6, "Def"}, {12, "Value"}, {12, "Data"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t i = 0;
        for(i = 0; i <= did_cnt; i++) {
            DidHandle_t* Node = DidGetNode(i);
            const DidConfig_t* Config = DidGetConfig(i);
            if(Config) {
                if(Node) {
                    strcpy(log_line, TSEP);
                    snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
                    snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, Config->did);
                    snprintf(log_line, sizeof(log_line), "%s %2s " TSEP, log_line, StorageAccessToStr(Config->access));
                    snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, StorageTypeToStr(Config->type));
                    snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Config->size);
                    snprintf(log_line, sizeof(log_line), "%s %23s " TSEP, log_line, Config->name);
                    snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, Config->default_value);
                    snprintf(log_line, sizeof(log_line), "%s %10s " TSEP, log_line,
                             DataToValueStr(Node->buff, Config->size, Config->type));
                    snprintf(log_line, sizeof(log_line), "%s [0x%s] " TSEP, log_line,
                             ArrayToStr(Node->buff, Config->size));
                    cli_printf("%s" CRLF, log_line);
                    res = true;
                }
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

const char* UdsDidToStr(UdsDid_t did) {
    const char* name = "?";
    const DidConfig_t* Config = DidGetConfigByDid(did);
    if(Config) {
        name = Config->name;
    }
    return name;
}

const char* UdsRoutineIdentifierToStr(UdsRoutineIdentifier_t routine_id) {
    const char* name = "?";
    const RoutineIdentifierConfig_t* Config = RoutineIdentifierGetConfig(routine_id);
    if(Config) {
        name = Config->name;
    }
    return name;
}
