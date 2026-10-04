#ifndef GD5F1GQ5_MCAL_H
#define GD5F1GQ5_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gd5f1gq5_config.h"
#include "gd5f1gq5_types.h"

#ifdef HAS_GD5F1GQ5_DIAG
#include "gd5f1gq5_diag.h"
#endif

/* API */
Gd5f1gq5Handle_t* Gd5f1gq5GetNode(uint8_t num);
const Gd5f1gq5Config_t* Gd5f1gq5GetConfig(uint8_t num);
bool Gd5f1gq5IsValidConfig(const Gd5f1gq5Config_t* const Config);

#ifdef HAS_GD5F1GQ5_CUSTOM
const Gd5f1gq5Info_t* Gd5f1gq5GetInfo(uint8_t num);
#endif

bool gd5f1gq5_mcal_init(void);
bool gd5f1gq5_init_custom(void);
bool gd5f1gq5_init_common(const Gd5f1gq5Config_t* const Config, Gd5f1gq5Handle_t* const Node);
bool gd5f1gq5_init_node(Gd5f1gq5Handle_t* const Node);
bool gd5f1gq5_init_one(uint8_t num);

bool gd5f1gq5_proc_one(const uint8_t num);
bool gd5f1gq5_proc(void);

/*setters*/
bool gd5f1gq5_page_program(const uint8_t num,
                           const uint32_t phy_address,
                           const uint8_t * const data, const uint32_t size);
bool gd5f1gq5_erase_block(const uint8_t num, const uint32_t phy_address);
bool gd5f1gq5_write_ctrl(const uint8_t num, const bool on_off);
bool gd5f1gq5_soft_reset(const uint8_t num);
bool gd5f1gq5_unlock_all_blocks(const uint8_t num);
bool gd5f1gq5_otp_ctrl(const uint8_t num, const bool enable);
bool gd5f1gq5_set_features(const uint8_t num, const uint8_t addr, const uint8_t data) ;


bool gd5f1gq5_program_load(const uint8_t num,
                           const uint32_t address,
                           const uint8_t * const data,
                           const uint32_t size);



/*getters*/
Gd5f1gq5RegInfo_t* Gd5f1gq5RegAddrToInfo(const uint8_t reg_addr) ;
uint32_t gd5f1gq5_phy_address_to_row_address(const uint32_t phy_address);
bool gd5f1gq5_read_page(const uint8_t num,
                        const uint32_t phy_address, uint8_t * const data, const uint32_t size);
bool Gd5f1gq5ParameterPageIsValid(const Gd5f1gq5ParameterPage_t * const ParamPage);
bool gd5f1gq5_read_parameter_page(const uint8_t num, uint8_t * const parameter_page);
bool gd5f1gq5_raw_reg_diag(uint8_t num);
bool gd5f1gq5_get_features(const uint8_t num, const uint8_t addr, uint8_t *const data) ;
bool gd5f1gq5_get_write_enable(const uint8_t num) ;
bool gd5f1gq5_get_otp_enable(const uint8_t num) ;
bool gd5f1gq5_read_uid(const uint8_t num, uint8_t * const uid) ;
bool gd5f1gq5_read_to_cache(const uint8_t num, const uint32_t address) ;
bool gd5f1gq5_read_id(const uint8_t num, Gd5f1gq5ID_t * const pID) ;
bool gd5f1gq5_read_from_cache(const uint8_t num, const uint32_t column_address, uint8_t * const data, const uint32_t size);
uint32_t gd5f1gq5_page_to_block(const uint32_t page_num);

#ifdef __cplusplus
}
#endif

#endif /* GD5F1GQ5_MCAL_H */
