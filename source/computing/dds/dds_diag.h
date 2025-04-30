
#ifndef DDS_DIAG_H
#define DDS_DIAG_H

#include "std_includes.h"
#include "dds_const.h"

#ifndef HAS_DIAG
#error  "+HAS_DIAG"
#endif /*HAS_DIAG*/

#ifndef HAS_DDS
#error  "+HAS_DDS"
#endif /*HAS_DDS*/

#ifndef HAS_DDS_DIAG
#error  "+HAS_DDS_DIAG"
#endif /*HAS_DDS_DIAG*/

#include "dds_type.h"

const char* DdsSampleToStr(const DdsHandle_t* const Node,uint32_t s);
const char* DdsNodeToStr(const DdsHandle_t* const Node);
const char* DdsConfigToStr(const DdsConfig_t* const Config);
const char* FramePatternToStr(FramePattern_t frame_pattern);
const char* SampleSize2Format(uint8_t sample_size);
const char* DdsMode2Str(DdsMode_t mode);
const char* DdsPlayerToStr(DdsPlayer_t player) ;
bool dds_diag(void) ;
bool dds_print_track(uint8_t dac_num) ;
bool DdsConfigDiag(const DdsConfig_t* const Config) ;
bool DdsNodeDiag(const DdsHandle_t* const Node) ;

#endif /*DAC_DIAG_H*/
