#ifndef AT24CXX_DRV_H
#define AT24CXX_DRV_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "at24cxx_types.h"
#include "at24cxx_config.h"
#ifdef HAS_AT24CXX_DIAG
#include "at24cxx_diag.h"
#endif
#include "at24cxx_read_drv.h"
#include "at24cxx_write_drv.h"

const At24cxxConfig_t* At24cxxGetConfig(uint8_t num);
At24cxxHandle_t* At24cxxGetNode(uint8_t num);

const At24cxxInfo_t* At24cxxGetInfo(At24cChipModel_t chip_model);
uint16_t ChipModel2PageSize(At24cChipModel_t chip_model);
bool at24cxx_is_connected(uint8_t num);
bool at24cxx_mcal_init(void);
bool at24cxx_init_one(uint8_t num);
bool at24cxx_proc_one(uint8_t num);
bool at24cxx_proc(void);

#endif /* AT24CXX_DRV_H */
