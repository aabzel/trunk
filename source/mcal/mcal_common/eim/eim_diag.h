#ifndef EIM_MCAL_DIAG_H
#define EIM_MCAL_DIAG_H

#include "std_includes.h"
#include "eim_types.h"

#ifdef HAS_EIM_CUSTOM
#include "eim_custom_diag.h"
#endif


#ifndef HAS_EIM_DIAG
#error "+ HAS_EIM_DIAG"
#endif /*HAS_EIM_DIAG*/

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif /*HAS_DIAG*/

const char* EimConfigToStr(const EimConfig_t* const Config) ;
bool EimDiagConfig(const EimConfig_t* const Config  );
bool eim_diag(void);
bool eim_diag_one(uint8_t num);

#endif /* EIM_MCAL_DIAG_H */
