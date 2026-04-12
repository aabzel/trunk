#ifndef CLI_DIAG_H
#define CLI_DIAG_H

#include "cli_types.h"

bool cli_print_ascii(const uint8_t start_byte );
bool cli_cmd_list_print(uint8_t num, const char* sub_name1, const char* sub_name2) ;
const char* CliCmdToStr(const CliCmdInfo_t* const NodeInfo);
const char* CliConfigToStr(const CliConfig_t* const Config);
const char* CliNodeToStr(const CliHandle_t* const Node);
bool cli_argument_diag(const int32_t argc, char* argv[]);

#endif /*CLI_DIAG_H*/
