#ifndef SPIFI_MCAL_H
#define SPIFI_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "spifi_config.h"
#include "spifi_isr.h"
#include "spifi_types.h"

#ifdef HAS_SPIFI_DIAG
#include "spifi_diag.h"
#endif

/*API*/
const SpiFiConfig_t* SpiFiGetConfig(uint8_t num);
SpiFiHandle_t* SpiFiGetNode(uint8_t num);
SpiFiInfo_t* SpiFiGetInfo(uint8_t num);
bool SpiFiIsValidConfig(const SpiFiConfig_t * const Config);

bool spifi_common_init(uint8_t num);
bool spifi_init_one(uint8_t num);
bool spifi_mcal_init(void);
bool spifi_proc_one(uint8_t num);
bool spifi_proc(void);
bool spifi_init_custom(void);
bool spifi_is_address(const uint32_t phy_address);

/*getter*/
bool spifi_read(uint8_t num, uint32_t address, uint8_t* const data, uint32_t size);
bool spifi_read_reg(uint8_t num, uint8_t reg_code,  uint8_t* const read_sreg) ;

/*setter*/
bool spifi_reset(uint8_t num) ;
bool spifi_chip_erase(uint8_t num) ;
bool spifi_write(uint8_t num, uint32_t address, const uint8_t* const data ,
                     uint32_t size);
bool spifi_write_enable(const uint8_t num);
bool spifi_write_ctrl(const uint8_t num, bool on_off);
bool spifi_page_program(const uint8_t num,
                        const uint32_t address,
                        const uint8_t *const wr_data,
                        const uint32_t size);
bool spifi_erase_sector(const uint8_t num,
                        const uint32_t address);
/*wait*/
/*getters*/

/*setters*/

#ifdef __cplusplus
}
#endif

#endif /* SPIFI_MCAL_H  */
