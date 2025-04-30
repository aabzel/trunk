#ifndef STRING_READER_DRIVER_H
#define STRING_READER_DRIVER_H
/*
 * string reader is a one line text editor
 */

#include <std_includes.h>

#include "string_reader_config.h"
#include "string_reader_types.h"
#ifdef HAS_STRING_READER_DIAG
#include "string_reader_diag.h"
#endif

const StringReaderConfig_t* StringReaderGetConfig(uint8_t num);
StringReaderHandle_t* StringReaderGetNode(uint8_t num);
StringReaderHandle_t* StringReaderInterfaceToNode(Interfaces_t interface_if) ;

bool string_reader_mcal_init(void);
bool string_reader_init_one(uint8_t num);
bool string_reader_reset_one(uint8_t num);
bool string_reader_proc_one(uint8_t num);
bool string_reader_secure_ctrl(uint8_t num, bool on_off);
bool string_reader_listen_proc_one(uint8_t num);
bool string_reader_proc(void);
bool string_reader_rx_byte(Interfaces_t interface_if, uint8_t rx_byte);
bool string_reader_rx_character(StringReaderHandle_t *Node, char character);
bool string_reader_proc_rx_byte(uint8_t num, uint8_t rx_byte);
bool string_reader_listen_proc(void);

#endif /*STRING_READER_DRIVER_H*/
