#ifndef VECTOR_CLI_H
#define VECTOR_CLI_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HAS_CLI
#define "+HAS_CLI"
#endif

#include "platform.h"

#include "general_types.h"

#include "vector_type.h"


STD_RESULT VECTOR_ReadVfromCli(const S32 argc,
                               char* argv[],
                               const S32 startArg,
                               VECTOR_F* const Node);


#ifdef __cplusplus
}
#endif

#endif /* VECTOR_CLI_H  */


