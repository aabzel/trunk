#include "mailbox_channel_config.h"

#include "data_utils.h"

const MailBoxChannelConfig_t MailBoxChannelConfig[] = {
};

MailBoxChannelHandle_t MailBoxChannelInstance[] = {
};

uint32_t mailbox_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(MailBoxChannelInstance);
    cnt2 = ARRAY_SIZE(MailBoxChannelConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
