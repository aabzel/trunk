#include "mailbox_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "debugger.h"
#include "log.h"
#include "mailbox_mcal.h"
#include "mcal_types.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

char* MailBoxStatusTypeToStr(const MB_StatusType code) {
    char* name = "?";
    switch(code) {
    case MB_STATUS_SUCCESS:
        name = "Ok";
        break;
    case MB_STATUS_FAILED:
        name = "FAILED";
        break;
    case MB_STATUS_PARAM_ERROR:
        name = "PARAM_ERROR";
        break;
    case MB_STATUS_ALREADY_INITED:
        name = "ALREADY_INITED";
        break;
    case MB_STATUS_UNINIT:
        name = "UNINIT";
        break;
    case MB_STATUS_LOCKED:
        name = "LOCKED";
        break;
    case MB_STATUS_NO_REQUEST:
        name = "NO_REQUEST";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

bool MailBoxStatusTypeDiagPrefix(const MB_StatusType ret, const char* const prefix) {
    bool res = false;
    switch(ret) {
    case MB_STATUS_SUCCESS: {
        LOG_DEBUG(MAILBOX, "%s,Ok", prefix);
        res = true;
    } break;

    case MB_STATUS_NO_REQUEST: {
        LOG_PARN(MAILBOX, "%s,NO_REQUEST", prefix);
        res = true;
    } break;

    default: {
        LOG_ERROR(MAILBOX, "%s:%u=%s", prefix, ret, MailBoxStatusTypeToStr(ret));
    } break;
    }

    return res;
}

bool MailBoxStatusTypeDiag(const MB_StatusType ret) {
    bool res = false;
    switch(ret) {
    case MB_STATUS_SUCCESS: {
        LOG_DEBUG(MAILBOX, "Ok");
        res = true;
    } break;

    case MB_STATUS_NO_REQUEST: {
        LOG_DEBUG(MAILBOX, "NO_REQUEST");
        res = true;
    } break;

    default: {
        LOG_ERROR(MAILBOX, "%u=%s", ret, MailBoxStatusTypeToStr(ret));
    } break;
    }

    return res;
}

//+n*30h
static const Reg32_t MailBoxReg1[] = {
    {
        .valid = true,
        .name = "MB_CCn_SEMA",
        .offset = 0x00,
    },
    {
        .valid = true,
        .name = "MB_CCn_SEMA_UNLK",
        .offset = 0x04,
    },
    {
        .valid = true,
        .name = "MB_CCn_REQUEST",
        .offset = 0x08,
    },
    {
        .valid = true,
        .name = "MB_CCn_DONE",
        .offset = 0x0c,
    },
    {
        .valid = true,
        .name = "MB_CCn_DONE_MASK",
        .offset = 0x10,
    },
    {
        .valid = true,
        .name = "MB_CCn_DATA0",
        .offset = 0x14,
    },
    {
        .valid = true,
        .name = "MB_CCn_DATA1",
        .offset = 0x18,
    },
    {
        .valid = true,
        .name = "MB_CCn_STAT",
        .offset = 0x1C,
    },
    {
        .valid = true,
        .name = "MB_CCn_CLR",
        .offset = 0x20,
    },
};

// +n*0x20
static const Reg32_t MailBoxReg2[] = {
    {
        .valid = true,
        .name = "MB_INTn_FLG",
        .offset = 0x800,
    },
    {
        .valid = true,
        .name = "MB_INTn_FLG_MASK",
        .offset = 0x804,
    },
    {
        .valid = true,
        .name = "MB_INTn_INTEN",
        .offset = 0x808,
    },
    {
        .valid = true,
        .name = "MB_INTn_FLG_STAT",
        .offset = 0x80C,
    },
    {
        .valid = true,
        .name = "MB_INTn_CTRL",
        .offset = 0x810,
    },
};

uint32_t mailbox_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(MailBoxReg1) + ARRAY_SIZE(MailBoxReg2);
    return cnt;
}

bool mailbox_raw_reg_diag(uint8_t num, uint32_t channel) {
    bool res = false;
    if(channel <= 15) {
        const MailBoxInfo_t* Info = MailBoxGetInfo(num);
        if(Info) {
            LOG_INFO(MAILBOX, "MAILBOX%u,Base:0x%p", num, Info->MAILBOXx);
            res = debug_raw_reg_diag(MAILBOX, ((uint32_t)Info->MAILBOXx) + channel * 0x30, MailBoxReg1,
                                     ARRAY_SIZE(MailBoxReg1));
            res = debug_raw_reg_diag(MAILBOX, ((uint32_t)Info->MAILBOXx) + channel * 0x20, MailBoxReg2,
                                     ARRAY_SIZE(MailBoxReg2));
        }
    }

    return res;
}

const char* MailBoxInitTypeToStr(const MB_InitType* const Init) {
    if(Init) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%su32EventMask:0x%08x,", text, Init->u32EventMask);
        snprintf(text, sizeof(text), "%su32IntrMask:0x%08x,", text, Init->u32IntrMask);
        snprintf(text, sizeof(text), "%spRequestCallback:0x%08x,", text, Init->pRequestCallback);
        snprintf(text, sizeof(text), "%spDoneCallback:0x%08x", text, Init->pDoneCallback);
    }
    return text;
}

