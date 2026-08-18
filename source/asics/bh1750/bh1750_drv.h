#ifndef BH1750_DRV_H
#define BH1750_DRV_H

#include "std_includes.h"
#include "bh1750_config.h"
#include "bh1750_types.h"
#include "bh1750_diag.h"

/*API*/
const Bh1750Config_t* Bh1750GetConfig(uint8_t num);
Bh1750Handle_t* Bh1750GetNode(uint8_t num);
bool bh1750_init_one(uint8_t num);
bool bh1750_mcal_init(void);
bool bh1750_proc(void);
double Bh1750Code2Lx(uint16_t word);

/*setters*/
bool bh1750_reset(uint8_t num);
bool bh1750_send_opcode(uint8_t num, BhOpCode_t op_code);

/*getters*/
bool bh1750_read_code(uint8_t num, uint16_t* const word);
bool bh1750_read_lx(uint8_t num, double* const lighting);
double bh1750_read_lx_short(uint8_t num);


#endif /* BH1750_DRV_H */
