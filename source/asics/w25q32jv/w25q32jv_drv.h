#ifndef W25Q32JV_DRV_H
#define W25Q32JV_DRV_H

#include "std_includes.h"
#include "w25q32jv_config.h"
#include "w25q32jv_types.h"

#ifdef HAS_W25Q32JV_DIAG
#include "w25q32jv_diag.h"
#endif

/*API*/
W25q32jvHandle_t* W25q32jvGetNode(uint8_t num);
const W25q32jvConfig_t* W25q32jvGetConfig(uint8_t num);
bool w25q32jv_proc_one(uint8_t num);
bool w25q32jv_proc(void) ;
bool w25q32jv_init_custom(void) ;
bool w25q32jv_init_one(uint8_t num);
bool w25q32jv_mcal_init(void);
bool  w25q32jv_wait_busy(const uint8_t num, const  uint32_t timeout);

/*Setter*/
bool w25q32jv_write_regs(const uint8_t num,
		const uint8_t sreg1,
		const uint8_t sreg2);
bool w25q32jv_prog_page(const uint8_t num, const uint32_t address, const uint8_t* const data, const uint16_t size);
bool w25q32jv_write_reg2(const uint8_t num, const uint8_t reg_val);
bool w25q32jv_write_enable(const uint8_t num);
bool w25q32jv_chip_erase(const uint8_t num);
bool w25q32jv_erase_sector(const uint8_t num, const uint32_t address);

/*Getter*/
bool w25q32jv_read_data(const uint8_t num, const uint32_t address, uint8_t* const data, const uint16_t size);
bool w25q32jv_read_reg(const uint8_t num,
		               const W25q32jvRegisterIndex_t reg_num,
		               W25q32jvRegUniversal_t* const uReg);

const W25q32jvOpCodes_t w25q32jv_reg_num_to_op_code(const W25q32jvRegisterIndex_t reg_num) ;




#endif /* W25Q32JV_DRV_H */
