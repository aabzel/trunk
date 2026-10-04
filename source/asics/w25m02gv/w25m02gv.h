#ifndef W25M02GV_DRV_H
#define W25M02GV_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "w25m02gv_config.h"
#include "w25m02gv_types.h"
#ifdef HAS_W25M02GV_DIAG
#include "w25m02gv_diag.h"
#endif

extern const W25m02gvRegInfo_t W25mRegInfo[];

uint32_t w25m02gv_static_reg_cnt(void);

/*API*/
W25m02gvHandle_t* W25m02gvGetNode(uint8_t num);
const W25m02gvConfig_t* W25m02gvGetConfig(uint8_t num);
const W25m02gvRegInfo_t* W25m02gvRegAddrToInfo(W25m02gvRegAddr_t addr);

bool w25m02gv_check(uint8_t num);
bool w25m02gv_mcal_init(void);
bool w25m02gv_init_one(uint8_t num);
bool w25m02gv_init_custom(void);
bool w25m02gv_is_valid_addr(uint8_t reg_addr);
bool w25m02gv_is_connected(uint8_t num);
bool w25m02gv_proc(void);
bool w25m02gv_proc_one(uint8_t num);

/*getters*/
bool w25m02gv_read(uint8_t num, uint16_t colomn_addr, uint8_t* const data, uint32_t size);

// 8.2.16 Read Data (03h)
bool w25m02gv_fast_read_buffer_mode(uint8_t num, uint16_t colomn_addr, uint8_t* const data, uint32_t size);

//8.2.17 Fast Read (0Bh)
bool w25m02gv_fast_read(uint8_t num, uint16_t colomn_addr, uint8_t* const data, uint32_t size);

bool w25m02gv_reg_read_ll(W25m02gvHandle_t* Node, W25m02gvRegAddr_t addr, uint8_t* const reg_val);
bool w25m02gv_reg_read_all(uint8_t num);
bool w25m02gv_jedec_id_read(uint8_t num, JedecInfo_t* const JedecInfo);
bool w25m02gv_register_read(uint8_t num, W25m02gvRegAddr_t sr_addr, W25m02gvRegUniversal_t* const value);
uint32_t w25m02gv_reg_cnt(void);

/*setters*/
bool w25m02gv_register_write(uint8_t num, W25m02gvRegAddr_t sr_addr, W25m02gvRegUniversal_t value);
bool w25m02gv_reg_write_ll(W25m02gvHandle_t* Node, W25m02gvRegAddr_t addr, uint8_t value);
bool w25m02gv_reg_write(uint8_t num, W25m02gvRegAddr_t reg_addr, uint8_t reg_val);
bool w25m02gv_write_enable(uint8_t num);
bool w25m02gv_write_ctrl(uint8_t num, bool on_off);

// 8.2.11 128KB Block Erase (D8h)
bool w25m02gv_block_erase(uint8_t num, uint16_t page_adddress);

bool w25m02gv_write_disable(uint8_t num);

bool w25m02gv_bad_block_management(uint8_t num,
                                   uint16_t logical_block_address,
                                   uint16_t physical_block_address);

bool w25m02gv_reg_write_verify(uint8_t num, W25m02gvRegAddr_t reg_addr, uint8_t value);
bool w25m02gv_reg_write_lazy(uint8_t num, W25m02gvRegAddr_t reg_addr, uint8_t value);
bool w25m02gv_reg_write_by_bitmask(uint8_t num, W25m02gvRegAddr_t reg_addr, char* bit_mask);
bool w25m02gv_reset(uint8_t num);

#endif /* W25M02GV_DRV_H */
