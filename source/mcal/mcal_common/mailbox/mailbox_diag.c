#include "mailbox_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "log.h"
#include "mailbox_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

const char* MailBoxConfigToStr(const MailBoxConfig_t* const Config) {
    if(Config) {
        sprintf(text, "N:%u,", Config->num);
        snprintf(text, sizeof(text), "%sName:%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sTxBuff:%p,", text, Config->TxData);
        snprintf(text, sizeof(text), "%sTxSize:%u,", text, Config->tx_data_size);
        snprintf(text, sizeof(text), "%sITon:%u", text, Config->interrupt_on);
    }

    return text;
}

bool MailBoxDiagConfig(const MailBoxConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(MAILBOX, "%s", MailBoxConfigToStr(Config));
    }

    return res;
}

static bool mailbox_diag_int_ll(const MailBoxHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(MAILBOX, "ISR:");
        LOG_INFO(MAILBOX, "isITon:%u", Node->interrupt_on);

        LOG_INFO(MAILBOX, "it_done:%u", Node->it_done);
        LOG_INFO(MAILBOX, "itCnt:%u", Node->it_cnt);

        LOG_INFO(MAILBOX, "rx_done:%u", Node->rx_done);
        LOG_INFO(MAILBOX, "rxCnt:%u", Node->rx_cnt);

        LOG_INFO(MAILBOX, "done_done:%u", Node->done_done);
        LOG_INFO(MAILBOX, "doneCnt:%u", Node->done_cnt);

        LOG_INFO(MAILBOX, "Flags:0x%08x", Node->done_flags);
        res = true;
    }
    return res;
}

bool mailbox_diag_one(uint32_t num) {
    bool res = false;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        LOG_WARNING(MAILBOX, "MailBoxHandle_t:%u", num);
        LOG_INFO(MAILBOX, "N:%u", Node->num);
        LOG_INFO(MAILBOX, "CH:%u", Node->channel);
        LOG_INFO(MAILBOX, "Data:%p", Node->TxData);
        LOG_INFO(MAILBOX, "Size:%u", Node->tx_data_size);
        LOG_INFO(MAILBOX, "wait_cnt:%u", Node->wait_cnt);
        LOG_INFO(MAILBOX, "spin:%u", Node->spin);
        LOG_INFO(MAILBOX, "init:%u", Node->init);

        mailbox_diag_int_ll(Node);
        LOG_INFO(MAILBOX, "Name:%s", Node->name);
        LOG_INFO(MAILBOX, "valid:%u", Node->valid);

        res = mailbox_diag_custon_one(num);
        res = true;
    }
    return res;
}

bool mailbox_diag(void) {
    bool res = false;
    uint8_t num = 0;
    uint32_t cnt = mailbox_get_cnt();
    static const table_col_t cols[] = {
        {5, "No"}, {5, "ch"}, {10, "name"}, {10, "spin"}, {5, "init"}, {5, "req"}, {5, "reqCn"}, {12, "flags"},
    };
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num <= cnt; num++) {
        MailBoxHandle_t* Node = MailBoxGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, Node->channel);
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Node->name);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, Node->spin);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, Node->init);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, Node->rx_done);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, Node->rx_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, Node->done_flags);
            snprintf(temp_str, sizeof(temp_str), "%s" TSEP, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
