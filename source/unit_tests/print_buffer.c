
#include "print_buffer.h"

#include <stdbool.h>
#include <string.h>

#include "ostream.h"

char last_cmd_result_str[LAST_CMD_RESULT_SIZE + 1U];
static char test_stream_str[64];
bool print_buf_stream_en = false;

static string_stream_t test_stream = STRING_STREAM(test_stream_str);

ostream_t* print_buf_ostream(void) { return &test_stream.s; }

char* print_buf_get(void) { return test_stream_str; }

void print_buf_reset(void) {
    test_stream.pos = 0;
    test_stream.overflow = false;
    (void)memset(test_stream_str, 0, sizeof(test_stream_str));
}
