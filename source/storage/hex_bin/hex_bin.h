#ifndef HEX_BIN_H
#define HEX_BIN_H

#include "std_includes.h"
#include "hex_bin_types.h"

#ifdef HAS_HEX_BIN_DIAG
#include "hex_bin_diag.h"
#endif

bool is_hex_file(const char* const file_name);
bool bin_to_hex(const char* const file_name);
bool hex_bin_init(void);
bool hex_proc_line(HexBinHandle_t* const Node, bool write);
bool hex_to_bin(const char* const file_name);

#endif /* HEX_BIN_H */
