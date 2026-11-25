#include "mailbox_config.h"

#include "data_utils.h"


static uint8_t TxData1[200] = {0};
static uint8_t TxData2[200] = {0};
static uint8_t TxData3[200] = {0};

static uint8_t RxData1[200] = {0};
static uint8_t RxData2[200] = {0};
static uint8_t RxData3[200] = {0};

#define MAIL_BOX_CONFIG_ONE(NUM)                 \
  { .num = NUM,                                  \
    .interrupt_on = true,                        \
    .TxData = TxData##NUM,                       \
    .tx_data_size = ARRAY_SIZE(TxData##NUM),     \
    .RxData = RxData##NUM,                       \
    .rx_data_size = ARRAY_SIZE(RxData##NUM),     \
    .channel = NUM+1,                            \
    .name = "MB"#NUM,                            \
    .valid =true,                                \
  },


#define MAIL_BOX_CONFIG_ALL   \
    MAIL_BOX_CONFIG_ONE(1)    \
    MAIL_BOX_CONFIG_ONE(2)    \
    MAIL_BOX_CONFIG_ONE(3)

const MailBoxConfig_t MailBoxConfig[] = {
    MAIL_BOX_CONFIG_ALL
};

MailBoxHandle_t MailBoxInstance[] = {
    { .num = 1, .valid = true, },
    { .num = 2, .valid = true, },
    { .num = 3, .valid = true, },
};

uint32_t mailbox_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MailBoxInstance);
    cnt2 = ARRAY_SIZE(MailBoxConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
