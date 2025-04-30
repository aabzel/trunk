#include "relay_drv.h"

#include "data_utils.h"
#include "relay_types.h"

Relay_t Relay[]={
	{.di_index=DI_index_00, .do_index=DO_index_00 , .cur_state =DI_state_UNDEF, .set_state= DO_state_OFF, .status=RELAY_ST_UNDEF, .err_cnt=0, .init=true, .name="Relay1"},
	{.di_index=DI_index_01, .do_index=DO_index_01 , .cur_state =DI_state_UNDEF, .set_state= DO_state_ON,  .status=RELAY_ST_UNDEF, .err_cnt=0, .init=true, .name="Relay2"},
	{.di_index=DI_index_02, .do_index=DO_index_02 , .cur_state =DI_state_UNDEF, .set_state= DO_state_OFF, .status=RELAY_ST_UNDEF, .err_cnt=0, .init=true, .name="Relay3"},
	{.di_index=DI_index_03, .do_index=DO_index_03 , .cur_state =DI_state_UNDEF, .set_state= DO_state_ON,  .status=RELAY_ST_UNDEF, .err_cnt=0, .init=true, .name="Relay4"},
	{.di_index=DI_index_04, .do_index=DO_index_04 , .cur_state =DI_state_UNDEF, .set_state= DO_state_ON,  .status=RELAY_ST_UNDEF, .err_cnt=0, .init=true, .name="Relay5"}
};

uint32_t relay_get_cnt(void){
    uint32_t cnt = 0;
    cnt =  ARRAY_SIZE(Relay);
    return cnt;
}




