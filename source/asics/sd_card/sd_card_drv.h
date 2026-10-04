#ifndef SD_CARD_DRV_H
#define SD_CARD_DRV_H

#include "std_includes.h"
#include "sd_card_config.h"
#include "sd_card_types.h"
#include "spi_mcal.h"

#ifdef HAS_FAT_FS
#include "diskio.h"
#endif

#ifdef HAS_SD_CARD_DIAG
#include "sd_card_diag.h"
#endif

/*API*/
const SdCommandInfo_t* SdCmdGetNode(uint8_t cmd);

bool sd_card_mcal_init(void);
bool sd_disk_initialize(void);
/*setter*/
bool sd_card_send_command(uint8_t cmd, uint32_t arg);
bool sd_card_block_len_set(uint32_t block_len);
bool sd_card_toggle_lock(void);
bool sd_card_power_on(void);
bool sd_card_chip_sel(uint8_t state);
bool sd_send_r2_cmd(uint8_t cmd, uint32_t arg, R2_t* R2);
bool sd_send_r3_cmd(uint8_t cmd, uint32_t arg, R3_t* R3);
bool sd_send_r7_cmd(uint8_t cmd, uint32_t arg, R7_t* R7, uint8_t exp_resp);
bool sd_erase_sector(uint32_t start_block_num, uint32_t end_block_num);
bool sd_control(void);
bool sd_write_sector(uint32_t block_num, const uint8_t* in_buff);
bool send_sd_write(uint8_t const* const buff, uint32_t size);
bool sent_74_ones(void);
bool send_sd_frame(const uint8_t cmd, const uint32_t arg);
DRESULT SD_disk_write(uint8_t pdrv, const uint8_t* buff, uint32_t sector, uint32_t count);
DRESULT sd_disk_ioctl(uint8_t drv, uint8_t ctrl, uint8_t* buff);
uint8_t sd_send_r1_cmd(uint8_t cmd, uint32_t arg);
int16_t get_resp_len(uint8_t cmd);


/*getter*/
bool sd_parse_is_valid_cid(const CID_t* const pCID);
bool sd_card_is_valid_r1(const uint8_t byte);
bool sd_card_csd_get(void);
bool sd_card_read_ssr(const SSR_t* const pSSR);
bool sd_card_read_sr( SR_t* const pSR);
bool sd_card_read_cid(CID_t* const pCID);
bool sd_card_read_csd(CSD_t* pCSD);
bool sd_card_read_ocr(OCR_t* pOCR);
bool sd_read(uint8_t* buff, uint32_t size);
bool sd_fetch_resp(uint8_t* const response);
bool sd_read_registers(void);
bool sd_read_multiple_sector(uint32_t block_num, uint8_t* out_buff, uint32_t sectors);
bool sd_read_sector(uint32_t block_num, uint8_t* const out_buff);
bool sd_card_read_csr(CSR_t *pCSR);
bool is_card_connected(void);
bool receive_response(uint8_t* const array, int32_t len);
DRESULT SD_disk_read(uint8_t pdrv, uint8_t* buff, uint32_t sector, uint32_t count);
uint16_t get_status_reg(void);
uint8_t sd_card_status(void);
uint8_t calc_cmd_num(uint8_t cmd);


#endif /* SD_CARD_DRV_H */
