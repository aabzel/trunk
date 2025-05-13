
#ifndef TBFP_CONFIG_H
#define TBFP_CONFIG_H

#include "std_includes.h"
#include "tbfp_types.h"

#ifndef HAS_TBFP
#error " +HAS_TBFP"
#endif

//#define TBFP_MAX_FRAME 512
#define TBFP_MAX_TX_BUFF 512U

#define TBFP_CNT 5

typedef enum{
	TBFP_NUM_UNDEF  =0,
	TBFP_NUM_STDIO  =1,
	TBFP_NUM_LOOPBACK  =2,
	TBFP_NUM_BLACK_HOLE  =3,
	TBFP_NUM_SERIAL_PORT  =4,
}TbfpLegalNums_t;

extern const TbfpConfig_t TbfpConfig[];
extern TbfpHandle_t TbfpInstance[];

uint32_t tbfp_get_cnt(void);

#endif /* TBFP_CONFIG_H */
