#ifndef DDS_DIAG_H
#define DDS_DIAG_H

#include <stdbool.h>

#include "dds_constants.h"
#include "general_macros.h"

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

#ifndef DDS_IN_USE
#error "+DDS_IN_USE"
#endif /*DDS_IN_USE*/


#ifndef DDS_IN_USE_DIAG
#error "+DDS_IN_USE_DIAG"
#endif /*DDS_IN_USE_DIAG*/

#include "dds_types.h"

bool        DDS_ConfigurationDiag(const DDS_CONFIG* const Config);
bool        DDS_Diagnostic(void);
bool        DDS_NodeDiag(const DDS_HANDLE* const Node);
bool        DDS_print_track(U8 dac_num);
const char* DDS_ConfigurationToStr(const DDS_CONFIG* const Config);
const char* DDS_FramePatternToStr(DDS_SAMPLE_PATTERN samplePattern);
const char* DDS_ModeToStr(DDS_SIGNAL mode);
const char* DDS_NodeToStr(const DDS_HANDLE* const Node);
const char* DDS_PlayerToStr(DDS_PLAYER player);
const char* DDS_SampleSizeToFormat(U8 sample_size);

#endif /*DAC_DIAG_H*/
