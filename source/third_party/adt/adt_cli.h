#ifndef ADT_CLI_H
#define ADT_CLI_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ADT_CLI
#error "+HAS_ADT_CLI"
#endif

#ifdef HAS_IQUEUE_CLI
#include "iqueue_cli.h"
#else
#define IQUEUE_CLI
#endif

#define ADT_CLI                                \
        IQUEUE_CLI

#ifdef __cplusplus
}
#endif

#endif /* ADT_CLI_H */
