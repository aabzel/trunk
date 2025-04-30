
#include "log_utils.h"
#include "oprintf.h"
#include "string_writer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* (*get)(void);
    void (*reset)(void);
} print_buffer_t;

#define UNIT_TEST_STREAM print_buf_ostream()

#define LAST_CMD_RESULT_SIZE 40U
extern char last_cmd_result_str[LAST_CMD_RESULT_SIZE + 1U];
extern bool print_buf_stream_en;

extern ostream_t* print_buf_ostream(void);
extern char* print_buf_get(void);
extern void print_buf_reset(void);
void redirect_stream_to_ut_stream(void);
void redirect_stream_to_stdio(void);

#define INIT_PRINT_BUF(name)                                                                                           \
    print_buffer_t name = {print_buf_get, print_buf_reset};                                                            \
    print_buf_reset()

#ifdef __cplusplus
}
#endif
