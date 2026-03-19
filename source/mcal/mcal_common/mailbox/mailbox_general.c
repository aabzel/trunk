#include "mailbox_mcal.h"

#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "log.h"
#include "std_includes.h"

COMPONENT_GET_NODE(MailBox, mailbox)
COMPONENT_GET_CONFIG(MailBox, mailbox)

COMPONENT_GET_NODE(MailBoxChannel, mailbox_channel)
COMPONENT_GET_CONFIG(MailBoxChannel, mailbox_channel)

__attribute__((weak)) bool mailbox_init_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool mailbox_channel_init_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool mailbox_channel_init_custom(void) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool mailbox_init_custom(void) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool mailbox_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

__attribute__((weak)) bool mailbox_channel_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

bool MailBoxIsValidConfig(const MailBoxConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }

    if(res) {
        if(Config->tx_data_size) {
            res = true;
        } else {
            res = false;
        }
    }

    if(res) {
        if(Config->TxData) {
            res = true;
        } else {
            res = false;
        }
    }

    if(res) {
        if(Config->RxData) {
            res = true;
        } else {
            res = false;
        }
    }

    if(res) {
        if(Config->rx_data_size) {
            res = true;
        } else {
            res = false;
        }
    }

    if(res) {
        res = Config->valid;
    }

    if(res) {
        if(Config->channel < MAILBOX_CHANNEL_CNT) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool mailbox_init_common(const MailBoxConfig_t* const Config, MailBoxHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->auto_release = Config->auto_release;
            Node->interrupt_on = Config->interrupt_on;
            Node->name = Config->name;
            Node->num = Config->num;
            Node->channel = Config->channel;
            Node->RxData = Config->RxData;
            Node->TxData = Config->TxData;
            Node->rx_data_size = Config->rx_data_size;
            Node->tx_data_size = Config->tx_data_size;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool mailbox1_proc(void) {
    bool res = mailbox_proc_one(1);
    return res;
}

bool mailbox2_proc(void) {
    bool res = mailbox_proc_one(2);
    return res;
}

bool mailbox3_proc(void) {
    bool res = mailbox_proc_one(3);
    return res;
}

bool mailbox1_channel_proc(void) {
    bool res = false;
    res = mailbox_channel_proc_one(1);
    return res;
}

bool mailbox2_channel_proc(void) {
    bool res = false;
    res = mailbox_channel_proc_one(2);
    return res;
}

bool mailbox3_channel_proc(void) {
    bool res = false;
    res = mailbox_channel_proc_one(3);
    return res;
}

bool mailbox1_init(void) {
    bool res = mailbox_init_one(1);
    return res;
}

bool mailbox2_init(void) {
    bool res = mailbox_init_one(2);
    return res;
}

bool mailbox3_init(void) {
    bool res = mailbox_init_one(3);
    return res;
}

COMPONENT_INIT_PATTERT(MAILBOX, MAILBOX, mailbox)
// COMPONENT_PROC_PATTERT(MAILBOX, MAILBOX, mailbox)

COMPONENT_INIT_PATTERT(MAILBOX, MAILBOX, mailbox_channel)
// COMPONENT_PROC_PATTERT(MAILBOX, MAILBOX, mailbox_channel)
