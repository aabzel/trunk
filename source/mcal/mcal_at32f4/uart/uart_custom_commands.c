#include "uart_custom_commands.h"

#include <inttypes.h>

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "ostream.h"
#include "string_reader.h"
#include "table_utils.h"
#include "uart_mcal.h"
#include "uart_types.h"
#include "writer_config.h"

static bool diag_uarts(ostream_t* stream) {
    LOG_NOTICE(SYS, "%s()", __FUNCTION__);

    return true;
}

bool cmd_uarts(int32_t argc, char* argv[]) {
    (void)argv;
    bool res = false;
    if(0 == argc) {
        res = diag_uarts(&(curWriterPtr->stream));
    }
    return res;
}
