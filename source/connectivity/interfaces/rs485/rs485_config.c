#include "rs485_config.h"

#include "rs485_types.h"
#include "data_utils.h"

Rs485Bus_t Rs485Bus={0};

ProtocolNode_t BusNet[] = {
		{.addr=5,  .status.byte=0,}	,
		{.addr=3,  .status.byte=0,}	,
		{.addr=6,  .status.byte=0,}
};

const uint32_t BusNetConfig[] = {5 ,3 ,6};


uint32_t bus_get_cnt(void){
	uint32_t cnt=0;
	uint32_t cnt1=ARRAY_SIZE(BusNetConfig);
	uint32_t cnt2=ARRAY_SIZE(BusNet);
	if(cnt1==cnt2){
		cnt = cnt1;
	}
	return cnt;
}
