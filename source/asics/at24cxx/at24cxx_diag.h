#ifndef AT24CXX_DIAG_H
#define AT24CXX_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "at24cxx_types.h"

#ifndef HAS_AT24CXX
#error "+HAS_AT24CXX"
#endif /*HAS_AT24C*/

#ifndef HAS_AT24CXX_DIAG
#error "+HAS_AT24CXX_DIAG"
#endif /*HAS_DIAG_AT24C*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

const char* At24cxxConfig2Str(const At24cxxConfig_t* const Config);
bool at24cxx_diag(void);
bool At24cxxDiagConfig(const At24cxxConfig_t* const Config);
bool At24cxxDiagInfo(const At24cxxInfo_t* const Info);

#endif /* AT24CXX_DIAG_H  */
