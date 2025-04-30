#ifndef CLI_WRAPPERS_H
#define CLI_WRAPPERS_H

#include <stdbool.h>
#include <stdint.h>

#include <windows.h>

#define READ_PAUSE_S 0.3f
#define WRIRE_PAUSE_S 0.4f
#define FLASH_WR_CHUNK_SIZE 64U /*byte*/

bool cli_wr_fw_crc(uint32_t fw_crc32);
bool cli_wr_fw_len(uint32_t new_fw_len);
bool cli_cmd_send(HANDLE hComm, char* txBuffer, uint32_t tx_buff_len);
bool is_target_connected(void);
bool cli_wrp_flash_write_verify(uint32_t base_addr, uint8_t* chunk_data, uint32_t size);
bool cli_wrp_launch_app(void);
bool cli_wrp_restore_target(void);
bool cli_wrp_parse_fw_version(void);
bool cli_wrp_flash_write(uint32_t base_addr, uint8_t* chunk_data, uint32_t size);
bool cli_wrp_flash_read(uint32_t addr, uint8_t* out_array, uint32_t len);
bool cli_wrp_errase_app(void);
#endif /* CLI_WRAPPERS_H */
