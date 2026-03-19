#ifndef MAILBOX_MCAL_H
#define MAILBOX_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mailbox_config.h"
#include "mailbox_channel_config.h"
#include "mailbox_isr.h"
#include "multicore_const.h"
#include "mailbox_types.h"
#ifdef HAS_MAILBOX_CUSTOM
#include "mailbox_custom_drv.h"
#endif

#ifdef HAS_MAILBOX_DIAG
#include "mailbox_diag.h"
#endif

/*API*/
const MailBoxConfig_t* MailBoxGetConfig(uint8_t num);
const MailBoxInfo_t* MailBoxGetInfo(uint8_t num);
MailBoxHandle_t* MailBoxGetNode(uint8_t num);

bool mailbox_mcal_init(void);
bool mailbox1_init(void);
bool mailbox2_init(void);
bool mailbox3_init(void);

bool mailbox_init_custom(void);
bool mailbox_init_common(const MailBoxConfig_t* const Config, MailBoxHandle_t* const Node);
bool mailbox_init_one(uint8_t num);

bool mailbox_proc_one(uint8_t num);
bool mailbox1_proc(void);
bool mailbox2_proc(void);
bool mailbox3_proc(void);

bool MailBoxIsValidConfig(const MailBoxConfig_t* const Config);

/*getters*/
bool MB_HWA_IsEnableIntrruptDone(uint8_t core_index, uint8_t channel);
bool MB_HWA_IsEnableIntrruptReq(uint8_t core_index, uint8_t channel);
bool mailbox_read_data(uint8_t num, uint8_t* const data_out, const uint32_t size, uint32_t* const rx_size);

/*setters*/
bool mailbox_send(uint8_t num, const CpuCoreNumber_t target_core_index, const uint8_t* const addr, const uint32_t size);
bool mailbox_send_data(uint8_t num, const CpuCoreNumber_t target_core_index, const MailBoxChannel_t channel,
        const uint8_t* const addr, const uint32_t size);
bool mailbox_release_channel(uint8_t num, uint32_t channel);
bool mailbox_take_channel(uint32_t channel);
bool mailbox_send_request(uint8_t num, uint8_t target_core_index, uint8_t channel, const uint8_t* const addr,
        uint32_t size);

/*Channel API*/
const MailBoxChannelConfig_t* MailBoxChannelGetConfig(uint8_t num);
MailBoxChannelHandle_t* MailBoxChannelGetNode(uint8_t num);

bool mailbox_channel_mcal_init(void);
bool mailbox_channel_init_one(uint8_t num);
bool mailbox_channel_init_custom(void);
bool mailbox1_channel_proc(void);
bool mailbox2_channel_proc(void);
bool mailbox3_channel_proc(void);
bool mailbox_channel_proc_one(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* MAILBOX_MCAL_H  */
