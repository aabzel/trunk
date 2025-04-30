#ifndef CLI_DIAG_H
#define CLI_DIAG_H

#include "cli_types.h"


const char* CliCmdToStr(const CliCmdInfo_t* const NodeInfo);
const char* CliConfigToStr(const CliConfig_t* const Config);
bool cli_argument_diag(const int32_t argc, char* argv[]);

#endif /*CLI_DIAG_H*/
