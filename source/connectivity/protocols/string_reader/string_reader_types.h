#ifndef STRING_READER_TYPES_H
#define STRING_READER_TYPES_H

#include "std_includes.h"

#include "string_reader_const.h"
#include "sys_constants.h"
#include "fifo_char.h"
#ifdef HAS_INTERFACES
#include "interfaces_const.h"
#endif

typedef bool (*handle_string_f)(uint8_t num, char* s);

#define STRING_READER_COMMON_VARIABLES      \
    Interfaces_t interface_if;              \
    handle_string_f callback;               \
    uint8_t num;                            \
    uint8_t cli_num;                        \
    bool secure_echo;                       \
    bool valid;                             \
    uint8_t if_num;                         \
    bool echo;                              \
    char * name;                            \
    char * fifo_heap;                       \
    char * string;      /*command itself*/  \
    int32_t string_size;                    \
    uint32_t fifo_heap_size;                \
    uint8_t feedback_led;

typedef struct {
    STRING_READER_COMMON_VARIABLES
} StringReaderConfig_t;

typedef struct {
    STRING_READER_COMMON_VARIABLES
    bool init_done;
#ifdef HAS_READER_CMD_HISTORY
    char prev_cmd[PREV_CMD_MAX_LEN];
#endif /*HAS_READER_CMD_HISTORY*/
    uint32_t enter_cnt;

#ifdef HAS_FIFO_CHAR
    FifoChar_t fifo; /*bytes stream from if*/
#endif
    int32_t lost_char_count;
    int32_t string_len;
    int64_t error_count;
    int64_t tx_cnt;
    int64_t total_string_count;

    char prev_char ;
    char prev_prev_char ;
   // uint8_t cli_num;

} StringReaderHandle_t;


#endif /*READER_TYPES_H*/
