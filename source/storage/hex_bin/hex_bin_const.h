#ifndef NOR_HEX_BIN_CONST_H
#define NOR_HEX_BIN_CONST_H

#include "hex_bin_dep.h"

typedef enum {
	HEX_REC_TYPE_DATA_RECORD =0, /*Data Record*/
	HEX_REC_TYPE_END_OF_FILE_RECORD =1, /*End of File Record*/
	HEX_REC_TYPE_EXTENDED_SEGMENT_ADDRESS_RECORD  =2, /*Extended Segment Address Record*/
	HEX_REC_TYPE_START_SEGMENT_ADDRESS_RECORD=3, /*Start Segment Address Record*/
	HEX_REC_TYPE_EXTENDED_LINEAR_ADDRESS_RECORD =4, /*Extended Linear Address Record*/
	HEX_REC_TYPE_START_LINEAR_ADDRESS_RECORD =5, /*Start Linear Address Record*/

	HEX_REC_TYPE_UNDEF=0xEE, /**/
}HexRecType_t;

#define HEX_LINE_DATA_OFFSET 9U
#define HEX_LINE_OFFSET_REC_TYPE 7U
#define HEX_LINE_OFFSET_ADDR_LITTLE 3U
#define HEX_LINE_OFFSET_REC_LEN 1U
#define HEX_LINE_OFFSET_PREAMBLE 0U

#endif /* NOR_HEX_BIN_CONST_H */
