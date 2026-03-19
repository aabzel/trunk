#ifndef FCSMU_MCAL_H
#define FCSMU_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "fcsmu_isr.h"
#include "fcsmu_types.h"
#include "fcsmu_config.h"
#include "writer_types.h"

#ifdef HAS_FCSMU_DIAG
#include "fcsmu_diag.h"
#endif

/*API*/
const FcsmuConfig_t* FcsmuGetConfig(uint8_t num);
FcsmuHandle_t* FcsmuGetNode(uint8_t num);
const FcsmuInfo_t* FcsmuGetInfo(uint8_t num);

bool FcsmuIsValidConfig(const FcsmuConfig_t* const Config ) ;
bool fcsmu_init_one(uint8_t num);
bool fcsmu_proc_one(uint8_t num);
bool fcsmu_control(uint8_t num, bool on_off);
bool fcsmu1_proc(void);
bool fcsmu2_proc(void);
bool fcsmu3_proc(void);
bool fcsmu_init_custom(void);
bool fcsmu_mcal_init(void);
bool fcsmu1_mcal_init(void);
bool fcsmu2_mcal_init(void);
bool fcsmu3_mcal_init(void);

/*getters*/

/*setters*/
bool fcsmu_inject_fault(uint8_t num, uint32_t channel) ;

#ifdef __cplusplus
}
#endif

#endif /* FCSMU_MCAL_H  */
