#include "mailbox_config.h"

#include "data_utils.h"

const MailBoxConfig_t MailBoxConfig[] = {
};

MailBoxHandle_t MailBoxInstance[] = {
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
