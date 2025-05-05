#ifndef END_OF_BLOCK_DIAG_H
#define END_OF_BLOCK_DIAG_H


#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>
#include "end_of_block_types.h"

bool end_of_block_diag(void);
bool EndOfBlockDiag(const EndOfBlockHandle_t* const Node);
const char* EndOfBlockDiag2Str(const EndOfBlockHandle_t* const Node);
const char* BraceInfoToStr(const  BraceInfo_t* const Node);
const char* EndOfBlockNodeReportToStr(const EndOfBlockHandle_t* const Node);
const char* EndOfBlockBugInfoToStr(const EndOfBlockHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* END_OF_BLOCK_DIAG_H */
