#include "mailbox_channel_config.h"

#include "data_utils.h"

const MailBoxChannelConfig_t MailBoxChannelConfig[] = {
		{ .num=1, .channel=1, .valid=true,},
		{ .num=2, .channel=2, .valid=true,},
		{ .num=3, .channel=3, .valid=true,},
		{ .num=4, .channel=4, .valid=true,},
		{ .num=5, .channel=5, .valid=true,},
		{ .num=6, .channel=6, .valid=true,},
		{ .num=7, .channel=7, .valid=true,},
		{ .num=8, .channel=8, .valid=true,},
		{ .num=9, .channel=9, .valid=true,},
		{ .num=11, .channel=10, .valid=true,},
		{ .num=12, .channel=11, .valid=true,},
		{ .num=13, .channel=12, .valid=true,},
		{ .num=14, .channel=13, .valid=true,},
		{ .num=15, .channel=14, .valid=true,},
		{ .num=16, .channel=15, .valid=true,},
		{ .num=17, .channel=16, .valid=true,},
};

MailBoxChannelHandle_t MailBoxChannelInstance[] = {
		{ .num=1,  .valid=true,},
		{ .num=2,  .valid=true,},
		{ .num=3,  .valid=true,},
		{ .num=4,  .valid=true,},
		{ .num=5,  .valid=true,},
		{ .num=6,  .valid=true,},
		{ .num=7,  .valid=true,},
		{ .num=8,  .valid=true,},
		{ .num=9,  .valid=true,},
		{ .num=11,  .valid=true,},
		{ .num=12,  .valid=true,},
		{ .num=13,  .valid=true,},
		{ .num=14,  .valid=true,},
		{ .num=15,  .valid=true,},
		{ .num=16,  .valid=true,},
		{ .num=17,  .valid=true,},
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