const char* MailBoxReceiveTypeToStr(const MB_ReceiveType* const Rx) {
    static char lText[200] = {0};
    if(Rx) {
        memset(lText, 0, sizeof(lText));
        strcpy(lText, "");
        uint8_t core_index = Cpm_HWA_GetCoreId();
        snprintf(lText, sizeof(lText), "%sIamCore:%u,", lText, core_index);
        /* The selected Mailbox channel */
        snprintf(lText, sizeof(lText), "%sCH:%u,", lText, Rx->u8Channel);
        /* Buffer to store the master core index */
        snprintf(lText, sizeof(lText), "%sCore:%u,", lText, Rx->u8MasterCoreIndex);
        /* The master security information of the core that currently obtains the channel */
        snprintf(lText, sizeof(lText), "%sSec:%u,", lText, Rx->bSecure);
        /*  The master processing mode of the core that currently obtains the channel. */
        snprintf(lText, sizeof(lText), "%sSup:%u,", lText, Rx->bSupervisor);
        /*  Buffer to store the receiving data */
        uint8_t* array = Rx->aData[0];
        size_t size = Rx->aData[1];
        snprintf(lText, sizeof(lText), "%sAddr:0x%08p,", lText, array);
        /*  Buffer to store the receiving data */
        snprintf(lText, sizeof(lText), "%sLen:%u,", lText, size);
        // snprintf(lText, sizeof(lText), "%sData:%s,", lText, ArrayToStr(array, size));
    }

    return lText;
}

bool MailBoxDiagRequest(const MB_ReceiveType* const Rx) {
    bool res = false;
    if(Rx) {
        LOG_WARNING(MAILBOX, "MB_ReceiveType:");
        /* The selected Mailbox channel */
        LOG_INFO(MAILBOX, "CH:%u,", Rx->u8Channel);
        /* Buffer to store the master core index */
        LOG_INFO(MAILBOX, "Core:%u,", Rx->u8MasterCoreIndex);
        /* The master security information of the core that currently obtains the channel */
        LOG_INFO(MAILBOX, "Secure:%u,", Rx->bSecure);
        /*  The master processing mode of the core that currently obtains the channel. */
        LOG_INFO(MAILBOX, "Supervisor:%u,", Rx->bSupervisor);
        /*  Buffer to store the receiving data */
        uint8_t* array = Rx->aData[0];
        size_t size = Rx->aData[1];
        LOG_INFO(MAILBOX, "Addr:0x%p,", array);
        /*  Buffer to store the receiving data */
        LOG_INFO(MAILBOX, "Len:%u,", size);
        // snprintf(text, sizeof(text), "%sData:%s,", text, ArrayToStr(array, size));
        res = true;
    }

    return res;
}

bool MailBoxDiagHandle(const MB_HandleType* const Handle) {
    bool res = false;
    if(Handle) {
        LOG_INFO(MAILBOX, "MB_MB_CCn_FLG_STAT_MASK:0x%08x", MB_MB_CCn_FLG_STAT_MASK);

        LOG_WARNING(MAILBOX, "MB_HandleType:");

        uint8_t core_index = Handle->tStatus.u8CoreIndex;
        uint32_t flag_stat = MB_HWA_GetFlagStat(core_index, MB_MB_CCn_FLG_STAT_MASK);
        LOG_INFO(MAILBOX, "FlagStat:0x%08x", flag_stat);

        LOG_INFO(MAILBOX, "u8CoreIndex:%u", core_index);
        LOG_INFO(MAILBOX, "u8MasterId:%u", Handle->tStatus.u8MasterId);
        LOG_INFO(MAILBOX, "pRequestCallback:%p", Handle->tStatus.pRequestCallback);
        LOG_INFO(MAILBOX, "pDoneCallback:%p", Handle->tStatus.pDoneCallback);
        res = true;
    }
    return res;
}

bool mailbox_diag_custon_one(const uint8_t num) {
    bool res = false;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        res = true;
        res = MailBoxDiagHandle(&Node->Handle) && res;
        res = MailBoxDiagRequest(&Node->Rx) && res;
    }
    return res;
}

static bool is_valid_mask(uint32_t req_mask) {
    bool res = false;
    if(req_mask) {
        res = true;
    }
    return res;
}

bool mailbox_diag_channel(uint8_t num) {
    bool res = false;
    LOG_INFO(MAILBOX, "MB_INT_CONFIG_COUNT:%u", MB_INT_CONFIG_COUNT);
    LOG_INFO(MAILBOX, "MB_COM_CHANNEL_COUNT:%u", MB_COM_CHANNEL_COUNT);
    static const table_col_t cols[] = {
        {4, "ch"}, {5, "core"}, {7, "EvDone"}, {7, "EvReq"}, {7, "IntDone"}, {7, "IntReq"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t core = 0;
    for(core = 0; core < MB_INT_CONFIG_COUNT; core++) {
        uint8_t channel = 0;
        for(channel = 0; channel < MB_COM_CHANNEL_COUNT; channel++) {

            uint32_t done_mask = MB_EVENT_DONE(channel);
            uint32_t ch_done_mask = MB_HWA_GetFlagMask(core, done_mask);

            uint32_t req_mask = MB_EVENT_REQ(channel);
            uint32_t ch_req = MB_HWA_GetFlagMask(core, req_mask);

            bool req_isr = MB_HWA_IsEnableIntrruptReq(core, channel);
            bool done_isr = MB_HWA_IsEnableIntrruptDone(core, channel);

            // Get the Communication Channel Semaphore Register
            // uint32_t Semaphore = MB_HWA_GetSemaphore( channel,  0xFFFFFFFF);
            char log_line[150] = {0};

            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, channel);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, core);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, is_valid_mask(ch_done_mask));
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, is_valid_mask(ch_req));
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, req_isr);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, done_isr);

            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool mailbox_diag_channel_req(uint8_t num) {
    bool res = false;
    LOG_INFO(MAILBOX, "DiagReq");
    LOG_INFO(MAILBOX, "MB_INT_CONFIG_COUNT:%u", MB_INT_CONFIG_COUNT);
    LOG_INFO(MAILBOX, "MB_COM_CHANNEL_COUNT:%u", MB_COM_CHANNEL_COUNT);
    static const table_col_t cols[] = {
        {4, "ch"}, {5, "core"}, {7, "Event"}, {6, "Flag"}, {6, "Stat"}, {4, "Int"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t core = 0;
    for(core = 0; core < MB_INT_CONFIG_COUNT; core++) {
        uint8_t channel = 0;
        for(channel = 0; channel < MB_COM_CHANNEL_COUNT; channel++) {
            uint32_t done_mask = MB_EVENT_REQ(channel);
            uint32_t ch_mask = MB_HWA_GetFlagMask(core, done_mask);
            uint32_t ch_flag = MB_HWA_GetFlag(core, done_mask);
            uint32_t flag_stat = MB_HWA_GetFlagStat(core, done_mask);
            bool done_isr = MB_HWA_IsEnableIntrruptDone(core, channel);

            char log_line[150] = {0};
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, channel);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, core);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, is_valid_mask(ch_mask));
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, is_valid_mask(ch_flag));
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, is_valid_mask(flag_stat));
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, done_isr);

            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool mailbox_diag_channel_done(uint8_t num) {
    bool res = false;
    LOG_INFO(MAILBOX, "DiagDone");
    LOG_INFO(MAILBOX, "MB_INT_CONFIG_COUNT:%u", MB_INT_CONFIG_COUNT);
    LOG_INFO(MAILBOX, "MB_COM_CHANNEL_COUNT:%u", MB_COM_CHANNEL_COUNT);
    static const table_col_t cols[] = {
        {4, "ch"}, {5, "core"}, {7, "Event"}, {7, "Flag"}, {7, "Stat"}, {7, "Int"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t core = 0;
    for(core = 0; core < MB_INT_CONFIG_COUNT; core++) {
        uint8_t channel = 0;
        for(channel = 0; channel < MB_COM_CHANNEL_COUNT; channel++) {
            uint32_t done_mask = MB_EVENT_DONE(channel);
            uint32_t ch_mask = MB_HWA_GetFlagMask(core, done_mask);
            uint32_t ch_flag = MB_HWA_GetFlag(core, done_mask);
            uint32_t flag_stat = MB_HWA_GetFlagStat(core, done_mask);
            bool done_isr = MB_HWA_IsEnableIntrruptDone(core, channel);

            char log_line[150] = {0};
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, channel);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, core);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, is_valid_mask(ch_mask));
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, is_valid_mask(ch_flag));
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, is_valid_mask(flag_stat));
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, done_isr);

            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool mailbox_diag_low_level(uint8_t num, const char* const keyword) {
    bool res = false;
    LOG_INFO(MAILBOX, "MB_COM_CHANNEL_COUNT:%u", MB_COM_CHANNEL_COUNT);
    static const table_col_t cols[] = {

        {4, "ch"}, {7, "MasID"}, {11, "DoneMasId"}, {20, "DATA"}, {12, "DoneMask"}, {12, "Semaphore"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t channel = 0;
    char log_line[150];
    for(channel = 0; channel < MB_COM_CHANNEL_COUNT; channel++) {
        // Get the master ID of the currently obtained channel
        uint32_t MasterID = MB_HWA_GetMasterID(channel);
        uint32_t Data[2] = {0};
        MB_HWA_GetData(channel, Data);

        // Get the master ID of the core that generates a done event
        uint32_t DoneMasterId = MB_HWA_GetDoneMasterId(channel);

        // Get the mask of the done events
        uint32_t DoneMask = MB_HWA_GetDoneMask(channel);

        // Get the Communication Channel Semaphore Register
        uint32_t Semaphore = MB_HWA_GetSemaphore(channel, 0xFFFFFFFF);

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, channel);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, MasterID);
        snprintf(log_line, sizeof(log_line), "%s %9u " TSEP, log_line, DoneMasterId);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x_%08x " TSEP, log_line, Data[0], Data[1]);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, DoneMask);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, Semaphore);

        cli_printf("%s" CRLF, log_line);
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
